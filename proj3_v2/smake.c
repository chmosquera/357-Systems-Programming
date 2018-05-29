/*
 * Project: smake
 * Program Name: smake.c
 * Author: Chanelle Mosquera
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "linkedlist.h"

extern struct LLRule * LIST_RULES;

int main(int argc, char ** argv) {
    
    FILE * file;
    struct Rule * currentRule;

    if ((file = fopen("Smakefile", "r")) == NULL) {
        fprintf(stderr, "smake: *** No targets. Stop.\n");
        exit(0);
    }
    
    LIST_RULES = BuildRules(file);

    /* Argument Provided */
    if (argc > 1) {
        if ((currentRule = SearchRule(argv[1])) == NULL) {
            NoTargetError(argv[1]);
        }
        ProcessRule(SearchRule(argv[1]));
    } else if (argc == 1) {
        ProcessRule(LIST_RULES->head->rule);
    }

    FreeLLRule(LIST_RULES);   

    return 1;

    
}
