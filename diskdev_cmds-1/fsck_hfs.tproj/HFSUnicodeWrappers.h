/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * "Portions Copyright (c) 1999 Apple Computer, Inc.  All Rights
 * Reserved.  This file contains Original Code and/or Modifications of
 * Original Code as defined in and that are subject to the Apple Public
 * Source License Version 1.0 (the 'License').  You may not use this file
 * except in compliance with the License.  Please obtain a copy of the
 * License at http://www.apple.com/publicsource and read it before using
 * this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License."
 * 
 * @APPLE_LICENSE_HEADER_END@
 */
/*
	File:		HFSUnicodeWrappers.h

	Contains:	IPI to Unicode routines used by File Manager.

	Version:	HFS Plus 1.0

	Written by:	Mark Day

	Copyright:	� 1996-1997 by Apple Computer, Inc., all rights reserved.

	File Ownership:

		DRI:				xxx put dri here xxx

		Other Contact:		xxx put other contact here xxx

		Technology:			xxx put technology here xxx

	Writers:

		(DSH)	Deric Horn
		(msd)	Mark Day
		(djb)	Don Brady

	Change History (most recent first):

	  <CS11>	11/16/97	djb		Change Unicode.h to UnicodeConverter.h.
	  <CS10>	 11/7/97	msd		Remove prototype for CompareUnicodeNames(). Add prototype for
									FastUnicodeCompare().
	   <CS9>	10/13/97	djb		Add encoding/index macros and add prototypes for new Get/Set
									encodding routines.
	   <CS8>	 9/15/97	djb		InitUnicodeConverter now takes a boolean.
	   <CS7>	 9/10/97	msd		Add prototype for InitializeEncodingContext.
	   <CS6>	 6/26/97	DSH		Include  "MockConverter" prototype for DFA usage.
	   <CS5>	 6/25/97	DSH		Removed Prototype definitions, and checked in Unicode.h and
									TextCommon.h from Julio Gonzales into InternalInterfaces.
	   <CS4>	 6/25/97	msd		Add prototypes for some new Unicode routines that haven't
									appeared in MasterInterfaces yet.
	   <CS3>	 6/18/97	djb		Add more ConversionContexts routines.
	   <CS2>	 6/13/97	djb		Switched to ConvertUnicodeToHFSName, ConvertHFSNameToUnicode, &
									CompareUnicodeNames.
	   <CS1>	 4/28/97	djb		first checked in
	  <HFS1>	12/12/96	msd		first checked in

*/


#if TARGET_OS_MAC
#include <Types.h>
#include <UnicodeConverter.h>
#include <TextCommon.h>
#include <HFSVolumesPriv.h>
#elif TARGET_OS_RHAPSODY
#ifndef __MACOSTYPES__
#include "MacOSTypes.h"
#endif
#endif 	/* TARGET_OS_MAC */


// Encoding vs. Index
//
// For runtime table lookups and for the volume encoding bitmap we
// need to map some encodings to keep them in a reasonable range.
//

enum {
	kIndexMacUkrainian	= 48,		// MacUkrainian encoding is 152
	kIndexMacFarsi		= 49		// MacFarsi encoding is 140
};

#define MapEncodingToIndex(e) \
	( (e) < 48 ? (e) : ( (e) == kTextEncodingMacUkrainian ? kIndexMacUkrainian : ( (e) == kTextEncodingMacFarsi ? kIndexMacFarsi : kTextEncodingMacRoman) ) )

#define MapIndexToEncoding(i) \
	( (i) == kIndexMacFarsi ? kTextEncodingMacFarsi : ( (i) == kIndexMacUkrainian ? kTextEncodingMacUkrainian : (i) ) )

#define ValidMacEncoding(e)	\
	( ((e) < 39)  ||  ((e) == kTextEncodingMacFarsi)  ||  ((e) == kTextEncodingMacUkrainian) )



extern OSErr		InitUnicodeConverter( Boolean forBootVolume );

extern TextEncoding	GetDefaultTextEncoding( void );

extern OSErr		SetDefaultTextEncoding( TextEncoding encoding );

extern ItemCount	CountInstalledEncodings( void );

extern	OSErr		GetTextEncodingForFont( ConstStr255Param fontName, UInt32 * textEncoding );



/*
	Convert a Unicode name (UniStr255) to an HFS name (Str31 or Str27).
	
	If cnid equals kHFSRootFolderID, then the HFS name will be limited to 27 characters
*/

extern OSErr ConvertUnicodeToHFSName( ConstUniStr255Param unicodeName, TextEncoding encoding, CatalogNodeID cnid, Str31 hfsName );



/*
	Convert an HFS name (Str31 or Str27) to a Unicode name (UniStr255).
*/

extern OSErr ConvertHFSNameToUnicode( ConstStr31Param hfsName, TextEncoding encoding, UniStr255 *unicodeName );



/*
	This routine compares two Unicode names based on an ordering defined by the HFS Plus B-tree.
	This ordering must stay fixed for all time.
	
	Output:
		-n		name1 < name2	(i.e. name 1 sorts before name 2)
		 0		name1 = name2
		+n		name1 > name2
	
	NOTE: You should not depend on the magnitude of the result, just its sign.  That is, when name1 < name2, then any
	negative number may be returned.
*/

extern SInt32 FastUnicodeCompare(register ConstUniCharArrayPtr str1, register ItemCount length1,
								 register ConstUniCharArrayPtr str2, register ItemCount length2);


extern OSErr InstallConversionContextsForInstalledScripts( void );


extern OSErr InstallVolumeConversionContexts( UInt64 encodingsBitmap );


extern OSErr InitializeEncodingContext( TextEncoding encoding, FSVarsRec *fsVars );


extern CatalogNodeID GetEmbeddedFileID( ConstStr31Param filename );

extern OSErr MockConvertFromUnicodeToPString( ByteCount unicodeLength, ConstUniCharArrayPtr unicodeStr,
											  Str31 pascalStr );

extern OSErr MockConvertFromPStringToUnicode( ConstStr31Param pascalStr, ByteCount maxUnicodeLen,
											  ByteCount *actualUnicodeLen, UniCharArrayPtr unicodeStr );
