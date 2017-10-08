//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_RUN_H
#define TASK_2_RUN_H


#include <iostream>
#include <set>
#include <vector>
#include "state.h"
#include "args.h"
#include "assign.h"



typedef std::set<State> StateSet;

typedef std::pair<State, State> Link;
typedef std::map<Link, Assign> LinkSet;

typedef std::pair<StateSet, LinkSet> StateGraph;

typedef std::vector<Assign> Code;
typedef std::pair<Code, uint> CodeWithState;

// Print information about the program
void print_info();

// Recursive function to iterate trough all possible states
void next_state(State current_state,
                std::set<State> &states,
                const std::vector<Assign> &f_code,
                uint c_f,
                const std::vector<Assign> &g_code,
                uint c_g,
                const State& prev_state,
                std::set<std::pair<State, State>>& links);

// Calculate state graph from given params
StateGraph
calculate_states(int f_a, int f_b, int g_a, int g_b);

// A function to print out a vector of State objects
std::ostream &operator<<(std::ostream &os, const StateSet &states);

// Main logic
int run(const Args &args);

#endif //TASK_2_RUN_H
