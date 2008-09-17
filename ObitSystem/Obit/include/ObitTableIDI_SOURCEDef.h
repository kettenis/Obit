/* $Id$   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
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
/*  Define the basic components of the ObitTableIDI_SOURCE  structure          */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableIDI_SOURCEDef.h
 * ObitTableIDI_SOURCE structure members for derived classes.
 */
#include "ObitTableDef.h"  /* Parent class definitions */
/** Table format revision number */
oint  tabrev;
/** Number of Stokes parameters */
oint  no_stkd;
/** First Stokes parameter */
oint  stk_1;
/** Number of frequency bands (IF) */
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
gchar  obscode[MAXKEYCHARTABLEIDI_SOURCE];
/** Array name */
gchar  ArrName[MAXKEYCHARTABLEIDI_SOURCE];
/** Reference date as "YYYY-MM-DD" */
gchar  RefDate[MAXKEYCHARTABLEIDI_SOURCE];
/** Column offset for Source ID in table record */
olong  SourIDOff;
/** Physical column number for Source ID in table record */
olong  SourIDCol;
/** Column offset for Source qualifier in table record */
olong  QualOff;
/** Physical column number for Source qualifier in table record */
olong  QualCol;
/** Column offset for Frequency group (AKA Band) ID in table record */
olong  FreqIDOff;
/** Physical column number for Frequency group (AKA Band) ID in table record */
olong  FreqIDCol;
/** Column offset for Right ascension at mean EPOCH (actually equinox) in table record */
olong  RAMeanOff;
/** Physical column number for Right ascension at mean EPOCH (actually equinox) in table record */
olong  RAMeanCol;
/** Column offset for Declination at mean EPOCH (actually equinox) in table record */
olong  DecMeanOff;
/** Physical column number for Declination at mean EPOCH (actually equinox) in table record */
olong  DecMeanCol;
/** Column offset for Mean Epoch (really equinox) for position in yr. since year 0.0 in table record */
olong  EpochOff;
/** Physical column number for Mean Epoch (really equinox) for position in yr. since year 0.0 in table record */
olong  EpochCol;
/** Column offset for Apparent Right ascension in table record */
olong  RAAppOff;
/** Physical column number for Apparent Right ascension in table record */
olong  RAAppCol;
/** Column offset for Apparent Declination in table record */
olong  DecAppOff;
/** Physical column number for Apparent Declination in table record */
olong  DecAppCol;
/** Column offset for Proper motion (deg/day) in RA in table record */
olong  PMRaOff;
/** Physical column number for Proper motion (deg/day) in RA in table record */
olong  PMRaCol;
/** Column offset for Proper motion (deg/day) in declination in table record */
olong  PMDecOff;
/** Physical column number for Proper motion (deg/day) in declination in table record */
olong  PMDecCol;
/** Column offset for Parallax in table record */
olong  parallaxOff;
/** Physical column number for Parallax in table record */
olong  parallaxCol;
/** Column offset for Source name in table record */
olong  SourceOff;
/** Physical column number for Source name in table record */
olong  SourceCol;
/** Column offset for Calibrator code in table record */
olong  CalCodeOff;
/** Physical column number for Calibrator code in table record */
olong  CalCodeCol;
/** Column offset for Total Stokes I flux density per IF in table record */
olong  IFluxOff;
/** Physical column number for Total Stokes I flux density per IF in table record */
olong  IFluxCol;
/** Column offset for Total Stokes Q flux density per IF in table record */
olong  QFluxOff;
/** Physical column number for Total Stokes Q flux density per IF in table record */
olong  QFluxCol;
/** Column offset for Total Stokes U flux density per IF in table record */
olong  UFluxOff;
/** Physical column number for Total Stokes U flux density per IF in table record */
olong  UFluxCol;
/** Column offset for Total Stokes V flux density per IF in table record */
olong  VFluxOff;
/** Physical column number for Total Stokes V flux density per IF in table record */
olong  VFluxCol;
/** Column offset for Spectral index per IF in table record */
olong  alphaOff;
/** Physical column number for Spectral index per IF in table record */
olong  alphaCol;
/** Column offset for Frequency offset (Hz) from IF nominal per IF in table record */
olong  FreqOffOff;
/** Physical column number for Frequency offset (Hz) from IF nominal per IF in table record */
olong  FreqOffCol;
/** Column offset for Systemic velocity per Band (IF) in table record */
olong  SysVelOff;
/** Physical column number for Systemic velocity per Band (IF) in table record */
olong  SysVelCol;
/** Column offset for Velocity type in table record */
olong  VelTypOff;
/** Physical column number for Velocity type in table record */
olong  VelTypCol;
/** Column offset for Velocity definition 'RADIO' or 'OPTICAL' in table record */
olong  VelDefOff;
/** Physical column number for Velocity definition 'RADIO' or 'OPTICAL' in table record */
olong  VelDefCol;
/** Column offset for Line rest frequency per Band (IF) in table record */
olong  RestFreqOff;
/** Physical column number for Line rest frequency per Band (IF) in table record */
olong  RestFreqCol;
