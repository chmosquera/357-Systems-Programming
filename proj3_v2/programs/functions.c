/*
 * Project: smake
 * Program Name: functions.c
 * Author: Chanelle Mosquera
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "functions.h"
#include "linkedlist.h"

extern struct LLRule * LIST_RULES;

/************************ store rules in file into data structure ***************/
/* Build linked list of rules in Smakefile */
struct LLRule * BuildRules(FILE * file){ 
    char * line, * target, * sep;
    struct Rule * rule = NULL;
    struct NodeRule * node_rule;
    struct NodeDepAct *node_act;
    struct LLRule * list_rules;
    struct LLDepAct * list_acts, * list_deps;

    list_acts = CreateLLDepAct();
    list_rules = CreateLLRule();

    while ((line = readline(file)) != NULL) {
        if (line[0] == '\0') {} /* skip blank lines */
        else if (line[0] == '\t') {
            /* if linked list for actions doesn't exist, create it. 
             * Add action to linked list. */
            if (list_acts->head == NULL) {
                list_acts = CreateLLDepAct();
            }
            ++line;
            node_act = CreateNodeDepAct(line);
            AddNodeDepAct(node_act, list_acts);
        }
        else {
            if (rule != NULL) { /* Finished creating a rule, add its actions, add rule to list */
                node_rule = BuildRule(rule, list_deps, list_acts);
                AddNodeRule(node_rule, list_rules);
                list_acts = CreateLLDepAct();
            }
            /* Create a new rule with target. Make sure separator exists */
            target = strtok(line, " ");
            sep = strtok(NULL, " ");
            if (strcmp(sep, ":") != 0) {        
                fprintf(stderr, "Smakefile: *** missing separator.  Stop.\n");
            }
            rule = CreateRule(target);
            list_deps = BuildDep(NULL);
        }
    }
    node_rule = BuildRule(rule, list_deps, list_acts);
    AddNodeRule(node_rule, list_rules);

    return list_rules;
}

/* Sets the Rule's dependencies and actions and returns node with that rule */
struct NodeRule * BuildRule(struct Rule *r, struct LLDepAct *d, struct LLDepAct *a){
    struct NodeRule * node_rule;

    r->deps = d;
    r->acts = a;

    node_rule = CreateNodeRule(r);
    return node_rule;
}

/* Given a string, creates a linked list of all the dependencies from string */
struct LLDepAct * BuildDep(char * s) {
    struct LLDepAct * list;
    struct NodeDepAct *n;
    char * str;
    char * tok;

    if (s == NULL) {
        str = NULL;
    } else {
        str = strdup(s);
    }

    list = CreateLLDepAct();

    /* Expand list */
    while ((tok = strtok(str, " ")) != NULL) {
        n = CreateNodeDepAct(tok);
        AddNodeDepAct(n, list);
        str = NULL;
    }

    return list;
}

/* Basic Node Constructor - only a target is required */
struct Rule * CreateRule(char *t){
    struct Rule * rule;
    rule = (struct Rule *)malloc(sizeof(struct Rule));
    rule->target = t;
    return rule;
}

void PrintRule(struct Rule * rule) {
    
    printf("\ntarget: %s\n", rule->target);
    printf("deps: \n");
    PrintLLDepAct(rule->deps);
    printf("acts: \n");
    PrintLLDepAct(rule->acts);
}

/****************** Rule Processing **********************/

void ProcessRule(struct Rule * rule) {
    struct NodeDepAct * currentDep;
    struct stat * ruleStat;   
    int i, needsUpdate = 0;

    /* Execute actions if no dependencies */
    if (rule->deps->head == NULL) {
        ExecuteActions(rule->acts);
        return;
    }

    /* Otherwise process each dependency */
    ruleStat = (struct stat *)malloc(sizeof(struct stat));
 
    currentDep = rule->deps->head;
    stat(rule->target, ruleStat);

    while (currentDep != NULL) {
        i = ProcessDep(currentDep);
/*        printf("\n\nRULE: %s\tDEP: %s\tDEPTYPE: %d\n", rule->target, currentDep->depAct, i);   */
        if (i == 0) {
            NoTargetError(rule->target);
        }
        else if (i == 1 || i == 3) { /* dep is file or a both target & file*/
            double time = 0;
            struct stat * depStat = (struct stat *)malloc(sizeof(struct stat));
            stat(currentDep->depAct, depStat);
            if ((time = difftime(ruleStat->st_mtime, depStat->st_mtime)) < 0
                 || (access(rule->target, F_OK) != 0) ) {
                needsUpdate = 1;
            }
            free(depStat);
        }
        else if (i == 2) { /* dep is target only */
            struct Rule * depRule;
            depRule = SearchRule(currentDep->depAct);
            ExecuteActions(depRule->acts);
            needsUpdate = 1;
        } 
        currentDep = currentDep->next;
    }
    if (needsUpdate == 1) {
        ExecuteActions(rule->acts);
    }

    free(ruleStat);
    return;
}


/* 0 - dep does not exist
 * 1 - dep is a file
 * 2 - dep is target
 * 3 - dep is target and file */
int ProcessDep(struct NodeDepAct * dep) {
    struct Rule * newRule;

    /* if dep is a target */
    if ((newRule = SearchRule(dep->depAct)) != NULL) {
        if (newRule->deps->head == NULL) {  /* dep is target w/out dependencies */
            return 2;
        }
        else {
            ProcessRule(newRule);
            return 3;
        }
    }
   /* if dep is a file */
    else if (access(dep->depAct, F_OK) == 0) { 
        return 1;
    }

    /* dep is not a file or a target */
    return 0;
}

/* Checks if given string is name of a target in list of rules */
struct Rule * SearchRule(char * t) {
    struct NodeRule * currentRule;

    currentRule = LIST_RULES->head;
    while (currentRule != NULL) {
        if (strcmp(t, currentRule->rule->target) == 0) {
            return currentRule->rule;
    }
        currentRule = currentRule->next;
    }
    return NULL;
}

void ExecuteActions(struct LLDepAct *list_acts) {
    struct NodeDepAct * act;
    char * temp;

    act = list_acts->head;
    while (act != NULL) {
        fprintf(stdout, "%s\n", act->depAct);
        temp = strdup(act->depAct);

        if (WEXITSTATUS(system(temp)) == 1) {
            exit(0);
        }
        free(temp);
        act = act->next;
    }
}


/************************* other functions *********************/

void NoTargetError(char * target) {
    fprintf(stderr, "smake: *** No rule to make target '%s'. Stop.\n", target);
    exit(0);
}


void FreeRule(Struct Rule * rule) {
    free(rule->target);
    FreeLLDepAct(rule->deps);
    FreeLLDepAct(rule->acts);
    free(rule);

}

/* Reads line */
char * readline(FILE * file){
    
    int size = 20;
    int cnt = 1;

    char *line;
    char c = NULL;

    if((line = (char *) malloc(sizeof(char) * size)) == NULL){
        exit(-1);   
    };

    c = fgetc(file);
    while (c != '\n' && c!= EOF) {
        if (cnt >=  size-1) { /* Array is not big enough, must realloc */
            char *temp = NULL;
            size = size * 2;
            temp = (char *) realloc(line, (sizeof(char)*size));
            if (temp == NULL) { /*if realloc was not able to allocate memory*/
                free(line);
                exit(-1);
            }
            line = temp;
        }

        line[cnt-1] = c;
        c = fgetc(file);
        ++cnt;
    }
    if (c == EOF && cnt == 1) {
        free(line);
        return NULL;
    }
    line[cnt-1] = '\0';
    line = realloc(line, (sizeof(char)*cnt));

    return line;
}
