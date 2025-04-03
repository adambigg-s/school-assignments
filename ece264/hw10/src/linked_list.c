#include <stdlib.h>

#include "linked_list.h"

struct LinkedList linkedlist_new() {
    struct LinkedList output = {.head = NULL, .tail = NULL};
    return output;
}

struct ListNode *new_node(size_t value) {
    struct ListNode *output = malloc(sizeof(struct ListNode));
    if (output == NULL) {
        fprintf(stderr, "fail making listnode");
        exit(1);
    }
    output->value = value;
    output->next = NULL;
    output->prev = NULL;
    return output;
}

void insert_at_head(struct LinkedList *list, size_t value) {
    struct ListNode *new = new_node(value);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    }
}

void insert_at_tail(struct LinkedList *list, size_t value) {
    struct ListNode *new = new_node(value);
    if (list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        new->prev = list->tail;
        list->tail = new;
    }
}

size_t remove_from_head(struct LinkedList *list) {
    if (list->head == NULL) {
        fprintf(stderr, "failure list empty");
        return 0;
    }
    struct ListNode *temp = list->head;
    size_t value = temp->value;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(temp);
    return value;
}

size_t remove_from_tail(struct LinkedList *list) {
    if (list->head == NULL) {
        fprintf(stderr, "failure list empty");
        return 0;
    }
    struct ListNode *temp = list->tail;
    size_t value = temp->value;
    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(temp);
    return value;
}

void free_list(struct LinkedList *list) {
    struct ListNode *current = list->head;
    while (current != NULL) {
        struct ListNode *next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
    list->tail = NULL;
}

void dump_list(struct LinkedList list) {
    printf("[ ");
    for (struct ListNode *cur = list.head; cur != NULL; cur = cur->next) {
        printf("%zu, ", cur->value);
    }
    printf("]\n");
}
