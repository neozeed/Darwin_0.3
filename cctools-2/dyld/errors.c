/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.1 (the "License").  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON- INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
#ifndef __OPENSTEP__ /* Rhapsody is not indr'ed yet */
#define NO_INDR_LIBC
#endif
#import <stdio.h>
#import <stdarg.h>
#import <string.h>
#import <libc.h>
#import <mach/mach.h>
#import "stuff/openstep_mach.h"
#define mach_error mach_error_not_used
#import <mach/mach_error.h>
#undef mach_error
#import <mach-o/nlist.h>

#import "images.h"
#import "symbols.h"
#import "errors.h"
#import "debug.h"
#import "lock.h"

/*
 * This used to print the error codes as symbolic values and is set to TRUE in
 * pickup_environment_variables() in dyld_init.c if the environment variable
 * DYLD_ERROR_PRINT is set.
 */
enum bool dyld_error_print = FALSE;

/*
 * These are the pointers to the user's three error handler functions.
 */
void (*user_undefined_handler)(
    const char *symbol_name) = NULL;

module_state * (*user_multiple_handler)(
    struct nlist *symbol,
    module_state *old_module,
    module_state *new_module) = NULL;

void (*user_linkEdit_handler)(
    enum link_edit_error_class error_class,
    int error_number,
    const char *file_name,
    const char *error_string) = NULL;

/*
 * Error strings are assembled in error_string using one of the routines below
 * and passed to the link edit error handler through link_edit_error().
 */
enum error_string_size { ERROR_STRING_SIZE = 1000 };
/*
 * The data is allocated in it's own section so it can go at the end of the
 * data segment.  Since normally errors never happen it is never touched and
 * never dirtied.
 */
extern char error_string[ERROR_STRING_SIZE];
static char *last;
static unsigned long left;

static void print_error_class(
    enum link_edit_error_class error_class);
static void print_error_number(
    enum link_edit_error_class error_class,
    int error_number);

/*
 * check_and_report_undefineds() checks for undefined symbols and if there are
 * any it reports them to the user's error handler if one is set.  If one is not
 * set this writes an error message on stderr and exits.
 */
void
check_and_report_undefineds(
void)
{
    struct symbol_list *undefined;

	if(undefined_list.next == &undefined_list)
	    return;

	/*
	 * Call the user's undefined symbol handler while there are undefined
	 * symbols and the handler is set.
	 */
	while(undefined_list.next != &undefined_list &&
	      user_undefined_handler != NULL){
	    linkedit_error_enter();
	    release_lock();
	    user_undefined_handler((const char *)undefined_list.next->name);
	    set_lock();
	}

	/*
	 * The default is to write(2) an error message to stderr (file
	 * descriptor 2) and exit if the user does not have a handler.
	 */
	error("Undefined symbols:");
	for(undefined = undefined_list.next;
	    undefined != &undefined_list;
	    undefined = undefined->next){
	    add_error_string("%s\n", undefined->name);
	}
	write(2, error_string, ERROR_STRING_SIZE - left);

	/* TODO: figure out what to do for debugging */

	exit(DYLD_EXIT_FAILURE_BASE + DYLD_EXIT_UNDEFINED);
}

/*
 * multiply_defined_error() is called when there is multiply defined symbol.
 * It called the user's error handler if one is set and discards the symbol
 * the user does not want to use.  If no handler is set this write an error
 * message on stderr and exits.
 */
void
multiply_defined_error(
char *symbol_name,
struct image *new_image,
struct nlist *new_symbol,
module_state *new_module,
char *new_library_name,
char *new_module_name,
struct image *prev_image,
struct nlist *prev_symbol,
module_state *prev_module,
char *prev_library_name,
char *prev_module_name)
{
    module_state *user_module;
    unsigned long symbol_value;
    kern_return_t r;

	/* call the user's multiply defined symbol handler */
	if(user_multiple_handler != NULL){
	    multiply_defined_enter();
    	    user_module = user_multiple_handler(prev_symbol, prev_module,
						new_module);
	    multiply_defined_exit();
	    /*
	     * If the user wants the new module mark the prev_symbol as
	     * discarded and set the symbol pointers to the new value.
	     */
	    if(user_module == new_module){
		/* make sure the linkedit segment for prev_image is writable */
		if((r = vm_protect(mach_task_self(),
		    prev_image->linkedit_segment->vmaddr +
		    prev_image->vmaddr_slide,
		    (vm_size_t)prev_image->linkedit_segment->vmsize, FALSE,
		    VM_PROT_WRITE | VM_PROT_READ)) != KERN_SUCCESS){
		    mach_error(r, "can't set vm_protection on segment: %.16s "
			"for: %s", prev_image->linkedit_segment->segname,
			prev_image->name);
		    link_edit_error(DYLD_MACH_RESOURCE, r, prev_image->name);
		}

		/* mark the prev_symbol as discarded in the n_desc */
		prev_symbol->n_desc |= N_DESC_DISCARDED;

		if((r = vm_protect(mach_task_self(),
		    prev_image->linkedit_segment->vmaddr +
		    prev_image->vmaddr_slide,
		    (vm_size_t)prev_image->linkedit_segment->vmsize, FALSE,
		    prev_image->linkedit_segment->initprot)) != KERN_SUCCESS){
		    mach_error(r, "can't set vm_protection on segment: %.16s "
			"for: %s", prev_image->linkedit_segment->segname,
			prev_image->name);
		    link_edit_error(DYLD_MACH_RESOURCE, r, prev_image->name);
		}
		/* update the symbol pointers to use the new symbol's value */
		symbol_value = new_symbol->n_value;
		if((new_symbol->n_type & N_TYPE) != N_ABS)
		    symbol_value += new_image->vmaddr_slide;
		change_symbol_pointers_in_images(symbol_name, symbol_value,
						 FALSE);
	    }
	    return;
	}


	/*
	 * The default is to write(2) an error message to stderr (file
	 * descriptor 2) and exit if the user does not have a handler.
	 */
	error("multiple definitions of symbol %s", symbol_name);
	if(prev_library_name != NULL)
	    add_error_string("%s(%s) definition of %s\n", prev_library_name,
		prev_module_name, symbol_name);
	else
	    add_error_string("%s definition of %s\n", prev_module_name,
		symbol_name);
	if(new_library_name != NULL)
	    add_error_string("%s(%s) definition of %s\n", new_library_name,
		new_module_name, symbol_name);
	else
	    add_error_string("%s definition of %s\n", new_module_name,
		symbol_name);
	write(2, error_string, ERROR_STRING_SIZE - left);

	/* TODO: figure out what to do for debugging */

	exit(DYLD_EXIT_FAILURE_BASE + DYLD_EXIT_MULTIPLY_DEFINED);
}

/*
 * unlinked_lazy_pointer_handler() is the value store into a lazy symbol
 * pointer when the reset_lazy_references option to unlink is used.  For now
 * it generates a link_edit_error().  Later it will walk back the stack and
 * dissassemble the instruction before the return address and figure out the
 * lazy pointer and what symbol was trying to be called.
 */
void
unlinked_lazy_pointer_handler(
void)
{
	error("Call to undefined routine after a NSUnLinkModule with the "
	      "NSUNLINKMODULE_OPTION_RESET_LAZY_REFERENCES option");
	link_edit_error(DYLD_OTHER_ERROR, DYLD_LAZY_BIND, NULL);
	exit(DYLD_EXIT_FAILURE_BASE + DYLD_OTHER_ERROR);
}

/*
 * dead_lock_error() is called from set_lock() if the same thread that has the
 * lock again trys to set the lock.  This can happen if the user's multiply
 * defined error handler or linkedit error handler attempts a dyld operation.
 */
void
dead_lock_error(
void)
{
    extern enum bool dyld_dead_lock_hang;

	error("dead lock (dyld operation attempted in a thread already doing "
	      "a dyld operation)");
	write(2, error_string, ERROR_STRING_SIZE - left);
	if(dyld_dead_lock_hang){
	     for(;;)
		;
	}
	exit(DYLD_EXIT_FAILURE_BASE + DYLD_DEAD_LOCK);
}

/*
 * link_edit_error() is called when there is a link edit error.  It calls the
 * user's link edit error handler if set.  If the handler returns or none is
 * set an error message is written to stderr and exit is called.
 */
void
link_edit_error(
enum link_edit_error_class error_class,
int error_number,
char *file_name)
{
	if(user_linkEdit_handler != NULL){
	    linkedit_error_enter();
	    user_linkEdit_handler(error_class, error_number,
				  (const char *)file_name,
				  (const char *)error_string); 
	}

	/*
	 * If the there is a handler and the error is of class FILE_ACCESS,
	 * FILE_FORMAT or WARNING then return to the dyld operation.
	 */
	if(user_linkEdit_handler != NULL &&
	   (error_class == DYLD_FILE_ACCESS ||
	    error_class == DYLD_FILE_FORMAT ||
	    error_class == DYLD_WARNING)){
	    return;
	}

	/*
	 * The default handling for WARNING is to write(2) the message to stderr
	 * (file descriptor 2) and return to the dyld operation.
	 */
	if(error_class == DYLD_WARNING){
	    write(2, error_string, ERROR_STRING_SIZE - left);
	    reset_error_string();
	    return;
	}

	/*
	 * The default handling for all other errors is to write(2) the message
	 * to stderr (file descriptor 2) and exit.
	 */
	write(2, error_string, ERROR_STRING_SIZE - left);

	if(dyld_error_print){
	    print_error_class(error_class);
	    print_error_number(error_class, error_number);
	}

	/* TODO: figure out what to do for debugging */
	exit(DYLD_EXIT_FAILURE_BASE + error_class);
}

/*
 * abort() is used by malloc() which drags in too much stuff out of libc.
 */
void
abort(
void)
{
	exit(DYLD_EXIT_FAILURE_BASE + DYLD_UNIX_RESOURCE);
}

/*
 * reset_error_string() logicly clears the error string.
 */
void
reset_error_string(
void)
{
	last = error_string;
	left = ERROR_STRING_SIZE;
	error_string[0] = '\0';
}

/*
 * error() takes the vprintf() style aguments and writes them into the start
 * of the error buffer preceded with "dyld: ".  This is used for non-kernel
 * errors.
 */
void
error(
const char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	set_error_string("dyld: ");
	add_error_string("%s ", executables_name);
	vadd_error_string(format, ap);
	add_error_string("\n");
	va_end(ap);
}

/*
 * system_error() takes the vprintf() style aguments and writes them into the
 * start of the error buffer preceded with "dyld: " and appends the errno
 * information.  This is used for UNIX system call errors.
 */
void
system_error(
int errnum,
const char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	set_error_string("dyld: ");
	add_error_string("%s ", executables_name);
	vadd_error_string(format, ap);
	add_error_string(" (%s, errno = %d)\n", strerror(errnum), errnum);
	va_end(ap);
}

/*
 * system_error() takes the vprintf() style aguments and writes them into the
 * start of the error buffer preceded with "dyld: " and appends the mach error
 * information.  This is used for mach call errors.
 */
void
mach_error(
kern_return_t r,
char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	set_error_string("dyld: ");
	add_error_string("%s ", executables_name);
	vadd_error_string(format, ap);
#ifdef NO_INDR_LIBC
	add_error_string(" (kern return = %d)\n", r);
#else
	add_error_string(" (%s, kern return = %d)\n", mach_error_string(r), r);
#endif
	va_end(ap);
}

void
set_error_string(
const char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	vset_error_string(format, ap);
	va_end(ap);
}

void
vset_error_string(
const char *format,
va_list ap)
{
    unsigned long new;

	last = error_string;
	left = ERROR_STRING_SIZE;
	/* for now hope the string does not overflow */
#ifdef __OPENSTEP__
	new = vsprintf(error_string, format, ap);
#else
	new = vsnprintf(last, left, format, ap);
#endif
	last += new;
	left -= new;
}

void
add_error_string(
const char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	vadd_error_string(format, ap);
	va_end(ap);
}

void
vadd_error_string(
const char *format,
va_list ap)
{
    unsigned long new;

	/* for now hope the string does not overflow */
#ifdef __OPENSTEP__
	new = vsprintf(last, format, ap);
#else
	new = vsnprintf(last, left, format, ap);
#endif
	last += new;
	left -= new;
}

static const char * const link_edit_error_class_names[] = {
    "DYLD_FILE_ACCESS",
    "DYLD_FILE_FORMAT",
    "DYLD_MACH_RESOURCE",
    "DYLD_UNIX_RESOURCE",
    "DYLD_OTHER_ERROR",
    "DYLD_WARNING"
};

static
void 
print_error_class(
enum link_edit_error_class error_class)
{
	if(error_class <= DYLD_WARNING)
	    print("error_class = %s\n",
		link_edit_error_class_names[error_class]);
	else
	    print("error_class = %u\n", error_class);
}

#import <errno.h>

static void print_error_number(
enum link_edit_error_class error_class,
int error_number)
{
	if(error_class == DYLD_OTHER_ERROR){
	    if(error_number == DYLD_RELOCATION)
		print("error_number = DYLD_RELOCATION\n");
	    else if(error_number == DYLD_LAZY_BIND)
		print("error_number = DYLD_LAZY_BIND\n");
	    else if(error_number == DYLD_INDR_LOOP)
		print("error_number = DYLD_INDR_LOOP\n");
	    else
		print("error_number = %d\n", error_number);
	}
	else{
	    if(error_number == EBADMACHO)
		print("error_number = EBADMACHO\n");
	    else if(error_number == EBADEXEC)
		print("error_number = EBADEXEC\n");
	    else if(error_number == EBADARCH)
		print("error_number = EBADARCH\n");
	    else if(error_number == ESHLIBVERS)
		print("error_number = ESHLIBVERS\n");
	    else
		print("error_number = %d\n", error_number);
	}
}

/*
 * print() just a wrapper around vfprintf(stderr, )
 */
void
print(
const char *format,
...)
{
    va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
}
