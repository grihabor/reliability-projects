//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_STATE_H
#define TASK_2_STATE_H


#include "state_mapping.h"

class State {
    /* Class to store the program state*/
private:
    // Mapping to store the state
    StateMapping mapping;

public:
    explicit State(StateMapping initial_mapping);

    std::string operator[](const std::string &field) const;

    std::string &operator[](const std::string &field);

    bool operator<(const State &other) const;

    operator std::string() const;
};

std::ostream &operator<<(std::ostream &os, const State &state);

#endif //TASK_2_STATE_H
