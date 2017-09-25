
/*
This is modified version of task code. Use it to analyze program behaviour

int h;
void
f (int a, int b)
{
    int x, y;
1:  x = 10;
2:  y = 5;
3:  h = 3;
4:  x = 4;
5:  y = 9;

    // always true
    if (h < y - x) {

        // always false
        if (y < 7) {
            if (h > 5) {
                y = 6;
            }
            x = 1;
        }
    }
6:}

void
g (int a, int b) {

    int x, y;
1:  x = 4;
2:  y = 3;
3:  h = b;

    // always false
    if (y > 5) {
         x = 10;
    } else {
4:       h = x; // h = 4;
    }
5:  x = 3;
6:  y = 3;

    // always false
    while (x < 2) {
        if (h > 0) {
            break;
        }
        if (h < x + y) {
            h = y - x;
            y = 3;
            x = 9;
        }
    }

7:}
*/


void print_info() {
    printf("Reliability Task 1\n");
    printf("Borodin Gregory\n");
    printf("2017\n");
    printf("\n");
    printf("Usage: task1 <f_a> <f_b> <g_a> <g_b>\n");
}


struct Args {
    /* Struct to store command line arguments */
    
    // name of the file to write output to
    std::string filename;
    // whether program should print count
    bool print_count;
    // values to feed into f and g
    int values[4];
    
    // if format is valid
    bool ok;
    
    Args() 
      : filename('states.txt'),
        print_count(false),
        ok(false)
    {}
}


Args parse_args(int argc, char **argv) {
    /* Parse command line arguments */
    
    // initialize args struct
    Args args;
    args.ok = false;
    args.print_count = false;
    
    int i = 0;
    int count = 0;
    
    for (i = 0; i < argc; ++i) {
        /* loop through argv */
        
        // read an arg
        std::string arg = argv[i];
        
        if (arg == '-file') {
            /* handle file parameter */
            // read next param
            ++i;
            // store it in `filename` field
            args.filename = argv[i];
        } else if (arg == '-count') {
            /* handle count parameter */
            args.print_count = true;
        } else {
            /* handle value */
            
            if (count >= 4) {
                /* too many values */
                count = -1;
                break;
            }
            // parse int value and store in `values`
            args.values[count++] = std::stoi(arg);
        }
    }
    
    if (count == 4) {
        /* Assert for exactly 4 args */
        args.ok = true;
    }
    
    return args;
}


void print_states(Args args) {
    ofstream f(args.filename);
    f << "c_f, c_g, h, f.x, f.y, g.x, g.y";
}

int main(int argc, char **argv) {
    /* Entrypoint */
    
    Args args = parse_args(argc, argv);
   
    if (!args.ok) {
        /* too few args */
        print_info();
        return 0;
    }
    
    print_states();
}






