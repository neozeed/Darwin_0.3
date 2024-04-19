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
/*
 * Copyright 1996 1995 by Open Software Foundation, Inc. 1997 1996 1995 1994 1993 1992 1991  
 *              All Rights Reserved 
 *  
 * Permission to use, copy, modify, and distribute this software and 
 * its documentation for any purpose and without fee is hereby granted, 
 * provided that the above copyright notice appears in all copies and 
 * that both the copyright notice and this permission notice appear in 
 * supporting documentation. 
 *  
 * OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 * FOR A PARTICULAR PURPOSE. 
 *  
 * IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR 
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM 
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT, 
 * NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION 
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. 
 * 
 */
/*
 * MKLINUX-1.0DR2
 */

#include <mach/boolean.h>

#ifndef NULL
#define	NULL	((void *) 0)	/* lion@apple.com 2/12/97 */
#endif

//#include <mach_kgdb.h>
//#include <debug.h>
//#include <mach_debug.h>
//#include <kern/misc_protos.h>
//#include <kern/assert.h>
//
//#include <kgdb/gdb_defs.h>
//#include <kgdb/kgdb_defs.h>	/* For kgdb_printf */

//#include <machdep/ppc/spl.h>
#include <machdep/ppc/proc_reg.h>
//#include <machdep/ppc/misc_protos.h>
//#include <machdep/ppc/trap.h>
//#include <machdep/ppc/exception.h>
#include <powermac.h>
#include <interrupts.h>
#include <chips/heathrow.h>

/* Prototypes */

static int
heathrow_find_entry(int device, struct powermac_interrupt **handler, int nentries);

static unsigned int
heathrow_int_to_number(int index);

static void
heathrow_register_int(int device, spl_t level,
		      void (*handler)(int, void *, void *), void *arg);

static spl_t
heathrow_set_priority_level(spl_t lvl);

static boolean_t
heathrow_enable_irq(int irq);

static boolean_t
heathrow_disable_irq(int irq);

static void
heathrow_interrupt(int type, struct ppc_saved_state *ssp,
		   unsigned int dsisr, unsigned int dar);

void heathrow_via1_interrupt(int device, void *ssp, void *arg);

/* Storage for interrupt table pointers */
struct powermac_interrupt *heathrow_interrupts;
struct powermac_interrupt *heathrow_via1_interrupts;
int nheathrow_via_interrupts;
int nheathrow_interrupts;

/* DBDMA Channel Map */
powermac_dbdma_channels_t heathrow_dbdma_channels =
{ -1,      // Heathrow does not have Curio
  0x00,    // Mesh
  0x01,    // Floppy
  0x02,    // Ethernet Transmit
  0x03,    // Ethernet Receive
  0x04,    // SCC Channel A Transmit
  0x05,    // SCC Channel A Receive
  0x06,    // SCC Channel B Transmit
  0x07,    // SCC Channel B Receive
  0x08,    // Audio Out
  0x09,    // Audio In
  0x0B,    // IDE 0
  0x0C     // IDE 1
};

static void	heathrow_interrupt(int type,
			struct ppc_saved_state *ssp,
			unsigned int dsisr, unsigned int dar);

/* Reset the hardware interrupt control */
void
heathrow_interrupt_initialize(void)
{
	pmac_int_to_number      = heathrow_int_to_number;
	pmac_register_int       = heathrow_register_int;
//	pmac_set_priority_level = heathrow_set_priority_level;
	pmac_enable_irq         = heathrow_enable_irq;
	pmac_disable_irq        = heathrow_disable_irq;
	pmac_interrupt          = heathrow_interrupt;

	*HEATHROW_INTERRUPT_MASK1_REG  = 0;	   /* Disable all interrupts */
	*HEATHROW_INTERRUPT_MASK2_REG  = 0;	   /* Disable all interrupts */
	eieio();
	*HEATHROW_INTERRUPT_CLEAR1_REG = 0xffffffff; /* Clear pending interrupts */
	*HEATHROW_INTERRUPT_CLEAR2_REG = 0xffffffff; /* Clear pending interrupts */
	eieio();
	*HEATHROW_INTERRUPT_MASK1_REG  = 0;	   /* Disable all interrupts */
	*HEATHROW_INTERRUPT_MASK2_REG  = 0;	   /* Disable all interrupts */
	eieio();

	*(v_u_char *)PCI_VIA1_PCR               = 0x00; eieio();
        *(v_u_char *)PCI_VIA1_IER               = 0x00; eieio();
        *(v_u_char *)PCI_VIA1_IFR               = 0x7f; eieio();
}

static int
heathrow_find_entry(int device,
	       struct powermac_interrupt **handler,
	       int nentries)
{
	int	i;

	for (i = 0; i < nentries; i++, (*handler)++)
		if ( (*handler)->i_device == device)
			return i;

	*handler = NULL;
	return 0;
}


unsigned int
heathrow_int_to_number(int index)
{

//kprintf("heathrow_pmac_int_to_number: Int: %d\n", index);

	if (index >= 0 && index < nheathrow_interrupts)
	    return (heathrow_interrupts[index].i_device);
	if (index < (nheathrow_interrupts + nheathrow_via_interrupts))
	    return (heathrow_via1_interrupts[index - nheathrow_interrupts].i_device);
	return (-1);
}

void
heathrow_register_int(int device, spl_t level, void (*handler)(int, void *, void *), 
		 void * arg)
{
	int	i;
	struct powermac_interrupt	*p;

//kprintf("heathrow_register_int: device: %d\n", device);

	/* Check primary interrupts */
	p = heathrow_interrupts;
	i = heathrow_find_entry(device, &p, nheathrow_interrupts);
	if (p) {
		if (p->i_handler) {
			panic("heathrow_register_int: "
			      "Interrupt %d already taken!? ", device);
		} else {
			p->i_handler = handler;
			p->i_level = level;
			p->i_arg = arg;
			if (i < 32) /* Is it in MASK1 or MASK2? */
			  *HEATHROW_INTERRUPT_MASK1_REG |= (1<<i);
			else
			  *HEATHROW_INTERRUPT_MASK2_REG |= (1<<(i - 32));
			eieio();

//kprintf("heathrow_register_int: MASK1: %x  MASK2: %x\n",
//	*HEATHROW_INTERRUPT_MASK1_REG,
//	*HEATHROW_INTERRUPT_MASK2_REG);

			return;
		}
		return;
	}
	/* Check cascaded interrupts */
	p = heathrow_via1_interrupts;
	i = heathrow_find_entry(device, &p, nheathrow_via_interrupts);
	if (p) {
		if (p->i_handler) {
			panic("heathrow_register_int: "
				"Interrupt %d already taken!? ", device);
		} else {
			p->i_handler = handler;
			p->i_level = level;
			p->i_arg = arg;

			*((v_u_char *) PCI_VIA1_IER) |= (1 << i);
			eieio();
			*HEATHROW_INTERRUPT_MASK1_REG |= (1<<10);	/* enable */
			eieio();
			return;
		}
		return;
	}

	panic("heathrow_register_int: Interrupt %d not found", device);
}

static spl_t
heathrow_set_priority_level(spl_t lvl)
{
}

static boolean_t
heathrow_enable_irq(int irq)
{
  /* make sure the irq is in the heathrow table and not via-cuda */
  if ((irq < 0) || (irq >= nheathrow_interrupts) || (irq == 10))
    return FALSE;

//kprintf("heathrow_enable_irq: irq = %d\n", irq);

  /* Unmask the source for this irq on heathrow */
  if (irq < 32) *HEATHROW_INTERRUPT_MASK1_REG |= (1 << irq);
  else *HEATHROW_INTERRUPT_MASK2_REG |= (1 << (irq - 32));
  eieio();

  return TRUE;
}

static boolean_t
heathrow_disable_irq(int irq)
{
  /* make sure the irq is in the heathrow table and not via-cuda */
  if ((irq < 0) || (irq >= nheathrow_interrupts) || (irq == 10))
    return FALSE;

//kprintf("heathrow_disable_irq: irq = %d\n", irq);

  /* Mask the source for this irq on gc */
  if (irq < 32) *HEATHROW_INTERRUPT_MASK1_REG &= ~(1 << irq);
  else *HEATHROW_INTERRUPT_MASK2_REG &= ~(1 << (irq - 32));
  eieio();

  return TRUE;
}

static void
heathrow_interrupt( int type, struct ppc_saved_state *ssp,
	       unsigned int dsisr, unsigned int dar)
{
	unsigned long int		bit, irq1, irq2;
	struct powermac_interrupt	*handler;

	irq1 = *HEATHROW_INTERRUPT_EVENTS1_REG;
	irq2 = *HEATHROW_INTERRUPT_EVENTS2_REG;
	eieio();

	*HEATHROW_INTERRUPT_CLEAR1_REG = irq1;	/* Clear out interrupts */
	*HEATHROW_INTERRUPT_CLEAR2_REG = irq2;
	eieio();

	/* Loop as long as there are bits set in irq1 */
	while (irq1) {
	  /* Find the bit position of the first set bit */
	  bit = 31 - cntlzw(irq1);
	  
	  /* Find the handler */
	  handler = &heathrow_interrupts[bit];
	  
	  if (handler->i_handler) {
	    handler->i_handler(handler->i_device, ssp, handler->i_arg);
	  } else {
	    printf("{HEATHROW INT %d}", bit);
	  }
	  
	  /* Clear the bit in irq1 that we just dispached. */
	  irq1 &= ~(1<<bit);
	}

	/* Loop as long as there are bits set in irq2 */
	while (irq2) {
	  /* Find the bit position of the first set bit */
	  bit = 31 - cntlzw(irq2);
	  
	  /* Find the handler */
	  handler = &heathrow_interrupts[bit + 32];
	  
	  if (handler->i_handler) {
	    handler->i_handler(handler->i_device, ssp, handler->i_arg);
	  } else {
	    printf("{HEATHROW INT %d}", bit + 32);
	  }
	  
	  /* Clear the bit in irq1 that we just dispached. */
	  irq2 &= ~(1<<bit);
	}
}

void heathrow_via1_interrupt(int device, void *ssp, void * arg)
{
	register unsigned long irq, bit;
	struct powermac_interrupt	*handler;

	irq = via_reg(PCI_VIA1_IFR); eieio();   /* get interrupts pending */
	irq &= via_reg(PCI_VIA1_IER); eieio();	/* only care about enabled */

	if (irq == 0)
		return;

	/*
	 * Unflag interrupts we're about to process.
	 */
	via_reg(PCI_VIA1_IFR) = irq;
	eieio();

	/* Loop as long as there are bits set */
	while (irq) {
	  /* Find the bit position of the first set bit */
	  bit = 31 - cntlzw(irq);
	  
	  /* Find the handler */
	  handler = &heathrow_via1_interrupts[bit];
	  
	  if (handler->i_handler) {
	    handler->i_handler(handler->i_device, ssp, handler->i_arg);
	  }
	  
	  /* Clear the bit in irq that we just dispached. */
	  irq &= ~(1<<bit);
	}
}
