#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void append_list(list_t *list, int data) {
    if (list->head == NULL) {
        list->head = new_node(data);
        list->tail = list->head;
    } else {
        list->tail->next = new_node(data);
        list->tail = list->tail->next;
    }
}

int contains_list(list_t *list, int data) {
    node_t *node = list->head;
    while (node) {
        if (node->data == data) {
            return 1;
        }
        node = node->next;
    }
    return 0;
}

list_t *new_list() {
    list_t *list = (list_t*)malloc(sizeof(list_t));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

void print_list(list_t *list) {
    node_t *node = list->head;
    while (node) {
        printf("%d",node->data);
        if (node->next != NULL) {
            printf("->");
        }
        node = node->next;
    }
    printf("\n");
}

void free_list(list_t *list) {
    node_t *node,*next;
    node = list->head;
    while (node) {
        next = node->next;
        free(node);
        node = next;
    }
    free(list);
}

node_t *new_node(int data) {
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->data = data;
    return node;
}