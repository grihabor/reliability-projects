int h;
void
f (int a, int b)
{
  int x, y;
  x = 10;
  y = 5;
  h = 3;
  x = 4;
  y = 9;
  if (h < y - x)
    {
      if (y < 7)
        {
          if (h > 5)
            {
              y = 6;
            }
          x = 1;
        }
    }
}

void
g (int a, int b)
{
  int x, y;
  x = 4;
  y = 3;
  h = b;
  if (y > 5)
    {
      x = 10;
    }
  else
    {
      h = x;
    }
  x = 3;
  y = 3;
  while (x < 2)
    {
      if (h > 0)
        break;
      if (h < x + y)
        {
          h = y - x;
          y = 3;
          x = 9;
        }
    }
}
