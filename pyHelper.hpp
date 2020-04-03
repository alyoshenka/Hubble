/*
this code taken from https://www.codeproject.com/Articles/820116/Embedding-Python-program-in-a-C-Cplusplus-code
it is totally 100% copied and in no way mine
*/

// also be sure to set PYTHONPATH to build directory

#ifndef PYHELPER_HPP
#define PYHELPER_HPP
#pragma once

#include <Python.h>

class CppPyInstance
{
public:
	CppPyInstance() { Py_Initialize(); }
	~CppPyInstance() { Py_Finalize(); }
};

class CppPyObject
{
private:
	PyObject* p;
public:
	CppPyObject() : p(NULL) {}
	CppPyObject(PyObject* _p) : p(_p) {}

	~CppPyObject() { Release(); }

	PyObject* getObject() { return p; }
	PyObject* setObject(PyObject* _p) { return (p = _p); }
	PyObject* AddRef() 
	{ 
		if (p) { Py_INCREF(p); } 
		return p;
	}
	void Release()
	{
		if (p) { Py_DECREF(p); }
		p = NULL;
	}
	PyObject* operator ->() { return p; }
	bool is() { return p; }
	operator PyObject* () { return p; }
	PyObject* operator = (PyObject* pp)
	{
		p = pp;
		return p;
	}
	operator bool() { return p; }
};

#endif
