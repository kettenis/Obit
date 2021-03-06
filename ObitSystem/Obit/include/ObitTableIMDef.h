/* $Id$   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2014                                              */
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
/*;         Internet email: bcotton@nrao.edu.                         */
/*;         Postal address: William Cotton                            */
/*;                         National Radio Astronomy Observatory      */
/*;                         520 Edgemont Road                         */
/*;                         Charlottesville, VA 22903-2475 USA        */
/*--------------------------------------------------------------------*/
/*  Define the basic components of the ObitTableIM  structure          */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableIMDef.h
 * ObitTableIM structure members for derived classes.
 */
#include "ObitTableDef.h"  /* Parent class definitions */
/** Reference date as "YYYYMMDD" */
gchar  RefDate[MAXKEYCHARTABLEIM];
/** The number of polarizations. */
oint  numPol;
/** Observation code */
gchar  obscode[MAXKEYCHARTABLEIM];
/** The number of Stokes(?) */
oint  numStkd;
/** The number of Bands(?). */
oint  numBand;
/** The number of spectral channels. */
oint  numChan;
/** Reference Frequency. */
odouble  refFreq;
/** Channel bandwidth. */
ofloat  chanBW;
/** Reference frequency Pixel. */
ofloat  refPixl;
/** [OPTIONAL]Reference frequency Pixel. */
ofloat  stk1;
/** The number of polynomial terms. */
oint  npoly;
/** Revision number of the table definition. */
oint  tabrev;
/** Revision number of the table definition. */
ofloat  revision;
/** Column offset for The center time. in table record */
olong  TimeOff;
/** Physical column number for The center time. in table record */
olong  TimeCol;
/** Column offset for Time interval of record in table record */
olong  TimeIOff;
/** Physical column number for Time interval of record in table record */
olong  TimeICol;
/** Column offset for Source ID number in table record */
olong  SourIDOff;
/** Physical column number for Source ID number in table record */
olong  SourIDCol;
/** Column offset for Antenna number in table record */
olong  antennaNoOff;
/** Physical column number for Antenna number in table record */
olong  antennaNoCol;
/** Column offset for Array number in table record */
olong  ArrayOff;
/** Physical column number for Array number in table record */
olong  ArrayCol;
/** Column offset for Frequency ID in table record */
olong  FreqIDOff;
/** Physical column number for Frequency ID in table record */
olong  FreqIDCol;
/** Column offset for Ionospheric Faraday Rotation in table record */
olong  IFROff;
/** Physical column number for Ionospheric Faraday Rotation in table record */
olong  IFRCol;
/** Column offset for FREQ.VAR (?) in table record */
olong  FreqVarOff;
/** Physical column number for FREQ.VAR (?) in table record */
olong  FreqVarCol;
/** Column offset for Phase delay in table record */
olong  PDelay1Off;
/** Physical column number for Phase delay in table record */
olong  PDelay1Col;
/** Column offset for Group delay in table record */
olong  GDelay1Off;
/** Physical column number for Group delay in table record */
olong  GDelay1Col;
/** Column offset for Phase delay rate in table record */
olong  PRate1Off;
/** Physical column number for Phase delay rate in table record */
olong  PRate1Col;
/** Column offset for Group delay rate in table record */
olong  GRate1Off;
/** Physical column number for Group delay rate in table record */
olong  GRate1Col;
/** Column offset for Dispersion in table record */
olong  Disp1Off;
/** Physical column number for Dispersion in table record */
olong  Disp1Col;
/** Column offset for Dispersion rate in table record */
olong  DRate1Off;
/** Physical column number for Dispersion rate in table record */
olong  DRate1Col;
/** Column offset for Phase delay in table record */
olong  PDelay2Off;
/** Physical column number for Phase delay in table record */
olong  PDelay2Col;
/** Column offset for Group delay in table record */
olong  GDelay2Off;
/** Physical column number for Group delay in table record */
olong  GDelay2Col;
/** Column offset for Phase delay rate in table record */
olong  PRate2Off;
/** Physical column number for Phase delay rate in table record */
olong  PRate2Col;
/** Column offset for Group delay rate in table record */
olong  GRate2Off;
/** Physical column number for Group delay rate in table record */
olong  GRate2Col;
/** Column offset for Dispersion in table record */
olong  Disp2Off;
/** Physical column number for Dispersion in table record */
olong  Disp2Col;
/** Column offset for Dispersion rate in table record */
olong  DRate2Off;
/** Physical column number for Dispersion rate in table record */
olong  DRate2Col;
