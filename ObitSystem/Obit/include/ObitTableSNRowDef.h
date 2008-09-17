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
/*  Define the basic components of the ObitTableRow structure       */
/*  This is intended to be included in a class structure definition   */
/**
 * \file ObitTableSNRowDef.h
 * ObitTableSNRow structure members for derived classes.
 */
#include "ObitTableRowDef.h"  /* Parent class definitions */
/** The center time of the solution */
odouble  Time;
/** Solution interval. */
ofloat  TimeI;
/** Source Identifier number */
oint  SourID;
/** Antenna number */
oint  antNo;
/** Subarray number. */
oint  SubA;
/** Frequency ID */
oint  FreqID;
/** Ionospheric Faraday Rotation */
ofloat  IFR;
/** Node number */
oint  NodeNo;
/** Multiband delay poln # 1 */
ofloat  MBDelay1;
/** Real (gain Poln # 1 ) */
ofloat*  Real1;
/** Imaginary (gain Poln # 1) */
ofloat*  Imag1;
/** Residual group delay Poln # 1 */
ofloat*  Delay1;
/** Residual fringe rate  Poln # 1 */
ofloat*  Rate1;
/** Weight of soln. Poln # 1 */
ofloat*  Weight1;
/** Reference antenna Poln # 1 */
oint*  RefAnt1;
/** Multiband delay poln # 2 */
ofloat  MBDelay2;
/** Real (gain Poln # 2 ) */
ofloat*  Real2;
/** Imaginary (gain Poln # 2) */
ofloat*  Imag2;
/** Residual group delay Poln # 2 */
ofloat*  Delay2;
/** Residual fringe rate  Poln # 2 */
ofloat*  Rate2;
/** Weight of soln. Poln # 2 */
ofloat*  Weight2;
/** Reference antenna Poln # 2 */
oint*  RefAnt2;
/** status 0=normal, 1=modified, -1=flagged */
olong  status;
