#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdbool.h>
#include <stdio.h>

struct ListNode {
    size_t value;
    struct ListNode *next;
    struct ListNode *prev;
};

struct LinkedList {
    struct ListNode *head;
    struct ListNode *tail;
};

struct LinkedList linkedlist_new();
void insert_at_head(struct LinkedList *list, size_t value);
void insert_at_tail(struct LinkedList *list, size_t value);
size_t remove_from_head(struct LinkedList *list);
size_t remove_from_tail(struct LinkedList *list);
void dump_list(struct LinkedList list);
void free_list(struct LinkedList *list);

#endif // LINKED_LIST_H_
