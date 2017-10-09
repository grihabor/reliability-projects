//
// Created by grihabor on 08.10.17.
//

#ifndef TASK_2_DOT_H
#define TASK_2_DOT_H

#include <string>
#include "typedefs.h"

typedef std::map<std::string, int> IndexMapping;

struct Dot {
    Dot(StateGraph graph);

    const StateGraph &graph;
};

std::ofstream &operator<<(std::ofstream &f, const Dot& graph);


#endif //TASK_2_DOT_H
