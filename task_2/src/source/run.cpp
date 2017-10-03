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

void print_info() {
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Reliability Task 1" << std::endl;
    std::cout << "Borodin Gregory" << std::endl;
    std::cout << "2017" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./task_1 <f_a> <f_b> <g_a> <g_b> [-file FILENAME] [-count]" << std::endl;
    std::cout << std::string(80, '*') << std::endl;
}


void next_state(State current_state,
                std::set<State> &states,
                const std::vector<Assign> &f_code,
                uint c_f,
                const std::vector<Assign> &g_code,
                uint c_g,
                const State& prev_state,
                LinksSet& links,
                const Assign& prev_assignment) {

    // Add state to state set
    current_state["c_f"] = std::to_string(c_f);
    current_state["c_g"] = std::to_string(c_g);
    states.insert(current_state);

    Link link = std::make_pair(prev_state, current_state);
    links[link] = prev_assignment;

    State saved_state = current_state;

    Assign assignment;

    if (c_f < f_code.size() - 1) {
        /* Choose to execute next operator of f function */
        assignment = f_code[c_f];
        current_state[assignment.field] = assignment.value;
        next_state(
                current_state, states,
                f_code, c_f + 1,
                g_code, c_g,
                saved_state,
                links,
                assignment
        );
    }

    if (c_g < g_code.size() - 1) {
        /* Choose to execute next operator of g function */
        assignment = g_code[c_g];
        current_state[assignment.field] = assignment.value;
        next_state(
                current_state, states,
                f_code, c_f,
                g_code, c_g + 1,
                saved_state,
                links,
                assignment
        );
    }
}

std::vector<Assign> generate_f_code() {

    // Fill in the f function code
    std::vector<Assign> f_code;
    f_code.emplace_back("f.x", "10");
    f_code.emplace_back("f.y", "5");
    f_code.emplace_back("h", "3");
    f_code.emplace_back("f.x", "4");
    f_code.emplace_back("f.y", "9");
    f_code.emplace_back();

    return f_code;
}

std::vector<Assign> generate_g_code(int g_b) {
    // Fill in the g function code
    std::vector<Assign> g_code;
    g_code.emplace_back("g.x", "4");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back("h", std::to_string(g_b));
    g_code.emplace_back("h", "4");
    g_code.emplace_back("g.x", "3");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back();

    return g_code;
}

std::pair<StatesSet, LinksSet>
calculate_states(int f_a, int f_b, int g_a, int g_b) {

    auto f_code = generate_f_code();
    auto g_code = generate_g_code(g_b);

    // Initialize states
    StatesSet states;
    LinksSet links;

    const StateMapping initial_mapping = {
            {"c_f", "0"},
            {"c_g", "0"},
            {"h",   "#"},
            {"f.x", "#"},
            {"f.y", "#"},
            {"g.x", "#"},
            {"g.y", "#"}
    };

    State current_state(initial_mapping);
    // Recursively search for possible states
    next_state(current_state, states,
               f_code, 0, g_code, 0,
               current_state, links, Assign("", ""));
    // Return found states
    return std::make_pair(states, links);
}


std::ostream &operator<<(std::ostream &os, const std::set<State> &states) {
    os << "c_f, c_g,   h, f.x, f.y, g.x, g.y" << std::endl;
    for (const State &state: states) {
        os << state << std::endl;
    }
    return os;
}

std::map<int, State> enumerate_states(std::set<State> states) {
    std::map<int, State> mapping;
    int counter = 0;
    for (const State &state: states) {
        mapping.insert(std::make_pair(counter, state));
        ++counter;
    }
    return mapping;
};

typedef std::map<std::string, int> IndexMapping;

int get_index(const State& state, IndexMapping mapping) {
    std::string s = static_cast<std::string>(state);
    return mapping.at(s);
}

void generate_dot(const std::string& filename,
                  const StatesSet &states,
                  const LinksSet &links) {
    std::ofstream f(filename);
    IndexMapping mapping;
    int count = 0;

    f << "digraph G {" << std::endl;

    for (const State& state : states) {
        /* Write nodes */
        std::string state_str = state;
        mapping[state_str] = count;
        f << count << " " << "[label=\"" << state_str << "\"];" << std::endl;
        ++count;
    }

    std::set<std::string> links_str;

    for (std::pair<Link, Assign> pair : links) {
        /* Write links */
        Link link = pair.first;
        Assign assign = pair.second;

        std::stringstream ss;
        ss << get_index(link.first, mapping) << " -> ";
        ss << get_index(link.second, mapping);
        ss << "[label=\"" << static_cast<std::string>(assign) << "\"];";

        std::string link_str = ss.str();
        links_str.insert(link_str);
    }

    for (const std::string & link_str: links_str) {
        f << link_str << std::endl;
    }

    f << "}" << std::endl;
}

int run(Args args) {
    if (!args.ok) {
        /* too few args */
        print_info();
        return 0;
    }

    StatesSet states;
    LinksSet links;

    // Recursively calculate set of states
    std::tie(states, links) = calculate_states(
            args.values[0],
            args.values[1],
            args.values[2],
            args.values[3]
    );

    generate_dot(args.filename + ".dot", states, links);

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