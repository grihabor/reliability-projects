//
// Created by grihabor on 03.10.17.
//


#include <stdexcept>
#include <iostream>
#include "../header/args.h"

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
            } catch (const std::invalid_argument &e) {
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

Args::Args()
        : filename(std::string("states.txt")),
          print_total_count(false),
          values{0, 0, 0, 0},
          ok(false) {}

Args::Args(int argc, char **argv) {
    Args args = parse_args(argc, argv);
    *this = args;
}
