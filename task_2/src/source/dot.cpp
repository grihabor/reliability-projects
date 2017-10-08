//
// Created by grihabor on 08.10.17.
//


#include <fstream>
#include <sstream>
#include <iostream>
#include "../header/dot.h"





int get_index(const State& state, IndexMapping mapping) {
    std::string s = static_cast<std::string>(state);
    std::cout << s << std::endl;
    return mapping.at(s);
}


std::ofstream &operator<<(std::ofstream &f, const Dot& dot) {
    const StateGraph &graph = dot.graph;

    IndexMapping mapping;
    int count = 0;

    f << "digraph G {" << std::endl;

    for (const State& state : graph.states) {
        /* Write nodes */
        std::string state_str = static_cast<std::string>(state);
        mapping[state_str] = count;
        f << count << " " << "[label=\"" << state_str << "\"];" << std::endl;
        ++count;
    }

    std::set<std::string> links_str;

    for (std::pair<Link, Assign> pair : graph.links) {
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

Dot::Dot(StateGraph graph) : graph(graph)
{}
