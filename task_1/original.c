int h;
void
f (int a, int b)
{
  int x, y;
0:  x = 10;
1:  y = 5;
2:  h = 3;
3:  x = 4;
4:  y = 9;
5:  if (h < y - x)
    {
6:      if (y < 7)
        {
7:          if (h > 5)
            {
8:              y = 6;
            }
9:          x = 1;
        }
    }
10:}

void
g (int a, int b)
{
  int x, y;
0:  x = 4;
1:  y = 3;
2:  h = b;
3:  if (y > 5)
    {
4:      x = 10;
    }
  else
    {
5:      h = x;
    }
6:  x = 3;
7:  y = 3;
8:  while (x < 2)
    {
9:      if (h > 0)
        break;
10:      if (h < x + y)
        {
11:          h = y - x;
12:          y = 3;
13:          x = 9;
        }
    }
14:}
