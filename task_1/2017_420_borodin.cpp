/*
 * Reliability Task 1
 * Borodin Gregory
 * 2017
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iomanip>


void print_info() {
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Reliability Task 1" << std::endl;
    std::cout << "Borodin Gregory" << std::endl;
    std::cout << "2017" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./task_1 <f_a> <f_b> <g_a> <g_b> [-file FILENAME] [-count]" << std::endl;
    std::cout << std::string(80, '*') << std::endl;
}


struct Args {
    /* Struct to store command line arguments */
    
    // name of the file to write output to
    std::string filename;
    // whether program should print count
    bool print_total_count;
    // values to feed into f and g
    int values[4];
    
    // if format is valid
    bool ok;
    
    Args()
      : filename(std::string("states.txt")),
        print_total_count(false),
        values{0, 0, 0, 0},
        ok(false)
    {}
};


Args parse_args(int argc, char **argv) {
    /* Parse command line arguments */
    
    // initialize args struct
    Args args;
    args.ok = false;
    args.print_total_count = false;
    
    int i = 0;
    int count = 0;
    
    for (i = 0; i < argc; ++i) {
        /* loop through argv */
        
        // read an arg
        std::string arg = argv[i];
        
        if (arg == "-file") {
            /* handle file parameter */
            // read next param
            ++i;
            // store it in `filename` field
            args.filename = argv[i];
        } else if (arg == "-count") {
            /* handle count parameter */
            args.print_total_count = true;
        } else {
            /* handle value */
            
            if (count >= 4) {
                /* too many values */
                count = -1;
                break;
            }
            
            int value;
            // parse int value and store in `values`
            try {
                value = std::stoi(arg);
            } catch (const std::invalid_argument& e) {
                std::cout << 
                    "Failed to cast `" << arg << "` to int" 
                    << std::endl;
                break;
            }
            args.values[count++] = value;
        }
    }
    
    if (count == 4) {
        /* Assert for exactly 4 args */
        args.ok = true;
    }
    
    return args;
}

struct Assign {
    std::string field;
    std::string value;
    
    Assign(std::string field, std::string value)
        : field(std::move(field)),
          value(std::move(value))
    {}
    
    Assign() 
        : field(std::string("")),
          value(std::string(""))
    {}
};

typedef std::map<std::string, std::string> StateMapping;

class State {
    /* Class to store the program state*/
    private:
        // Mapping to store the state
        StateMapping mapping;
    
    public:
        explicit State(StateMapping initial_mapping) : mapping(std::move(initial_mapping))
        {/* Constructor */}
        std::string operator[] (const std::string& field) const {
            /* Overloaded const [] access */
            return this->mapping.at(field);
        }
        std::string& operator[] (const std::string& field) {
            /* Overloaded reference [] access */
            return this->mapping.at(field);
        }
        bool operator< (const State& other) const {
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
};

void next_state(State state, 
                std::set<State>& states,
                const std::vector<Assign>& f_code,
                uint c_f,
                const std::vector<Assign>& g_code,
                uint c_g) {
    /* Recursive function to iterate trough all possible states */

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
    /* Calculate possible states from given params */

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


std::ostream& operator<<(std::ostream& os, const State& state) {
    /* A function to print out a State object */
    os << std::setw(3) << state["c_f"] << ", ";
    os << std::setw(3) << state["c_g"] << ", ";
    os << std::setw(3) << state["h"] << ", ";
    os << std::setw(3) << state["f.x"] << ", ";
    os << std::setw(3) << state["f.y"] << ", ";
    os << std::setw(3) << state["g.x"] << ", ";
    os << std::setw(3) << state["g.y"] << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<State>& states) {
    /* A function to print out a vector of State objects */
    os << "c_f, c_g,   h, f.x, f.y, g.x, g.y" << std::endl;
    for (const State &state: states) {
        os << state;
    }
    return os;
}


int main(int argc, char **argv) {
    /* Entrypoint */
    
    // Parse arguments from 1 to argc-1
    Args args = parse_args(argc - 1, argv + 1);
    
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
        std::cout << "Total states count: " << "6 * 7 * 3 * 3 * 3 * 2 * 4 * 2 ^ (32 * 4)" << std::endl;
    }
}






