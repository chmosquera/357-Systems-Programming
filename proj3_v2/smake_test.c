/* Test - smake functions and linkedlist */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "functions.h"
#include "linkedlist.h"

extern struct LLRule * LIST_RULES;

/********** LINKED LIST TESTS *********/
void CreateNode_t() {

}

/********** FUNCTIONS TESTS *********/

/* Tests: CreateLLDepAct(), CreateNodeDepAct(), PrintLLDepAct(), AddNodeDepAct() */
void CreateLLDepAct_t() {
    char * item1 = "hello";
    char * item2 = "world";
    char * item3 = "apple";
    char * item4 = "orange";
    struct NodeDepAct * node, * prevNode;
    struct LLDepAct * list;

    printf("\nTesting: CreateLLDepAct_t\n\n");

    list = CreateLLDepAct();
    node = CreateNodeDepAct(item1);
    AddNodeDepAct(node, list);

    printf("head: %s \t tail %s\n", list->head->depAct, list->tail->depAct);

    prevNode = node;
    node = CreateNodeDepAct(item2);
    prevNode->next = node;
    list->tail = node;

    printf("head: %s \t tail %s\n", list->head->depAct, list->tail->depAct);
    
    prevNode = node;
    node = CreateNodeDepAct(item3);
    prevNode->next = node;
    list->tail = node;
    printf("head: %s \t tail %s\n", list->head->depAct, list->tail->depAct);

    /* AddNodeDepAct() */
    node = CreateNodeDepAct(item4);
    AddNodeDepAct(node, list);

    printf("head: %s \t tail %s\n", list->head->depAct, list->tail->depAct);

    PrintLLDepAct(list);
}

/* Test: build a linked list of dependencies when given a line */
void BuildDep_t(char * s) {
    struct LLDepAct * list;
    printf("\nTesting: BuildDep_t\n\n");
    list = BuildDep(s);
    PrintLLDepAct(list);
}

void BuildAct_t() {

    struct LLDepAct * list_act = CreateLLDepAct();
    struct NodeDepAct * n;
    char * a1 = "action 1";
    char * a2 = "action 2";

    printf("\n Testing: BuildAct_t\n\n");

    n = CreateNodeDepAct(a1);
    AddNodeDepAct(n, list_act);
    printf("head: %s \t tail: %s\n", list_act->head->depAct, list_act->tail->depAct);
    
    n = CreateNodeDepAct(a2);
    AddNodeDepAct(n, list_act);
    printf("head: %s \t tail: %s\n", list_act->head->depAct, list_act->tail->depAct);
}

/*
void CreateRule_t() {
    struct NodeRule * n;
    struct Rule * r;
    char * target = "hello";

    struct LLDepAct * list_dep, * list_act;
    struct NodeDepAct * d, * a;
    char * deps = "main.o other.o echo";
    char * act = "gcc other action words";
        
    r = CreateRule(target);
    n = CreateNodeRule(r);

    list_dep = BuildDep(deps);
    SetDeps(r, list_dep);
} */

void BuildRules_t() {
    FILE * file;
    struct LLRule * list_rules;

    printf("\nTesting: BuildRules_t\n\n");
    file = fopen("Makefile.testing", "r");
    list_rules = BuildRules(file);

    PrintLLRule(list_rules);
    fclose(file);
}

void SearchRule_t() {
    struct Rule * rule;
    char * rule1 = "main", *rule2 = "echo", *rule3 = "notrule";

    printf("\nTesting: SearchRule_t()\n");

    printf("\nSearching '%s' ...\n", rule1);
    if ((rule = SearchRule(rule1)) != NULL) {
        PrintRule(rule);
    }
    else {
        printf("'%s' does not exist\n", rule1);
    }
    
    printf("\nSearching '%s' ...\n", rule2);
    if ((rule = SearchRule(rule2)) != NULL) {
        PrintRule(rule);
    }
    else {
        printf("'%s' does not exist\n", rule2);
    }

    printf("\nSearching '%s' ...\n", rule3);
    if ((rule = SearchRule(rule3)) != NULL) {
        PrintRule(rule);
    }
    else {
        printf("'%s' does not exist\n", rule3);
    }

}

void ProcessDep_t() {
    struct NodeDepAct * dep;
    double ruleModTime;
    char * fileName;
    struct stat * ruleStat = (struct stat *)malloc(sizeof(struct stat));
    int i;

    /* main -> main.o *
     * main.o -> main.c */

    /* ERROR */
    fileName = "main";
    stat(fileName, ruleStat);
    dep = CreateNodeDepAct("notarealfile");    
    ruleModTime = ruleStat->st_mtime;
    i = ProcessDep(dep);       
    printf("Expected '3', actual '%d'\n\n", i);
    free(dep);

    /* Target */
    fileName = "main";
    stat(fileName, ruleStat);
    dep = CreateNodeDepAct("main.o");
    ruleModTime = ruleStat->st_mtime;
    i = ProcessDep(dep);       
    printf("Expected '2', actual '%d'\n\n", i);
    free(dep);

    /* Updated File */
    FILE * file = fopen("main.c", "w");
    fprintf(file, "ProcessDep_t()\n");
    fclose(file);

    fileName = "main.o";
    stat(fileName, ruleStat);
    dep = CreateNodeDepAct("main.c");
    ruleModTime = ruleStat->st_mtime;
    i = ProcessDep(dep);       
    printf("Expected '1', actual '%d'\n\n", i);
    free(dep);

    /* Non-updated File */
    file = fopen("main.o", "w");
    fprintf(file, "ProcessDep_t()\n");
    fclose(file);

    fileName = "main.o"; /* hAs not been updated in a long time */
    stat(fileName, ruleStat);
    dep = CreateNodeDepAct("main.c");
    ruleModTime = ruleStat->st_mtime;
    i = ProcessDep(dep);       
    printf("Expected '0', actual '%d'\n\n", i);
    free(dep);
}

void ExecuteActions_t() {
    struct Rule * currentRule = LIST_RULES->head->rule;
    struct LLDepAct *list_acts;

    list_acts = currentRule->acts;

    ExecuteActions(list_acts);

}

void strtok_t(char * line, char * delim) {
    char * tok;
    char * s = strdup(line);

    printf("Testing: strtok_t()\n");
    printf("%s\n", line);

    tok = strtok(s, delim);

    while (tok != NULL) {
        printf("line: %s\n", line);
        printf("%s\t\t", tok);
        tok = strtok(NULL, delim);
    }
    printf("\n\n");
}

void ProcessRule_t() {
    struct NodeRule * currentRule;

    printf("Testing: ProcessRule_t()\n");

    currentRule = LIST_RULES->head;


    ProcessRule(currentRule->rule);
    
/*    while (currentRule != NULL) {
        ProcessRule(currentRule->rule);
        currentRule = currentRule->next;
    } */

 
}

int main(int argc, char ** argv) {
    FILE * file;
    file = fopen(argv[1], "r");

    LIST_RULES = BuildRules(file);
/*    PrintLLRule(LIST_RULES); */


/*    strtok_t("hello world we are testing strtok()", " ");
    strtok_t("main : main.o other.o echo", " ");
    strtok_t("main : main.o ~ other.o : echo", ": ~"); */

/*    BuildDep_t("main.o other.o echo");
    BuildAct_t();
    CreateLLDepAct_t();*/
/*    BuildRules_t(); */
/*    SearchRule_t();*/
/*    ProcessDep_t();*/
/*    ExecuteActions_t();*/
    ProcessRule_t(); 

    return 1;

}
