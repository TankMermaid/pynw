#include <Python.h>
#include "nw.h"

static char module_docstring[] = "Needleman-Wunsch alignment in C.";
static char nw_docstring[] =
    "Number of mismatches (mismatched positions or gaps) in a Needleman-Wunsch alignment."
    ""
    "params:";

static PyObject *nw_nw(PyObject *self, PyObject *args) {
    char *s1, *s2;
    int match_score, mismatch_score, gap_score;
    double score;
    int print_alignments = 0;
    if (!PyArg_ParseTuple(args, "ssiii", &s1, &s2, &match_score, &mismatch_score, &gap_score))
        return NULL;

    score = nw(s1, s2, match_score, mismatch_score, gap_score, print_alignments);

    PyObject *ret = Py_BuildValue("d", score);
    return ret;
}

static PyMethodDef module_methods[] = {
    {"nw", nw_nw, METH_VARARGS, nw_docstring},
    {NULL, NULL, 0, NULL}
};


#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "nw",
    module_docstring,
    -1,
    module_methods
};

PyMODINIT_FUNC PyInit__nw(void) {
    PyObject *module;
    module = PyModule_Create(&module_def);
    if (module == NULL)
        return NULL;

    return module;
}

#else // Python 2

void init_nw(void) {
    PyObject *module = Py_InitModule3("_nw", module_methods, module_docstring);
    if (module == NULL)
        return;
}

#endif // Python version
