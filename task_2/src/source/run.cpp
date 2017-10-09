//
// Created by grihabor on 03.10.17.
//



#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <sstream>
#include "../header/state.h"
#include "../header/assign.h"
#include "../header/args.h"
#include "../header/run.h"
#include "../header/init/code_with_state.h"
#include "../header/init/state.h"
#include "../header/dot.h"

void print_info() {
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Reliability Task 1" << std::endl;
    std::cout << "Borodin Gregory" << std::endl;
    std::cout << "2017" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./task_1 <f_a> <f_b> <g_a> <g_b> [-file FILENAME] [-count]" << std::endl;
    std::cout << std::string(80, '*') << std::endl;
}


void maybe_store_state_and_link(const State &current_state,
                                const State &prev_state,
                                StateGraph &graph,
                                const Assign &assingment) {
    /* Store state and store link if not initial state */
    // Store current state
    graph.states.insert(current_state);

    if (current_state != prev_state) {
        /* If not initial state */
        // Store link from previous to current state
        Link link = std::make_pair(prev_state, current_state);
        graph.links[link] = assingment;
    }
}

void maybe_next_state(int index,
                      State current_state,
                      StateGraph& graph,
                      std::vector<CodeWithState> &functions) {
    CodeWithState &func = functions[index];
    State prev_state = current_state;
    if (func.counter < func.code.size() - 1) {
        /* Choose to execute next operator of the function */
        Assign assignment = func.code[func.counter];
        current_state[assignment.field] = assignment.value;
        auto funcs = std::vector<CodeWithState>(functions);
        funcs[index].counter += 1;
        next_state(
                current_state,
                prev_state,
                graph,
                funcs,
                assignment
        );
    }
}


void next_state(State current_state,
                const State& prev_state,
                StateGraph &graph,
                std::vector<CodeWithState> &functions,
                const Assign& prev_assignment) {


    // Set state counters
    current_state["c_f"] = std::to_string(functions[0].counter);
    current_state["c_g"] = std::to_string(functions[1].counter);
    maybe_store_state_and_link(
            current_state,
            prev_state,
            graph,
            prev_assignment
    );


    for (int i = 0; i < functions.size(); ++i) {
        /* Iterate through functions and execute assignments recursively */
        maybe_next_state(
                i,
                current_state,
                graph,
                functions
        );
    }
}





StateGraph
calculate_states(int f_a, int f_b, int g_a, int g_b, bool abstract) {

    std::vector<CodeWithState> functions;
    State current_state;
    if (abstract) {
        current_state = get_initial_state_h_only();
        functions.push_back(get_f_code_with_state_h_only());
        functions.push_back(get_g_code_with_state_h_only(g_b));
    } else {
        current_state = get_initial_state();
        functions.push_back(get_f_code_with_state());
        functions.push_back(get_g_code_with_state(g_b));
    }


    StateGraph graph;


    // Recursively search for possible states
    next_state(current_state,
               current_state,
               graph,
               functions,
               Assign("", ""));
    // Return found states
    return graph;
}


std::ostream &operator<<(std::ostream &os, const std::set<State> &states) {
    os << "c_f, c_g,   h, f.x, f.y, g.x, g.y" << std::endl;
    for (const State &state: states) {
        os << state << std::endl;
    }
    return os;
}


int run(const Args &args) {
    if (!args.ok) {
        /* too few args */
        print_info();
        return 0;
    }
    State().abstract = args.abstract;

    // Recursively calculate set of states
    StateGraph graph = calculate_states(
            args.values[0],
            args.values[1],
            args.values[2],
            args.values[3],
            args.abstract
    );

    {
        /* Write graph to file as dot */
        std::ofstream f(args.lts_filename);
        f << Dot(graph);
    }

    {
        /* Write states to file */
        std::ofstream f(args.states_filename);
        f << graph.states;
    }

    // Write count to stdout
    std::cout << "Possible states count: " << graph.states.size() << std::endl;
    if (args.print_total_count) {
        std::cout << "Total states count: ";
        std::cout << "6 * 7 * 3 * 3 * 3 * 2 * 4 * 2 ^ (32 * 4) = ";
        std::cout << 6 * 7 * 3 * 3 * 3 * 2 * 4 << " * 2 ^ (32 * 4)" << std::endl;
    }
}