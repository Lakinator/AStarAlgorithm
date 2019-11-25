#ifndef LIST_H
#define LIST_H

#include "node.h"

typedef struct _LIST {
    int len;
    struct _NODE* start;
} LIST;

void l_insertFirst(LIST* list, POINT data);
void l_insertLast(LIST* list, POINT data);
int l_deleteNodeAt(LIST* list, int pos);
NODE* l_getNodeAt(LIST* list, int pos);
int l_getNodePos(LIST* list, NODE* n); // NODE *n will be free'd !
void l_printList(LIST* list);

#endif