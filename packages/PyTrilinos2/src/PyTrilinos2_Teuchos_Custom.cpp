// @HEADER
// ***********************************************************************
//
//          PyTrilinos2: Automatic Python Interfaces to Trilinos Packages
//                 Copyright (2022) Sandia Corporation
//
// Under the terms of Contract DE-AC04-94AL85000 with Sandia
// Corporation, the U.S. Government retains certain rights in this
// software.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// 3. Neither the name of the Corporation nor the names of the
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY SANDIA CORPORATION "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL SANDIA CORPORATION OR THE
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Questions? Contact Kim Liegeois (knliege@sandia.gov)
//
// ***********************************************************************
// @HEADER

#include <PyTrilinos2_Teuchos_Custom.hpp>

#if PY_VERSION_HEX >= 0x03000000

#define PyClass_Check(obj) PyObject_IsInstance(obj, (PyObject *)&PyType_Type)
#define PyInt_Check(x) PyLong_Check(x)
#define PyInt_AsLong(x) PyLong_AsLong(x)
#define PyInt_FromLong(x) PyLong_FromLong(x)
#define PyInt_FromSize_t(x) PyLong_FromSize_t(x)
#define PyString_Check(name) PyBytes_Check(name)
#define PyString_FromString(x) PyUnicode_FromString(x)
#define PyString_FromStringAndSize(x,s) PyUnicode_FromStringAndSize(x,s)
#define PyString_Format(fmt, args)  PyUnicode_Format(fmt, args)
#define PyString_AsString(str) PyBytes_AsString(str)
#define PyString_Size(str) PyBytes_Size(str)    
#define PyString_InternFromString(key) PyUnicode_InternFromString(key)
#define Py_TPFLAGS_HAVE_CLASS Py_TPFLAGS_BASETYPE
#define PyString_AS_STRING(x) PyUnicode_AS_STRING(x)
#define PyObject_Compare(x, y) (1-PyObject_RichCompareBool(x, y, Py_EQ))
#define _PyLong_FromSsize_t(x) PyLong_FromSsize_t(x)
#define convertPyStringToChar(pyobj) PyBytes_AsString(PyUnicode_AsASCIIString(pyobj))
#else
#define convertPyStringToChar(pyobj) PyString_AsString(pyobj)
#endif

namespace py = pybind11;

// Implementation based on:
// https://github.com/trilinos/Trilinos/tree/master/packages/PyTrilinos/src/PyTrilinos_Teuchos_Util.cpp
bool setPythonParameter(Teuchos::RCP<Teuchos::ParameterList> plist,
			const std::string      & name,
			py::object             value)
{
  py::handle h = value;

  // Boolean values
  if (PyBool_Check(value.ptr ()))
  {
    plist->set(name, h.cast<bool>());
  }

  // Integer values
  else if (PyInt_Check(value.ptr ()))
  {
    plist->set(name, h.cast<int>());
  }

  // Floating point values
  else if (PyFloat_Check(value.ptr ()))
  {
    plist->set(name, h.cast<double>());
  }

  // Unicode values
  else if (PyUnicode_Check(value.ptr ()))
  {
    PyObject * pyBytes = PyUnicode_AsASCIIString(value.ptr ());
    if (!pyBytes) return false;
    plist->set(name, std::string(PyBytes_AsString(pyBytes)));
    Py_DECREF(pyBytes);
  }

  // String values
  else if (PyString_Check(value.ptr ()))
  {
    plist->set(name, h.cast<std::string>());
  }

  // None object not allowed: this is a python type not usable by
  // Trilinos solver packages, so we reserve it for the
  // getPythonParameter() function to indicate that the requested
  // parameter does not exist in the given Teuchos::ParameterList.
  // For logic reasons, this check must come before the check for
  // Teuchos::ParameterList
  else if (value.ptr () == Py_None)
  {
    return false;
  }

  // All other value types are unsupported
  else
  {
    return false;
  }

  // Successful type conversion
  return true;
}    // setPythonParameter


// Implementation based on:
// https://github.com/trilinos/Trilinos/tree/master/packages/PyTrilinos/src/PyTrilinos_Teuchos_Util.cpp
py::object getPythonParameter(Teuchos::RCP<Teuchos::ParameterList> plist,
			      const std::string            & name)
{
  // Get the parameter entry.  I now deal with the Teuchos::ParameterEntry
  // objects so that I can query the Teuchos::ParameterList without setting
  // the "used" flag to true.
  const Teuchos::ParameterEntry * entry = plist->getEntryPtr(name);
  // Boolean parameter values
  if (entry->isType< bool >())
  {
    bool value = Teuchos::any_cast< bool >(entry->getAny(false));
    return py::cast(value);
  }
  // Integer parameter values
  else if (entry->isType< int >())
  {
    int value = Teuchos::any_cast< int >(entry->getAny(false));
    return py::cast(value);
  }
  // Double parameter values
  else if (entry->isType< double >())
  {
    double value = Teuchos::any_cast< double >(entry->getAny(false));
    return py::cast(value);
  }
  // String parameter values
  else if (entry->isType< std::string >())
  {
    std::string value = Teuchos::any_cast< std::string >(entry->getAny(false));
    return py::cast(value.c_str());
  }
  // Char * parameter values
  else if (entry->isType< char * >())
  {
    char * value = Teuchos::any_cast< char * >(entry->getAny(false));
    return py::cast(value);
  }

  else if (entry->isArray())
  {
    try
    {
      Teuchos::Array< int > tArray =
        Teuchos::any_cast< Teuchos::Array< int > >(entry->getAny(false));
      return copyTeuchosArrayToNumPy(tArray);
    }
    catch(Teuchos::bad_any_cast &e)
    {
      try
      {
        Teuchos::Array< long > tArray =
          Teuchos::any_cast< Teuchos::Array< long > >(entry->getAny(false));
        return copyTeuchosArrayToNumPy(tArray);
      }
      catch(Teuchos::bad_any_cast &e)
      {
        try
        {
          Teuchos::Array< float > tArray =
            Teuchos::any_cast< Teuchos::Array< float > >(entry->getAny(false));
          return copyTeuchosArrayToNumPy(tArray);
        }
        catch(Teuchos::bad_any_cast &e)
        {
          try
          {
            Teuchos::Array< double > tArray =
              Teuchos::any_cast< Teuchos::Array< double > >(entry->getAny(false));
            return copyTeuchosArrayToNumPy(tArray);
          }
          catch(Teuchos::bad_any_cast &e)
          {
            return py::none();
          }
        }
      }
    }
  }

  // All  other types are unsupported
  return py::none();
}    // getPythonParameter
