# $Id$
#-----------------------------------------------------------------------
#  Copyright (C) 2006-2019
#  Associated Universities, Inc. Washington DC, USA.
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License as
#  published by the Free Software Foundation; either version 2 of
#  the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public
#  License along with this program; if not, write to the Free
#  Software Foundation, Inc., 675 Massachusetts Ave, Cambridge,
#  MA 02139, USA.
#
#  Correspondence concerning this software should be addressed as follows:
#         Internet email: bcotton@nrao.edu.
#         Postal address: William Cotton
#                         National Radio Astronomy Observatory
#                         520 Edgemont Road
#                         Charlottesville, VA 22903-2475 USA
#-----------------------------------------------------------------------

# Python package for Obit Table Utilities 
from __future__ import absolute_import
import Obit, Table, Image, OErr

def PCCMerge(inTab, outTab, err):
    """ Merge CC in the same cell

    inTab    = input Python Obit Table
    outTab   = extant output Python Obit Table
    err      = Python Obit Error/message stack
    """
    ################################################################
    # Checks
    if not Table.PIsA(inTab):
        raise TypeError("inTab MUST be a Table")
    if not Table.PIsA(outTab):
        raise TypeError("outTab MUST be a Table")
    if not err.IsA():
        raise TypeError("err MUST be an OErr")
    if err.isErr: # existing error?
        return
    #
    Obit.TableCCUtilMerge(inTab.me, outTab.me, err.me)
    # end PCCMerge

def PConvolve(inFA1, inFA2, err):
    """ Return the convolution of two 2-D arrays

    inFA1 and inFA2 must be compatible size and should not contain magic value blanks.
    Convolved array returned.
    inFA1   = First array
    inFA2   = Second array
    err     = Python Obit Error/message stack
    """
    ################################################################
    # Checks
    if not FArray.PIsA(inFA1):
        raise TypeError("inFA1 MUST be a Python Obit FArray")
    if not FArray.PIsA(inFA2):
        raise TypeError("inFA2 MUST be a Python Obit FArray")
    # 
    outFA = FArray.FArray("None")
    outFA.me = Obit.FArrayUtilConvolve (inFA1.me, inFA2.me, err.me)
    return outFA
    # end PConvolve

def PTableCCT2Spec (inImage, outImage, nTerm,
                    inCCVer, outCCVer, err, startCC=0, endCC=0):
    """ Convert an (tabulated) TSpec CC Table to spectral parameter table

    Output CC Table will have fitted spectra rather than tabulated spectra.
    Tabulated spectrum fitted with spectrum weighting by primary beam
    inImage   input Obit Python Image 1
              Must have freq axis type = "SPECLNMF"
              Optional parameters on List member:
                 "dropNeg" boolean if True drop negative components [True] 
                 "doPBCor" boolean if True Primary beam correct [False] 
    outImage  output Obit Python image must be type ObitImageWB
              This can be created by ImageUtil.PImageT2Spec
    nTerm     Number of output Spectral terms, 2=SI, 3=also curve.
    inCCVer   Input CCTable to convert, 0=> highest
    outCCVer  Output CCTable, 0=>1
    err       Python Obit Error/message stack
    startCC   First 1-rel component to convert
    endCC     Last 1-rel component to convert, 0=> all
    """
    ################################################################
    # Checks
    if not Image.PIsA(inImage):
        raise TypeError("inImage MUST be a Python Obit Image")
    if not Image.PIsA(outImage):
        raise TypeError("outImage MUST be a Python Obit Image")
    if not err.IsA():
        raise TypeError("err MUST be an OErr")
    #
    Obit.TableCCUtilT2Spec(inImage.me, outImage.me, nTerm, inCCVer, \
                           outCCVer, startCC, endCC, err.me)
    if err.isErr:
        OErr.printErrMsg(err, "Error Converting CC Table")
# end PTableCCT2Spec

def PTableCCFixTSpec (inImage, inCCVer, refFreq, nTerm, terms, \
                      err, startCC=1, endCC=0, ):
    """ Convert an (tabulated) TSpec CC Table to spectral parameter table

    Output CC Table will have fitted spectra rather than tabulated spectra.
    Tabulated spectrum fitted with spectrum weighting by primary beam
    inImage   input Obit Python Image 1
              Must have freq axis type = "SPECLNMF"
    inCCVer   CCTable to modify, 0=> highest
    refFreq   Reference frequency for spectrum (Hz)
    nTerm     Number of terms in spectrum
    err       Python Obit Error/message stack
    startCC   First 1-rel component to consider
    endCC     Last 1-rel component to consider, 0=> all
    """
    ################################################################
    # Checks
    if not Image.PIsA(inImage):
        raise TypeError("inImage MUST be a Python Obit Image")
    if not err.IsA():
        raise TypeError("err MUST be an OErr")
    #
    Obit.TableCCUtilFixTSpec(inImage.me, inCCVer, refFreq, nTerm, terms, \
                             startCC, endCC, err.me)
    if err.isErr:
        OErr.printErrMsg(err, "Error Modifying CC Table")
# end PTableCCFixTSpec

def PTableCCAppendShift (inImage, inCCVer, outImage, outCCVer, \
                         uvData, err, startCC=1, endCC=0):
    """ Append one CC table to another correcting for position shift

    inImage   input Obit Python Image
    inCCVer   CCTable to read, 0=> highest
    outImage  output Obit Python Image
    outCCVer  CCTable to modify, 0=> highest
    uvData    uv data used to generate inImage
    err       Python Obit Error/message stack
    startCC   First 1-rel component to consider
    endCC     Last 1-rel component to consider, 0=> all
    """
    ################################################################
    # Checks
    if not Image.PIsA(inImage):
        raise TypeError("inImage MUST be a Python Obit Image")
    if not err.IsA():
        raise TypeError("err MUST be an OErr")
    #
    Obit.TableCCUtilAppendShift(inImage.me, inCCVer, outImage.me, outCCVer, \
                                uvData.me, startCC, endCC, err.me)
    if err.isErr:
        OErr.printErrMsg(err, "Error Modifying CC Table")
# end PTableCCAppendShift

