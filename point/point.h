#ifndef POINT_H
#define POINT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _POINT {
    int x;
    int y;
    int scoreF;
    int scoreG;
    int scoreH;
    struct _POINT* parent;
} POINT;

int p_cmp(POINT* p1, POINT* p2);
void p_print(POINT* p);

#endif