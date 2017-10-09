//
// Created by grihabor on 03.10.17.
//

#include <vector>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "../header/state.h"

bool State::abstract = false;

State::State(StateMapping initial_mapping)
        : mapping(std::move(initial_mapping)) {/* Constructor */}

std::string State::operator[](const std::string &field) const {
    /* Overloaded const [] access */
    return this->mapping.at(field);
}

std::string &State::operator[](const std::string &field) {
    /* Overloaded reference [] access */
    return this->mapping.at(field);
}

bool State::operator<(const State &other) const {
    /* *
     * Overloaded comparison between states
     *
     * This function allows State objects to be stored in std::set
     * */
    const State &self = *this;
    return static_cast<std::string>(self) < static_cast<std::string>(other);
}

State::operator std::string() const {
    std::stringstream ss;
    const State& state = *this;

    if (!state.abstract) {
        ss << std::setw(3) << state["c_f"] << ", ";
        ss << std::setw(3) << state["c_g"] << ", ";
    }
    ss << std::setw(3) << state["h"] << ", ";
    if (!state.abstract) {
        ss << std::setw(3) << state["f.x"] << ", ";
        ss << std::setw(3) << state["f.y"] << ", ";
        ss << std::setw(3) << state["g.x"] << ", ";
        ss << std::setw(3) << state["g.y"];
    }
    return ss.str();
}

bool State::exists(const std::string &key) const {
    /*  */
    const auto mapping = this->mapping;
    return mapping.find(key) != mapping.end();
}

bool State::operator!=(const State &other) const {
    const State &self = *this;
    return self < other || other < self;
}


std::ostream &operator<<(std::ostream &os, const State &state) {
    /* A function to print out a State object */
    os << static_cast<std::string>(state);
    return os;
}
