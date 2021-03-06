# Python interface to Obit GPU float array class.
# $Id:  $
""" 
Python Obit GPU multidimensional array of float class

This class is A limited subset of FArray used to communicate data to GPU memory.

Virtual (read only) members

======  ==============================================
Ndim    Number of axes in array
Naxis   list of axis dimensions (by storage order)
======  ==============================================
"""
#-----------------------------------------------------------------------
#  Copyright (C) 2014,2019
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

# Python shadow class to ObitGPUFArray class
from __future__ import absolute_import
from __future__ import print_function
import Obit, _Obit, InfoList, OErr

class GPUFArray(Obit.GPUFArray):
    """ 
    Python Obit multidimensional array of float class
    
    This class is for moving FArrays between host and GPU memory
    
    Virtual (read only) members
    
    ======  ==============================================
    Ndim    Number of axes in array
    Naxis   list of axis dimensions (by storage order)
    ======  ==============================================
    """
    def __init__(self, name, naxis=[1]):
        ndim = len(naxis)
        super(GPUFArray, self).__init__()
        lnaxis =[int(naxis[0])]
        if len(naxis)>1:
            lnaxis.append(int(naxis[1]))
        if len(naxis)>2:
            lnaxis.append(int(naxis[2]))
        Obit.CreateGPUFArray(self.this, name, int(ndim), lnaxis)
    def __del__(self, DeleteGPUFArray=_Obit.DeleteGPUFArray):
        if _Obit!=None:
            DeleteGPUFArray(self.this)
    def __setattr__(self,name, value):
        if name == "me" :
            # Out with the old
            if self.this!=None:
                Obit.GPUFArrayUnref(Obit.GPUFArray_Get_me(self.this))
            # In with the new
            Obit.GPUFArray_Set_me(self.this,value)
            return
        self.__dict__[name] = value
    def __getattr__(self,name):
        if not isinstance(self, GPUFArray):
            return  "Bogus Dude"+str(self.__class__)
        if name == "me" : 
            return Obit.GPUFArray_Get_me(self.this)
        if name=="List":
            out    = InfoList.InfoList()
            out.me = Obit.GPUFArrayGetList(self.me)
            return out
        # Virtual members
        if name=="Ndim":
            return PGetNdim(self)
        if name=="Naxis":
            return PGetNaxis(self)
        raise AttributeError(str(name))
    def __repr__(self):
        if not isinstance(self, GPUFArray):
            return  "Bogus Dude"+str(self.__class__)
        return "<C GPUFArray instance> " + Obit.GPUFArrayGetName(self.me)
# end GPUFArray class     

def PCreate(inFA):
    """ 
    Create a GPUFArray from an FArray

    Returns new object
    * inFA  = input Obit Python FArray
    """
    ################################################################
    return GPUFArray("GPUFArray", inFA.Ndim, inFA.Naxis)
# end PCreate

def PToData(inGFA, data, err):
    """ 
    Copy host array to data

    Copys data from GPUFArray locked host array to data
    * inFA  = input Python GPUFArray
    * data  = FArray containing data array
    * err   = Obit error/message stack
    """
    ################################################################
    return Obit.GPUFArrayToData (inFA.me, data.me, err.me)
# end PToData

def PFromData(inGFA, data, err):
    """ 
    Copy from data to host GPUFArray

    Copys data from data to GPUFArray locked host array
    * inFA  = input Python GPUFArray
    * data  = FArray containing data array
    * err   = Obit error/message stack
    """
    ################################################################
    return Obit.GPUFArrayFromData (inFA.me, data.me, err.me)
# end PFromData

def PToGPU(inGFA, err):
    """ 
    Copy data array from host to GPU

    * inFA  = input Python GPUFArray
    * err   = Obit error/message stack
    """
    ################################################################
    return Obit.GPUFArrayToGPU (inFA.me, err.me)
# end PToGPU

def PToHost(inGFA, err):
    """ 
    Copy data array from GPU to host

    * inFA  = input Python GPUFArray
    * err   = Obit error/message stack
    """
    ################################################################
    return Obit.GPUFArrayToHost (inFA.me, err.me)
# end PToHost

def PCopy (inFA, err):
    """  
    Make copy an GPUFArray
    
    returns copy
    
    * inFA = input Python GPUFArray
    * err  = Python Obit Error/message stack
    """
    ################################################################
    # Checks
    if not PIsA(inFA):
        print("Actually ",inFA.__class__)
        raise TypeError("inFA MUST be a Python Obit GPUFArray")
    outFA = GPUFArray("None")
    outFA.me = Obit.GPUFArrayCopy (inFA.me, outFA.me, err.me);
    if err.isErr:
        OErr.printErrMsg(err, "Error copying GPUFArray")
    return outFA
    # end PCopy

def PClone (inFA, err):
    """  
    Make copy the structure of an GPUFArray
    
    Zero fill and return GPUFArray with same structure as in
    
    * inFA  = input Python GPUFArray
    * err  = Python Obit Error/message stack
    """
    ################################################################
    # Checks
    if not PIsA(inFA):
        print("Actually ",inFA.__class__)
        raise TypeError("inFA MUST be a Python Obit GPUFArray")
    outFA = GPUFArray("Clone")
    Obit.GPUFArrayClone (inFA.me, outFA.me, err.me);
    if err.isErr:
        OErr.printErrMsg(err, "Error zero cloning GPUFArray")
    return outFA
    # end PClone

def PIsA (inFA):
    """ 
    Tells if the input is a Python ObitGPUFArray
    
    returns True or False
    * inFA = Python Obit GPUFArray to test
    """
    ################################################################
      # Checks
    if not isinstance(inFA, GPUFArray):
        return False
    return Obit.GPUFArrayIsA(inFA.me)!=0
    # end PIsA

def PUnref (inFA):
    """ 
    Decrement reference count
    
    Decrement reference count which will destroy object if it goes to zero
    Python object stays defined.
    * inFA   = Python GPUFArray object
    """
    ################################################################
     # Checks
    if not PIsA(inFA):
        raise TypeError("inFA MUST be a Python Obit GPUFArray")

    inFA.me = Obit.GPUFArrayUnref(inFA.me)
    # end PUnref

def PGetNdim (inFA):
    """ 
    Returns the number of dimensions in array
    
    * inFA = Python Obit GPUFArray
    """
    ################################################################
      # Checks
    if not PIsA(inFA):
        print("Actually ",inFA.__class__)
        raise TypeError("inFA MUST be a Python Obit GPUFArray")
    return Obit.GPUFArrayGetNdim(inFA.me)
    # end PGetNdim

def PGetNaxis (inFA):
    """ 
    Returns array of 7 elements with dimensions in array
    
    * inFA = Python Obit GPUFArray
    """
    ################################################################
    # Checks
    if not PIsA(inFA):
        print("Actually ",inFA.__class__)
        raise TypeError("inFA MUST be a Python Obit GPUFArray")
    return Obit.GPUFArrayGetNaxis(inFA.me)
    # end PGetNaxis
