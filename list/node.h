#ifndef NODE_H
#define NODE_H

#include "../point/point.h"

typedef struct _NODE {
    POINT data;
    struct _NODE* next;
} NODE;

NODE* createNode(POINT data); // Pointer must be free'd !
int n_cmp(NODE* n1, NODE* n2);
void n_insertLast(NODE* node, POINT data);
int n_deleteNodeAt(NODE* node, int pos);
NODE* n_getNodeAt(NODE* node, int pos);
int n_getNodePos(NODE* node, NODE* n, int pos);
void n_printNode(NODE* node);

#endif