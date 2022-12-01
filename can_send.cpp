#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <Python.h>

void can_send_s()
{

    Py_Initialize();
    PyRun_SimpleString("import sys; sys.path.append('.')");
    PyRun_SimpleString("import can_python;");
    PyRun_SimpleString("can_python.read()");
    //Py_Finalize();


}

int can_send_u()
{
    Py_Initialize();

    PyObject* myModuleString = PyUnicode_FromString((char*)"can_python");
    PyObject* myModule = PyImport_Import(myModuleString);


    PyObject* myFunction = PyObject_GetAttrString(myModule,(char*)"read");


    PyObject* myResult = PyObject_CallObject(myFunction,0);


    int result;
    result = (int)PyFloat_AsDouble(myResult);
    return result;

}
