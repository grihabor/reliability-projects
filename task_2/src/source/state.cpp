//
// Created by grihabor on 03.10.17.
//

#include <vector>
#include <iomanip>
#include <iostream>
#include "../header/state_mapping.h"
#include "../header/state.h"

State::State(StateMapping initial_mapping)
    : mapping(std::move(initial_mapping))
{/* Constructor */}

std::string State::operator[] (const std::string& field) const {
    /* Overloaded const [] access */
    return this->mapping.at(field);
}

std::string& State::operator[] (const std::string& field) {
    /* Overloaded reference [] access */
    return this->mapping.at(field);
}

bool State::operator< (const State& other) const {
    /* *
     * Overloaded comparison between states
     *
     * This function allows State objects to be stored in std::set
     * */
    const State& self = *this;

    // Initialize conditions to check for `less`
    std::vector<bool> less_conditions;
    less_conditions.push_back(self["c_f"] < other["c_f"]);
    less_conditions.push_back(self["c_g"] < other["c_g"]);
    less_conditions.push_back(self["h"] < other["h"]);
    less_conditions.push_back(self["f.x"] < other["f.x"]);
    less_conditions.push_back(self["f.y"] < other["f.y"]);
    less_conditions.push_back(self["g.x"] < other["g.x"]);
    less_conditions.push_back(self["g.y"] < other["g.y"]);

    for (bool c : less_conditions) {
        /* Iterate through conditions */
        if (c) {
            /* If any condition is true */
            return true;
        }
    }
    // Otherwise
    return false;
}


std::ostream& operator<<(std::ostream& os, const State& state) {
    /* A function to print out a State object */
    os << std::setw(3) << state["c_f"] << ", ";
    os << std::setw(3) << state["c_g"] << ", ";
    os << std::setw(3) << state["h"] << ", ";
    os << std::setw(3) << state["f.x"] << ", ";
    os << std::setw(3) << state["f.y"] << ", ";
    os << std::setw(3) << state["g.x"] << ", ";
    os << std::setw(3) << state["g.y"];
    return os;
}
