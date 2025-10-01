/*
    Copyright (c) 2025 Ghica Ana-Maria
    All rights reserved

    Facultatea de Automatica si Calculatoare
    Seria CD, grupa 314
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---STRUCTURI---------------------------------------------------------

typedef struct page {
    int id;
    char URL[50];
    char *description;
} *TPage;

typedef struct tab {
    int id;
    struct page *currentPage;
    struct stack *backwardStack;
    struct stack *forwardStack;
} *Ttab;

typedef struct tabNode {
    struct tab *tab;
    struct tabNode *prev;
    struct tabNode *next;
} tabNode, *tabsList;

typedef struct browser {
    struct tab *currentTab;
    tabsList list;
} *TBrowser;

typedef struct stackNode {
    TPage page;
    struct stackNode* next;
} *TStackNode;

typedef struct stack {
    TStackNode head;
    int size;
} *TStack;

// ---FUNCTII------------------------------------------------------------

TPage createPage(int id, char* URL, char *description);
TStack createStack();
Ttab createTab();
tabsList createTabNode();
tabsList createList();
TBrowser createBrowser();
TBrowser new_tab(TBrowser browser, int* tab_id_counter);
void print(TBrowser browser, FILE* output_file);
TBrowser close(TBrowser browser, FILE* output_file);
TBrowser open(TBrowser browser, FILE* output_file, int id);
TBrowser next(TBrowser browser);
TBrowser prev(TBrowser browser);
TStack push(TStack stack, TPage current_page);
void print_history(TBrowser browser, FILE* output_file, int tab_id);
TBrowser page(TBrowser browser, int page_id,
     TPage array_pages, int num_pages, FILE* output_file);
int isEmptyStack(TStack stack);
TStack pop(TStack stack);
TBrowser backward(TBrowser browser, FILE* output_file);
TBrowser Forward(TBrowser browser, FILE* output_file);
void deleteStack(TStack *stack);
void deletePage(TPage *page);
void deleteTab(Ttab *tab);
void deleteTabNode(tabsList *node);
void deleteList(tabsList *sentinel);
void deleteBrowser(TBrowser* browser);
#endif
