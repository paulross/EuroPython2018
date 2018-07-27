//
//  Person.cpp
//  EuroPython2018
//
//  Created by Paul Ross on 27/07/2018.
//  Copyright © 2018 Paul Ross. All rights reserved.
//

#include "Person.h"

const std::string &Person::get_first() const {
    return m_first;
}

void Person::set_first(const std::string &first) {
    m_first = first;
}

std::string Person::get_last() const {
    return m_last;
}

void Person::set_last(const std::string &last) {
    m_first = last;
}

std::string Person::name() {
    return m_first + " " + m_last;
}
