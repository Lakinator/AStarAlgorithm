#include "list.h"

void l_insertFirst(LIST* list, POINT data) {
    if (list->len == 0) {
        list->start = createNode(data);
    } else {
        NODE* newNode = createNode(data);
        newNode->next = list->start;
        list->start = newNode;
    }

    list->len++;
}

void l_insertLast(LIST* list, POINT data) {
    if (list->len == 0)
        l_insertFirst(list, data);
    else {
        n_insertLast(list->start, data);
        list->len++;
    }
}

int l_deleteNodeAt(LIST* list, int pos) {
    if (list->len == 0 || pos < 0)
        return 0;
    else if (list->len > 0 && pos == 0) {
        NODE* n = list->start;
        list->start = n->next;
        free(n);
        list->len--;
        return 1;
    } else {
        if (n_deleteNodeAt(list->start, pos)) {
            list->len--;
            return 1;
        } else {
            return 0;
        }
    }
}

NODE* l_getNodeAt(LIST* list, int pos) {
    if (list->len == 0 || pos < 0)
        return NULL;
    else {
        return n_getNodeAt(list->start, pos);
    }
}

int l_getNodePos(LIST* list, NODE* n) {
    if (list->len == 0) {
        free(n);
        return -1;
    } else {
        if (n_cmp(list->start, n)) {
            free(n);
            return 0;
        } else if (list->len > 1) {
            return n_getNodePos(list->start->next, n, 1);
        } else {
            free(n);
            return -1;
        }
    }
}

void l_printList(LIST* list) {
    if (list->len == 0)
        printf("Empty list!\n");
    else {
        n_printNode(list->start);
    }
}