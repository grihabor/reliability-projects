//
// Created by grihabor on 09.10.17.
//

#ifndef TASK_2_TYPEDEFS_H
#define TASK_2_TYPEDEFS_H


#include <utility>
#include <vector>
#include <map>
#include <set>
#include "assign.h"
#include "state.h"

typedef std::set<State> StateSet;

typedef std::pair<State, State> Link;
typedef std::map<Link, Assign> LinkSet;

struct StateGraph {
    StateSet states;
    LinkSet links;
};

typedef std::vector<Assign> Code;

struct CodeWithState {
    Code code;
    uint counter;

    CodeWithState(Code code, uint counter)
    : code(code), counter(counter)
    {}
};

#endif //TASK_2_TYPEDEFS_H
