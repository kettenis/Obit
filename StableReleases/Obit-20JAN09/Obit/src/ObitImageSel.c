/* $Id$    */
/*--------------------------------------------------------------------*/
/*;  Copyright (C) 2003-2008                                          */
/*;  Associated Universities, Inc. Washington DC, USA.                */
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
/*; Correspondence about this software should be addressed as follows:*/
/*;         Internet email: bcotton@nrao.edu.                         */
/*;         Postal address: William Cotton                            */
/*;                         National Radio Astronomy Observatory      */
/*;                         520 Edgemont Road                         */
/*;                         Charlottesville, VA 22903-2475 USA        */
/*--------------------------------------------------------------------*/
#include "Obit.h"
#include "ObitImageSel.h"
#include "ObitMem.h"

/*-------------- Obit: Merx mollis mortibus nuper ------------*/
/**
 * \file ObitImageSel.c
 * ObitImageSel ObitImage selector class definition.
 *
 * This contains information about data selection.
 */

/*--------------- File Global Variables  ----------------*/
/** name of the class defined in this file */
static gchar *myClassName = "ObitImageSel";

/** Function to obtain parent ClassInfo - Obit */
static ObitGetClassFP ObitParentGetClass = ObitGetClass;

/**
 * ClassInfo global structure ObitIOClassInfo.
 * This structure is used by class objects to access class functions.
 */
static ObitImageSelClassInfo myClassInfo = {FALSE};

/*---------------Private function prototypes----------------*/
/** Private: Initialize newly instantiated object. */
void  ObitImageSelInit  (gpointer in);

/** Private: Deallocate members. */
void  ObitImageSelClear (gpointer in);

/** Private: Set Class function pointers. */
static void ObitImageSelClassInfoDefFn (gpointer inClass);

/*---------------Public functions---------------------------*/
/**
 * Construct Object.
 * \return pointer to object created.
 */
ObitImageSel* newObitImageSel (gchar *name)
{
  ObitImageSel* out;

  /* Class initialization if needed */
  if (!myClassInfo.initialized) 
    ObitImageSelClassInit();

  /* allocate structure */
  out = ObitMemAlloc0Name(sizeof(ObitImageSel), "ObitImageSel");

  /* initialize values */
  if (name!=NULL) out->name = g_strdup(name);
  else out->name = g_strdup("Noname");

 /* set classInfo */
  out->ClassInfo = (gpointer)&myClassInfo;

  /* initialize other stuff */
  ObitImageSelInit((gpointer)out);

  return out;
} /* end newObitImageSel */

/**
 * Returns ClassInfo pointer for the class.
 * Initializes class if needed on first call.
 * \return pointer to the class structure.
 */
gconstpointer ObitImageSelGetClass (void)
{
  /* Class initialization if needed */
  if (!myClassInfo.initialized) 
    ObitImageSelClassInit();

  return (gconstpointer)&myClassInfo;
} /* end ObitImageSelGetClass */

/**
 * Copy constructor.
 * \param in Pointer to object to be copied.
 * \param out Pointer to object to be written.  
 *            If NULL then a new structure is created.
 * \param err ObitErr error stack
 * \return Pointer to new object.
 */
ObitImageSel* 
ObitImageSelCopy (ObitImageSel* in, ObitImageSel* out, 
		  ObitErr *err)
{
  const ObitClassInfo *ParentClass;
  gboolean oldExist;
  gchar *outName;
  olong i;

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return out;
  g_assert (ObitIsA(in, &myClassInfo));
  if (out) g_assert (ObitIsA(out, &myClassInfo));

  /* Create if it doesn't exist */
  oldExist = out!=NULL;
  if (!oldExist) {
    /* derive object name */
    outName = g_strconcat ("Copy: ",in->name,NULL);
    out = newObitImageSel(outName);
    g_free(outName);
  }

  /* deep copy any base class members */
  ParentClass = myClassInfo.ParentClass;
  g_assert ((ParentClass!=NULL) && (ParentClass->ObitCopy!=NULL));
  ParentClass->ObitCopy (in, out, err);

  /* copy */
  for (i=0; i<IM_MAXDIM; i++) {
    out->blc[i] = in->blc[i];
    out->trc[i] = in->trc[i];
  }

  return out;
} /* end ObitImageSelCopy */

/**
 * Creates/resizes image I/O buffer
 * for data transfers as described by data members.
 * \param buffer Preexisting buffer or NULL if none
 * \param desc   Pointer input descriptor.
 * \param sel    Image selector.
 * \return size in floats needed for I/O.
 */
ObitFArray* 
ObitImageSelBuffer (ObitFArray *buffer, ObitImageDesc* desc, 
		    ObitImageSel* sel)
{
  ObitFArray *out = buffer;
  olong ndim=0, naxis[2];

  /* error checks */
  if (desc==NULL) return out; 
  g_assert (ObitIsA(desc, ObitImageDescGetClass()));
  g_assert (ObitIsA(sel, &myClassInfo));

  /* make sure defaults filled in */
  ObitImageSelDefault (desc, sel);

  /* determine to size needed */  
  /* big enough for a subimaged row or plane */
  if (desc->IOsize==OBIT_IO_byRow) {
    ndim = 1;
    naxis[0] = sel->trc[0] - sel->blc[0] + 1;
  } else if (desc->IOsize==OBIT_IO_byPlane) {
    ndim = 2;
    naxis[0] = sel->trc[0] - sel->blc[0] + 1;
    naxis[1] = sel->trc[1] - sel->blc[1] + 1;
  }

  /* Create out is none exists */
  if (out==NULL) {
     out = ObitFArrayCreate ("Image Buffer", ndim, naxis);
  } else { /* resize */
    out = ObitFArrayRealloc (out, ndim, naxis);
  }

  return out;
} /* end ObitImageSelBufferSize */

/**
 * minimum inaxes is 1, 
 * blc default 1 but must be between 1 and max(trc,inaxes)
 * trc defaults to inaxes but must be between blc and inaxes.
 * Also indexes structure.
 * \param in Pointer to descriptor.
 * \param sel Image selector, blc, trc members changed if needed.
 */
void ObitImageSelDefault (ObitImageDesc* in, ObitImageSel* sel)
{
  olong i;

  /* error checks */
  g_assert (ObitIsA(in, ObitImageDescGetClass()));
  g_assert (ObitIsA(sel, &myClassInfo));

  /* minimum axis dimension = 1 */
  for (i=0; i<IM_MAXDIM; i++) in->inaxes[i] = MAX (1,in->inaxes[i]);

  /* default blc = 1 */
  for (i=0; i<IM_MAXDIM; i++) 
    if (sel->blc[i] <= 0) sel->blc[i] = 1;
  for (i=0; i<IM_MAXDIM; i++) 
    if (sel->blc[i] > in->inaxes[i]) sel->blc[i] = in->inaxes[i];

  /* default trc = inaxes */
  for (i=0; i<IM_MAXDIM; i++) 
    if (sel->trc[i] <=0) sel->trc[i] = in->inaxes[i];
  for (i=0; i<IM_MAXDIM; i++) 
    if (sel->trc[i] > in->inaxes[i]) sel->trc[i] = in->inaxes[i];

  /* Index as well */
  ObitImageDescIndex(in);
} /* end ObitImageSelDefault */

/**
 * Apply selection criteria to input descriptor to derive output.
 * \param in Pointer to input descriptor.
 * \param sel Image selector, blc, trc members changed if needed.
 * \param out Pointer to output descriptor.
 * \param err Obit error stack
 */
void ObitImageSelSetDesc (ObitImageDesc* in, ObitImageSel* sel,
			  ObitImageDesc* out, ObitErr *err)
{
  olong i;

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitIsA(in, ObitImageDescGetClass()));
  g_assert (ObitIsA(sel, &myClassInfo));
  g_assert (ObitIsA(out, ObitImageDescGetClass()));

  /* make sure defaults filled in */
  ObitImageSelDefault (in, sel);

  /* copy most values */
  ObitImageDescCopy (in, out, err);
  if (err->error) /* add traceback, return on error */
      Obit_traceback_msg (err, "ObitImageSelSetDesc", 
			  in->name);

  out->naxis = in->naxis;
  /* apply sel->blc, sel->trc */
  for (i=0; i<in->naxis; i++) {
    /* number of axes */
    out->inaxes[i] = sel->trc[i] - sel->blc[i] + 1;
    /* reference pixel */
    out->crpix[i] = in->crpix[i] - sel->blc[i] + 1;
  }

  /* Decrement alternate reference pixel for any selection in frequency */
  if (out->jlocf>=0) {
    out->altCrpix = out->altCrpix - sel->blc[out->jlocf] + 1;
  }

} /* end ObitImageSelSetDesc */

/**
 * Initialize global ClassInfo Structure.
 */
void ObitImageSelClassInit (void)
{
  if (myClassInfo.initialized) return;  /* only once */
  
  /* Set name and parent for this class */
  myClassInfo.ClassName   = g_strdup(myClassName);
  myClassInfo.ParentClass = ObitParentGetClass();

  /* Set function pointers */
  ObitImageSelClassInfoDefFn ((gpointer)&myClassInfo);
 
  myClassInfo.initialized = TRUE; /* Now initialized */
 
} /* end ObitImageSelClassInit */

/**
 * Initialize global ClassInfo Function pointers.
 */
static void ObitImageSelClassInfoDefFn (gpointer inClass)
{
  ObitImageSelClassInfo *theClass = (ObitImageSelClassInfo*)inClass;
  ObitClassInfo *ParentClass = (ObitClassInfo*)myClassInfo.ParentClass;

  if (theClass->initialized) return;  /* only once */

  /* Check type of inClass */
  g_assert (ObitInfoIsA(inClass, (ObitClassInfo*)&myClassInfo));

  /* Initialize (recursively) parent class first */
  if ((ParentClass!=NULL) && 
      (ParentClass->ObitClassInfoDefFn!=NULL))
    ParentClass->ObitClassInfoDefFn(theClass);

  /* function pointers defined or overloaded this class */
  theClass->ObitClassInit = (ObitClassInitFP)ObitImageSelClassInit;
  theClass->ObitClassInfoDefFn = (ObitClassInfoDefFnFP)ObitImageSelClassInfoDefFn;
  theClass->ObitGetClass  = (ObitGetClassFP)ObitImageSelGetClass;
  theClass->newObit       = (newObitFP)newObitImageSel;
  theClass->ObitCopy      = (ObitCopyFP)ObitImageSelCopy;
  theClass->ObitClone     = NULL;
  theClass->ObitClear     = (ObitClearFP)ObitImageSelClear;
  theClass->ObitInit      = (ObitInitFP)ObitImageSelInit;

} /* end ObitImageSelClassDefFn */

/*---------------Private functions--------------------------*/

/**
 * Creates empty member objects, initialize reference count.
 * Does (recursive) initialization of base class members before 
 * this class.
 * \param inn Pointer to the object to initialize.
 */
void ObitImageSelInit  (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitImageSel *in = inn;
  olong i;

  /* error checks */
  g_assert (in != NULL);
  
  /* recursively initialize parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  if ((ParentClass!=NULL) && ( ParentClass->ObitInit!=NULL)) 
    ParentClass->ObitInit (inn);

  /* set members in this class */
  for (i=0; i<IM_MAXDIM; i++) {
    in->blc[i] = 1;
    in->trc[i] = 0;
  }

} /* end ObitImageSelInit */

/**
 * Deallocates member objects.
 * Does (recursive) deallocation of parent class members.
 * \param  inn Pointer to the object to deallocate.
 */
void ObitImageSelClear (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitImageSel *in = inn;

  /* error checks */
  g_assert (ObitIsA(in, &myClassInfo));

  /* free this class members */
  
  /* unlink parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  /* delete parent class members */
  if ((ParentClass!=NULL) && ( ParentClass->ObitClear!=NULL)) 
    ParentClass->ObitClear (inn);

} /* end ObitImageSelClear */


