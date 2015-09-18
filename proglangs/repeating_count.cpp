#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

extern "C" {
    #include <Python.h>
}

using std::vector;
using std::string;

/**
 * The namespace for searching max repeating using prefix function.
 */
namespace repeating_count {
    /**
     * Array for prefix values
     */
    static size_t prefixFunction[5001];
    /**
     * Current result of searching
     */
    static size_t answer = 1;

    /**
     * Computing k-repeatings from some start symbol.
     * If the result is more then previous, result will be upfdated.
     * @param str - input string,
     * @param start - starting symbol in str
     */
    void solve(size_t start, string str) {
        for (size_t i = 0; i < str.length(); ++i) {
            prefixFunction[i] = 0;
        }
        for (size_t i = start + 1; i < str.length(); ++i) {
            int jInd = prefixFunction[i - 1];
            while (jInd > 0 && str[i] != str[start + jInd]) {
                jInd = prefixFunction[start + jInd - 1];
            }
            if (str[i] == str[start + jInd]){
                ++jInd;
            }
            prefixFunction[i] = jInd;
            size_t len = i - start + 1;
            if (len % (len - jInd) == 0) {
                answer = std::max(answer, len / (len - jInd));
            }
        }
    }

    /**
     * Computing max k-repeatings.
     * @param str - input string
     */
    size_t count(string str){
        answer = 1;
        for (size_t i = 0; i < str.length(); ++i) {
            solve(i, str);
        }
        return answer;
    }
}

/**
 * Run algorithm for single string.
 * Returns single number.
 */
PyObject* count_rep_single(PyObject *mod, PyObject *args){
    char* s;
    if(!PyArg_ParseTuple(args, "s", &s)){
        return NULL;
    }
    return Py_BuildValue("i", repeating_count::count(string(s)));
}

/**
 * Run algorithm for list of strings or the single string.
 * Returns list of numbers (even if the single string inputted).
 */
PyObject* count_rep_list(PyObject *mod, PyObject *args){
    PyObject *inputList = PyTuple_GetItem(args, 0);
    PyObject *outputList = PyList_New(0);
    char* str;
    if(PyList_Check(inputList)) {
        for (size_t i = 0; i < PyList_Size(inputList); ++i) {
            PyObject *list_item = PyList_GetItem(inputList, i);
            if (!PyArg_Parse(list_item, "s", &str)) {
                Py_XDECREF(list_item);
                Py_XDECREF(inputList);
                Py_XDECREF(outputList);
                return NULL;
            }
            // Py_DECREF(list_item);
            PyList_Append(outputList, PyLong_FromSize_t(repeating_count::count(string(str))));
        }
    }
    else if(!PyArg_Parse(inputList, "s", &str)){
        Py_XDECREF(inputList);
        Py_XDECREF(outputList);
        return NULL;
    }
    else {
        PyList_Append(outputList, PyLong_FromSize_t(repeating_count::count(string(str))));
    }
    return outputList;
}

/**
 * Registring the Python module.
 */
PyMODINIT_FUNC PyInit_repeating_count() {
    static PyMethodDef ModuleMethods[] = {
            {"count_rep_single", count_rep_single, METH_VARARGS, "Counting repeatings for single string. Returns single number." },
            {"count_rep_list", count_rep_list, METH_VARARGS,
                    "Counting repeatings for list of strings or the single string. Returns list of numbers (even if the single string inputted)."},
            { NULL, NULL, 0, NULL}
    };
    static PyModuleDef ModuleDef = {
            PyModuleDef_HEAD_INIT,
            "repeating_count",
            "solving Task 1.4. (SHAD, 2nd semester) for list of strings or for the single one.",
            -1, ModuleMethods,
            NULL, NULL, NULL, NULL
    };
    PyObject* module = PyModule_Create(&ModuleDef);
    return module;
}
