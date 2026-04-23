#include <stdio.h>
#include <stdlib.h>

// 1. A estrutura básica (o "tijolo")
typedef struct no
{
    int info;
    struct no *prox;
} No;

// 2. Os apelidos didáticos (todos são No*)
typedef No *Elemento;   // Use para: Criar novos nós (malloc)
typedef No *Cursor;     // Use para: Percorrer a lista (em loops while/for)
typedef No *Referencia; // Use para: Guardar o 'inicio' e 'fim' dentro da struct Lista
typedef No *ListaLigada;

// 3. O "Gerente" da lista
typedef struct lista
{
    Referencia inicio;
    Referencia fim;
    int tamanho;
} Controle;

Elemento novoNo(int info)
{
    Elemento novo = malloc(sizeof(No));
    if(!novo) return NULL;

    novo->info = info;
    novo->prox = NULL;
    return novo;
}

typedef Controle *Lista; // A lista que você passa para as funções

void inserirNoInicio(Lista l, int info)
{
    Elemento novo = novoNo(info);
    if (!novo)
        return; // se falhar, mantém a lista como estava

    novo->prox = l->inicio;
    l->inicio = novo;

    if (l->tamanho == 0)
    {
        l->fim = novo;
    }
    l->tamanho++;
}

void inserirNoFim(Lista l, int info)
{
    Elemento novo = novoNo(info);
    // Precisamos encontrar o último elemento da lista. Quando encontramos, adicionamos o novo!

    if (l->inicio == NULL)
    {
        l->inicio = novo;
        l->fim = novo;
    }
    else
    {
        Cursor curr = l->inicio;
        while (curr->prox != NULL)
        {
            curr = curr->prox;
        }
        curr->prox = novo;
        l->fim = novo;
    }
    l->tamanho++;
}
Lista criarLista()
{
    Lista l = (Lista)malloc(sizeof(Controle));
    if (l)
    {
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
    }
    return l;
}

// Suas funções inserirNoInicio e inserirNoFim estão perfeitas agora!

void imprimirLista(Lista l)
{
    Cursor curr = l->inicio;
    printf("Lista (%d itens): ", l->tamanho);
    while (curr != NULL)
    {
        printf("%d -> ", curr->info);
        curr = curr->prox;
    }
    printf("NULL\n");
}

// Crie uma função que remove um nó da lista através de seu valor: remove_value(Lista l, int valor)

void removePorNumero(Lista l, int valor)
{
    if (l->inicio == NULL)
        return;

    if (l->inicio->info == valor)
    {
        Elemento antigo = l->inicio;
        l->inicio = antigo->prox;

        if (l->inicio == NULL) l->fim = NULL;
        
        free(antigo);
        l->tamanho--;
        return;
    }

    Cursor curr = l->inicio;
    // Percorrer a lista procurando pelo valor
    while (curr->prox != NULL)
    {
        // se o proximo nó tiver o valor
        if (curr->prox->info == valor)
        {
            // alteração dos ponteiros
            Elemento removido = curr->prox;

            // curr vai pro prox prox
            curr->prox = removido->prox;

            // se o proximo do removido for nulo, quer dizer que o removido era o ultimo, então precisa-se
            // trocar o ponteiro do fim para ele
            if (removido == l->fim)
                l->fim = curr;
            // remove
            free(removido);
            l->tamanho--;
            return;
        }
        curr = curr->prox;
    }
}

// Implemente a função reverse_list(struct no * lista).
// Ela deve retornar o ponteiro para o nó de início da lista que,
// se impressa por print_list, mostrará a lista original reversa.

Lista inverteLista(Lista l)
{
    // cria um novo gerente para a lista invertida
    Lista listaInvertida = criarLista();
    Cursor curr = l->inicio;

    while (curr != NULL)
    {
        inserirNoInicio(listaInvertida, curr->info);
        curr = curr->prox;
    }

    return listaInvertida; // retorna o gerente da lista invertida
}

void removePrimeiro(Lista l)
{
    if (l->inicio == NULL)
        return; // lista vazia

    Elemento antigo = l->inicio;
    l->inicio = antigo->prox;

    if (l->inicio == NULL)
        l->fim = NULL;

    free(antigo);
    l->tamanho--;
}

void removeUltimo(Lista l)
{
    if (l->fim == NULL)
        return;
    if (l->inicio == l->fim)
    {
        free(l->inicio);
        l->inicio = NULL;
        l->fim = NULL;
        l->tamanho = 0;
        return;
    }

    Elemento penultimo = l->inicio;
    while (penultimo->prox != l->fim)
    {
        penultimo = penultimo->prox;
    }
    free(l->fim);
    penultimo->prox = NULL;
    l->fim = penultimo;
    l->tamanho--;
}

int main()
{
    Lista myList = criarLista();
    inserirNoFim(myList, 10);
    inserirNoFim(myList, 20);
    inserirNoFim(myList, 30);

    imprimirLista(myList); // 10 -> 20 -> 30 -> NULL
    Lista invertida = inverteLista(myList);
    imprimirLista(invertida); // 30 -> 20 -> 10 -> NULL
}