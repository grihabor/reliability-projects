//
// Created by grihabor on 03.10.17.
//



#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include "../header/state.h"
#include "../header/assign.h"
#include "../header/args.h"

void print_info() {
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Reliability Task 1" << std::endl;
    std::cout << "Borodin Gregory" << std::endl;
    std::cout << "2017" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./task_1 <f_a> <f_b> <g_a> <g_b> [-file FILENAME] [-count]" << std::endl;
    std::cout << std::string(80, '*') << std::endl;
}


void next_state(State state,
                std::set<State> &states,
                const std::vector<Assign> &f_code,
                uint c_f,
                const std::vector<Assign> &g_code,
                uint c_g) {

    // Add state to state set
    state["c_f"] = std::to_string(c_f);
    state["c_g"] = std::to_string(c_g);
    states.insert(state);

    Assign assignment;

    if (c_f < f_code.size() - 1) {
        /* Choose to execute next operator of f function */
        assignment = f_code[c_f];
        state[assignment.field] = assignment.value;
        next_state(
                state, states,
                f_code, c_f + 1,
                g_code, c_g
        );
    }

    if (c_g < g_code.size() - 1) {
        /* Choose to execute next operator of g function */
        assignment = g_code[c_g];
        state[assignment.field] = assignment.value;
        next_state(
                state, states,
                f_code, c_f,
                g_code, c_g + 1
        );
    }
}

std::set<State> calculate_states(int f_a, int f_b, int g_a, int g_b) {

    // Fill in the f function code
    std::vector<Assign> f_code;
    f_code.emplace_back("f.x", "10");
    f_code.emplace_back("f.y", "5");
    f_code.emplace_back("h", "3");
    f_code.emplace_back("f.x", "4");
    f_code.emplace_back("f.y", "9");
    f_code.emplace_back();

    // Fill in the g function code
    std::vector<Assign> g_code;
    g_code.emplace_back("g.x", "4");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back("h", std::to_string(g_b));
    g_code.emplace_back("h", "4");
    g_code.emplace_back("g.x", "3");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back();

    // Initialize states
    std::set<State> states;

    const StateMapping initial_mapping = {
            {"c_f", "#"},
            {"c_g", "#"},
            {"h",   "#"},
            {"f.x", "#"},
            {"f.y", "#"},
            {"g.x", "#"},
            {"g.y", "#"}
    };

    State state(initial_mapping);
    // Recursively search for possible states
    next_state(state, states,
               f_code, 0, g_code, 0);
    // Return found states
    return states;
}


std::ostream &operator<<(std::ostream &os, const std::set<State> &states) {
    os << "c_f, c_g,   h, f.x, f.y, g.x, g.y" << std::endl;
    for (const State &state: states) {
        os << state << std::endl;
    }
    return os;
}

int run(Args args) {
    if (!args.ok) {
        /* too few args */
        print_info();
        return 0;
    }

    // Recursively calculate set of states
    std::set<State> states = calculate_states(
            args.values[0],
            args.values[1],
            args.values[2],
            args.values[3]
    );

    // Write states to file
    std::ofstream f(args.filename);
    f << states;

    // Write count to stdout
    std::cout << "Possible states count: " << states.size() << std::endl;
    if (args.print_total_count) {
        std::cout << "Total states count: ";
        std::cout << "6 * 7 * 3 * 3 * 3 * 2 * 4 * 2 ^ (32 * 4) = ";
        std::cout << 6 * 7 * 3 * 3 * 3 * 2 * 4 << " * 2 ^ (32 * 4)" << std::endl;
    }
}