//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_ASSIGN_H
#define TASK_2_ASSIGN_H

#include <string>

struct Assign {
    std::string field;
    std::string value;

    Assign(std::string field, std::string value);

    Assign();

    explicit operator std::string() const;
};


#endif //TASK_2_ASSIGN_H
