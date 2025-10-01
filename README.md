**Liste dublu inlantuite, stive - simularea unui browser web**
**-------------------------------------------------------------------------------------------------------**

Proiectul este alcatuit din 3 fisiere sursa:
    main.c -> gestioneaza apelurile functiilor, lucrul cu fisierele (citire/afisare), reprezinta interfata programului
        Citeste din fisierul de intrare paginile web si le salveaza intr-un vector de structuri alocat dinamic
        Se aloca memorie pentru browser
        Apoi, citeste instructiunile / functiile care vor fi aplicate asupra browserului si apeleaza functiile corespunzatoare
        La final se dealoca memoria pentru browser si pentru vectorul de structuri. Se inchid fisierele de in/out
    utils.c -> implementarea tuturor functiilor din cerinta
        Functiile respecta cerintele din enunt si sunt descrise in acest fisier, mai jos
    utils.h -> implementarea structurilor
        Fisierul contine toate structurile folosite in program si apelul tuturor functiilor implementate in "utils.c"
        

**-------------------------------------------------------------------------------------------------------**

Descrierea structurilor folosite:
-   struct page: retine informatiile despre o pagina {id, URL, descriere}
-   struct tab: retine informatiile despre un tab {pagina curenta, stiva backward, stiva forward}
-   struct tabNode: retine informatiile despre un nod al listei dublu inlantuite {tab-ul respectiv, tab-ul anterior si cel urmator}
-   struct browser: retine informatiile despre browser {tab-ul curent si lista dublu inlantuita de tab-uri}
-   struct stackNode: retine informatiile despre un nod al stivei, folosit in implementarea stivelor backward si forward
-   struct stack: retine informatiile despre stiva {head, size}

**-------------------------------------------------------------------------------------------------------**

Descrierea functiilor implementate:

-   createPage(id, URL, description) 
        Aloca si initializeaza o structura de tip pagina web (TPage) cu un ID, un URL si o descriere

-   createStack()
        Creeaza o stiva goala pentru istoricul de navigare (backward/forward) al unui tab

-   createTab()
        Initializeaza un nou tab cu o pagina implicita si doua stive (backward si forward)

-   createTabNode()
        Creeaza un nod de lista dublu inlantuita ce contine un tab. Este folosit pentru gestionarea tab-urilor deschise

-   createList()
        Creeaza o lista circulara dublu inlantuita cu un nod santinela si un prim tab (ID = 0)

-   createBrowser() 
        Initializeaza structura principala a browserului, creand lista de tab-uri si setand tab-ul curent (initial este cel cu ID = 0)

-   new_tab(browser, tab_id_counter)
        Creeaza un tab nou cu ID unic si il insereaza in lista de tab-uri, apoi il seteaza ca tab curent

-   print(browser, output_file)
        Afiseaza ID-urile tab-urilor in ordinea deschiderii si descrierea paginii curente

-   close(browser, output_file)
        Inchide tab-ul curent (daca este permis) si seteaza tab-ul anterior ca activ

-   open(browser, output_file, id)
        Comuta tab-ul curent catre tab-ul cu ID-ul specificat, daca acesta exista

-   next(browser)
        Comuta tab-ul curent catre urmatorul din lista, in ordine circulara

-   prev(browser)
        Comuta tab-ul curent catre precedentul din lista, in ordine circulara

-   push(stack, page)
        Adauga o pagina pe stiva specificata (pentru backward/forward navigation)

-   print_history(browser, output_file, tab_id)
        Afiseaza istoricul de navigare (forward, pagina curenta si backward) al tab-ului cu ID-ul dat

-   page(browser, page_id, array_pages, num_pages, output_file) 
        Incarca o pagina dintr-un array de pagini in tab-ul curent, salvand pagina precedenta in stiva backward si resetand stiva forward

-   isEmptyStack(stack)
        Verifica daca o stiva este goala

-   pop(stack)
        Elimina elementul din varful stivei si elibereaza memoria asociata

-   deleteStack(&stack)
        Sterge toate nodurile unei stive si elibereaza structura

-   backward(browser, output_file)
        Navigheaza inapoi in istoricul unui tab, mutand pagina curenta in stiva forward

-   Forward(browser, output_file) 
        Navigheaza inainte in istoricul unui tab, mutand pagina curenta in stiva backward

-   deletePage(&page)
        Elibereaza memoria asociata unei pagini (inclusiv descrierea dinamica)

-   deleteTab(&tab)
        Elibereaza memoria unui tab: pagina curenta si cele doua stive

-   deleteTabNode(&node)
        Elibereaza un nod din lista de tab-uri, impreuna cu tab-ul pe care il contine

-   deleteList(&sentinel)
        Sterge intreaga lista de tab-uri (cu exceptia santinelei), eliberand toate nodurile si tab-urile

-   deleteBrowser(&browser)
        Elibereaza complet structura browserului, inclusiv lista de tab-uri si toate componentele interne

**-------------------------------------------------------------------------------------------------------**

Punctajul obținut la teste (la rularea pe calculatorul propriu):
**Total: 100/100**
**Valgrind: 20/20**