#include "part6.h"

struct point create_point(double x, double y)
{
   struct point p = {x, y};
   return p;
}

int is_a_square(struct rectangle rect) {
   double w, h;
   w = rect.bottom_right.x - rect.top_left.x;
   h = rect.top_left.y - rect.bottom_right.y;
   if (w == h) return 1;  
   return 0;

}
