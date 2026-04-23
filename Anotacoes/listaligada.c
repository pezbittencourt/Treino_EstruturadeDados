#include<stdio.h>
#include <stdlib.h>

// 1. A estrutura básica (o "tijolo")
typedef struct no {
    int info;
    struct no *prox;
} No;

// 2. Os apelidos didáticos (todos são No*)
typedef No* Elemento;    // Use para: Criar novos nós (malloc)
typedef No* Cursor;      // Use para: Percorrer a lista (em loops while/for)
typedef No* Referencia;  // Use para: Guardar o 'inicio' e 'fim' dentro da struct Lista

// 3. O "Gerente" da lista
typedef struct lista {
    Referencia inicio;
    Referencia fim;
    int tamanho;
} Controle;

typedef Controle* Lista; // A lista que você passa para as funções

void inserirNoInicio(Lista l, int valor) {
    Elemento novo = (Elemento)malloc(sizeof(No));
    if (!novo) return; // Se o malloc falhar, sai da função

    novo->info = valor;
    novo->prox = l->inicio; // O novo nó aponta para quem era o antigo primeiro
    l->inicio = novo;       // O "Gerente" agora diz que o início é o novo nó

    if (l->tamanho == 0) {  // Se era o primeiro elemento da lista
        l->fim = novo;
    }
    l->tamanho++;           
}

void inserirNoFim(Lista l, int valor) {
    Elemento novo = (Elemento)malloc(sizeof(No));
    if (!novo) return;

    novo->info = valor;
    novo->prox = NULL; // Como é o último, ele aponta para o vazio

    if (l->tamanho == 0) {    // Se a lista estiver vazia
        l->inicio = novo;
        l->fim = novo;
    } else {
        l->fim->prox = novo;  // O antigo último agora aponta para o novo
        l->fim = novo;        // O "Gerente" atualiza quem é o novo último
    }
    l->tamanho++;
}
Lista criarLista() {
    Lista l = (Lista)malloc(sizeof(Controle));
    if (l) {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

// Suas funções inserirNoInicio e inserirNoFim estão perfeitas agora!

void imprimirLista(Lista l) {
    Cursor curr = l->inicio;
    printf("Lista (%d itens): ", l->tamanho);
    while (curr != NULL) {
        printf("%d -> ", curr->info);
        curr = curr->prox;
    }
    printf("NULL\n");
}


struct no * remove_first(struct no * lista) {
    if (lista == NULL) return NULL; // lista vazia

    struct no *novo_inicio = lista->prox;
    return novo_inicio;
}
 /*
 
 1. Cria a lista (O Gerente)
Lista myList = criarLista();

 2. Insere os valores
    inserirNoInicio(myList, valor);
    inserirNoFim(myList, valor);
  3. Testa o resultado
imprimirLista(myList);

*/
int main() { 

}