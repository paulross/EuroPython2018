//
//  Person.hpp
//  EuroPython2018
//
//  Created by Paul Ross on 27/07/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

// A C++ implementation of the CPython 'Noddy' class using pybind11
//  https://docs.python.org/3.6/extending/newtypes_tutorial.html#providing-finer-control-over-data-attributes

#ifndef Person_hpp
#define Person_hpp

#include <string>

class Person {
public:
    Person(std::string first, std::string last, int number) \
        : m_first(first), m_last(last), m_number(number) {}
    // Slightly quirky pattern for pybind11, do not overload the functions in C++
    // but bind them together in the pybind11 file.
    const std::string &get_first() const;
    void set_first(const std::string &first);
    std::string get_last() const;
    void set_last(const std::string &last);
    int number() const { return m_number; }
    std::string name();
private:
    std::string m_first;
    std::string m_last;
public:
    int m_number;
};

#endif /* Person_hpp */
