#include "point.h"

int p_cmp(POINT* p1, POINT* p2) { return (p1->x == p2->x && p1->y == p2->y); }

void p_print(POINT* p) {
    printf("POINT{x = %d, y = %d, scoreF = %d, scoreG = %d, scoreH = %d}\n",
           p->x, p->y, p->scoreF, p->scoreG, p->scoreH);
}