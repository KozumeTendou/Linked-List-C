#include <stdio.h>
#include <stdlib.h>

struct Nodo{  //Definizione della stuttura
    int dato;
    struct Nodo* next;
};

struct Nodo* creaNodo(int valore){
    struct Nodo* newNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    newNodo -> dato = valore;
    newNodo -> next = NULL;

    return newNodo;
}

//inserisci in testa
void insertHead(struct Nodo** head, int valore){
    struct Nodo* newNodo = creaNodo(valore);
    newNodo -> next = *head;
    *head = newNodo;
}

//inserisci in coda
void insertTail(struct Nodo** head, int valore){ 
    //struct Nodo** head = è un puntatore al puntatore alla testa della lista. Serve perché vogliamo modificare direttamente la lista originale

    struct Nodo* newNodo = creaNodo(valore);
    if(*head == NULL){ //Controlla se la lista è vuota
        *head = newNodo; //Il nuovo nodo diventa il primo e unico nodo della lista 
        return; //Fine
    }

    struct Nodo* corrente = *head; //Creo puntatore nuovo che punta all'inizio della lista -> scorro la lista senza modificare il puntatore originale
    while(corrente->next != NULL){ //Scorro lista fino all'ultimo nodo
        corrente = corrente -> next; //Quando esce dal ciclo, corrente punta all'ultimo nodo della lista
    }
    corrente -> next = newNodo; //Collega il nuovo nodo alla fine della lista: fa puntare next dell’ultimo nodo esistente al nuovo nodo
}

//inserisci in posizione data
void insertPosition(struct Nodo** head, int valore, int posizione){
    struct Nodo* newNodo = creaNodo(valore);
    //caso speciale: inserimento in testa
    if(posizione==0){
        newNodo -> next = *head;
        *head = newNodo;
        return;
    }

    struct Nodo* corrente = *head;
    int indice = 0;

     //scorri fino alla posizione precedente a quella desiderata
     while(corrente!=NULL && indice < posizione-1){
        //printf("\nValore corrente: %d\n", corrente->dato);
        corrente = corrente -> next;
        indice++;
     } 

     //se posizione è oltre fine della lista
     if(corrente == NULL){
        printf("Posizione fuori range\n");
        free(newNodo);
        return;
     }

     //inserisci nuovo nodo tra corrente e successivo
     newNodo -> next = corrente -> next;
     corrente -> next = newNodo;

     /*  A -> B -> C -> D -> NULL
        Vuoi inserire X dopo B (cioè in posizione 2, contando da 0)
        corrente punta a B
        newNodo è X con next == NULL

        nuovoNodo->next = corrente->next;   // X->next = C
        corrente->next = nuovoNodo;         // B->next = X
     
        A -> B -> X -> C -> D -> NULL
     */ 
}

//elimina in testa
void deleteHead(struct Nodo** head){
    if(*head == NULL){
        return;
    }
    struct Nodo* temp = *head;
    *head = (*head) -> next;
    free(temp);
}

//elimina in coda
void deleteTail(struct Nodo** head){
    if(*head == NULL){
        return;
    }

    struct Nodo* corrente = *head;

    if(corrente->next == NULL){ //se c'è solo un nodo presente
        free(corrente);
        *head = NULL;
        return;
    }

    //scorro fino penultimo nodo
    while(corrente->next->next != NULL){
        corrente = corrente->next;
    }

    free(corrente->next);
    corrente->next = NULL;

}

//elimina in posizione data
void deletePosition(struct Nodo** head, int posizione){
    if(*head == NULL || posizione < 0){
        return;
    }

    struct Nodo* corrente = *head;
    //se posizione = 0 elimino in testa
    if(posizione==0){
        *head = corrente->next;
        free(corrente);
        return;
    }

    //scorro fino nodo precedente
    int indice = 0;
    while(corrente != NULL && indice<posizione-1){
        corrente = corrente->next;
        indice++;
    }

    if(corrente == NULL || corrente->next == NULL){
        printf("Posizione fuori range\n");
        return;
    }

    //elimina nodo in posizione
    struct Nodo* delete = corrente->next;
    corrente->next = delete->next;
    free(delete);
}

//stampa lista
void printList(struct Nodo* head){
    struct Nodo* corrente = head; //parto dalla testa
    while(corrente!=NULL){
        printf("%d -> ", corrente->dato);
        corrente = corrente -> next;
    }
    printf("NULL\n");  //ultimo che stampa
}

//libera lista
void freeList(struct Nodo* head){
    struct Nodo* temp;
    while(head!=NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }
}

int size(struct Nodo* head){
    int conta = 0;
    while(head != NULL){
        conta++;
        head = head->next;
    }
    return conta;
}

int main(void){
    struct Nodo* head = NULL;
    //inserisci valori
    for(size_t i=0; i<10; i++){
        insertHead(&head, i);
    }

    //stampo lunghezza della lista
    printf("Lunghezza lista: %d\n", size(head));

    //stampo inserimento dalla testa
    printf("Lista insert head: ");
    printList(head);

    //stampo inserimento nuovo valore a fine lista
    printf("Lista insert new value in tail: ");
    insertTail(&head, 11);
    printList(head);

    //stampo inserimento in posizione data
    printf("Lista insert in position: ");
    insertPosition(&head, 34, 5);
    printList(head);

    //caso in cui posizione > capacità della lista
    printf("Lista insert in position with error: ");
    insertPosition(&head, 34, 20);

    //stampo elimina in testa
    printf("Lista delete in head: ");
    deleteHead(&head);
    printList(head);

    //stampo elimina in coda
    printf("Lista delete in tail: ");
    deleteTail(&head);
    printList(head);

    //stampo elimina in posizione data
    printf("Lista delete in position: ");
    deletePosition(&head, 5);
    printList(head);

    //svuoto lista
    freeList(head);
    head = NULL;

    return 0;
}
