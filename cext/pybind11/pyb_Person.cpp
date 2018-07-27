//
//  pyb_Person.cpp
//  EuroPython2018
//
//  Created by Paul Ross on 27/07/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

// A C++ implementation of the CPython 'Noddy' class using pybind11
//  https://docs.python.org/3.6/extending/newtypes_tutorial.html#providing-finer-control-over-data-attributes

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "Person.h"

namespace py = pybind11;

PYBIND11_MODULE(pbPerson, m) {
    m.doc() = R"pbdoc(
    Example of Pybind11
    -------------------

    .. currentmodule:: pbPerson

    .. autosummary::
    :toctree: _generate

    Person
    )pbdoc";

    py::class_<Person>(m, "Person", "Documentation for Person class.")
    .def(py::init<const std::string &, const std::string &, int>(),
         "Constructor",
         py::arg("first"),
         py::arg("last"),
         py::arg("number")=0
    )
    // Slightly quirky pattern for pybind11, do not overload the functions in C++
    // but bind them together in the pybind11 file.
//    .def("first", (void (Person::*)(const std::string&)) &Person::set_first, "")
//    .def("first", (const std::string& (Person::*)()) &Person::get_first, "")
//    .def("last", (void (Person::*)(const std::string&)) &Person::set_last, "")
//    .def("last", (const std::string& (Person::*)()) &Person::get_last, "")
//    .def("number", &Person::number, "Documentation for number()")
    .def("name", &Person::name, "Documentation for name()")
    ;

}
