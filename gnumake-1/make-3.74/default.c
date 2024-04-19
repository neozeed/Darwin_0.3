/* Data base of default implicit rules for GNU Make.
Copyright (C) 1988, 89, 90, 91, 92, 93, 94, 1995 Free Software Foundation, Inc.
This file is part of GNU Make.

GNU Make is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU Make is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU Make; see the file COPYING.  If not, write to
the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.  */

#include "make.h"
#include "rule.h"
#include "dep.h"
#include "file.h"
#include "commands.h"
#include "variable.h"

/* Define GCC_IS_NATIVE if gcc is the native development environment on
   your system (gcc/bison/flex vs cc/yacc/lex).  */
#if defined (__MSDOS__) || defined (WIN32)
#define GCC_IS_NATIVE
#endif


/* This is the default list of suffixes for suffix rules.
   `.s' must come last, so that a `.o' file will be made from
   a `.c' or `.p' or ... file rather than from a .s file.  */

#if NeXT || NeXT_PDO
/*
 * Add Objective-C (.m)
 */
static char default_suffixes[]
  = ".out .a .ln .o .c .cc .C .p .f .F .m .r .y .l .ym .lm .s .S \
.mod .sym .def .h .info .dvi .tex .texinfo .texi .txinfo \
.w .ch .web .sh .elc .el";
#else /* NeXT || NeXT_PDO */
static char default_suffixes[]
  = ".out .a .ln .o .c .cc .C .p .f .F .r .y .l .s .S \
.mod .sym .def .h .info .dvi .tex .texinfo .texi .txinfo \
.w .ch .web .sh .elc .el";
#endif /* NeXT || NeXT_PDO */

static struct pspec default_pattern_rules[] =
  {
    { "(%)", "%",
	"$(AR) $(ARFLAGS) $@ $<" },

    /* The X.out rules are only in BSD's default set because
       BSD Make has no null-suffix rules, so `foo.out' and
       `foo' are the same thing.  */
    { "%.out", "%",
	"@rm -f $@ \n cp $< $@" },

    /* Syntax is "ctangle foo.w foo.ch foo.c".  */
    { "%.c", "%.w %.ch",
	"$(CTANGLE) $^ $@" },
    { "%.tex", "%.w %.ch",
	"$(CWEAVE) $^ $@" },

    { 0, 0, 0 }
  };

static struct pspec default_terminal_rules[] =
  {
    /* RCS.  */
    { "%", "%,v",
	"+$(CHECKOUT,v)" },
    { "%", "RCS/%,v",
	"+$(CHECKOUT,v)" },

    /* SCCS.  */
    { "%", "s.%",
	"$(GET) $(GFLAGS) $(SCCS_OUTPUT_OPTION) $<" },
    { "%", "SCCS/s.%",
	"$(GET) $(GFLAGS) $(SCCS_OUTPUT_OPTION) $<" },

    { 0, 0, 0 }
  };

static char *default_suffix_rules[] =
  {
    ".o",
    "$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".s",
    "$(LINK.s) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".S",
    "$(LINK.S) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".c",
    "$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".cc",
    "$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".C",
    "$(LINK.C) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".f",
    "$(LINK.f) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#if NeXT || NeXT_PDO
    ".m",
    "$(LINK.m) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#endif /* NeXT || NeXT_PDO */
    ".p",
    "$(LINK.p) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".F",
    "$(LINK.F) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".r",
    "$(LINK.r) $^ $(LOADLIBES) $(LDLIBS) -o $@",
    ".mod",
    "$(COMPILE.mod) -o $@ -e $@ $^",

    ".def.sym", 
    "$(COMPILE.def) -o $@ $<",

    ".sh",
    "cat $< >$@ \n chmod a+x $@",

    ".s.o",
#if !defined(M_XENIX) || defined(__GNUC__)
    "$(COMPILE.s) -o $@ $<",
#else	/* Xenix.  */
    "$(COMPILE.s) -o$@ $<",
#endif	/* Not Xenix.  */
    ".S.o",
#if !defined(M_XENIX) || defined(__GNUC__)
    "$(COMPILE.S) -o $@ $<",
#else	/* Xenix.  */
    "$(COMPILE.S) -o$@ $<",
#endif	/* Not Xenix.  */
    ".c.o",
    "$(COMPILE.c) $< $(OUTPUT_OPTION)",
    ".cc.o",
    "$(COMPILE.cc) $< $(OUTPUT_OPTION)",
    ".C.o",
    "$(COMPILE.C) $< $(OUTPUT_OPTION)",
    ".f.o",
    "$(COMPILE.f) $< $(OUTPUT_OPTION)",
#if NeXT || NeXT_PDO
    ".m.o",
    "$(COMPILE.m) $< $(OUTPUT_OPTION)",
#endif /* NeXT || NeXT_PDO */
#if ! (NeXT || NeXT_PDO)
    ".p.o",
    "$(COMPILE.p) $< $(OUTPUT_OPTION)",
#endif /* NeXT (.p is a precomp) */   
    ".F.o",
    "$(COMPILE.F) $< $(OUTPUT_OPTION)",
    ".r.o",
    "$(COMPILE.r) $< $(OUTPUT_OPTION)",
    ".mod.o",
    "$(COMPILE.mod) -o $@ $<",

    ".c.ln",
    "$(LINT.c) -C$* $<",
    ".y.ln",
#if ! (defined (__MSDOS__) || defined (WIN32))
    "$(YACC.y) $< \n $(LINT.c) -C$* y.tab.c \n $(RM) y.tab.c",
#else
    "$(YACC.y) $< \n $(LINT.c) -C$* y_tab.c \n $(RM) y_tab.c",
#endif
    ".l.ln",
    "@$(RM) $*.c\n $(LEX.l) $< > $*.c\n$(LINT.c) -i $*.c -o $@\n $(RM) $*.c",

    ".y.c",
#if ! (defined (__MSDOS__) || defined (WIN32))
    "$(YACC.y) $< \n mv -f y.tab.c $@",
#else
    "$(YACC.y) $< \n mv -f y_tab.c $@",
#endif
    ".l.c",
    "@$(RM) $@ \n $(LEX.l) $< > $@",

#if NeXT || NeXT_PDO
    ".ym.m",
    "$(YACC.m) $< \n mv -f y.tab.c $@",
    ".lm.m",
    "@$(RM) $@ \n $(LEX.m) $< > $@",
#endif /* NeXT || NeXT_PDO */

    ".F.f",
    "$(PREPROCESS.F) $< $(OUTPUT_OPTION)",
    ".r.f",
    "$(PREPROCESS.r) $< $(OUTPUT_OPTION)",

    /* This might actually make lex.yy.c if there's no %R%
       directive in $*.l, but in that case why were you
       trying to make $*.r anyway?  */
    ".l.r",
    "$(LEX.l) $< > $@ \n mv -f lex.yy.r $@",

    ".S.s",
    "$(PREPROCESS.S) $< > $@",

    ".texinfo.info",
    "$(MAKEINFO) $(MAKEINFO_FLAGS) $< -o $@",

    ".texi.info",
    "$(MAKEINFO) $(MAKEINFO_FLAGS) $< -o $@",

    ".txinfo.info",
    "$(MAKEINFO) $(MAKEINFO_FLAGS) $< -o $@",

    ".tex.dvi",
    "$(TEX) $<",

    ".texinfo.dvi",
    "$(TEXI2DVI) $(TEXI2DVI_FLAGS) $<",

    ".texi.dvi",
    "$(TEXI2DVI) $(TEXI2DVI_FLAGS) $<",

    ".txinfo.dvi",
    "$(TEXI2DVI) $(TEXI2DVI_FLAGS) $<",

    ".w.c",
    "$(CTANGLE) $< - $@",	/* The `-' says there is no `.ch' file.  */

    ".web.p",
    "$(TANGLE) $<",

    ".w.tex",
    "$(CWEAVE) $< - $@",	/* The `-' says there is no `.ch' file.  */

    ".web.tex",
    "$(WEAVE) $<",

    0, 0,
  };

static char *default_variables[] =
  {
#if NeXT || NeXT_PDO
    "GNUMAKE", "YES",
#if NeXT_PDO
    "MAKEFILEPATH", "$(NEXT_ROOT)/Developer/Makefiles",
#else
    "MAKEFILEPATH", "$(NEXT_ROOT)/System/Developer/Makefiles",
#endif
#endif	/* NeXT || NeXT_PDO */
    "AR", "ar",
    "ARFLAGS", "rv",
    "AS", "as",
#if NeXT_PDO
    "CC", "gcc",
    "CXX", "gcc",
#else
    "CC", "cc",
    "CXX", "g++",
#endif

    /* This expands to $(CO) $(COFLAGS) $< $@ if $@ does not exist,
       and to the empty string if $@ does exist.  */
    "CHECKOUT,v",
    "$(patsubst $@-noexist,$(CO) $(COFLAGS) $< $@,\
		$(filter-out $@,$(firstword $(wildcard $@) $@-noexist)))",

    "CO", "co",
    "CPP", "$(CC) -E",
#ifdef	CRAY
    "CF77PPFLAGS", "-P",
    "CF77PP", "/lib/cpp",
    "CFT", "cft77",
    "CF", "cf77",
    "FC", "$(CF)",
#else	/* Not CRAY.  */
#ifdef	_IBMR2
    "FC", "xlf",
#else
#ifdef	__convex__
    "FC", "fc",
#else
    "FC", "f77",
#endif /* __convex__ */
#endif /* _IBMR2 */
    /* System V uses these, so explicit rules using them should work.
       However, there is no way to make implicit rules use them and FC.  */
    "F77", "$(FC)",
    "F77FLAGS", "$(FFLAGS)",
#endif	/* Cray.  */
    "GET", SCCS_GET,
    "LD", "ld",
#ifdef GCC_IS_NATIVE
    "LEX", "flex",
#else
    "LEX", "lex",
#endif
    "LINT", "lint",
    "M2C", "m2c",
#ifdef	pyr
    "PC", "pascal",
#else
#ifdef	CRAY
    "PC", "PASCAL",
    "SEGLDR", "segldr",
#else
    "PC", "pc",
#endif	/* CRAY.  */
#endif	/* pyr.  */
#ifdef GCC_IS_NATIVE
    "YACC", "bison -y",
#else
    "YACC", "yacc",	/* Or "bison -y"  */
#endif
    "MAKEINFO", "makeinfo",
    "TEX", "tex",
    "TEXI2DVI", "texi2dvi",
    "WEAVE", "weave",
    "CWEAVE", "cweave",
    "TANGLE", "tangle",
    "CTANGLE", "ctangle",

    "RM", "rm -f",

    "LINK.o", "$(CC) $(LDFLAGS) $(TARGET_ARCH)",
    "COMPILE.c", "$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
    "LINK.c", "$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
#if NeXT || NeXT_PDO
    "COMPILE.m", "$(COMPILE.c)",
    "LINK.m", "$(LINK.c)",
#endif /* NeXT || NeXT_PDO */
    "COMPILE.cc", "$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
    "COMPILE.C", "$(COMPILE.cc)",
    "LINK.cc", "$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
    "LINK.C", "$(LINK.cc)",
    "YACC.y", "$(YACC) $(YFLAGS)",
    "LEX.l", "$(LEX) $(LFLAGS) -t",
#if NeXT || NeXT_PDO
    "YACC.m", "$(YACC) $(YFLAGS)",
    "LEX.m", "$(LEX) $(LFLAGS) -t",
#endif /* NeXT || NeXT_PDO */
    "COMPILE.f", "$(FC) $(FFLAGS) $(TARGET_ARCH) -c",
    "LINK.f", "$(FC) $(FFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
    "COMPILE.F", "$(FC) $(FFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
    "LINK.F", "$(FC) $(FFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
    "COMPILE.r", "$(FC) $(FFLAGS) $(RFLAGS) $(TARGET_ARCH) -c",
    "LINK.r", "$(FC) $(FFLAGS) $(RFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
    "COMPILE.def", "$(M2C) $(M2FLAGS) $(DEFFLAGS) $(TARGET_ARCH)",
    "COMPILE.mod", "$(M2C) $(M2FLAGS) $(MODFLAGS) $(TARGET_ARCH)",
    "COMPILE.p", "$(PC) $(PFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
    "LINK.p", "$(PC) $(PFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
    "LINK.s", "$(CC) $(ASFLAGS) $(LDFLAGS) $(TARGET_MACH)",
    "COMPILE.s", "$(AS) $(ASFLAGS) $(TARGET_MACH)",
    "LINK.S", "$(CC) $(ASFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_MACH)",
    "COMPILE.S", "$(CC) $(ASFLAGS) $(CPPFLAGS) $(TARGET_MACH) -c",
#if !defined(M_XENIX) || defined(__GNUC__)
    "PREPROCESS.S", "$(CC) -E $(CPPFLAGS)",
#else	/* Xenix.  */
    "PREPROCESS.S", "$(CC) -EP $(CPPFLAGS)",
#endif	/* Not Xenix.  */
    "PREPROCESS.F", "$(FC) $(FFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -F",
    "PREPROCESS.r", "$(FC) $(FFLAGS) $(RFLAGS) $(TARGET_ARCH) -F",
    "LINT.c", "$(LINT) $(LINTFLAGS) $(CPPFLAGS) $(TARGET_ARCH)",

#ifndef	NO_MINUS_C_MINUS_O
#if !defined(M_XENIX) || defined(__GNUC__)
    "OUTPUT_OPTION", "-o $@",
#else	/* Xenix.  */
    "OUTPUT_OPTION", "-Fo$@",
#endif	/* Not Xenix.  */
#endif

#ifdef	SCCS_GET_MINUS_G
    "SCCS_OUTPUT_OPTION", "-G$@",
#endif

    0, 0
  };

/* Set up the default .SUFFIXES list.  */

void
set_default_suffixes ()
{
  suffix_file = enter_file (".SUFFIXES");

  if (no_builtin_rules_flag)
    (void) define_variable ("SUFFIXES", 8, "", o_default, 0);
  else
    {
      char *p = default_suffixes;
      suffix_file->deps = (struct dep *)
	multi_glob (parse_file_seq (&p, '\0', sizeof (struct dep), 1),
		    sizeof (struct dep));
      (void) define_variable ("SUFFIXES", 8, default_suffixes, o_default, 0);
    }
}

/* Enter the default suffix rules as file rules.  This used to be done in
   install_default_implicit_rules, but that loses because we want the
   suffix rules installed before reading makefiles, and thee pattern rules
   installed after.  */

void
install_default_suffix_rules ()
{
  register char **s;
  
  if (no_builtin_rules_flag)
    return;

 for (s = default_suffix_rules; *s != 0; s += 2)
    {
      register struct file *f = enter_file (s[0]);
      /* Don't clobber cmds given in a makefile if there were any.  */
      if (f->cmds == 0)
	{
	  f->cmds = (struct commands *) xmalloc (sizeof (struct commands));
	  f->cmds->filename = 0;
	  f->cmds->commands = s[1];
	  f->cmds->command_lines = 0;
	}
    }
}


/* Install the default pattern rules.  */

void
install_default_implicit_rules ()
{
  register struct pspec *p;
  
  if (no_builtin_rules_flag)
    return;

  for (p = default_pattern_rules; p->target != 0; ++p)
    install_pattern_rule (p, 0);

  for (p = default_terminal_rules; p->target != 0; ++p)
    install_pattern_rule (p, 1);
}

void
define_default_variables ()
{
  register char **s;

  for (s = default_variables; *s != 0; s += 2)
    (void) define_variable (s[0], strlen (s[0]), s[1], o_default, 1);
}
