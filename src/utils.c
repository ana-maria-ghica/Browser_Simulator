/*
    Copyright (c) 2025 Ghica Ana-Maria
    All rights reserved

    Facultatea de Automatica si Calculatoare
    Seria CD, grupa 314
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define BUFFER_SIZE 100
#define INIT_ID 0
#define INIT_URL "https://acs.pub.ro/"
#define INIT_DESCRIPRION "Computer Science\n"

TPage createPage(int id, char* URL, char *description) {
    TPage page = malloc(sizeof(struct page));
    if (!page) {
        printf("Eroare la alocarea dinamica a paginii.\n");
        return NULL;
    }
    page->id = id;

    strcpy(page->URL, URL);

    int description_length = strlen(description) + 1;
    page->description = malloc(description_length * sizeof(char));
    if (!page->description) {
        printf("Eroare la alocarea dinamica a descrierii.\n");
        free(page);
        return NULL;
    }
    strcpy(page->description, description);
    return page;
}

TStack createStack() {
    TStack stack = malloc(sizeof(struct stack));
    if (!stack) {
        printf("Eroare la alocarea memoriei.\n");
        return NULL;
    }
    stack->head = NULL;
    stack->size = 0;
    return stack;
}

Ttab createTab() {
    Ttab tab = malloc(sizeof(struct tab));
    if (!tab) {
        printf("Eroare la alocarea dinamica a tab-ului.\n");
        return NULL;
    }
    tab->id = 0;
    tab->currentPage = createPage(INIT_ID, INIT_URL, INIT_DESCRIPRION);
    tab->backwardStack = createStack();
    tab->forwardStack = createStack();

    return tab;
}

tabsList createTabNode() {
    tabsList node = malloc(sizeof(struct tabNode));
    if (!node) {
        printf("Eroare la alocarea dinamica a nodului.\n");
        return NULL;
    }
    node->tab = createTab();
    node->prev = node->next = NULL;
    return node;
}

tabsList createList() {
    tabsList sentinel = malloc(sizeof(struct tabNode));
    if (!sentinel) {
        printf("Eroare la alocarea dinamica a listei.\n");
        return NULL;
    }
    sentinel->tab = NULL;
    sentinel->next = sentinel->prev = sentinel;

    tabsList tabNode = createTabNode();
    tabNode->next = sentinel;
    tabNode->prev = sentinel;

    sentinel->next = tabNode;
    sentinel->prev = tabNode;

    return sentinel;
}

TBrowser createBrowser() {
    TBrowser browser = malloc(sizeof(struct browser));
    if (!browser) {
        printf("Eroare la alocarea dinamica a browser-ului.\n");
        return NULL;
    }

    browser->list = createList();
    if (!browser->list) {
        printf("Eroare la alocarea memoriei pentru lista.\n");
        free(browser);
        return NULL;
    }

    browser->currentTab = browser->list->next->tab;
    return browser;
}

TBrowser new_tab(TBrowser browser, int* tab_id_counter) {
    Ttab new_tab = createTab();
    (*tab_id_counter)++;
    new_tab->id = (*tab_id_counter);

    tabsList iter = browser->list->next;
    int tab_index = 1;
    while (iter->next != browser->list) {
        iter = iter->next;
        tab_index++;
    }

    tabsList new_node = createTabNode();
    Ttab old_tab = new_node->tab;
    new_node->tab = new_tab;
    deleteTab(&old_tab);

    new_node->prev = iter;
    new_node->next = browser->list;
    iter->next = new_node;
    browser->list->prev = new_node;

    browser->currentTab = new_tab;
    return browser;
}

void print(TBrowser browser, FILE* output_file) {
    fprintf(output_file, "%d", browser->currentTab->id);

    tabsList iter = browser->list->next;
    while ((iter != browser->list) &&
        (iter->tab->id != browser->currentTab->id))
        iter = iter->next;

    tabsList currentTabNode = iter;
    iter = iter->next;
    while (iter != currentTabNode) {
        if (iter != browser->list)
            fprintf(output_file, " %d", iter->tab->id);
        iter = iter->next;
    }
    fprintf(output_file, "\n");
    fprintf(output_file, "%s", browser->currentTab->currentPage->description);
}

TBrowser close(TBrowser browser, FILE* output_file) {
    if (browser == NULL)
        return NULL;

    if (browser->currentTab->id == 0) {
        fprintf(output_file, "403 Forbidden\n");
        return browser;
    } else {
        tabsList iter = browser->list->next->next;
        while (iter != browser->list) {
            if (iter->tab == browser->currentTab)
                break;
            iter = iter->next;
        }
        browser->currentTab->id--;
        browser->currentTab = iter->prev->tab;
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
        deleteTabNode(&(iter));
    }
    return browser;
}

TBrowser open(TBrowser browser, FILE* output_file, int id) {
    if (browser == NULL) {
        fprintf(output_file, "403 Forbidden\n");
        return NULL;
    }

    int found = 0;
    tabsList iter = browser->list->next;
    while (iter != browser->list) {
        if (id == iter->tab->id) {
            browser->currentTab = iter->tab;
            found = 1;
            break;
        }
        iter = iter->next;
    }
    if (found == 0) {
        fprintf(output_file, "403 Forbidden\n");
        return browser;
    }
    return browser;
}

TBrowser next(TBrowser browser) {
    if (browser == NULL) {
        return NULL;
    }

    tabsList iter = browser->list->next;
    while (iter->tab->id != browser->currentTab->id)
        iter = iter->next;

    if (iter->next == browser->list)
        iter = iter->next->next;
    else
        iter = iter->next;

    browser->currentTab = iter->tab;
    return browser;
}

TBrowser prev(TBrowser browser) {
    if (browser == NULL) {
        return NULL;
    }

    tabsList iter = browser->list->next;
    while (iter->tab->id != browser->currentTab->id)
        iter = iter->next;

    if (iter->prev == browser->list)
        iter = iter->prev->prev;
    else
        iter = iter->prev;

    browser->currentTab = iter->tab;
    return browser;
}

TStack push(TStack stack, TPage current_page) {
    if (stack == NULL)
        return NULL;

    TStackNode node = malloc(sizeof(struct stackNode));
    if (!node) {
        printf("Eroare la alocarea dinamica a nodului din stiva\n");
        return NULL;
    }
    node->page = current_page;
    node->next = stack->head;
    stack->head = node;
    stack->size++;

    return stack;
}

void print_history(TBrowser browser, FILE* output_file, int tab_id) {
    tabsList iter = browser->list->next;
    int found = 0;

    while (iter != browser->list) {
        if (iter->tab->id == tab_id) {
            found = 1;
            break;
        }
        iter = iter->next;
    }
    if (found == 0) {
        fprintf(output_file, "403 Forbidden\n");
        return;
    }

    // afisare din stiva forward
    TStackNode forward_iter = iter->tab->forwardStack->head;
    TStack auxiliaryStack = createStack();
    while (forward_iter != NULL) {
        auxiliaryStack = push(auxiliaryStack, forward_iter->page);
        forward_iter = forward_iter->next;
    }

    TStackNode aux_iter = auxiliaryStack->head;
    while (aux_iter != NULL) {
        fprintf(output_file, "%s\n", aux_iter->page->URL);
        aux_iter = aux_iter->next;
    }

    aux_iter = auxiliaryStack->head;
    while (aux_iter != NULL) {
        TStackNode aux = aux_iter;
        aux_iter = aux_iter->next;
        auxiliaryStack->size--;
        free(aux);
    }
    deleteStack(&auxiliaryStack);
    auxiliaryStack = NULL;


    // afisare pagina curenta
    if (iter->tab->currentPage != NULL) {
        fprintf(output_file, "%s\n", iter->tab->currentPage->URL);
    }

    // afisare din stiva background
    TStackNode backward_iter = iter->tab->backwardStack->head;
    while (backward_iter != NULL) {
        fprintf(output_file, "%s\n", backward_iter->page->URL);
        backward_iter = backward_iter->next;
    }
}

TBrowser page(TBrowser browser,
    int page_id, TPage array_pages, int num_pages, FILE* output_file) {
    if (browser == NULL)
        return NULL;
    int found = 0;
    int index = 0;

    for (int i = 0; i < num_pages; i++) {
        if (page_id == array_pages[i].id) {
            found = 1;
            index = i;
            break;
        }
    }
    if (found == 0) {
        fprintf(output_file, "403 Forbidden\n");
        return browser;
    }

    browser->currentTab->backwardStack =
        push(browser->currentTab->backwardStack,
            browser->currentTab->currentPage);

    browser->currentTab->currentPage =
        createPage(array_pages[index].id,
            array_pages[index].URL, array_pages[index].description);

    deleteStack(&browser->currentTab->forwardStack);
    browser->currentTab->forwardStack = createStack();
    return browser;
}

int isEmptyStack(TStack stack) {
    // (1) - empty; (0) - NOTempty
    return stack->size == 0;
}

TStack pop(TStack stack) {
    if (stack == NULL)
        return NULL;

    TStackNode aux = stack->head;

    stack->head = stack->head->next;
    stack->size--;

    deletePage(&(aux->page));
    free(aux);

    return stack;
}

void deleteStack(TStack *stack) {
    if ((*stack) == NULL)
        return;
    while (!isEmptyStack(*stack))
        *stack = pop(*stack);
    free(*stack);
    *stack = NULL;
    return;
}

TBrowser backward(TBrowser browser, FILE* output_file) {
    if (isEmptyStack(browser->currentTab->backwardStack)) {
        fprintf(output_file, "403 Forbidden\n");
        return NULL;
    }
    browser->currentTab->forwardStack =
        push(browser->currentTab->forwardStack,
            browser->currentTab->currentPage);

    TStackNode backward_head_node = browser->currentTab->backwardStack->head;

    browser->currentTab->currentPage =
        createPage(backward_head_node->page->id,
            backward_head_node->page->URL,
                backward_head_node->page->description);

    browser->currentTab->backwardStack =
        pop(browser->currentTab->backwardStack);
    return browser;
}

TBrowser Forward(TBrowser browser, FILE* output_file) {
    if (isEmptyStack(browser->currentTab->forwardStack)) {
        fprintf(output_file, "403 Forbidden\n");
        return NULL;
    }
    browser->currentTab->backwardStack =
        push(browser->currentTab->backwardStack,
            browser->currentTab->currentPage);

    TStackNode forward_head_node = browser->currentTab->forwardStack->head;

    browser->currentTab->currentPage =
        createPage(forward_head_node->page->id,
            forward_head_node->page->URL, forward_head_node->page->description);

    browser->currentTab->forwardStack = pop(browser->currentTab->forwardStack);
    return browser;
}

void deletePage(TPage *page) {
    if ((*page) == NULL)
        return;

    free((*page)->description);
    (*page)->description = NULL;

    free(*page);
    (*page) = NULL;

    return;
}

void deleteTab(Ttab *tab) {
    if ((*tab) == NULL)
        return;

    if ((*tab)->currentPage != NULL) {
        deletePage(&(*tab)->currentPage);
        (*tab)->currentPage = NULL;
    }

    if ((*tab)->backwardStack != NULL)
        deleteStack(&(*tab)->backwardStack);

    if ((*tab)->forwardStack != NULL)
        deleteStack(&(*tab)->forwardStack);

    free(*tab);
    (*tab) = NULL;

    return;
}

void deleteTabNode(tabsList *node) {
    if (*node == NULL)
        return;

    if ((*node)->tab != NULL)
        deleteTab(&(*node)->tab);

    free(*node);
    (*node) = NULL;

    return;
}

void deleteList(tabsList *sentinel) {
    if ((*sentinel) == NULL)
        return;

    tabsList iter = (*sentinel)->next;

    while (iter != (*sentinel)) {
        tabsList aux = iter;
        iter = iter->next;

        aux->prev->next = aux->next;
        aux->next->prev = aux->prev;

        deleteTabNode(&aux);
    }
    free(*sentinel);
    *sentinel = NULL;
}

void deleteBrowser(TBrowser* browser) {
    if ((*browser) == NULL)
        return;
    deleteList(&((*browser)->list));
    free(*browser);
    *browser = NULL;
    return;
}
