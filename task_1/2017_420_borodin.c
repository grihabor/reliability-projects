#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>


void print_info() {
    std::cout << std::string(80, '*') << std::endl;
    std::cout << "Reliability Task 1" << std::endl;
    std::cout << "Borodin Gregory" << std::endl;
    std::cout << "2017" << std::endl;
    std::cout << std::endl;
    std::cout << "Usage: ./task_1 <f_a> <f_b> <g_a> <g_b>" << std::endl;
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
      : filename("states.txt"),
        print_total_count(false),
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
        : field(field),
          value(value)
    {}
    
    Assign() 
        : field(""),
          value("")
    {}
};

class State {
    private:
        std::map<std::string, std::string> states;
    
    public:
        State() 
            : states({{"c_f", "#"},
                      {"c_g", "#"},
                      {"h",   "#"},
                      {"f.x", "#"},
                      {"f.y", "#"},
                      {"g.x", "#"},
                      {"g.y", "#"}})
        {}
        std::string& operator[] (std::string field) {
            return this->states[field];
        }
};

void next_state(State state, 
                std::vector<State>& states, 
                const std::vector<Assign>& f_code,
                uint c_f,
                const std::vector<Assign>& g_code,
                uint c_g) {
    
    Assign assignment;
    
    if (c_f < f_code.size() - 1) {
        assignment = f_code[c_f];
        state[assignment.field] = assignment.value;
        states.push_back(state);
        next_state(
            state, 
            states, 
            f_code,
            c_f,
            g_code,
            c_g
        );
    }    
    
    if (c_g < g_code.size() - 1) {
        assignment = g_code[c_g];
        state[assignment.field] = assignment.value;
        states.push_back(state);
        next_state(
            state, 
            states, 
            f_code,
            c_f,
            g_code,
            c_g
        );
    }    
}

std::vector<State> calculate_states(int f_a, int f_b, int g_a, int g_b) {
    std::vector<Assign> f_code = [
        Assign("f.x", "10"),
        Assign("f.y", "5"),
        Assign("h", "3"),
        Assign("f.x", "4"),
        Assign("f.y", "9"),
        Assign()
    ];

    std::vector<Assign> g_code = [
        Assign("g.x", "4"),
        Assign("g.y", "3"),
        Assign("h", std::to_string(g_b)),
        Assign("h", "4"),
        Assign("g.x", "3"),
        Assign("g.y", "3"),
        Assign()
    ];
    
    std::vector<State> states;
    State state;
    next_state(
        state,
        states,
        f_code,
        0,
        g_code,
        0
    );
    return states;
}

void print_states(std::string filename, std::vector<State> states) {
    std::ofstream f(filename);
    f << "c_f, c_g, h, f.x, f.y, g.x, g.y" << std::endl;
    for (const State& state: states) {
        f << state["c_f"] << ", "
          << state["c_g"] << ", "
          << state["h"] << ", "
          << state["f.x"] << ", "
          << state["f.y"] << ", "
          << state["g.x"] << ", "
          << state["g.y"] << std::endl;           
    }
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
    
    std::vector<State> states = calculate_states(
        args.values[0], 
        args.values[1],
        args.values[2],
        args.values[3]
    );
    
    print_states(args.filename, states);
    // if (args.count
}






