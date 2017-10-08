//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_RUN_H
#define TASK_2_RUN_H


#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "state.h"
#include "args.h"
#include "assign.h"
#include "typedefs.h"


// Print information about the program
void print_info();

// Recursive function to iterate trough all possible states
void next_state(State,
                const State&,
                StateGraph &,
                std::vector<CodeWithState> &,
                const Assign&);

// Calculate state graph from given params
StateGraph
calculate_states(int f_a, int f_b, int g_a, int g_b);

// A function to print out a vector of State objects
std::ostream &operator<<(std::ostream &os, const StateSet &states);

// Main logic
int run(const Args &args);

#endif //TASK_2_RUN_H
