//
// Created by grihabor on 08.10.17.
//


#include "../../header/run.h"

Code get_f_code() {

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

Code get_f_code_h_only() {

    // Fill in the f function code
    std::vector<Assign> f_code;
    f_code.emplace_back("h", "3");
    f_code.emplace_back();

    return f_code;
}

Code get_g_code(int b) {
    // Fill in the g function code
    std::vector<Assign> g_code;
    g_code.emplace_back("g.x", "4");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back("h", std::to_string(b));
    g_code.emplace_back("h", "4");
    g_code.emplace_back("g.x", "3");
    g_code.emplace_back("g.y", "3");
    g_code.emplace_back();

    return g_code;
}

Code get_g_code_h_only(int g_b) {
    // Fill in the g function code
    std::vector<Assign> g_code;
    g_code.emplace_back("h", std::to_string(g_b));
    g_code.emplace_back("h", "4");
    g_code.emplace_back();

    return g_code;
}
