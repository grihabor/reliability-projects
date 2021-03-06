//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_STATE_H
#define TASK_2_STATE_H


#include <map>
#include <string>

typedef std::map<std::string, std::string> StateMapping;

class State {
    /* Class to store the program state*/
private:
    // Mapping to store the state
    StateMapping mapping;

public:
    static bool abstract;

    explicit State(StateMapping initial_mapping);
    State(){}

    std::string operator[](const std::string &field) const;

    std::string &operator[](const std::string &field);

    bool operator<(const State &other) const;
    bool operator!=(const State &other) const;

    explicit operator std::string() const;

    bool exists(const std::string &key) const;
};

std::ostream &operator<<(std::ostream &os, const State &state);

#endif //TASK_2_STATE_H
