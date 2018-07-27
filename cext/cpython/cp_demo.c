/*
 This is taken directly from the Python docs:
 https://docs.python.org/3.6/extending/newtypes_tutorial.html#providing-finer-control-over-data-attributes
 An renamed Noddy -> cpdemo.Person
 Minor modifications:
    Formatting.
    Change first and last to be unicode (U) rather than bytes (S).
*/
#include <Python.h>
#include "structmember.h"

typedef struct {
    PyObject_HEAD
    PyObject *first;
    PyObject *last;
    int number;
} Person;

static void
Person_dealloc(Person* self) {
    Py_XDECREF(self->first);
    Py_XDECREF(self->last);
    Py_TYPE(self)->tp_free((PyObject*)self);
}

static PyObject *
Person_new(PyTypeObject *type, PyObject *args, PyObject *kwds) {
    Person *self;

    self = (Person *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->first = PyUnicode_FromString("");
        if (self->first == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->last = PyUnicode_FromString("");
        if (self->last == NULL) {
            Py_DECREF(self);
            return NULL;
        }

        self->number = 0;
    }

    return (PyObject *)self;
}

static int
Person_init(Person *self, PyObject *args, PyObject *kwds) {
    PyObject *first=NULL, *last=NULL, *tmp;

    static char *kwlist[] = {"first", "last", "number", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|UUi", kwlist,
                                      &first, &last,
                                      &self->number))
        return -1;

    if (first) {
        tmp = self->first;
        Py_INCREF(first);
        self->first = first;
        Py_DECREF(tmp);
    }

    if (last) {
        tmp = self->last;
        Py_INCREF(last);
        self->last = last;
        Py_DECREF(tmp);
    }

    return 0;
}

static PyMemberDef Person_members[] = {
    {"number", T_INT, offsetof(Person, number), 0,
        "person number"},
    {NULL}  /* Sentinel */
};

static PyObject *
Person_getfirst(Person *self, void *closure) {
    Py_INCREF(self->first);
    return self->first;
}

static int
Person_setfirst(Person *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the first attribute");
        return -1;
    }

    if (! PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The first attribute value must be a string");
        return -1;
    }

    Py_DECREF(self->first);
    Py_INCREF(value);
    self->first = value;

    return 0;
}

static PyObject *
Person_getlast(Person *self, void *closure) {
    Py_INCREF(self->last);
    return self->last;
}

static int
Person_setlast(Person *self, PyObject *value, void *closure) {
    if (value == NULL) {
        PyErr_SetString(PyExc_TypeError, "Cannot delete the last attribute");
        return -1;
    }

    if (! PyUnicode_Check(value)) {
        PyErr_SetString(PyExc_TypeError,
                        "The last attribute value must be a string");
        return -1;
    }

    Py_DECREF(self->last);
    Py_INCREF(value);
    self->last = value;

    return 0;
}

static PyGetSetDef Person_getseters[] = {
    {"first",
        (getter)Person_getfirst, (setter)Person_setfirst,
        "first name",
        NULL},
    {"last",
        (getter)Person_getlast, (setter)Person_setlast,
        "last name",
        NULL},
    {NULL}  /* Sentinel */
};

static PyObject *
Person_name(Person* self) {
    return PyUnicode_FromFormat("%U %U", self->first, self->last);
}

static PyMethodDef Person_methods[] = {
    {"name", (PyCFunction)Person_name, METH_NOARGS,
        "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyTypeObject PersonType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "cp_demo.Person",             /* tp_name */
    sizeof(Person),             /* tp_basicsize */
    0,                         /* tp_itemsize */
    (destructor)Person_dealloc, /* tp_dealloc */
    0,                         /* tp_print */
    0,                         /* tp_getattr */
    0,                         /* tp_setattr */
    0,                         /* tp_reserved */
    0,                         /* tp_repr */
    0,                         /* tp_as_number */
    0,                         /* tp_as_sequence */
    0,                         /* tp_as_mapping */
    0,                         /* tp_hash  */
    0,                         /* tp_call */
    0,                         /* tp_str */
    0,                         /* tp_getattro */
    0,                         /* tp_setattro */
    0,                         /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT |
    Py_TPFLAGS_BASETYPE,   /* tp_flags */
    "Person objects",           /* tp_doc */
    0,                         /* tp_traverse */
    0,                         /* tp_clear */
    0,                         /* tp_richcompare */
    0,                         /* tp_weaklistoffset */
    0,                         /* tp_iter */
    0,                         /* tp_iternext */
    Person_methods,             /* tp_methods */
    Person_members,             /* tp_members */
    Person_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Person_init,      /* tp_init */
    0,                         /* tp_alloc */
    Person_new,                 /* tp_new */
};

static PyModuleDef cp_demomodule = {
    PyModuleDef_HEAD_INIT,
    "cp_demo",
    "Example module that creates an extension type.",
    -1,
    NULL, NULL, NULL, NULL, NULL
};

PyMODINIT_FUNC
PyInit_cp_demo(void) {
    PyObject* m;

    if (PyType_Ready(&PersonType) < 0) {
        return NULL;
    }

    m = PyModule_Create(&cp_demomodule);
    if (m == NULL) {
        return NULL;
    }

    Py_INCREF(&PersonType);
    PyModule_AddObject(m, "Person", (PyObject *)&PersonType);
    return m;
}

