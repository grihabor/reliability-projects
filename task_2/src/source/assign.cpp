//
// Created by grihabor on 03.10.17.
//

#include "../header/assign.h"

Assign::Assign(std::string field, std::string value)
        : field(std::move(field)),
          value(std::move(value)) {}

Assign::Assign()
        : field(std::string("")),
          value(std::string("")) {}
