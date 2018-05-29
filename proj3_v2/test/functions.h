/*
 * Project: smake
 * Program Name: functions.h
 * Author: Chanelle Mosquera
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "linkedlist.h"

struct LLRule * LIST_RULES;

struct Rule {
    char * target;
    struct LLDepAct * deps;
    struct LLDepAct * acts;
};

/* Keeps track of whether target main needs an update */
int UpdateMain;

void OpenFile();

struct LLRule * BuildRules(FILE * file);

struct NodeRule * BuildRule(struct Rule *, struct LLDepAct *, struct LLDepAct *);

struct LLDepAct * BuildDep(char *);

struct Rule * CreateRule(char *t);

/* Processes given rule, checking type of target and update status
 * execute rule's actions if necessary
 */
void ProcessRule(struct Rule *);

int ProcessDep(struct NodeDepAct *);

struct Rule * DepIsTarget(char *);

struct FILE * DepIsFile(char *);

int NeedUpdate(FILE *);

void ExecuteActions(struct LLDepAct *);

void FreeRule(struct Rule *);

struct Rule * SearchRule(char *);

char * readline(FILE *file);

void NoTargetError(char * target);

    /* For testing purposes */
void PrintRule(struct Rule *);


#endif
