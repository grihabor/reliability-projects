/*
 * Reliability Task 1
 * Borodin Gregory
 * 2017
 */

#include "header/run.h"


int main(int argc, char **argv) {
    /* Entrypoint */

    // Parse arguments from 1 to argc-1
    Args args(argc - 1, argv + 1);
    run(args);
}






