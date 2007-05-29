//
// 	 Enemy Engaged RAH-66 Comanche Versus KA-52 Hokum
// 	 Copyright (C) 2000 Empire Interactive (Europe) Ltd,
// 	 677 High Road, North Finchley, London N12 0DA
//
// 	 Please see the document LICENSE.TXT for the full licence agreement
//
// 2. LICENCE
//  2.1
//  	Subject to the provisions of this Agreement we now grant to you the
//  	following rights in respect of the Source Code:
//   2.1.1
//   	the non-exclusive right to Exploit  the Source Code and Executable
//   	Code on any medium; and
//   2.1.2
//   	the non-exclusive right to create and distribute Derivative Works.
//  2.2
//  	Subject to the provisions of this Agreement we now grant you the
// 	following rights in respect of the Object Code:
//   2.2.1
// 	the non-exclusive right to Exploit the Object Code on the same
// 	terms and conditions set out in clause 3, provided that any
// 	distribution is done so on the terms of this Agreement and is
// 	accompanied by the Source Code and Executable Code (as
// 	applicable).
//
// 3. GENERAL OBLIGATIONS
//  3.1
//  	In consideration of the licence granted in clause 2.1 you now agree:
//   3.1.1
// 	that when you distribute the Source Code or Executable Code or
// 	any Derivative Works to Recipients you will also include the
// 	terms of this Agreement;
//   3.1.2
// 	that when you make the Source Code, Executable Code or any
// 	Derivative Works ("Materials") available to download, you will
// 	ensure that Recipients must accept the terms of this Agreement
// 	before being allowed to download such Materials;
//   3.1.3
// 	that by Exploiting the Source Code or Executable Code you may
// 	not impose any further restrictions on a Recipient's subsequent
// 	Exploitation of the Source Code or Executable Code other than
// 	those contained in the terms and conditions of this Agreement;
//   3.1.4
// 	not (and not to allow any third party) to profit or make any
// 	charge for the Source Code, or Executable Code, any
// 	Exploitation of the Source Code or Executable Code, or for any
// 	Derivative Works;
//   3.1.5
// 	not to place any restrictions on the operability of the Source
// 	Code;
//   3.1.6
// 	to attach prominent notices to any Derivative Works stating
// 	that you have changed the Source Code or Executable Code and to
// 	include the details anddate of such change; and
//   3.1.7
//   	not to Exploit the Source Code or Executable Code otherwise than
// 	as expressly permitted by  this Agreement.
//


#ifndef _VERSION_H_INCLUDED_

#define _VERSION_H_INCLUDED_


#define ENV_NAME	"COMANCHE_HOKUM"

/* please edit "OPTION VERSION=<major>.<data>" in \aphavoc\makefile whenever
 * MAJOR_VERSION or DATA_VERSION changes.
 */

// major version max value: 3
#define MAJOR_VERSION	1

// data version max value: 127
#define DATA_VERSION	8

// minor version max value: 127
#define MINOR_VERSION	5


/* Please ensure you update the version number in BUILD_TYPE _and_ APP_NAME
 * whenever you build a release executable.
 */
// used in:
//Razorworks\eech-new\aphavoc\source\init.c
//Razorworks\eech-new\aphavoc\source\comms\comm_man.c
#define BUILD_TYPE	"MFDEXPORT"

// used in comms/comm_man.c to make sure client and server use same version
#define VERSION_NUMBER_INT 10805

#define APP_NAME	"Enemy Engaged RAH66 Comanche Vs KA52 Hokum v1.8.5MEM3"

/* NOTE: EECHDEV Team have hijacked BUILD_TYPE from it's original Razorworks usage
 *
 * first letter: W => Open Watcom Build, T is a temp version for bug finding
 *               V => Visual C Build
 *               G => gcc build (only theoretical at present)
 *
 * number: integer build number of each test release. Increment this whenever
 *         you make a build intended for distribution (not just official
 *         releases but all interim test, alpha, and debug releases).
 */

#define NAME		APP_NAME

#define TITLE		APP_NAME

#endif /* _VERSION_H_INCLUDED_ */
