/* $Id$   */
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
#include "ObitTableOB.h"
#include "ObitTableList.h"
#include "ObitData.h"

/*----------------Obit:  Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitTableOB.c
 * ObitTableOB class function definitions.
 *
 * This class is derived from the #ObitTable class.
 */

/** name of the class defined in this file */
static gchar *myClassName = "ObitTableOB";

/**  Function to obtain parent Table ClassInfo - ObitTable */
static ObitGetClassFP ObitParentGetClass = ObitTableGetClass;

/** name of the Row class defined in this file */
static gchar *myRowClassName = "ObitTableOBRow";

/**  Function to obtain parent TableRow ClassInfo */
static ObitGetClassFP ObitParentGetRowClass = ObitTableRowGetClass;

/*--------------- File Global Variables  ----------------*/
/*----------------  Table Row  ----------------------*/
/**
 * ClassInfo structure ObitTableClassInfo.
 * This structure is used by class objects to access class functions.
 */
static ObitTableOBRowClassInfo myRowClassInfo = {FALSE};

/*------------------  Table  ------------------------*/
/**
 * ClassInfo structure ObitTableOBClassInfo.
 * This structure is used by class objects to access class functions.
 */
static ObitTableOBClassInfo myClassInfo = {FALSE};

/*---------------Private function prototypes----------------*/
/** Private: Initialize newly instantiated Row object. */
void  ObitTableOBRowInit  (gpointer in);

/** Private: Deallocate Row members. */
void  ObitTableOBRowClear (gpointer in);

/** Private: Initialize newly instantiated object. */
void  ObitTableOBInit  (gpointer in);

/** Private: Deallocate members. */
void  ObitTableOBClear (gpointer in);

/** Private: update table specific info */
static void ObitTableOBUpdate (ObitTableOB *in, ObitErr *err);

/** Private: copy table keywords to descriptor info list */
static void ObitTableOBDumpKey (ObitTableOB *in, ObitErr *err);

/** Private: Set Class function pointers */
static void ObitTableOBClassInfoDefFn (gpointer inClass);

/** Private: Set Row Class function pointers */
static void ObitTableOBRowClassInfoDefFn (gpointer inClass);
/*----------------------Public functions---------------------------*/

/*------------------  Table Row ------------------------*/
/**
 * Constructor.
 * If table is open and for write, the row is attached to the buffer
 * Initializes Row class if needed on first call.
 * \param name An optional name for the object.
 * \return the new object.
 */
ObitTableOBRow* newObitTableOBRow (ObitTableOB *table)
{
  ObitTableOBRow* out;
  odouble   *dRow;
  oint      *iRow;
  gshort    *siRow;
  ofloat    *fRow;
  gchar     *cRow;
  gboolean  *lRow;
  guint8    *bRow;

  /* Class initialization if needed */
  if (!myRowClassInfo.initialized) ObitTableOBRowClassInit();

  /* allocate/init structure */
  out = g_malloc0(sizeof(ObitTableOBRow));

  /* initialize values */
  out->name = g_strdup("TableOB Row");

  /* set ClassInfo */
  out->ClassInfo = (gpointer)&myRowClassInfo;

  /* initialize other stuff */
  ObitTableOBRowInit((gpointer)out);
  out->myTable   = (ObitTable*)ObitTableRef((ObitTable*)table);

  /* If writing attach to buffer */
  if ((table->buffer) && (table->myDesc->access != OBIT_IO_ReadOnly) &&
      (table->myStatus != OBIT_Inactive)) {
    /* Typed pointers to row of data */  
    dRow  = (odouble*)table->buffer;
    iRow  = (oint*)table->buffer;
    siRow = (gshort*)table->buffer;
    fRow  = (ofloat*)table->buffer;
    cRow  = (gchar*)table->buffer;
    lRow  = (gboolean*)table->buffer;
    bRow  = (guint8*)table->buffer;
  
    /* Set row pointers to buffer */
    out->orbXYZ = dRow + table->orbXYZOff;
    out->velXYZ = dRow + table->velXYZOff;
    out->sunAngle = fRow + table->sunAngleOff;
    out->eclipse = fRow + table->eclipseOff;
  } /* end attaching row to table buffer */

 return out;
} /* end newObitTableOBRow */

/**
 * Returns ClassInfo pointer for the Row class.
 * \return pointer to the Row class structure.
 */
gconstpointer ObitTableOBRowGetClass (void)
{
  /* Class initialization if needed */
  if (!myRowClassInfo.initialized) ObitTableOBRowClassInit();
  return (gconstpointer)&myRowClassInfo;
} /* end ObitTableOBRowGetClass */

/*------------------  Table  ------------------------*/
/**
 * Constructor.
 * Initializes class if needed on first call.
 * \param name An optional name for the object.
 * \return the new object.
 */
ObitTableOB* newObitTableOB (gchar* name)
{
  ObitTableOB* out;

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitTableOBClassInit();

  /* allocate/init structure */
  out = g_malloc0(sizeof(ObitTableOB));

  /* initialize values */
  if (name!=NULL) out->name = g_strdup(name);
  else out->name = g_strdup("Noname");

  /* set ClassInfo */
  out->ClassInfo = (gpointer)&myClassInfo;

  /* initialize other stuff */
  ObitTableOBInit((gpointer)out);

 return out;
} /* end newObitTableOB */

/**
 * Returns ClassInfo pointer for the class.
 * \return pointer to the class structure.
 */
gconstpointer ObitTableOBGetClass (void)
{
  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitTableOBClassInit();

  return (gconstpointer)&myClassInfo;
} /* end ObitOBGetClass */

/**
 * Constructor from values.
 * Creates a new table structure and attaches to the TableList of file.
 * If the specified table already exists then it is returned.
 * Initializes class if needed on first call.
 * Forces an update of any disk resident structures (e.g. AIPS header).
 * \param name   An optional name for the object.
 * \param file   ObitData which which the table is to be associated.
 * \param ver    Table version number. 0=> add higher, value used returned
 * \param access access (OBIT_IO_ReadOnly, means do not create if it doesn't exist.
 * \param err Error stack, returns if not empty.
 * \return the new object, NULL on failure.
 */
ObitTableOB* newObitTableOBValue (gchar* name, ObitData *file, olong *ver,
 	                    ObitIOAccess access,
  		    
		     ObitErr *err)
{
  ObitTableOB* out=NULL;
  ObitTable *testTab=NULL;
  ObitTableDesc *desc=NULL;
  ObitTableList *list=NULL;
  ObitInfoList  *info=NULL;
  gboolean exist, optional;
  olong colNo, i, ncol, highVer;
  ObitIOCode retCode;
  gchar *tabType = "AIPS OB";
  gchar *routine = "newObitTableOBValue";

 /* error checks */
  g_assert(ObitErrIsA(err));
  if (err->error) return NULL;
  g_assert (ObitDataIsA(file));

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitTableOBClassInit();

  /* Check if the table already exists */
  /* Get TableList */
  list = ((ObitData*)file)->tableList;
  info = ((ObitData*)file)->info;

  /* Get highest version number if not specified */
  if (*ver==0) { 
    highVer = ObitTableListGetHigh (list, "AIPS OB");
    if (access==OBIT_IO_ReadOnly) *ver = highVer;
    else if (access==OBIT_IO_ReadWrite) *ver = highVer;
    else if (access==OBIT_IO_WriteOnly) *ver = highVer+1;
  }
  /* See if it already exists */
  exist = FALSE;
  if (*ver>0) { /* has to be specified */
    exist = ObitTableListGet(list, tabType, ver, &testTab, err);
    if (err->error) /* add traceback,return */
      Obit_traceback_val (err, routine,"", out);
  
    /* if readonly, it must exist to proceed */
    if ((access==OBIT_IO_ReadOnly) && !exist) return out;
    if (testTab!=NULL) { /* it exists, use it if is an ObitTableOB */
      if (ObitTableOBIsA(testTab)) { /* it is an ObitTableOB */
	out = ObitTableRef(testTab);
      } else { /* needs conversion */
 	out = ObitTableOBConvert(testTab);
	/* Update the TableList */
	ObitTableListPut(list, tabType, ver, (ObitTable*)out, err);
	if (err->error) /* add traceback,return */
	  Obit_traceback_val (err, routine,"", out);
      }
      testTab = ObitTableUnref(testTab); /* remove reference */
      return out; /* done */
    }
  } /* end of test for previously existing table */
  
  /* If access is ReadOnly make sure one exists */
  if (access==OBIT_IO_ReadOnly) { 
    highVer = ObitTableListGetHigh (list, "AIPS OB");
    if (highVer<=0) return out;
  }
  
  /* create basal table */
  testTab = newObitDataTable ((ObitData*)file, access, tabType,
			       ver, err);
  if (err->error) Obit_traceback_val (err, routine,"", out);
  
  /* likely need to convert */
  if (ObitTableOBIsA(testTab)) { 
    out = ObitTableRef(testTab);
  } else { /* needs conversion */
    out = ObitTableOBConvert(testTab);
  }
  testTab = ObitTableUnref(testTab); /* remove reference */

  /* Update the TableList */
  ObitTableListPut(list, tabType, ver, (ObitTable*)out, err);
  if (err->error) Obit_traceback_val (err, routine,"", out);

  /* if it previously existed merely return it */
  if (exist) return out; 

  /* set ClassInfo */
  out->ClassInfo = (gpointer)&myClassInfo;

  /* Set values */
  out->revision = 2;

  /* initialize descriptor */
  desc = out->myDesc;
  /* How many columns actually in table? */
  ncol = 8 ;
  desc->FieldName = g_malloc0((ncol+1)*sizeof(gchar*));
  desc->FieldUnit = g_malloc0((ncol+1)*sizeof(gchar*));
  desc->type      = g_malloc0((ncol+1)*sizeof(ObitInfoType));
  desc->dim       = g_malloc0((ncol+1)*sizeof(gint32*));
  for (i=0; i<ncol+1; i++) 
    desc->dim[i] = g_malloc0(MAXINFOELEMDIM*sizeof(gint32));

  desc->TableName = g_strdup(tabType);
  desc->sort[0] = 0;
  desc->sort[1] = 0;
  colNo = 0;

  /* Define Columns */
  desc->FieldName[colNo] = g_strdup("ANTENNA_NO");
  desc->FieldUnit[colNo] = g_strdup("");
  desc->type[colNo] = OBIT_oint;
  for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
  colNo++;
  desc->FieldName[colNo] = g_strdup("SUBARRAY   ");
  desc->FieldUnit[colNo] = g_strdup("");
  desc->type[colNo] = OBIT_oint;
  for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
  colNo++;
  desc->FieldName[colNo] = g_strdup("TIME    ");
  desc->FieldUnit[colNo] = g_strdup("DAYS");
  desc->type[colNo] = OBIT_double;
  for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
  colNo++;
  optional = FALSE;
  if ((3 > 0) || (!optional)) {
    desc->FieldName[colNo] = g_strdup("ORBXYZ    ");
    desc->FieldUnit[colNo] = g_strdup("METERS");
    desc->type[colNo] = OBIT_double;
    for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
    desc->dim[colNo][0] = 3;
    colNo++;
  }
  optional = FALSE;
  if ((3 > 0) || (!optional)) {
    desc->FieldName[colNo] = g_strdup("VELXYZ    ");
    desc->FieldUnit[colNo] = g_strdup("M/SEC");
    desc->type[colNo] = OBIT_double;
    for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
    desc->dim[colNo][0] = 3;
    colNo++;
  }
  optional = FALSE;
  if ((3 > 0) || (!optional)) {
    desc->FieldName[colNo] = g_strdup("SUN_ANGLE ");
    desc->FieldUnit[colNo] = g_strdup("DEGREES");
    desc->type[colNo] = OBIT_float;
    for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
    desc->dim[colNo][0] = 3;
    colNo++;
  }
  optional = FALSE;
  if ((4 > 0) || (!optional)) {
    desc->FieldName[colNo] = g_strdup("ECLIPSE ");
    desc->FieldUnit[colNo] = g_strdup("DAYS");
    desc->type[colNo] = OBIT_float;
    for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
    desc->dim[colNo][0] = 4;
    colNo++;
  }
  desc->FieldName[colNo] = g_strdup("ORIENTATION ");
  desc->FieldUnit[colNo] = g_strdup("DEGREES");
  desc->type[colNo] = OBIT_float;
  for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
  colNo++;
  /* Add _status column at end */
  desc->FieldName[colNo] = g_strdup("_status");
  desc->FieldUnit[colNo] = g_strdup("        ");
  desc->type[colNo] = OBIT_long;
  for (i=0; i<MAXINFOELEMDIM; i++) desc->dim[colNo][i] = 1;
  
  /* number of fields */
  desc->nfield = colNo + 1;

  /* initialize descriptor keywords */
  ObitTableOBDumpKey (out, err);
 
  /* index table descriptor */
  ObitTableDescIndex (desc);

  /* Open and Close to fully instantiate */
  retCode = ObitTableOBOpen(out, OBIT_IO_WriteOnly, err);
  if ((retCode!=OBIT_IO_OK) || (err->error)) /* add traceback,return */
    Obit_traceback_val (err, routine, out->name, out);    
  
  retCode = ObitTableOBClose(out, err);
  if ((retCode!=OBIT_IO_OK) || (err->error)) /* add traceback,return */
    Obit_traceback_val (err, routine, out->name, out); 

  /* Force update of disk resident info */
  retCode = ObitIOUpdateTables (((ObitData*)file)->myIO, info, err);
  if ((retCode!=OBIT_IO_OK) || (err->error)) /* add traceback,return */
    Obit_traceback_val (err, routine, out->name, out); 
  
 return out;
} /* end newObitTableOBValue */

/**
 * Convert an ObitTable to an ObitTableOB.
 * New object will have references to members of in.
 * \param in  The object to copy, will still exist afterwards 
 *            and should be Unrefed if not needed.
 * \return pointer to the new object.
 */
ObitTableOB* ObitTableOBConvert (ObitTable* in)
{
  ObitTableOB *out;

  /* error check */
  g_assert(ObitTableIsA(in));

  /* create basic object */
  out = newObitTableOB(in->name);

  /* Delete structures on new */
  out->info   = ObitInfoListUnref(out->info);
  out->thread = ObitThreadUnref(out->thread);
  out->myDesc = ObitTableDescUnref(out->myDesc);
  out->mySel  = ObitTableSelUnref(out->mySel);
  
  /* Reference members of in */
  
  out->info   = ObitInfoListRef(in->info);
  out->thread = ObitThreadRef(in->thread);
  out->myDesc = ObitTableDescRef(in->myDesc);
  out->mySel  = ObitTableSelRef(in->mySel);

  /* Remember who I am */
 out->tabType = g_strdup(in->tabType);
 out->tabVer  = in->tabVer;
  /* Secret reference to host */ 
 out->myHost  = in->myHost;

  return out;
} /* end ObitTableOBConvert */


/**
 * Make a deep copy of input object.
 * Copies are made of complex members including disk files; these 
 * will be copied applying whatever selection is associated with the input.
 * Objects should be closed on input and will be closed on output.
 * In order for the disk file structures to be copied, the output file
 * must be sufficiently defined that it can be written.
 * The copy will be attempted but no errors will be logged until
 * both input and output have been successfully opened.
 * ObitInfoList and ObitThread members are only copied if the output object
 * didn't previously exist.
 * Parent class members are included but any derived class info is ignored.
 * \param in  The object to copy
 * \param out An existing object pointer for output or NULL if none exists.
 * \param err Error stack, returns if not empty.
 * \return pointer to the new object.
 */
ObitTableOB* ObitTableOBCopy (ObitTableOB *in, ObitTableOB *out, ObitErr *err)
{
  gchar *routine = "ObitTableOBCopy";

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitTableOBClassInit();

 /* error checks */
  g_assert(ObitErrIsA(err));
  if (err->error) return NULL;
  g_assert (ObitIsA(in, &myClassInfo));
  if (out) g_assert (ObitIsA(out, &myClassInfo));

  /* Use parent class to copy */
  out = (ObitTableOB*)ObitTableCopy ((ObitTable*)in, (ObitTable*)out, err);
  if (err->error) /* add traceback,return */
    Obit_traceback_val (err, routine,in->name, out);

  /* Copy this class  info */
  out->revision = in->revision;
  /* Update class specific info */
  ObitTableOBUpdate (out, err);
    
  return out;
} /* end ObitTableOBCopy */

/**
 * Initialize structures and open file.
 * The image descriptor is read if OBIT_IO_ReadOnly or 
 * OBIT_IO_ReadWrite and written to disk if opened OBIT_IO_WriteOnly.
 * After the file has been opened the member, buffer is initialized
 * for reading/storing the table unless member bufferSize is <0.
 * If the requested version ("Ver" in InfoList) is 0 then the highest
 * numbered table of the same type is opened on Read or Read/Write, 
 * or a new table is created on on Write.
 * The file etc. info should have been stored in the ObitInfoList:
 * \li "FileType" OBIT_long scalar = OBIT_IO_FITS or OBIT_IO_AIPS 
 *               for file type (see class documentation for details).
 * \li "nRowPIO" OBIT_long scalar = Maximum number of table rows
 *               per transfer, this is the target size for Reads (may be 
 *               fewer) and is used to create buffers.
 * \param in Pointer to object to be opened.
 * \param access access (OBIT_IO_ReadOnly,OBIT_IO_ReadWrite,
 *               or OBIT_IO_WriteOnly).
 *               If OBIT_IO_WriteOnly any existing data in the output file
 *               will be lost.
 * \param err ObitErr for reporting errors.
 * \return return code, OBIT_IO_OK=> OK
 */
ObitIOCode ObitTableOBOpen (ObitTableOB *in, ObitIOAccess access, 
			  ObitErr *err)
{
  ObitIOCode retCode = OBIT_IO_SpecErr;
  gint32 dim[MAXINFOELEMDIM] = {1,1,1,1,1};
  olong nRowPIO;
  gchar *routine = "ObitTableOBOpen";

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitTableOBClassInit();

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return retCode;
  g_assert (ObitIsA(in, &myClassInfo));

   /* Do one row at a time */
   nRowPIO = 1;
   ObitInfoListPut(in->info, "nRowPIO", OBIT_long, dim, (gconstpointer)&nRowPIO, err);
   if (err->error) /* add traceback,return */
     Obit_traceback_val (err, routine, in->name, retCode);
   
   /* use parent class open */
   retCode = ObitTableOpen ((ObitTable*)in, access, err);
   if ((retCode!=OBIT_IO_OK) || (err->error)) /* add traceback,return */
     Obit_traceback_val (err, routine, in->name, retCode);
   
   /* Update class specific info */
   ObitTableOBUpdate (in, err);
   
   return retCode;
} /* end ObitTableOBOpen */

/**
 * Read a table row and return an easily digested version.
 * Scalar values are copied but for array values, pointers 
 * into the data array are returned.
 * \param in       Table to read
 * \param iOBRow   Row number, -1 -> next
 * \param row      Table Row structure to receive data
 * \param err ObitErr for reporting errors.
 * \return return code, OBIT_IO_OK=> OK
 */
ObitIOCode 
ObitTableOBReadRow  (ObitTableOB *in, olong iOBRow, ObitTableOBRow *row,
		     ObitErr *err)
{
  ObitIOCode retCode = OBIT_IO_SpecErr;
  odouble   *dRow;
  oint      *iRow;
  gshort    *siRow;
  ofloat    *fRow;
  gchar     *cRow;
  gboolean  *lRow;
  guint8    *bRow;
  gchar *routine = "ObitTableOBReadRow";
  
  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return retCode;
  g_assert (ObitIsA(in, &myClassInfo));

  if (in->myStatus == OBIT_Inactive) {
    Obit_log_error(err, OBIT_Error,
		   "AIPS OB Table is inactive for  %s ", in->name);
    return retCode;
 }

  /* read row iOBRow */
  retCode = ObitTableRead ((ObitTable*)in, iOBRow, NULL,  err);
  if (err->error) 
    Obit_traceback_val (err, routine, in->name, retCode);

  /* Typed pointers to row of data */  
  dRow  = (odouble*)in->buffer;
  iRow  = (oint*)in->buffer;
  siRow = (gshort*)in->buffer;
  fRow  = (ofloat*)in->buffer;
  cRow  = (gchar*)in->buffer;
  lRow  = (gboolean*)in->buffer;
  bRow  = (guint8*)in->buffer;
  
  /* Copy scalar fields, for arrays only set pointer*/
  row->antennaNo = iRow[in->antennaNoOff];
  row->SubA = iRow[in->SubAOff];
  row->Time = dRow[in->TimeOff];
  row->orientation = fRow[in->orientationOff];
  row->orbXYZ = dRow + in->orbXYZOff;
  row->velXYZ = dRow + in->velXYZOff;
  row->sunAngle = fRow + in->sunAngleOff;
  row->eclipse = fRow + in->eclipseOff;
  row->status = iRow[in->myDesc->statusOff];

  return retCode;
} /*  end ObitTableOBReadRow */

/**
 * Attach an ObitTableRow to the buffer of an ObitTable.
 * This is only useful prior to filling a row structure in preparation .
 * for a WriteRow operation.  Array members of the Row structure are .
 * pointers to independently allocated memory, this routine allows using .
 * the table IO buffer instead of allocating yet more memory..
 * This routine need only be called once to initialize a Row structure for write..
 * \param in  Table with buffer to be written 
 * \param row Table Row structure to attach 
 * \param err ObitErr for reporting errors.
 */
void 
ObitTableOBSetRow  (ObitTableOB *in, ObitTableOBRow *row,
		     ObitErr *err)
{
  odouble   *dRow;
  oint      *iRow;
  gshort    *siRow;
  ofloat    *fRow;
  gchar     *cRow;
  gboolean  *lRow;
  guint8    *bRow;
  
  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitIsA(in, &myClassInfo));
  g_assert (ObitIsA(row, &myRowClassInfo));

  if (in->myStatus == OBIT_Inactive) {
    Obit_log_error(err, OBIT_Error,
		   "OB Table is inactive for  %s ", in->name);
    return;
 }

  /* Typed pointers to row of data */  
  dRow  = (odouble*)in->buffer;
  iRow  = (oint*)in->buffer;
  siRow = (gshort*)in->buffer;
  fRow  = (ofloat*)in->buffer;
  cRow  = (gchar*)in->buffer;
  lRow  = (gboolean*)in->buffer;
  bRow  = (guint8*)in->buffer;
  
  /* Set row pointers to buffer */
  row->orbXYZ = dRow + in->orbXYZOff;
  row->velXYZ = dRow + in->velXYZOff;
  row->sunAngle = fRow + in->sunAngleOff;
  row->eclipse = fRow + in->eclipseOff;

} /*  end ObitTableOBSetRow */

/**
 * Write a table row.
 * Before calling this routine, the row structure needs to be initialized
 * and filled with data. The array members of the row structure are  
 * pointers to independently allocated memory.  These pointers can be set to the 
 * correct table buffer locations using ObitTableOBSetRow  
 * \param in       Table to read
 * \param iOBRow   Row number, -1 -> next
 * \param row Table Row structure containing data
 * \param err ObitErr for reporting errors.
 * \return return code, OBIT_IO_OK=> OK
 */
ObitIOCode 
ObitTableOBWriteRow  (ObitTableOB *in, olong iOBRow, ObitTableOBRow *row,
		      ObitErr *err)
{
  ObitIOCode retCode = OBIT_IO_SpecErr;
  gshort    *siRow;
  odouble   *dRow;
  oint      *iRow, i;
  ofloat    *fRow;
  gchar     *cRow;
  gboolean  *lRow;
  guint8    *bRow;
  gchar *routine = "ObitTableOBWriteRow";
  

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return retCode;
  g_assert (ObitIsA(in, &myClassInfo));

  if (in->myStatus == OBIT_Inactive) {
    Obit_log_error(err, OBIT_Error,
		   "AIPS OB Table is inactive for %s ", in->name);
    return retCode;
 }

  /* Typed pointers to row of data */  
  dRow  = (odouble*)in->buffer;
  siRow = (gshort*)in->buffer;
  iRow  = (oint*)in->buffer;
  fRow  = (ofloat*)in->buffer;
  cRow  = (gchar*)in->buffer;
  lRow  = (gboolean*)in->buffer;
  bRow  = (guint8*)in->buffer;
  
  /* Make full copy of all data */
  iRow[in->antennaNoOff] = row->antennaNo;
  iRow[in->SubAOff] = row->SubA;
  dRow[in->TimeOff] = row->Time;
  fRow[in->orientationOff] = row->orientation;
  if (in->orbXYZCol >= 0) { 
    for (i=0; i<in->myDesc->repeat[in->orbXYZCol]; i++) 
      dRow[in->orbXYZOff+i] = row->orbXYZ[i];
  } 
  if (in->velXYZCol >= 0) { 
    for (i=0; i<in->myDesc->repeat[in->velXYZCol]; i++) 
      dRow[in->velXYZOff+i] = row->velXYZ[i];
  } 
  if (in->sunAngleCol >= 0) { 
    for (i=0; i<in->myDesc->repeat[in->sunAngleCol]; i++) 
      fRow[in->sunAngleOff+i] = row->sunAngle[i];
  } 
  if (in->eclipseCol >= 0) { 
    for (i=0; i<in->myDesc->repeat[in->eclipseCol]; i++) 
      fRow[in->eclipseOff+i] = row->eclipse[i];
  } 

  /* copy status */
  iRow[in->myDesc->statusOff] = row->status;
   
  /* Write one row */
  in->myDesc->numRowBuff = 1;
 
  /* Write row iOBRow */
  retCode = ObitTableWrite ((ObitTable*)in, iOBRow, NULL,  err);
  if (err->error) 
    Obit_traceback_val (err, routine,in->name, retCode);

  return retCode;
} /*  end ObitTableOBWriteRow */

/**
 * Shutdown I/O.
 * \param in Pointer to object to be closed.
 * \param err ObitErr for reporting errors.
 * \return error code, OBIT_IO_OK=> OK
 */
ObitIOCode ObitTableOBClose (ObitTableOB *in, ObitErr *err)
{
  ObitIOCode retCode = OBIT_IO_SpecErr;
  gchar *routine = "ObitTableOBClose";

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return retCode;
  g_assert (ObitIsA((Obit*)in, &myClassInfo));
  /* Something going on? */
  if (in->myStatus == OBIT_Inactive) return OBIT_IO_OK;

  /* Update keywords on descriptor if not ReadOnly*/
  if (in->myDesc->access != OBIT_IO_ReadOnly) 
    ObitTableOBDumpKey (in, err);
  if (err->error) 
    Obit_traceback_val (err, routine, in->name, retCode);

  /* Close */
  retCode = ObitTableClose ((ObitTable*)in, err);
  if (err->error) 
    Obit_traceback_val (err, routine, in->name, retCode);

  return retCode;
} /* end ObitTableOBClose */

/*---------------Private functions--------------------------*/
/*----------------  TableOB Row  ----------------------*/
/**
 * Creates empty member objects, initialize reference count.
 * Parent classes portions are (recursively) initialized first
 * \param inn Pointer to the object to initialize.
 */
void ObitTableOBRowInit  (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitTableOBRow *in = inn;

  /* error checks */
  g_assert (in != NULL);

  /* recursively initialize parent class members */
  ParentClass = (ObitClassInfo*)(myRowClassInfo.ParentClass);
  if ((ParentClass!=NULL) && ( ParentClass->ObitInit!=NULL)) 
    ParentClass->ObitInit (inn);

  /* set members in this class */
  /* Set array members to NULL */
  in->orbXYZ = NULL;
  in->velXYZ = NULL;
  in->sunAngle = NULL;
  in->eclipse = NULL;

} /* end ObitTableOBRowInit */

/**
 * Deallocates member objects.
 * Does (recursive) deallocation of parent class members.
 * For some reason this wasn't build into the GType class.
 * \param  inn Pointer to the object to deallocate.
 *           Actually it should be an ObitTableOBRow* cast to an Obit*.
 */
void ObitTableOBRowClear (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitTableOBRow *in = inn;

  /* error checks */
  g_assert (ObitIsA(in, &myRowClassInfo));

  /* delete this class members */
  /* Do not free data array pointers as they were not malloced */
  
  /* unlink parent class members */
  ParentClass = (ObitClassInfo*)(myRowClassInfo.ParentClass);
  /* delete parent class members */
  if ((ParentClass!=NULL) && ( ParentClass->ObitClear!=NULL)) 
    ParentClass->ObitClear (inn);
  
} /* end ObitTableOBRowClear */

/**
 * Initialize global ClassInfo Structure.
 */
void ObitTableOBRowClassInit (void)
{
  if (myRowClassInfo.initialized) return;  /* only once */
  
  /* Set name and parent for this class */
  myRowClassInfo.ClassName   = g_strdup(myRowClassName);
  myRowClassInfo.ParentClass = ObitParentGetRowClass();

  /* Set function pointers */
  ObitTableOBRowClassInfoDefFn ((gpointer)&myRowClassInfo);
 
  myRowClassInfo.initialized = TRUE; /* Now initialized */
 
} /* end ObitTableOBRowClassInit */

/**
 * Initialize global ClassInfo Function pointers.
 */
static void ObitTableOBRowClassInfoDefFn (gpointer inClass)
{
  ObitTableOBRowClassInfo *theClass = (ObitTableOBRowClassInfo*)inClass;
  ObitClassInfo *ParentClass = (ObitClassInfo*)myRowClassInfo.ParentClass;

  if (theClass->initialized) return;  /* only once */

  /* Check type of inClass */
  g_assert (ObitInfoIsA(inClass, (ObitClassInfo*)&myRowClassInfo));

  /* Initialize (recursively) parent class first */
  if ((ParentClass!=NULL) && 
      (ParentClass->ObitClassInfoDefFn!=NULL))
    ParentClass->ObitClassInfoDefFn(theClass);

  /* function pointers defined or overloaded this class */
  theClass->ObitClassInit = (ObitClassInitFP)ObitTableOBRowClassInit;
  theClass->ObitClassInfoDefFn = (ObitClassInfoDefFnFP)ObitTableOBRowClassInfoDefFn;
  theClass->ObitGetClass  = (ObitGetClassFP)ObitTableOBRowGetClass;
  theClass->newObit         = NULL;
  theClass->newObitTableRow = (newObitTableRowFP)newObitTableOBRow;
  theClass->ObitCopy        = NULL;
  theClass->ObitClone       = NULL;
  theClass->ObitClear       = (ObitClearFP)ObitTableOBRowClear;
  theClass->ObitInit        = (ObitInitFP)ObitTableOBRowInit;

} /* end ObitTableOBRowClassDefFn */

/*------------------  TableOB  ------------------------*/

/**
 * Creates empty member objects, initialize reference count.
 * Parent classes portions are (recursively) initialized first
 * \param inn Pointer to the object to initialize.
 */
void ObitTableOBInit  (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitTableOB *in = inn;

  /* error checks */
  g_assert (in != NULL);

  /* recursively initialize parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  if ((ParentClass!=NULL) && ( ParentClass->ObitInit!=NULL)) 
    ParentClass->ObitInit (inn);

  /* set members in this class */

} /* end ObitTableOBInit */

/**
 * Deallocates member objects.
 * Does (recursive) deallocation of parent class members.
 * For some reason this wasn't build into the GType class.
 * \param  inn Pointer to the object to deallocate.
 *           Actually it should be an ObitTableOB* cast to an Obit*.
 */
void ObitTableOBClear (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitTableOB *in = inn;

  /* error checks */
  g_assert (ObitIsA(in, &myClassInfo));

  /* delete this class members */
  
  /* unlink parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  /* delete parent class members */
  if ((ParentClass!=NULL) && ( ParentClass->ObitClear!=NULL)) 
    ParentClass->ObitClear (inn);
  
} /* end ObitTableOBClear */

/**
 * Initialize global ClassInfo Structure.
 */
void ObitTableOBClassInit (void)
{
  if (myClassInfo.initialized) return;  /* only once */
  
  /* Set name and parent for this class */
  myClassInfo.ClassName   = g_strdup(myClassName);
  myClassInfo.ParentClass = ObitParentGetClass();

  /* Set function pointers */
  ObitTableOBClassInfoDefFn ((gpointer)&myClassInfo);
 
  myClassInfo.initialized = TRUE; /* Now initialized */
 
} /* end ObitTableOBClassInit */

/**
 * Initialize global ClassInfo Function pointers.
 */
static void ObitTableOBClassInfoDefFn (gpointer inClass)
{
  ObitTableOBClassInfo *theClass = (ObitTableOBClassInfo*)inClass;
  ObitClassInfo *ParentClass = (ObitClassInfo*)myClassInfo.ParentClass;

  if (theClass->initialized) return;  /* only once */

  /* Check type of inClass */
  g_assert (ObitInfoIsA(inClass, (ObitClassInfo*)&myClassInfo));

  /* Initialize (recursively) parent class first */
  if ((ParentClass!=NULL) && 
      (ParentClass->ObitClassInfoDefFn!=NULL))
    ParentClass->ObitClassInfoDefFn(theClass);

  /* function pointers defined or overloaded this class */
  theClass->ObitClassInit = (ObitClassInitFP)ObitTableOBClassInit;
  theClass->ObitClassInfoDefFn = (ObitClassInfoDefFnFP)ObitTableOBClassInfoDefFn;
  theClass->ObitGetClass  = (ObitGetClassFP)ObitTableOBGetClass;
  theClass->newObit       = (newObitFP)newObitTableOB;
  theClass->ObitCopy      = (ObitCopyFP)ObitTableOBCopy;
  theClass->ObitClone     = (ObitCloneFP)ObitTableClone;
  theClass->ObitClear     = (ObitClearFP)ObitTableOBClear;
  theClass->ObitInit      = (ObitInitFP)ObitTableOBInit;
  theClass->ObitTableConvert = (ObitTableConvertFP)ObitTableOBConvert;
  theClass->ObitTableOpen    = (ObitTableOpenFP)ObitTableOBOpen;
  theClass->ObitTableClose   = (ObitTableCloseFP)ObitTableOBClose;
  theClass->ObitTableRead    = (ObitTableReadFP)ObitTableRead;
  theClass->ObitTableReadSelect = 
    (ObitTableReadSelectFP)ObitTableReadSelect;
  theClass->ObitTableWrite = (ObitTableWriteFP)ObitTableWrite;
  theClass->ObitTableReadRow = 
    (ObitTableReadRowFP)ObitTableOBReadRow;
  theClass->ObitTableWriteRow = 
    (ObitTableWriteRowFP)ObitTableOBWriteRow;

} /* end ObitTableOBClassDefFn */

/**
 * Get table specific information from the infolist or descriptor
 * \param info Table to update
 * \param err  ObitErr for reporting errors.
 */
static void ObitTableOBUpdate (ObitTableOB *in, ObitErr *err)
{
  olong i;
  ObitInfoType type;
  gint32 dim[MAXINFOELEMDIM];
  ObitTableDesc *desc;
   

 /* error checks */
   g_assert(ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitIsA(in, &myClassInfo));

  /* Get Keywords */
   /* revision */
  in->revision = 2; 
  ObitInfoListGetTest(in->myDesc->info, "TABREV", &type, dim, 
		       (gpointer)&in->revision);

  /* initialize column numbers/offsets */
  in->antennaNoOff = -1;
  in->antennaNoCol = -1;
  in->SubAOff = -1;
  in->SubACol = -1;
  in->TimeOff = -1;
  in->TimeCol = -1;
  in->orbXYZOff = -1;
  in->orbXYZCol = -1;
  in->velXYZOff = -1;
  in->velXYZCol = -1;
  in->sunAngleOff = -1;
  in->sunAngleCol = -1;
  in->eclipseOff = -1;
  in->eclipseCol = -1;
  in->orientationOff = -1;
  in->orientationCol = -1;
  /* Find columns and set offsets */
  desc = in->myDesc;
  if (desc->FieldName) {
    for (i=0; i<desc->nfield; i++) {
      if (!strncmp (desc->FieldName[i], "ANTENNA_NO", 10)) {
	 in->antennaNoOff = desc->offset[i];
 	 in->antennaNoCol = i;
      }
      if (!strncmp (desc->FieldName[i], "SUBARRAY   ", 11)) {
	 in->SubAOff = desc->offset[i];
 	 in->SubACol = i;
      }
      if (!strncmp (desc->FieldName[i], "TIME    ", 8)) {
	 in->TimeOff = desc->offset[i];
 	 in->TimeCol = i;
      }
      if (!strncmp (desc->FieldName[i], "ORBXYZ    ", 10)) {
	 in->orbXYZOff = desc->offset[i];
 	 in->orbXYZCol = i;
      }
      if (!strncmp (desc->FieldName[i], "VELXYZ    ", 10)) {
	 in->velXYZOff = desc->offset[i];
 	 in->velXYZCol = i;
      }
      if (!strncmp (desc->FieldName[i], "SUN_ANGLE ", 10)) {
	 in->sunAngleOff = desc->offset[i];
 	 in->sunAngleCol = i;
      }
      if (!strncmp (desc->FieldName[i], "ECLIPSE ", 8)) {
	 in->eclipseOff = desc->offset[i];
 	 in->eclipseCol = i;
      }
      if (!strncmp (desc->FieldName[i], "ORIENTATION ", 12)) {
	 in->orientationOff = desc->offset[i];
 	 in->orientationCol = i;
      }
     }
  }

  /* Check required columns */
  Obit_return_if_fail((in->antennaNoOff > -1), err,
       "ObitTableOBUpdate: Could not find column antennaNo");
  Obit_return_if_fail((in->SubAOff > -1), err,
       "ObitTableOBUpdate: Could not find column SubA");
  Obit_return_if_fail((in->TimeOff > -1), err,
       "ObitTableOBUpdate: Could not find column Time");
  Obit_return_if_fail((in->orbXYZOff > -1), err,
       "ObitTableOBUpdate: Could not find column orbXYZ");
  Obit_return_if_fail((in->velXYZOff > -1), err,
       "ObitTableOBUpdate: Could not find column velXYZ");
  Obit_return_if_fail((in->sunAngleOff > -1), err,
       "ObitTableOBUpdate: Could not find column sunAngle");
  Obit_return_if_fail((in->eclipseOff > -1), err,
       "ObitTableOBUpdate: Could not find column eclipse");
} /* end ObitTableOBUpdate */

/**
 * Copy table specific (keyword) information  to infolist.
 * \param info Table to update
 * \param err  ObitErr for reporting errors.
 */
static void ObitTableOBDumpKey (ObitTableOB *in, ObitErr *err)
{
  ObitInfoList *info=NULL;
  ObitInfoType type;
  gint32 dim[MAXINFOELEMDIM] = {1,1,1,1,1};

 /* error checks */
   g_assert(ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitIsA(in, &myClassInfo));

  /* Set Keywords */
  if (in->myIO!=NULL) info = ((ObitTableDesc*)(in->myIO->myDesc))->info;
  else info = in->myDesc->info;
  /* revision */
  type  = OBIT_oint;
  dim[0] = 1;
  ObitInfoListAlwaysPut(info, "TABREV", type, dim, 
		  (gpointer)&in->revision);
   
} /* end ObitTableOBDumpKey */
