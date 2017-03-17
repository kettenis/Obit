/* $Id$        */
/*--------------------------------------------------------------------*/
/*;  Copyright (C) 2008,2017                                          */
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

#include "ObitBeamShape.h"
#include "ObitPBUtil.h"
#include "ObitImageMF.h"

/*----------------Obit: Merx mollis mortibus nuper ------------------*/
/**
 * \file ObitBeamShape.c
 * ObitBeamShape class function definitions.
 * This class is derived from the Obit base class.
 */

/** name of the class defined in this file */
static gchar *myClassName = "ObitBeamShape";

/** Function to obtain parent ClassInfo */
static ObitGetClassFP ObitParentGetClass = ObitGetClass;

/**
 * ClassInfo structure ObitBeamShapeClassInfo.
 * This structure is used by class objects to access class functions.
 */
static ObitBeamShapeClassInfo myClassInfo = {FALSE};

/*--------------- File Global Variables  ----------------*/


/*---------------Private function prototypes----------------*/
/** Private: Initialize newly instantiated object. */
void  ObitBeamShapeInit  (gpointer in);

/** Private: Deallocate members. */
void  ObitBeamShapeClear (gpointer in);

/** Private: Set Class function pointers. */
static void ObitBeamShapeClassInfoDefFn (gpointer inClass);

/** Private: Check/set tabulated beam. */
static void FindTabBeam (ObitBeamShape *in);

/** Private: Check/set MeerKat tabulated beam. */
static void MeerKATTabBeam (ObitBeamShape *in);

/** Private: Check/set VLITE tabulated beam. */
static void FindVLITEBeam (ObitBeamShape *in);
 
/** Private: Interpolate tabulated beam. */
static ofloat GetTabBeam (ObitBeamShape *in, odouble Angle);
/*----------------------Public functions---------------------------*/
/**
 * Constructor.
 * Initializes class if needed on first call.
 * \param name An optional name for the object.
 * \return the new object.
 */
ObitBeamShape* newObitBeamShape (gchar* name)
{
  ObitBeamShape* out;

  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitBeamShapeClassInit();

  /* allocate/init structure */
  out = g_malloc0(sizeof(ObitBeamShape));

  /* initialize values */
  if (name!=NULL) out->name = g_strdup(name);
  else out->name = g_strdup("Noname");

  /* set ClassInfo */
  out->ClassInfo = (gpointer)&myClassInfo;

  /* initialize other stuff */
  ObitBeamShapeInit((gpointer)out);

 return out;
} /* end newObitBeamShape */

/**
 * Returns ClassInfo pointer for the class.
 * \return pointer to the class structure.
 */
gconstpointer ObitBeamShapeGetClass (void)
{
  /* Class initialization if needed */
  if (!myClassInfo.initialized) ObitBeamShapeClassInit();

  return (gconstpointer)&myClassInfo;
} /* end ObitBeamShapeGetClass */

/**
 * Make a deep copy of an ObitBeamShape.
 * \param in  The object to copy
 * \param out An existing object pointer for output or NULL if none exists.
 * \param err Obit error stack object.
 * \return pointer to the new object.
 */
ObitBeamShape* ObitBeamShapeCopy  (ObitBeamShape *in, ObitBeamShape *out, ObitErr *err)
{
  const ObitClassInfo *ParentClass;
  gboolean oldExist;
  gchar *outName;

  /* error checks */
  if (err->error) return out;
  g_assert (ObitIsA(in, &myClassInfo));
  if (out) g_assert (ObitIsA(out, &myClassInfo));

  /* Create if it doesn't exist */
  oldExist = out!=NULL;
  if (!oldExist) {
    /* derive object name */
    outName = g_strconcat ("Copy: ",in->name,NULL);
    out = newObitBeamShape(outName);
    g_free(outName);
  }

  /* deep copy any base class members */
  ParentClass = myClassInfo.ParentClass;
  g_assert ((ParentClass!=NULL) && (ParentClass->ObitCopy!=NULL));
  ParentClass->ObitCopy (in, out, err);

  /*  copy this class */
  out->myDesc  = ObitImageRef(in->myDesc);
  out->pbmin   = in->pbmin;
  out->antSize = in->antSize;
  out->doGain  = in->doGain;
  out->doJinc  = in->doJinc;
  out->doTab   = in->doTab;
  out->doVLITE = in->doVLITE;
  out->refFreq = in->refFreq;
  out->itabRefFreq = in->itabRefFreq;
  out->icellSize   = in->icellSize;
  out->myFI        = ObitFInterpolateCopy(in->myFI,  out->myFI, err);
  ObitImageDescGetPoint(out->myDesc, &out->raPnt, &out->decPnt) ;
  out->raPnt      *= DG2RAD;
  out->decPnt     *= DG2RAD;
  return out;
} /* end ObitBeamShapeCopy */

/**
 * Make a copy of a object but do not copy the actual data
 * This is useful to create an BeamShape similar to the input one.
 * \param in  The object to copy
 * \param out An existing object pointer for output, must be defined.
 * \param err Obit error stack object.
 */
void ObitBeamShapeClone  (ObitBeamShape *in, ObitBeamShape *out, ObitErr *err)
{
  const ObitClassInfo *ParentClass;

  /* error checks */
  g_assert (ObitErrIsA(err));
  if (err->error) return;
  g_assert (ObitIsA(in, &myClassInfo));
  g_assert (ObitIsA(out, &myClassInfo));

  /* deep copy any base class members */
  ParentClass = myClassInfo.ParentClass;
  g_assert ((ParentClass!=NULL) && (ParentClass->ObitCopy!=NULL));
  ParentClass->ObitCopy (in, out, err);

  /*  copy this class */
  out->myDesc  = ObitImageRef(in->myDesc);
  out->pbmin   = in->pbmin;
  out->antSize = in->antSize;
  out->doGain  = in->doGain;
  out->refFreq = in->refFreq;
  out->doJinc  = in->doJinc;
  out->doTab   = in->doTab;
  out->doVLITE = in->doVLITE;
  out->refFreq = in->refFreq;
  out->itabRefFreq = in->itabRefFreq;
  out->icellSize   = in->icellSize;
  out->myFI        = ObitFInterpolateCopy(in->myFI,  out->myFI, err);
  ObitImageDescGetPoint(out->myDesc, &out->raPnt, &out->decPnt) ;
  out->raPnt      *= DG2RAD;
  out->decPnt     *= DG2RAD;
} /* end ObitBeamShapeClone */

/**
 * Creates an ObitBeamShape 
 * \param name    An optional name for the object.
 * \param image   Image for which beam shape is desired
 *                Control on info member:
 * \li doTab      If TRUE use tabulated beam if available [def FALSE]
 *                Traps MeerKAT case, uses Tabulated beam
 *                Traps VLITE case, uses Tabulated beam
 * \param pbmin   Minimum gain, lower values will be clipped at this value
 * \param antSize Size of Antenna in (m)
 * \param doGain  If true gain wanted, else gain set to 1.0
 * \return the new object.
 */
ObitBeamShape* ObitBeamShapeCreate (gchar* name, ObitImage *image, 
				    ofloat pbmin, ofloat antSize, 
				    gboolean doGain)
{
  ObitBeamShape* out;
  gboolean doTab=FALSE, isMeerKAT=FALSE, doVLITE=FALSE;
  gint32   dim[MAXINFOELEMDIM] = {1,1,1,1,1};
  ObitInfoType type;

  /* Create basic structure */
  out = newObitBeamShape (name);
  out->myDesc  = ObitImageRef(image->myDesc);
  out->pbmin   = pbmin;
  out->antSize = antSize;
  out->doGain  = doGain;
  out->refFreq = ObitImageMFGetPlaneFreq(image);
  out->doJinc  = out->refFreq >= 1.0e9;
  ObitImageDescGetPoint(out->myDesc, &out->raPnt, &out->decPnt) ;
  out->raPnt  *= DG2RAD;  /* to radians */
  out->decPnt *= DG2RAD;  /* to radians */
  /* tabulated beam? */
  ObitInfoListGetTest(image->info, "doTab", &type, dim, &doTab);
  isMeerKAT = !strncmp(image->myDesc->teles, "MeerKAT",7); /* MeerKAT */
  ObitInfoListGetTest(image->info, "doVLITE", &type, dim, &doVLITE); /* VLITE */
  doVLITE = doVLITE || !strncmp(image->myDesc->instrument, "VLITE",5);
  if (isMeerKAT)    MeerKATTabBeam(out);  /* Always use for MeerKAT */
  else if (doVLITE) FindVLITEBeam(out);   /* Use VLITE beam  */
  else if (doTab)   FindTabBeam(out);     /* Use standard if available */
  return out;
} /* end ObitBeamShapeCreate */

/**
 * Calculate gain in a given direction.
 * Simple function of distance from pointing center.
 * \param in     the BeamShape object
 * \param ra     RA (deg) of direction for gain
 * \param dec    Declination (deg) of direction for gain
 * \param parAng Parallactic angle (rad) NYI
 * \return Gain
 */
ofloat ObitBeamShapeGain (ObitBeamShape *in, odouble ra, odouble dec, 
			  ofloat parAng)
{
  ofloat gain=1.0;
  odouble xx, yy, zz, Angle;

  /* Compute gain? */
  if (!in->doGain) return gain;

  /* get offset */
  xx = DG2RAD * (ra);
  yy = DG2RAD * (dec);
  zz = sin (yy) * sin (in->decPnt) + cos (yy) * cos (in->decPnt) * cos (xx-in->raPnt);
  zz = MIN (zz, 1.000);
  Angle = acos (zz) * RAD2DG;

  /* Compute */
  if (in->doTab)  gain = GetTabBeam (in, Angle);
  else if (in->doJinc) gain = ObitPBUtilJinc(Angle, in->refFreq, in->antSize, in->pbmin);
  else                 gain = ObitPBUtilPoly(Angle, in->refFreq, in->pbmin);
  return gain;
} /* end ObitBeamShapeGain */

/**
 * Calculate gain in a given offset from a symmetric beam shape.
 * Simple function of distance from pointing center.
 * \param in     the BeamShape object
 * \param Angle  Angular distance (deg) from pointing center
 * \return power gain
 */
ofloat ObitBeamShapeGainSym (ObitBeamShape *in, odouble Angle)
{
  ofloat gain=1.0;
  gboolean doKAT=FALSE;

  /* Compute gain? */
  if (!in->doGain) return gain;
  doKAT = !strncmp(in->myDesc->teles, "KAT-7",5); /* Kat-7 */

  /* Compute */
  if (in->doTab)        gain = GetTabBeam (in, Angle);
  else if (in->doVLITE) gain = GetTabBeam (in, Angle);
  else if (doKAT)       gain = ObitPBUtilKAT7 (Angle, in->refFreq, 0.0);
  else if (in->doJinc)  gain = ObitPBUtilJinc(Angle, in->refFreq, in->antSize, in->pbmin);
  else                  gain = ObitPBUtilPoly(Angle, in->refFreq, in->pbmin);
  return gain;
} /* end ObitBeamShapeGainSym */

/**
 * Calculate angular distance from pointing center
 * \param in     the BeamShape object
 * \param ra     RA (deg) of direction for angle
 * \param dec    Declination (deg) of direction for angle
 * \param parAng Parallactic angle (rad) NYI
 * \return Angle from pointing center (deg)
 */
odouble ObitBeamShapeAngle (ObitBeamShape *in, odouble ra, odouble dec, 
			    ofloat parAng)
{
  odouble xx, yy, zz, Angle=0.0;

  /* get offset */
  xx = DG2RAD * (ra);
  yy = DG2RAD * (dec);
  zz = sin (yy) * sin (in->decPnt) + cos (yy) * cos (in->decPnt) * cos (xx-in->raPnt);
  zz = MIN (zz, 1.000);
  Angle = acos (zz) * RAD2DG;
  return Angle;
} /* end ObitBeamShapeAngle */

/**
 * Initialize global ClassInfo Structure.
 */
void ObitBeamShapeClassInit (void)
{
  if (myClassInfo.initialized) return;  /* only once */
  
  /* Set name and parent for this class */
  myClassInfo.ClassName   = g_strdup(myClassName);
  myClassInfo.ParentClass = ObitParentGetClass();

  /* Set function pointers */
  ObitBeamShapeClassInfoDefFn ((gpointer)&myClassInfo);
 
  myClassInfo.initialized = TRUE; /* Now initialized */
 
} /* end ObitBeamShapeClassInit */

/**
 * Initialize global ClassInfo Function pointers.
 */
static void ObitBeamShapeClassInfoDefFn (gpointer inClass)
{
  ObitBeamShapeClassInfo *theClass = (ObitBeamShapeClassInfo*)inClass;
  ObitClassInfo *ParentClass = (ObitClassInfo*)myClassInfo.ParentClass;

  if (theClass->initialized) return;  /* only once */

  /* Check type of inClass */
  g_assert (ObitInfoIsA(inClass, (ObitClassInfo*)&myClassInfo));

  /* Initialize (recursively) parent class first */
  if ((ParentClass!=NULL) && 
      (ParentClass->ObitClassInfoDefFn!=NULL))
    ParentClass->ObitClassInfoDefFn(theClass);

  /* function pointers defined or overloaded this class */
  theClass->ObitClassInit = (ObitClassInitFP)ObitBeamShapeClassInit;
  theClass->newObit       = (newObitFP)newObitBeamShape;
  theClass->ObitClassInfoDefFn = (ObitClassInfoDefFnFP)ObitBeamShapeClassInfoDefFn;
  theClass->ObitGetClass  = (ObitGetClassFP)ObitBeamShapeGetClass;
  theClass->ObitCopy      = (ObitCopyFP)ObitBeamShapeCopy;
  theClass->ObitClone     = NULL;
  theClass->ObitClear     = (ObitClearFP)ObitBeamShapeClear;
  theClass->ObitInit      = (ObitInitFP)ObitBeamShapeInit;
  theClass->ObitBeamShapeCreate = (ObitBeamShapeCreateFP)ObitBeamShapeCreate;
  theClass->ObitBeamShapeGain   = (ObitBeamShapeGainFP)ObitBeamShapeGain;
  theClass->ObitBeamShapeGainSym= (ObitBeamShapeGainSymFP)ObitBeamShapeGainSym;
  theClass->ObitBeamShapeAngle  = (ObitBeamShapeAngleFP)ObitBeamShapeAngle;

} /* end ObitBeamShapeClassDefFn */

/*---------------Private functions--------------------------*/

/**
 * Creates empty member objects, initialize reference count.
 * Parent classes portions are (recursively) initialized first
 * \param inn Pointer to the object to initialize.
 */
void ObitBeamShapeInit  (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitBeamShape *in = inn;

  /* error checks */
  g_assert (in != NULL);

  /* recursively initialize parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  if ((ParentClass!=NULL) && ( ParentClass->ObitInit!=NULL)) 
    ParentClass->ObitInit (inn);

  /* set members in this class */
  in->myDesc     = NULL;
  in->myFI       = NULL;
  in->pbmin      = 0.0;
  in->antSize    = 0.0;
  in->icellSize  = 0.0;
  in->doGain     = FALSE;
  in->raPnt      = 0.0;
  in->decPnt     = 0.0;
  in->refFreq    = 0.0;
  in->itabRefFreq= 0.0;
  in->doJinc     = FALSE;
  in->doTab      = FALSE;
} /* end ObitBeamShapeInit */

/**
 * Deallocates member objects.
 * Does (recursive) deallocation of parent class members.
 * \param  inn Pointer to the object to deallocate.
 *           Actually it should be an ObitBeamShape* cast to an Obit*.
 */
void ObitBeamShapeClear (gpointer inn)
{
  ObitClassInfo *ParentClass;
  ObitBeamShape *in = inn;

  /* error checks */
  g_assert (ObitIsA(in, &myClassInfo));

  /* delete this class members */
  in->myDesc  = ObitImageDescUnref(in->myDesc);
  in->myFI    = ObitFInterpolateUnref(in->myFI);

  /* unlink parent class members */
  ParentClass = (ObitClassInfo*)(myClassInfo.ParentClass);
  /* delete parent class members */
  if ((ParentClass!=NULL) && ( ParentClass->ObitClear!=NULL)) 
    ParentClass->ObitClear (inn);
  
} /* end ObitBeamShapeClear */

/**
 * Check if a tabulated beam is available and if so enable it
 * Currently implemented: VLA P, S Band, C Band
 * \param in     the BeamShape object
 */
static void FindTabBeam (ObitBeamShape *in)
{
  olong i, j, itab, ndim=1, naxis[] = {1};
  ObitFArray *tFA = NULL;
  olong   ntab   = 3;            /* How many tables? */
  olong   hwidth = 2;            /* Interpolation half width */
  /*                      P      S       C */
  odouble minFreq[] = {200.0e6, 1.8e9, 2.0e9, };  /* Lower bound of bands */
  odouble maxFreq[] = {500.0e6, 3.8e9, 7.8e9, };  /* Upper  bound of bands */
  odouble refFreq[] = {340.0e6, 3.0e9, 6.0e9, };  /* Tabulated reference freq */

  /* Have a tabulated beam? */
  in->doTab = FALSE;
  itab = -1;  /* Which beam */
  for (i=0; i<ntab; i++) {
    if ((in->refFreq>=minFreq[i]) && (in->refFreq<=maxFreq[i])) {
      itab = i;
      break;
    }
  }
  /* Find one? */
  if (itab<0) return; /* Nope */
  /* Fill in details */
  switch (itab) {
  case 0:     /* P band */
    in->itabRefFreq = 1.0/refFreq[itab]; /* 1/tabulated ref freq */
    in->icellSize   = 3600.0/250.0;     /* 1/Tabulated cell spacing */
    olong  Pncell   = 300;
    /* 10 Nov2015, P Band 300 entries  cell 250.0/3600, refFreq  = 340.0e6 */
    ofloat Pbeam[]  = {    /* Fitted to beam */
      1.000000, 0.998248, 0.993048, 0.984058, 0.970796, 0.955100, 0.939748, 0.912643, 0.886224,
      0.867500, 0.830706, 0.793851, 0.771507, 0.747092, 0.722266, 0.695144, 0.666975, 0.638199,
      0.608038, 0.577563, 0.546267, 0.514786, 0.483709, 0.451885, 0.421084, 0.391206, 0.361235,
      0.332097, 0.303311, 0.275288, 0.248056, 0.220403, 0.193054, 0.166338, 0.138971, 0.112269,
      0.086202, 0.061056, 0.035924, 0.012253,-0.011110,-0.033139,-0.056696,-0.074705,-0.091836,
     -0.108188,-0.119736,-0.130505,-0.138099,-0.144492,-0.148338,-0.152569,-0.154990,-0.157243,
     -0.158610,-0.159265,-0.159365,-0.158356,-0.156740,-0.154839,-0.153190,-0.151059,-0.148089,
     -0.144850,-0.141322,-0.137659,-0.133187,-0.128910,-0.124340,-0.119538,-0.114051,-0.108139,
     -0.103371,-0.098704,-0.093910,-0.089438,-0.084935,-0.080243,-0.075727,-0.071550,-0.067402,
     -0.062761,-0.058984,-0.055482,-0.052036,-0.048765,-0.045855,-0.043183,-0.041011,-0.039075,
     -0.037319,-0.035561,-0.033798,-0.032735,-0.031881,-0.031131,-0.030240,-0.029644,-0.029222,
     -0.028921,-0.028558,-0.028655,-0.028869,-0.029189,-0.029516,-0.030054,-0.030669,-0.031355,
     -0.032283,-0.033223,-0.034139,-0.034954,-0.035681,-0.036417,-0.037149,-0.037820,-0.038435,
     -0.038967,-0.039466,-0.039883,-0.040226,-0.040512,-0.040651,-0.040659,-0.040359,-0.040056,
     -0.039284,-0.038972,-0.038596,-0.038105,-0.037470,-0.036376,-0.035456,-0.033998,-0.032957,
     -0.031710,-0.030480,-0.029148,-0.027525,-0.025789,-0.024095,-0.022282,-0.020765,-0.019174,
     -0.017573,-0.015583,-0.013725,-0.012100,-0.010378,-0.008902,-0.007481,-0.006150,-0.004723,
     -0.003377,-0.002155,-0.001147,-0.000536, 0.000203, 0.000865, 0.001340, 0.001923, 0.002231,
      0.002408, 0.002378, 0.002177, 0.001899, 0.001426, 0.001066, 0.000533, 0.000073,-0.000631,
     -0.001448,-0.002298,-0.003168,-0.003954,-0.004920,-0.005864,-0.006699,-0.007743,-0.008659,
     -0.009452,-0.010132,-0.010690,-0.011086,-0.011309,-0.011851,-0.012474,-0.012585,-0.012583,
     -0.012258,-0.011698,-0.010891,-0.010301,-0.009587,-0.008786,-0.007685,-0.006226,-0.004800,
     -0.003321,-0.002036,-0.000653, 0.000758, 0.002152, 0.003543, 0.004861, 0.006130, 0.007524,
      0.008955, 0.010038, 0.011105, 0.013919, 0.014813, 0.015765, 0.016394, 0.016900, 0.017360,
      0.017642, 0.018007, 0.018134, 0.018125, 0.018098, 0.017966, 0.017623, 0.017367, 0.017176,
      0.016799, 0.016424, 0.015927, 0.015253, 0.014508, 0.013456, 0.012689, 0.011830, 0.011033,
      0.010307, 0.009657, 0.009023, 0.008565, 0.007511, 0.006803, 0.006060, 0.005279, 0.004655,
      0.004088, 0.003540, 0.003182, 0.003064, 0.002707, 0.002566, 0.002285, 0.002189, 0.002264,
      0.002423, 0.002526, 0.002785, 0.003154, 0.003435, 0.003552, 0.004070, 0.005006, 0.005364,
      0.005837, 0.006182, 0.006740, 0.007079, 0.007322, 0.007627, 0.007587, 0.007766, 0.007941,
      0.008522, 0.008887, 0.008494, 0.008300, 0.008574, 0.008664, 0.008907, 0.009141, 0.009420,
      0.009731, 0.009579, 0.009681, 0.009798, 0.008858, 0.007708, 0.007665, 0.007506, 0.007470,
      0.007620, 0.007608, 0.007569, 0.006601, 0.006494, 0.006344, 0.005570, 0.006879, 0.006602,
      0.007726, 0.007875};
    naxis[0] = Pncell;   /* Create/fill FArray with beam shape for interpolator */
    tFA = ObitFArrayCreate("TempFA", ndim, naxis);
    for (j=0; j<Pncell; j++) tFA->array[j] = Pbeam[j]*Pbeam[j];  /* Voltage to power */
    in->myFI = newObitFInterpolateCreate ("Interp", tFA, in->myDesc, hwidth);
    tFA = ObitFArrayUnref(tFA);    /* Unreference temp FA */
    break;
  case 1:     /* S band */
    in->itabRefFreq = 1.0/refFreq[itab]; /* 1/tabulated ref freq */
    in->icellSize   = 3600.0/30.0;       /* 1/Tabulated cell spacing */
    olong  Sncell  = 250;
    /* 15 Dec 15 S Band 250 entries, cell 30.0/3600, refFreq  = 3.0e9 */
    ofloat Sbeam[] = {    /* Fitted to voltage beam */
       1.000000, 0.997801, 0.991191, 0.979534, 0.963917, 0.945477, 0.925469, 0.902924,
       0.877989, 0.850618, 0.820960, 0.788785, 0.754457, 0.718072, 0.679851, 0.639915,
       0.598547, 0.556108, 0.512954, 0.469143, 0.425074, 0.381071, 0.337314, 0.293631,
       0.251205, 0.210151, 0.170330, 0.131907, 0.095075, 0.060002, 0.026808,-0.004369,
      -0.033414,-0.060111,-0.084383,-0.106189,-0.125516,-0.142382,-0.156810,-0.168836,
      -0.178508,-0.185931,-0.191124,-0.194186,-0.195177,-0.194241,-0.191455,-0.186927,
      -0.180851,-0.173404,-0.164744,-0.155074,-0.144559,-0.133349,-0.121636,-0.109558,
      -0.097257,-0.084910,-0.072642,-0.060605,-0.048917,-0.037715,-0.027097,-0.017189,
      -0.008081, 0.000135, 0.007436, 0.013753, 0.019071, 0.023365, 0.026618, 0.028834,
       0.030028, 0.030255, 0.029542, 0.027926, 0.025465, 0.022204, 0.018204, 0.013505,
       0.008183, 0.002350,-0.003892,-0.010405,-0.017047,-0.023758,-0.030407,-0.036969,
      -0.043382,-0.049580,-0.055471,-0.060975,-0.066024,-0.070577,-0.074561,-0.078006,
      -0.080809,-0.082940,-0.084391,-0.085216,-0.085304,-0.084722,-0.083528,-0.081607,
      -0.079001,-0.075808,-0.072112,-0.067903,-0.063302,-0.058277,-0.052895,-0.047243,
      -0.041358,-0.035287,-0.029134,-0.022834,-0.016636,-0.010580,-0.004612, 0.001007,
       0.006283, 0.011364, 0.015945, 0.020120, 0.024015, 0.027299, 0.030071, 0.032507,
       0.034261, 0.035475, 0.036158, 0.036473, 0.036126, 0.035281, 0.034121, 0.032342,
       0.030147, 0.027706, 0.024814, 0.021625, 0.018355, 0.014773, 0.011045, 0.007359,
       0.003429,-0.000425,-0.004357,-0.008201,-0.011823,-0.015388,-0.018852,-0.021985,
      -0.024917,-0.027582,-0.029917,-0.031863,-0.033594,-0.034882,-0.035838,-0.036543,
      -0.036923,-0.036918,-0.036655,-0.036032,-0.035119,-0.034013,-0.032658,-0.031008,
      -0.029239,-0.027303,-0.025200,-0.022939,-0.020680,-0.018365,-0.015953,-0.013662,
      -0.011393,-0.009033,-0.006836,-0.004746,-0.002665,-0.000855, 0.000758, 0.002372,
       0.003605, 0.004623, 0.005435, 0.006260, 0.006732, 0.007053, 0.007470, 0.007507,
       0.007187, 0.006721, 0.006158, 0.005485, 0.004737, 0.003936, 0.003081, 0.002209,
       0.001331, 0.000459,-0.000365,-0.001158,-0.001882,-0.002531,-0.003091,-0.003569,
      -0.003950,-0.004220,-0.004365,-0.004399,-0.004327,-0.004131,-0.003800,-0.003388,
      -0.002845,-0.002230,-0.001516,-0.000734, 0.000109, 0.001006, 0.001937, 0.002879,
       0.003840, 0.004793, 0.005728, 0.006657, 0.007614, 0.008493, 0.009317, 0.010081,
       0.010751, 0.011335, 0.011832, 0.012213, 0.012516, 0.012726, 0.012827, 0.012838,
       0.012723, 0.012484, 0.012118, 0.011647, 0.011070, 0.010442, 0.009695, 0.008852,
       0.007935, 0.006959};
    naxis[0] = Sncell;   /* Create/fill FArray with beam shape for interpolator */
    tFA = ObitFArrayCreate("TempFA", ndim, naxis);
    for (j=0; j<Sncell; j++) tFA->array[j] = Sbeam[j]*Sbeam[j];  /*  Voltage to power */
    in->myFI = newObitFInterpolateCreate ("Interp", tFA, in->myDesc, hwidth);
    tFA = ObitFArrayUnref(tFA);    /* Unreference temp FA */
   break;
  case 2:     /* C band */
    in->itabRefFreq = 1.0/refFreq[itab]; /* 1/tabulated ref freq */
    /* 17 Mar 17 C Band 290 entries, cell 15.0/3600, refFreq  = 6.0e9 */
    in->icellSize   = 3600.0/15.000000;
    olong  Cncell  = 290;
    ofloat Cbeam[] = {    /* Fitted to voltage beam */
      1.000350,   0.998689,   0.993724,   0.985498,   0.973971,   0.959182,   0.941439,   0.920737,
      0.897211,   0.871018,   0.842357,   0.811418,   0.778478,   0.743635,   0.707077,   0.669131,
      0.629947,   0.589735,   0.548718,   0.507120,   0.465189,   0.423077,   0.381107,   0.339505,
      0.298470,   0.258229,   0.218980,   0.180967,   0.144222,   0.108930,   0.075163,   0.043060,
      0.012831,  -0.015431,  -0.041598,  -0.065376,  -0.086698,  -0.105532,  -0.121901,  -0.135882,
     -0.147613,  -0.157138,  -0.164639,  -0.170134,  -0.173671,  -0.175346,  -0.175248,  -0.173557,
     -0.170279,  -0.165598,  -0.159672,  -0.152718,  -0.144820,  -0.136138,  -0.126740,  -0.116748,
     -0.106307,  -0.095539,  -0.084594,  -0.073507,  -0.062515,  -0.051752,  -0.041402,  -0.031635,
     -0.022571,  -0.014344,  -0.006967,  -0.000480,   0.005138,   0.009880,   0.013763,   0.016753,
      0.018863,   0.020092,   0.020430,   0.019898,   0.018556,   0.016423,   0.013549,   0.010023,
      0.005847,   0.001160,  -0.004044,  -0.009650,  -0.015530,  -0.021588,  -0.027755,  -0.033964,
     -0.040104,  -0.046120,  -0.052003,  -0.057623,  -0.062913,  -0.067838,  -0.072351,  -0.076366,
     -0.079880,  -0.082838,  -0.085234,  -0.087039,  -0.088243,  -0.088845,  -0.088851,  -0.088268,
     -0.087103,  -0.085368,  -0.083106,  -0.080324,  -0.077052,  -0.073324,  -0.069193,  -0.064728,
     -0.059918,  -0.054857,  -0.049595,  -0.044171,  -0.038677,  -0.033149,  -0.027701,  -0.022370,
     -0.017262,  -0.012378,  -0.007757,  -0.003434,   0.000552,   0.004199,   0.007483,   0.010392,
      0.012885,   0.014956,   0.016581,   0.017759,   0.018489,   0.018796,   0.018903,   0.018512,
      0.017863,   0.016814,   0.015485,   0.013941,   0.011979,   0.009903,   0.007502,   0.004883,
      0.002277,  -0.000632,  -0.003411,  -0.006362,  -0.009319,  -0.012100,  -0.014923,  -0.017518,
     -0.020103,  -0.022367,  -0.024538,  -0.026481,  -0.027951,  -0.029381,  -0.030606,  -0.031367,
     -0.031981,  -0.032190,  -0.032213,  -0.031953,  -0.031302,  -0.030483,  -0.029300,  -0.027989,
     -0.026467,  -0.024626,  -0.022865,  -0.020584,  -0.018423,  -0.016172,  -0.013752,  -0.011412,
     -0.008928,  -0.006622,  -0.004335,  -0.002441,  -0.000506,   0.001317,   0.003012,   0.004379,
      0.005716,   0.006866,   0.007819,   0.008569,   0.009113,   0.009451,   0.009594,   0.009390,
      0.009149,   0.008787,   0.008259,   0.007574,   0.006775,   0.005775,   0.004747,   0.003675,
      0.002555,   0.001404,   0.000246,  -0.001042,  -0.002126,  -0.003209,  -0.004383,  -0.005467,
     -0.006460,  -0.007324,  -0.008082,  -0.008705,  -0.009183,  -0.009527,  -0.009720,  -0.009773,
     -0.009662,  -0.009422,  -0.009033,  -0.008501,  -0.007880,  -0.007124,  -0.006299,  -0.005404,
     -0.004375,  -0.003316,  -0.002270,  -0.001127,   0.000002,   0.001097,   0.002222,   0.003299,
      0.004321,   0.005297,   0.006210,   0.007030,   0.007745,   0.008364,   0.008886,   0.009255,
      0.009526,   0.009641,   0.009662,   0.009552,   0.009259,   0.008934,   0.008402,   0.007737,
      0.007158,   0.006338,   0.005404,   0.004584,   0.003525,   0.002366,   0.001399,   0.000168,
     -0.001141,  -0.002132,  -0.003033,  -0.004171,  -0.004998,  -0.005960,  -0.006658,  -0.007358,
     -0.007868,  -0.008244,  -0.008430,  -0.008432,  -0.008532,  -0.008334,  -0.007884,  -0.007801,
     -0.007298,  -0.006688,  -0.006515,  -0.005689,  -0.004932,  -0.004692,  -0.003673,  -0.002620,
     -0.002201,  -0.001030,  -0.000652,   0.000838,   0.002058,   0.002403,   0.003789,   0.004832,
      0.005110,   0.000000};
    naxis[0] = Cncell;   /* Create/fill FArray with beam shape for interpolator */
    tFA = ObitFArrayCreate("TempFA", ndim, naxis);
    for (j=0; j<Cncell; j++) tFA->array[j] = Cbeam[j]*Cbeam[j];  /*  Voltage to power */
    in->myFI = newObitFInterpolateCreate ("Interp", tFA, in->myDesc, hwidth);
    tFA = ObitFArrayUnref(tFA);    /* Unreference temp FA */
   break;
  default:    /* Doh */
    return;
  }; /* end switch */
  in->doTab = TRUE;    /* Must be OK if it gets here */
} /* end FindTabBeam */

/**
 * Set MeerKAT tabulated beam
 * \param in     the BeamShape object
 */
static void MeerKATTabBeam (ObitBeamShape *in)
{
  olong i, j, itab, ndim=1, naxis[] = {1};
  ObitFArray *tFA = NULL;
  olong   ntab   = 1;            /* How many? */
  olong   hwidth = 2;            /* Interpolation half width */
  /*                    */
  odouble minFreq[] = { 800.0e6};  /* Lower bound of bands */
  odouble maxFreq[] = {2000.0e6};  /* Upper  bound of bands */
  odouble refFreq[] = {1350.0e6};  /* Tabulated reference freq */

  /* Have a tabulated beam? */
  in->doTab = FALSE;
  itab = -1;  /* Which beam */
  for (i=0; i<ntab; i++) {
    if ((in->refFreq>=minFreq[i]) && (in->refFreq<=maxFreq[i])) {
      itab = i;
      break;
    }
  }
  /* Find one? */
  if (itab<0) return; /* Nope */
  /* Fill in details */
  switch (itab) {
  case 0:     /* 1.35 GHz beam */
    in->itabRefFreq = 1.0/refFreq[itab]; /* 1/tabulated ref freq */
    in->icellSize   = 3600.0/30.0;       /* 1/Tabulated cell spacing */
    /* 26 Jul 16 S MeerKAT 1.3-1.4 GHz, cell 30.0/3600, refFreq  = 1.35e9 */
    olong  MKncell  = 175;
    ofloat MKbeam[] = {    /* Fitted to voltage beam */
      1.000000,0.999920,0.999679,0.999278,0.998717,0.997996,0.997116,0.996075,0.994876,0.993518,
      0.992002,0.990328,0.988497,0.986509,0.984365,0.982066,0.979612,0.977006,0.974246,0.971334,
      0.968272,0.965059,0.961697,0.958187,0.954532,0.950731,0.946786,0.942698,0.938469,0.934100,
      0.929591,0.924946,0.920166,0.915252,0.910205,0.905028,0.899722,0.894288,.888729, 0.883045,
      0.877241,0.871318,0.865278,0.859118,0.852851,0.846466,0.839977,0.833374,0.826673,0.819866,
      0.812954,0.805952,0.798846,0.791648,0.784367,0.776988,0.769525,0.761978,0.754352,0.746645,
      0.738862,0.731004,0.723075,0.715081,0.707017,0.698888,0.690705,0.682462,0.674161,0.665812,
      0.657410,0.648964,0.640473,0.631937,0.623368,0.614762,0.606119,0.597448,0.588752,0.580035, 
      0.571291,0.562529,0.553751,0.544967,0.536166,0.527358,0.518550,0.509741,0.500926,0.492125,
      0.483325,0.474535,0.465762,0.457003,0.448264,0.439542,0.430849,0.422179,0.413538,0.404930,
      0.396351,0.387820,0.379324,0.370871,0.362465,0.354103,0.345796,0.337535,0.329336,0.321190,
      0.313106,0.305086,0.297133,0.289241,0.281423,0.273674,0.265988,0.258370,0.250832,0.243372,
      0.235992,0.228700,0.221495,0.214373,0.207335,0.200393,0.193529,0.186762,0.180058,0.173477,
      0.166996,0.160628,0.154340,0.148136,0.142154,0.136344,0.130664,0.125113,0.119700,0.114493,
      0.109589,0.105007,0.100781,0.096646,0.092559,0.088636,0.085108,0.081382,0.077876,0.073577,
      0.069953,0.066347,0.062494,0.058545,0.055008,0.051969,0.047982,0.044959,0.042908,0.041673,
      0.039321,0.038724,0.038647,0.039247,0.040620,0.042692,0.045443,0.048629,0.049098,0.052326,
      0.056978,0.052184,0.054663,0.056593,0.059868};
    naxis[0] = MKncell;   /* Create/fill FArray with beam shape for interpolator */
    tFA = ObitFArrayCreate("TempFA", ndim, naxis);
    for (j=0; j<MKncell; j++) tFA->array[j] = MKbeam[j]*MKbeam[j];  /*  Voltage to power */
    in->myFI = newObitFInterpolateCreate ("Interp", tFA, in->myDesc, hwidth);
    tFA = ObitFArrayUnref(tFA);    /* Unreference temp FA */
    break;
  default:    /* Doh */
    return;
  }; /* end switch */
  in->doTab = TRUE;    /* Must be OK if it gets here */
} /* end MeerKATabBeam */

/**
 * Set MeerKAT tabulated beam
 * Add Tabulated Power Beam for VLITE use on PBCorr only
 *  Might be valid for eVLA Pband PBCorr as well
 *  Should not be used for normalizing asymmetric beam correctiosn
 *  \param in   the BeamShape object
 */
static void FindVLITEBeam (ObitBeamShape *in)
{
   olong j, ndim=1, naxis[] = {1};
   ObitFArray *tFA = NULL;
   /* olong   ntab   = 1;            How many? */
   olong   hwidth = 2;            /* Interpolation half width */
  /*                    P       */
  /*odouble minFreq[] = {320.0e6};   Lower bound of bands */
  /*odouble maxFreq[] = {364.0e6};   Upper  bound of bands */
  odouble refFreq[] = {340.85e6};  /* Tabulated reference freq */
  in->itabRefFreq = 1.0/refFreq[0]; /* 1/tabulated ref freq */
  in->icellSize   = 3600.0/60.0;     /* 1/Tabulated cell spacing */
  olong  Pncell   = 305;
  /* 6 June 2016  tabulated entries at 60 arcsec from fits to VLITE Data  */
  ofloat Pbeam[]  = {     /* extrapolated beyond 4 degrees */
    1.000000, 0.999878, 0.999510, 0.998898, 0.998042, 0.996943, 0.995600, 0.994017, 
    0.992192, 0.990128, 0.987827, 0.985289, 0.982518, 0.979514, 0.976280, 0.972819, 
    0.969132, 0.965223, 0.961094, 0.956748, 0.952189, 0.947420, 0.942443, 0.937263, 
    0.931883, 0.926307, 0.920539, 0.914583, 0.908443, 0.902123, 0.895627, 0.888961,
    0.882128, 0.875133, 0.867981, 0.860677, 0.853225, 0.845630, 0.837898, 0.830033, 
    0.822040, 0.813925, 0.805693, 0.797349, 0.788898, 0.780345, 0.771696, 0.762956, 
    0.754130, 0.745223, 0.736242, 0.727190, 0.718074, 0.708899, 0.699669, 0.690391, 
    0.681068, 0.671707, 0.662312, 0.652889, 0.643442, 0.633977, 0.624498, 0.615009, 
    0.605517, 0.596025, 0.586539, 0.577061, 0.567598, 0.558154, 0.548732, 0.539337, 
    0.529973, 0.520216, 0.511762, 0.503513, 0.495461, 0.487594, 0.479860, 0.472211, 
    0.464602, 0.457008, 0.449412, 0.441815, 0.434249, 0.426702, 0.419148, 0.411588, 
    0.404046, 0.396562, 0.389173, 0.381904, 0.374788, 0.367862, 0.361166, 0.354740, 
    0.348596, 0.342691, 0.336999, 0.331508, 0.326200, 0.321041, 0.315993, 0.310997, 
    0.306006, 0.301010, 0.296015, 0.291027, 0.286066, 0.281138, 0.276259, 0.271462, 
    0.266785, 0.262279, 0.257999, 0.253991, 0.250247, 0.246743, 0.243471, 0.240415, 
    0.237547, 0.234840, 0.232247, 0.229724, 0.227250, 0.224829, 0.222460, 0.220124, 
    0.217801, 0.215473, 0.213142, 0.210840, 0.208615, 0.206543, 0.204695, 0.203071, 
    0.201650, 0.200431, 0.199443, 0.198684, 0.198089, 0.197593, 0.197155, 0.196772, 
    0.196469, 0.196265, 0.196165, 0.196158, 0.196211, 0.196283, 0.196370, 0.196456, 
    0.196508, 0.196493, 0.196381, 0.196145, 0.195762, 0.195209, 0.194474, 0.193558, 
    0.192453, 0.191135, 0.189614, 0.187899, 0.186036, 0.184078, 0.182076, 0.180053, 
    0.178012, 0.175960, 0.173921, 0.171933, 0.170017, 0.168171, 0.166373, 0.164585, 
    0.162761, 0.160912, 0.159070, 0.157270, 0.155546, 0.153908, 0.152345, 0.150844, 
    0.149398, 0.147996, 0.146621, 0.145267, 0.143926, 0.142593, 0.141266, 0.139946, 
    0.138640, 0.137347, 0.136058, 0.134761, 0.133446, 0.132103, 0.130722, 0.129305, 
    0.127858, 0.126383, 0.124879, 0.123340, 0.121757, 0.120120, 0.118419, 0.116645, 
    0.114804, 0.112903, 0.110950, 0.108962, 0.106957, 0.104948, 0.102953, 0.100984, 
    0.099052, 0.097169, 0.095345, 0.093592, 0.091916, 0.090322, 0.088818, 0.087409, 
    0.086097, 0.084879, 0.083751, 0.082710, 0.081753, 0.080875, 0.080070, 0.079334, 
    0.078660, 0.078042, 0.077474, 0.076950, 0.076461, 0.075996, 0.075544, 0.075095, 
    0.074642, 0.074184, 0.073720, 0.073249, 0.072772, 0.072287, 0.071795, 0.071295, 
    0.070788, 0.070276, 0.069758, 0.069235, 0.068709, 0.068179, 0.067645, 0.067108, 
    0.066569, 0.066028, 0.065484, 0.064940, 0.064394, 0.063847, 0.063301, 0.062754, 
    0.062207, 0.061660, 0.061113, 0.060566, 0.060020, 0.059473, 0.058926, 0.057779,
    0.057232, 0.056685, 0.056138, 0.055591, 0.055044, 0.054497, 0.053950, 0.053403, 
    0.052856, 0.052309, 0.051762, 0.051215, 0.050668, 0.050121, 0.049574, 0.049027,
    0.048480, 0.047933, 0.047386, 0.046839, 0.046292, 0.045745, 0.045198, 0.044651,
    0.044104, 0.043557, 0.043010, 0.042463, 0.041916, 0.041369, 0.040822, 0.040275,
    0.039728};
  naxis[0] = Pncell;   /* Create/fill FArray with beam shape for interpolator */
  tFA = ObitFArrayCreate("TempFA", ndim, naxis);
  for (j=0; j<Pncell; j++) tFA->array[j] = Pbeam[j];  
  in->myFI = newObitFInterpolateCreate ("Interp", tFA, in->myDesc, hwidth);
  tFA = ObitFArrayUnref(tFA);    /* Unreference temp FA */
    
  in->doVLITE = TRUE;    /* Must be OK if it gets here */
} /* end FindVLITEBeam */

/**
 * Check if a tabulated beam is available and if so enable it
 * Currently implemented: VLA S Band, P Band
 * Returns pbmin if out of tabulated beam shape
 * \param in  the BeamShape object
 * \param in  Angle from pointing in degrees
 * \return  beam power gain
 */
static ofloat GetTabBeam (ObitBeamShape *in, odouble Angle)
{
  ofloat pixel;
  pixel = 1.0+Angle*in->icellSize*in->itabRefFreq*in->refFreq;
  if (pixel<=1.1) return 1.0;                /* Trap center */
  if (pixel>in->myFI->nx) return in->pbmin;  /* Beyond tabulation */
  return ObitFInterpolate1D(in->myFI, pixel);
} /* end GetTabBeam */
