/* $Id:  $   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2009                                              */
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
/*  Define the basic components of the ObitTableIDI_FLAG  structure          */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableIDI_FLAGDef.h
 * ObitTableIDI_FLAG structure members for derived classes.
 */
#include "ObitTableDef.h"  /* Parent class definitions */
/** Table format revision number */
oint  tabrev;
/** Number of Stokes parameters */
oint  no_stkd;
/** First Stokes parameter */
oint  stk_1;
/** Number of frequency bands */
oint  no_band;
/** Number of frequency channels */
oint  no_chan;
/** Reference frequency (Hz) */
odouble  ref_freq;
/** Channel bandwidth (Hz) */
odouble  chan_bw;
/** Reference frequency bin */
oint  ref_pixl;
/** Observation project code */
gchar  obscode[MAXKEYCHARTABLEIDI_FLAG];
/** Array name */
gchar  ArrName[MAXKEYCHARTABLEIDI_FLAG];
/** Reference date as "YYYY-MM-DD" */
gchar  RefDate[MAXKEYCHARTABLEIDI_FLAG];
/** Column offset for Source Identifier number in table record */
olong  SourIDOff;
/** Physical column number for Source Identifier number in table record */
olong  SourIDCol;
/** Column offset for Array number. in table record */
olong  ArrayOff;
/** Physical column number for Array number. in table record */
olong  ArrayCol;
/** Column offset for Frequency ID number for row, this is a random parameter in the uv data in table record */
olong  fqidOff;
/** Physical column number for Frequency ID number for row, this is a random parameter in the uv data in table record */
olong  fqidCol;
/** Column offset for Antenna numbers of baseline, 0 means any in table record */
olong  antsOff;
/** Physical column number for Antenna numbers of baseline, 0 means any in table record */
olong  antsCol;
/** Column offset for Beginning and end times in table record */
olong  timerangeOff;
/** Physical column number for Beginning and end times in table record */
olong  timerangeCol;
/** Column offset for Band flag, not 0 means corresponding band flagged in table record */
olong  bandsOff;
/** Physical column number for Band flag, not 0 means corresponding band flagged in table record */
olong  bandsCol;
/** Column offset for Lowest and highest (1-rel) spectral channel numbers in table record */
olong  chansOff;
/** Physical column number for Lowest and highest (1-rel) spectral channel numbers in table record */
olong  chansCol;
/** Column offset for Polarization flags, non 0 means corresponding Stokes is flagged in table record */
olong  pflagsOff;
/** Physical column number for Polarization flags, non 0 means corresponding Stokes is flagged in table record */
olong  pflagsCol;
/** Column offset for Reason for flagging in table record */
olong  reasonOff;
/** Physical column number for Reason for flagging in table record */
olong  reasonCol;
/** Column offset for Severity, -1:no level, 0:known bad, 1:probably bad, 2:may be bad in table record */
olong  severityOff;
/** Physical column number for Severity, -1:no level, 0:known bad, 1:probably bad, 2:may be bad in table record */
olong  severityCol;