
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

    always true
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

    always false
    if (y > 5) {
         x = 10;
    } else {
4:       h = x; // h = 4;
    }
5:  x = 3;
6:  y = 3;

    always false
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



int main(int argc, char** argv) {
    
}

