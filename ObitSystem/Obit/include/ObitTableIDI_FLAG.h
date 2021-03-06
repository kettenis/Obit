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
#ifndef OBITTABLEIDI_FLAG_H 
#define OBITTABLEIDI_FLAG_H 

#include "Obit.h"
#include "ObitErr.h"
#include "ObitTable.h"
#include "ObitData.h"

/*-------- Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitTableIDI_FLAG.h
 * ObitTableIDI_FLAG class definition.
 *
 * This class is derived from the #ObitTable class.
 *
 * This class contains tabular data and allows access.
 * This table is part of the IDI uv data format.
 * "IDI\_FLAG" contains descriptions of data to be ignored in uv data.
 * An ObitTableIDI\_FLAG is the front end to a persistent disk resident structure.
 * Only FITS cataloged data are supported.
 * This class is derived from the ObitTable class.
 *
 * This class contains tabular data and allows access.
 * "IDI_FLAG" table
 * An ObitTableIDI_FLAG is the front end to a persistent disk resident structure.
 * Only FITS (as Tables) are supported.
 *
 * \section TableDataStorage Table data storage
 * In memory tables are stored in a fashion similar to how they are 
 * stored on disk - in large blocks in memory rather than structures.
 * Due to the word alignment requirements of some machines, they are 
 * stored by order of the decreasing element size: 
 * double, float long, int, short, char rather than the logical order.
 * The details of the storage in the buffer are kept in the 
 * #ObitTableIDI_FLAGDesc.
 *
 * In addition to the normal tabular data, a table will have a "_status"
 * column to indicate the status of each row.
 *
 * \section ObitTableIDI_FLAGSpecification Specifying desired data transfer parameters
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
 * The convenience Macro #ObitTableIDI_FLAGSetFITS simplifies specifying the 
 * desired data.
 * Binary tables are used for storing visibility data in FITS.
 * For accessing FITS files the following entries in the ObitInfoList 
 * are used:
 * \li "FileName" OBIT_string (?,1,1) FITS file name.
 * \li "TabName"  OBIT_string (?,1,1) Table name (e.g. "AIPS CC").
 * \li "Ver"      OBIT_int    (1,1,1) Table version number
 *
 *
 * \section ObitTableIDI_FLAGaccess Creators and Destructors
 * An ObitTableIDI_FLAG can be created using newObitTableIDI_FLAGValue which attaches the 
 * table to an ObitData for the object.  
 * If the output ObitTableIDI_FLAG has previously been specified, including file information,
 * then ObitTableIDI_FLAGCopy will copy the disk resident as well as the memory 
 * resident information.
 *
 * A copy of a pointer to an ObitTableIDI_FLAG should always be made using the
 * ObitTableIDI_FLAGRef function which updates the reference count in the object.
 * Then whenever freeing an ObitTableIDI_FLAG or changing a pointer, the function
 * ObitTableIDI_FLAGUnref will decrement the reference count and destroy the object
 * when the reference count hits 0.
 *
 * \section ObitTableIDI_FLAGUsage I/O
 * Visibility data is available after an input object is "Opened"
 * and "Read".
 * I/O optionally uses a buffer attached to the ObitTableIDI_FLAG or some external
 * location.
 * To Write an ObitTableIDI_FLAG, create it, open it, and write.
 * The object should be closed to ensure all data is flushed to disk.
 * Deletion of an ObitTableIDI_FLAG after its final unreferencing will automatically
 * close it.
 */

/*--------------Class definitions-------------------------------------*/

/** Number of characters for Table keyword */
 #define MAXKEYCHARTABLEIDI_FLAG 24

/** ObitTableIDI_FLAG Class structure. */
typedef struct {
#include "ObitTableIDI_FLAGDef.h"   /* this class definition */
} ObitTableIDI_FLAG;

/** ObitTableIDI_FLAGRow Class structure. */
typedef struct {
#include "ObitTableIDI_FLAGRowDef.h"   /* this class row definition */
} ObitTableIDI_FLAGRow;

/*----------------- Macroes ---------------------------*/
/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_FLAG
 * returns an ObitTableIDI_FLAG*.
 * in = object to unreference
 */
#define ObitTableIDI_FLAGUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_FLAG.
 * returns an ObitTableIDI_FLAG*.
 * in = object to reference
 */
#define ObitTableIDI_FLAGRef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_FLAGIsA(in) ObitIsA (in, ObitTableIDI_FLAGGetClass())

/** 
 * Macro to unreference (and possibly destroy) an ObitTableIDI_FLAGRow
 * returns an ObitTableIDI_FLAGRow*.
 * in = object to unreference
 */
#define ObitTableIDI_FLAGRowUnref(in) ObitUnref (in)

/** 
 * Macro to reference (update reference count) an ObitTableIDI_FLAGRow.
 * returns an ObitTableIDI_FLAGRow*.
 * in = object to reference
 */
#define ObitTableIDI_FLAGRowRef(in) ObitRef (in)

/** 
 * Macro to determine if an object is the member of this or a 
 * derived class.
 * Returns TRUE if a member, else FALSE
 * in = object to reference
 */
#define ObitTableIDI_FLAGRowIsA(in) ObitIsA (in, ObitTableIDI_FLAGRowGetClass())

/*---------------Public functions---------------------------*/
/*----------------Table Row Functions ----------------------*/
/** Public: Row Class initializer. */
void ObitTableIDI_FLAGRowClassInit (void);

/** Public: Constructor. */
ObitTableIDI_FLAGRow* newObitTableIDI_FLAGRow (ObitTableIDI_FLAG *table);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_FLAGRowGetClass (void);

/*------------------Table Functions ------------------------*/
/** Public: Class initializer. */
void ObitTableIDI_FLAGClassInit (void);

/** Public: Constructor. */
ObitTableIDI_FLAG* newObitTableIDI_FLAG (gchar* name);

/** Public: Constructor from values. */
ObitTableIDI_FLAG* 
newObitTableIDI_FLAGValue (gchar* name, ObitData *file, olong *ver,
  		     ObitIOAccess access,
                     oint no_band,
		     ObitErr *err);

/** Public: Class initializer. */
void ObitTableIDI_FLAGClassInit (void);

/** Public: ClassInfo pointer */
gconstpointer ObitTableIDI_FLAGGetClass (void);

/** Public: Copy (deep) constructor. */
ObitTableIDI_FLAG* ObitTableIDI_FLAGCopy  (ObitTableIDI_FLAG *in, ObitTableIDI_FLAG *out, 
			   ObitErr *err);

/** Public: Copy (shallow) constructor. */
ObitTableIDI_FLAG* ObitTableIDI_FLAGClone (ObitTableIDI_FLAG *in, ObitTableIDI_FLAG *out);

/** Public: Convert an ObitTable to an ObitTableIDI_FLAG */
ObitTableIDI_FLAG* ObitTableIDI_FLAGConvert  (ObitTable *in);

/** Public: Create ObitIO structures and open file */
ObitIOCode ObitTableIDI_FLAGOpen (ObitTableIDI_FLAG *in, ObitIOAccess access, 
			  ObitErr *err);

/** Public: Read a table row */
ObitIOCode 
ObitTableIDI_FLAGReadRow  (ObitTableIDI_FLAG *in, olong iIDI_FLAGRow, ObitTableIDI_FLAGRow *row,
		     ObitErr *err);

/** Public: Init a table row for write */
void 
ObitTableIDI_FLAGSetRow  (ObitTableIDI_FLAG *in, ObitTableIDI_FLAGRow *row,
		     ObitErr *err);

/** Public: Write a table row */
ObitIOCode 
ObitTableIDI_FLAGWriteRow  (ObitTableIDI_FLAG *in, olong iIDI_FLAGRow, ObitTableIDI_FLAGRow *row,
		     ObitErr *err);

/** Public: Close file and become inactive */
ObitIOCode ObitTableIDI_FLAGClose (ObitTableIDI_FLAG *in, ObitErr *err);

/*----------- ClassInfo Structure -----------------------------------*/
/**
 * ClassInfo Structure.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_FLAGClassDef.h"
} ObitTableIDI_FLAGClassInfo; 

/**
 * ClassInfo Structure For TableIDI_FLAGRow.
 * Contains class name, a pointer to any parent class
 * (NULL if none) and function pointers.
 */
typedef struct  {
#include "ObitTableIDI_FLAGRowClassDef.h"
} ObitTableIDI_FLAGRowClassInfo; 
#endif /* OBITTABLEIDI_FLAG_H */ 
