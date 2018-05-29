/*
 * Project: smake
 * Program Name: linkedlist.c
 * Author: Chanelle Mosquera
 */

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "functions.h"

/* Constructs node with rule */
struct NodeRule * CreateNodeRule(struct Rule * r) {
    struct NodeRule * temp;
    temp = (struct NodeRule *)malloc(sizeof(struct NodeRule));
    temp->rule = r;
    temp->next = NULL;
    return temp;
}

/* Construct node with either a dependency or an action */
struct NodeDepAct * CreateNodeDepAct(char * da){
    struct NodeDepAct * temp;
    temp = (struct NodeDepAct *)malloc(sizeof(struct NodeDepAct));
    temp->depAct = da;
    temp->next = NULL;
    return temp;
}

/* Construct linked list of rule nodes */
struct LLRule * CreateLLRule(){
    struct LLRule * list;
    list = (struct LLRule *)malloc(sizeof(struct LLRule));
    return list;
}

/* Construct linked list of dependencies or actions */
struct LLDepAct * CreateLLDepAct(){
    struct LLDepAct * list;
    list = (struct LLDepAct *)malloc(sizeof(struct LLDepAct));
    return list;
}

/* Add dependency/action node into linked list. if list is empty, set as head */
void AddNodeDepAct(struct NodeDepAct * n, struct LLDepAct * list) {
    if (list->head == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        struct NodeDepAct * prevn;
        prevn = list->tail;
        prevn->next = n;
        list->tail = n;
    }
}

/* Add rule node into linked list. if list is empty, set as head */
void AddNodeRule(struct NodeRule * n, struct LLRule * list) {
    if (list->head == NULL) {
        list->head = n;
        list->tail = n;
    } else {
        struct NodeRule * prevn;
        prevn = list->tail;
        prevn->next = n;
        list->tail = n;
    }
}

/* TESTING PURPOSES - print list of dep/act nodes */
void PrintLLDepAct(struct LLDepAct * list) {
    struct NodeDepAct * current;

    current = list->head;

    while (current != NULL) {
        printf("%s\t", (current)->depAct);
        current = current->next;
    }
    printf("\n");
}

/* TESTING PURPOSES - print list of rule nodes */
void PrintLLRule(struct LLRule *list) {
    struct NodeRule * current;

    current = list->head;
    if (current == NULL) {
        printf("\ncurrent is null\n");
    }
    while( current != NULL) {
        printf("\n$Target: %s\n", current->rule->target);
        printf("\n$Dependencies:\n");
        PrintLLDepAct(current->rule->deps);
        printf("\n$Actions:\n");
        PrintLLDepAct(current->rule->acts);
        printf("\n");
        current = current->next;
    }
}

void FreeNodeDepAct(struct NodeDepAct * da) {
    free(da->depAct);
    free(da);
}

void FreeLLDepAct(struct LLDepAct * list) {
    struct NodeDepAct * temp, *prevtemp;

    temp = list->head;
    while (list->tail != NULL) {
        prevtemp = temp;
        temp = temp->next;
        FreeNodeDepAct(prevTemp);
    }
}

void FreeNodeRule(struct NodeRule * node_rule) {
    FreeRule(node_rule->rule);
    free(node_rule);
}

void FreeLLRule(struct LLRule * list) {
    struct NodeRule * temp, *prevtemp;

    temp = list->head;
    while (list->tail != NULL) {
        prevtemp = temp;
        temp = temp->next;
        FreeNodeRule(prevTemp);
    }
}

