/* $Id$  */
/* DO NOT EDIT - file generated by ObitSDTables.pl                    */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2008                                              */
/*;  Associated Universities, Inc. Washington DC, USA.                */
/*;                                                                   */
/*;  This program is free software; you can redistribute it and/or    */
/*;  modify it under the terms of the GNU General Public License as   */
/*;  published by the Free Software Foundation; either version 2 of   */
/*;  the License, or (at your option) any later version.              */
/*;                                                                   */
/*;  This program is distributed in the hope that it will be useful,  */
/*;  but WITHOUT ANY WARRANTY; without even the implied warranty of   */
/*;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    */
/*;  GNU General Public License for more details.                     */
/*;                                                                   */
/*;  You should have received a copy of the GNU General Public        */
/*;  License along with this program; if not, write to the Free       */
/*;  Software Foundation, Inc., 675 Massachusetts Ave, Cambridge,     */
/*;  MA 02139, USA.                                                   */
/*;                                                                   */
/*;Correspondence about this software should be addressed as follows: */
/*;         Internet email: bcotton@nrao.edu.                        */
/*;         Postal address: William Cotton                            */
/*;                         National Radio Astronomy Observatory      */
/*;                         520 Edgemont Road                         */
/*;                         Charlottesville, VA 22903-2475 USA        */
/*--------------------------------------------------------------------*/
/*  Define the basic components of the ObitTableGBTCCBDATA  structure          */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableGBTCCBDATADef.h
 * ObitTableGBTCCBDATA structure members for derived classes.
 */
#include "ObitTableDef.h"  /* Parent class definitions */
/** Column offset for MJD of the integration start. in table record */
olong  dmjdOff;
/** Physical column number for MJD of the integration start. in table record */
olong  dmjdCol;
/** Column offset for  in table record */
olong  usableOff;
/** Physical column number for  in table record */
olong  usableCol;
/** Column offset for Is Cal A ``on''? in table record */
olong  calaOff;
/** Physical column number for Is Cal A ``on''? in table record */
olong  calaCol;
/** Column offset for Is Cal B ``on''? in table record */
olong  calbOff;
/** Physical column number for Is Cal B ``on''? in table record */
olong  calbCol;
/** Column offset for Is each daughter card in an OK state? in table record */
olong  slaveokOff;
/** Physical column number for Is each daughter card in an OK state? in table record */
olong  slaveokCol;
/** Column offset for DATA overflowed? - same order as DATA in table record */
olong  ovrflowOff;
/** Physical column number for DATA overflowed? - same order as DATA in table record */
olong  ovrflowCol;
/** Column offset for unsigned (PORT,CCBSTATE) in table record */
olong  dataOff;
/** Physical column number for unsigned (PORT,CCBSTATE) in table record */
olong  dataCol;