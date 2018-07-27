# EuroPython2018
Presentations and helpdesk at EuroPython 2018

## Help Desk: C/C++ Extensions with Python

If you want your Python code to run really fast you can get dramatic performance improvements
if you are willing to write some of your code in C/C++.

There are several ways to do this from traditional Python C extensions to using environments such as Cython or Pybind11.

This help desk is here so you can choose the best approach to achieve that magical 100x performance increase without pain.

In `cext/` there are examples of writing C extensions in various ways:

* In `cext/cpython/` there are some examples of traditional CPython
extensions.
* In `cext/cython/` there are some examples of Cython code.
* In `cext/pybind11` there are some examples of pybind11 exposing C++ code to Python.

To build all of them:

```
python setup.py build_ext --inplace
python setup_pybind11.py build_ext --inplace
```

If you would like to know more then these repos might be of interest:

* **Cython:** https://github.com/paulross/NotesOnCython
* **C Extensions:** https://github.com/paulross/PythonExtensionPatterns
* A comparison of the performance of C Extensions, Cython and pybind11: https://github.com/paulross/xmlwriter 
