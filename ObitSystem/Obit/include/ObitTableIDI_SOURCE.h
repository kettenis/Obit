/* $Id$   */
/* DO NOT EDIT - file generated by ObitTables.pl                      */
/*--------------------------------------------------------------------*/
/*;  Copyright (C)  2013                                              */
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
#ifndef OBITTABLEIDI_SOURCE_H 
#define OBITTABLEIDI_SOURCE_H 

#include "Obit.h"
#include "ObitErr.h"
#include "ObitTable.h"
#include "ObitData.h"

/*-------- Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitTableIDI_SOURCE.h
 * ObitTableIDI_SOURCE class definition.
 *
 * This class is derived from the #ObitTable class.
 *
 * This class contains tabular data and allows access.
 * This table is part of the IDI uv data format.
 * "IDI\_SOURCE" contains information about astronomical sources.
 * An ObitTableIDI\_SOURCE is the front end to a persistent disk resident structure.
 * Only FITS cataloged data are supported.
 * This class is derived from the ObitTable class. 
 *
 * This class contains tabular data and allows access.
 * "IDI_SOURCE" table
 * An ObitTableIDI_SOURCE is the front end to a persistent disk resident structure.
 * Only FITS (as Tables) are supported.
 *
 * \section TableDataStorage Table data storage
 * In memory tables are stored in a fashion similar to how they are 
 * stored on disk - in large blocks in memory rather than structures.
 * Due to the word alignment requirements of some machines, they are 
 * stored by order of the decreasing element size: 
 * double, float long, int, short, char rather than the logical order.
 * The details of the storage in the buffer are kept in the 
 * #ObitTableIDI_SOURCEDesc.
 *
 * In addition to the normal tabular data, a table will have a "_status"
 * column to indicate the status of each row.
 *
 * \section ObitTableIDI_SOURCESpecification Specifying desired data transfer parameters
 * The desired data transfers are specified in the member ObitInfoList.
 * In the following an ObitInfoList entry is defined by 
 * the name in double quotes, the data type code as an #ObitInfoType enum 
 * and the dimensions of the array (? => depends on application).
 *
 * The following apply to both types of files:
 * \li "nRowPIO", OBIT_int, Max. Number of visibilities per 
 *     "Read" or "Write" operation.  Default = 1.
 *
 * \subsection TableFITS FITS files
 * This implementation uses cfitsio which allows using, in addition to 
 * regular FITS images, gzip compressed files, pipes, shared memory 
 * and a number of other input forms.
 * The convenience Macro #ObitTableIDI_SOURCESetFITS simplifies specifying the 
 * desired data.
 * Binary tables are used for storing visibility data in FITS.
 * For accessing FITS files the following entries in the ObitInfoList 
 * are used:
 * \li "FileName" OBIT_string (?,1,1) FITS file name.
 * \li "TabName"  OBIT_string (?,1,1) Table name (e.g. "AIPS CC").
 * \li "Ver"      OBIT_int    (1,1,1) Table version number
 *
 *
 * \section ObitTableIDI_SOURCEaccess Creators and Destructors
 * An ObitTableIDI_SOURCE can be created using newObitTableIDI_SOURCEValue which attaches the 
 * table to an ObitData for the object.  
 * If the output ObitTableIDI_SOURCE has previously been specified, including file information,
 * then ObitTableIDI_SOURCECopy will copy the disk resident as well as the memory 
 * resident information.
 *
 * A copy of a pointer to an ObitTableIDI_SOURCE should always be made using the
 * ObitTableIDI_SOURCERef function which updates the reference count in the object.
 * Then whenever freeing an ObitTableIDI_SOURCE or changing a pointer, the function
 * ObitTableIDI_SOURCEUnref will decrement the reference count and destroy the object
 * when the reference count hits 0.
 *
 * \section ObitTableIDI_SOURCEUsage I/O
 * Visibility data is available after an input object is "Opened"
 * and "Read".
 * I/O optionally uses a buffer attached to the ObitTableIDI_SOURCE or some external
 * location.
 * To Write an ObitTableIDI_SOURCE, create it, open it, and write.
 * The object should be closed to ensure all data is flushed to disk.
 * Deletion of an ObitTableIDI_SOURCE after its final unreferencing will automatically
 * close it.
 */

/*--------------Class definitions-------------------------------------*/

/** Number of characters for Table keyword */
 #define MAXKEYCHARTABLEIDI_SOURCE 24

/** ObitTableIDI_SOURCE Class structure. */
typedef struct {
#include "ObitTableIDI_SOURCEDef.h"   /* this class definition */
} ObitTableIDI_SOURCE;

/** ObitTableIDI_SOURCERow Class structure. */
typedef struct {
#include "ObitTableIDI_SOURCERowDef.h"   /* this class row definition */
} ObitTableIDI_SOURCERow;

/*----------------- Macroes ---------------------------*/
/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_SOURCE
 * returns an ObitTableIDI_SOURCE*.
 * in = object to unreference
 */
#define ObitTableIDI_SOURCEUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_SOURCE.
 * returns an ObitTableIDI_SOURCE*.
 * in = object to reference
 */
#define ObitTableIDI_SOURCERef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_SOURCEIsA(in) ObitIsA (in, ObitTableIDI_SOURCEGetClass())

/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_SOURCERow
 * returns an ObitTableIDI_SOURCERow*.
 * in = object to unreference
 */
#define ObitTableIDI_SOURCERowUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_SOURCERow.
 * returns an ObitTableIDI_SOURCERow*.
 * in = object to reference
 */
#define ObitTableIDI_SOURCERowRef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_SOURCERowIsA(in) ObitIsA (in, ObitTableIDI_SOURCERowGetClass())

/*---------------Public functions---------------------------*/
/*----------------Table Row Functions ----------------------*/
/** Public: Row Class initializer. */
void ObitTableIDI_SOURCERowClassInit (void);

/** Public: Constructor. */
ObitTableIDI_SOURCERow* newObitTableIDI_SOURCERow (ObitTableIDI_SOURCE *table);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_SOURCERowGetClass (void);

/*------------------Table Functions ------------------------*/
/** Public: Class initializer. */
void ObitTableIDI_SOURCEClassInit (void);

/** Public: Constructor. */
ObitTableIDI_SOURCE* newObitTableIDI_SOURCE (gchar* name);

/** Public: Constructor from values. */
ObitTableIDI_SOURCE* 
newObitTableIDI_SOURCEValue (gchar* name, ObitData *file, olong *ver,
  		     ObitIOAccess access,
                     oint no_band,
		     ObitErr *err);

/** Public: Class initializer. */
void ObitTableIDI_SOURCEClassInit (void);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_SOURCEGetClass (void);

/** Public: Copy (deep) constructor. */
ObitTableIDI_SOURCE* ObitTableIDI_SOURCECopy  (ObitTableIDI_SOURCE *in, ObitTableIDI_SOURCE *out, 
			   ObitErr *err);

/** Public: Copy (shallow) constructor. */
ObitTableIDI_SOURCE* ObitTableIDI_SOURCEClone (ObitTableIDI_SOURCE *in, ObitTableIDI_SOURCE *out);

/** Public: Convert an ObitTable to an ObitTableIDI_SOURCE */
ObitTableIDI_SOURCE* ObitTableIDI_SOURCEConvert  (ObitTable *in);

/** Public: Create ObitIO structures and open file */
ObitIOCode ObitTableIDI_SOURCEOpen (ObitTableIDI_SOURCE *in, ObitIOAccess access, 
			  ObitErr *err);

/** Public: Read a table row */
ObitIOCode 
ObitTableIDI_SOURCEReadRow  (ObitTableIDI_SOURCE *in, olong iIDI_SOURCERow, ObitTableIDI_SOURCERow *row,
		     ObitErr *err);

/** Public: Init a table row for write */
void 
ObitTableIDI_SOURCESetRow  (ObitTableIDI_SOURCE *in, ObitTableIDI_SOURCERow *row,
		     ObitErr *err);

/** Public: Write a table row */
ObitIOCode 
ObitTableIDI_SOURCEWriteRow  (ObitTableIDI_SOURCE *in, olong iIDI_SOURCERow, ObitTableIDI_SOURCERow *row,
		     ObitErr *err);

/** Public: Close file and become inactive */
ObitIOCode ObitTableIDI_SOURCEClose (ObitTableIDI_SOURCE *in, ObitErr *err);

/*----------- ClassInfo Structure -----------------------------------*/
/**
 * ClassInfo Structure.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_SOURCEClassDef.h"
} ObitTableIDI_SOURCEClassInfo; 

/**
 * ClassInfo Structure For TableIDI_SOURCERow.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_SOURCERowClassDef.h"
} ObitTableIDI_SOURCERowClassInfo; 
#endif /* OBITTABLEIDI_SOURCE_H */ 
