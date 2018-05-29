/*
 * Project: smake
 * Program Name: linkedlist.h
 * Author: Chanelle Mosquera
 */
#include "functions.h"
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct NodeRule {
    struct Rule * rule;
    struct NodeRule * next;
};

struct NodeDepAct {
    char * depAct;
    struct NodeDepAct * next;
};

struct LLRule {
    struct NodeRule * head;
    struct NodeRule * tail;
};

struct LLDepAct {
    struct NodeDepAct * head;
    struct NodeDepAct * tail;
};

struct NodeRule * CreateNodeRule(struct Rule *);

struct NodeDepAct * CreateNodeDepAct(char *);

struct LLRule * CreateLLRule();

struct LLDepAct * CreateLLDepAct();

void AddNodeDepAct(struct NodeDepAct *, struct LLDepAct *);

void AddNodeRule(struct NodeRule *, struct LLRule *);

void PrintLLDepAct(struct LLDepAct *);

void PrintLLRule(struct LLRule *);
/*

void FreeList(struct LinkedList);
*/

#endif
