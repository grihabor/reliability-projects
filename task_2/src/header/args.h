//
// Created by grihabor on 03.10.17.
//

#ifndef TASK_2_ARGS_H
#define TASK_2_ARGS_H


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

    // if you should generate lts
    bool lts;

    Args();

    Args(int argc, char **argv);
};


#endif //TASK_2_ARGS_H
