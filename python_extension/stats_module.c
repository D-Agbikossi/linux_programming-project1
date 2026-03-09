#include <Python.h>
#include <math.h>

static PyObject* compute_statistics_c(PyObject* self, PyObject* args) {
    PyObject* list_obj;
    
    // Parse Python list input
    if (!PyArg_ParseTuple(args, "O", &list_obj))
        return NULL;
    
    // Check if it's a list
    if (!PyList_Check(list_obj)) {
        PyErr_SetString(PyExc_TypeError, "Expected a list");
        return NULL;
    }
    
    Py_ssize_t n = PyList_Size(list_obj);
    if (n == 0) {
        return Py_BuildValue("(ddd)", 0.0, 0.0, 0.0);
    }
    
    // First pass: calculate mean
    double total = 0.0;
    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject* item = PyList_GetItem(list_obj, i);
        if (!PyFloat_Check(item) && !PyLong_Check(item)) {
            PyErr_SetString(PyExc_TypeError, "List must contain numbers");
            return NULL;
        }
        total += PyFloat_AsDouble(item);
    }
    double mean = total / n;
    
    // Second pass: calculate variance
    double variance = 0.0;
    for (Py_ssize_t i = 0; i < n; i++) {
        PyObject* item = PyList_GetItem(list_obj, i);
        double diff = PyFloat_AsDouble(item) - mean;
        variance += diff * diff;
    }
    variance /= n;
    
    // Calculate standard deviation
    double std_dev = sqrt(variance);
    
    // Return tuple of results
    return Py_BuildValue("(ddd)", mean, variance, std_dev);
}

// Method definition
static PyMethodDef StatsMethods[] = {
    {"compute_statistics", compute_statistics_c, METH_VARARGS, 
     "Compute statistics on a list of numbers using C"},
    {NULL, NULL, 0, NULL}
};

// Module definition
static struct PyModuleDef statsmodule = {
    PyModuleDef_HEAD_INIT,
    "stats_c",
    "C extension for fast statistics computation",
    -1,
    StatsMethods
};

// Module initialization
PyMODINIT_FUNC PyInit_stats_c(void) {
    return PyModule_Create(&statsmodule);
}
