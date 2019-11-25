#include "node.h"

NODE* createNode(POINT data) {
    NODE* newNode = malloc(sizeof(NODE));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

int n_cmp(NODE* n1, NODE* n2) { return p_cmp(&n1->data, &n2->data); }

void n_insertLast(NODE* node, POINT data) {
    if (node->next == NULL) {
        NODE* newNode = createNode(data);
        node->next = newNode;
    } else {
        n_insertLast(node->next, data);
    }
}

int n_deleteNodeAt(NODE* node, int pos) {
    if (pos == 1) {
        NODE* n = node->next;
        node->next = n->next;
        free(n);
        return 1;
    } else {
        return n_deleteNodeAt(node->next, --pos);
    }
}

NODE* n_getNodeAt(NODE* node, int pos) {
    if (pos == 0)
        return node;
    else
        return n_getNodeAt(node->next, --pos);
}

int n_getNodePos(NODE* node, NODE* n, int pos) {
    if (n_cmp(node, n)) {
        free(n);
        return pos;
    } else {
        if (node->next != NULL)
            return n_getNodePos(node->next, n, ++pos);
        else {
            free(n);
            return -1;
        }
    }
}

void n_printNode(NODE* node) {
    p_print(&node->data);

    if (node->next != NULL) {
        n_printNode(node->next);
    } else {
        printf("End of list reached!\n");
    }
}
