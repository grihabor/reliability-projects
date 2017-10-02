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

// Print information about the program
void print_info();

// Recursive function to iterate trough all possible states
void next_state(State state,
                std::set<State>& states,
                const std::vector<Assign>& f_code,
                uint c_f,
                const std::vector<Assign>& g_code,
                uint c_g);

// Calculate possible states from given params
std::set<State> calculate_states(int f_a, int f_b, int g_a, int g_b);

// A function to print out a vector of State objects
std::ostream& operator<<(std::ostream& os, const std::set<State>& states);

// Main logic
int run(Args args);

#endif //TASK_2_RUN_H
