//
// Created by grihabor on 08.10.17.
//


#include "../../header/init/state.h"
#include "../../header/state.h"

State get_initial_state() {

    StateMapping initial_mapping = {
            {"c_f", "0"},
            {"c_g", "0"},
            {"h",   "#"},
            {"f.x", "#"},
            {"f.y", "#"},
            {"g.x", "#"},
            {"g.y", "#"}
    };
    return State(initial_mapping);
}


State get_initial_state_h_only() {

    StateMapping initial_mapping = {
            {"c_f", "0"},
            {"c_g", "0"},
            {"h",   "#"},
    };
    return State(initial_mapping);
}
