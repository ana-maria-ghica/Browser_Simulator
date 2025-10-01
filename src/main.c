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

int main() {
    FILE *input_file = fopen("file.in", "r");
    FILE *output_file = fopen("file.out", "w");

    int num_pages;
    fscanf(input_file, "%d", &num_pages);
    fgetc(input_file);

    // aloc vector de structuri pentru a tine paginile citite ca input
    struct page *array_pages = malloc(num_pages * sizeof(struct page));
    if (!array_pages) {
        fprintf(output_file,
            "Eroare: alocarea memoriei pentru array_pages nu a reusit.\n");
        exit(1);
    }

    // aloc memorie pentru buffer-ul care citeste din fisier
    char *buffer = malloc(BUFFER_SIZE * sizeof(char));
    if (!buffer) {
        fprintf(output_file,
            "Eroare: alocarea memoriei pentru buffer nu a reusit.\n");
        exit(1);
    }

    // citesc datele pt fiecare pagina si le atribui campurilor
    for (int i = 0; i < num_pages; i++) {
        fscanf(input_file, "%d", &array_pages[i].id);
        fgetc(input_file);

        fgets(buffer, BUFFER_SIZE, input_file);
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(array_pages[i].URL, buffer);

        fgets(buffer, BUFFER_SIZE, input_file);
        int description_length = strlen(buffer) + 1;

        array_pages[i].description = malloc(description_length * sizeof(char));
        if (!array_pages[i].description) {
            fprintf(output_file,
                "Eroare: alocarea memoriei pentru descriere nu a reusit.\n");
            exit(1);
        }
        strcpy(array_pages[i].description, buffer);
    }

    TBrowser browser = createBrowser();
    if (!browser) {
        printf("Eroare la alocarea memoriei pentru browser.\n");
        return 1;
    }
    int tab_id_counter = 0;

    int num_instructions = 0;
    fscanf(input_file, "%d", &num_instructions);
    fgetc(input_file);

    // citesc si interpretez pe rand fiecare instructiune
    for (int i = 0; i < num_instructions; i++) {
        fgets(buffer, BUFFER_SIZE, input_file);

        if (strstr(buffer, "NEW_TAB")) {
            browser = new_tab(browser, &tab_id_counter);
        } else if (strstr(buffer, "PRINT_HISTORY")) {
            int tab_id;
            int len = strlen("PRINT HISTORY ");
            char *p = buffer + len;
            tab_id = atoi(p);
            print_history(browser, output_file, tab_id);
        } else if (strstr(buffer, "PRINT")) {
            print(browser, output_file);
        } else if (strstr(buffer, "CLOSE")) {
            close(browser, output_file);
        } else if (strstr(buffer, "OPEN")) {
            int id;
            char *p = buffer + 5;
            id = atoi(p);
            open(browser, output_file, id);
        } else if (strstr(buffer, "PREV")) {
            prev(browser);
        } else if (strstr(buffer, "NEXT")) {
            next(browser);
        } else if (strstr(buffer, "PAGE")) {
            int page_id;
            char *p = buffer + 5;
            page_id = atoi(p);
            page(browser, page_id, array_pages, num_pages, output_file);
        } else if (strstr(buffer, "BACKWARD")) {
            backward(browser, output_file);
        } else if (strstr(buffer, "FORWARD")) {
            Forward(browser, output_file);
        }
    }

    deleteBrowser(&browser);

    for (int i = 0; i < num_pages; i++) {
        free(array_pages[i].description);
        array_pages[i].description = NULL;
    }
    free(array_pages);
    array_pages = NULL;

    free(buffer);
    buffer = NULL;

    fclose(input_file);
    fclose(output_file);
    return 0;
}
