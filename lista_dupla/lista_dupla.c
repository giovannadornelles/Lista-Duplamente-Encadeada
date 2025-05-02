#include "lista_dupla.h"

void inicializarLista(ListaDupla* lista) {
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->tamanho = 0;
}

void cadastrarLivro(ListaDupla* lista, Livro livro) {
    No* novo = (No*) malloc(sizeof(No));
    novo->livro = livro;
    novo->proximo = NULL;
    novo->anterior = lista->cauda;

    if (lista->cauda)
        lista->cauda->proximo = novo;
    else
        lista->cabeca = novo;

    lista->cauda = novo;
    lista->tamanho++;
}

No* buscarLivroPorISBN(ListaDupla* lista, const char* isbn) {
    No* atual = lista->cabeca;
    while (atual) {
        if (strcmp(atual->livro.isbn, isbn) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

int emprestarLivro(ListaDupla* lista, const char* isbn, const char* nome_usuario, const char* data) {
    No* no = buscarLivroPorISBN(lista, isbn);
    if (!no || no->livro.status == EMPRESTADO) return 0;
    no->livro.status = EMPRESTADO;
    strcpy(no->livro.nome_usuario, nome_usuario);
    strcpy(no->livro.data_emprestimo, data);
    return 1;
}

int devolverLivro(ListaDupla* lista, const char* isbn) {
    No* no = buscarLivroPorISBN(lista, isbn);
    if (!no || no->livro.status == DISPONIVEL) return 0;
    no->livro.status = DISPONIVEL;
    no->livro.nome_usuario[0] = '\0';
    no->livro.data_emprestimo[0] = '\0';
    return 1;
}

void listarLivrosFrente(ListaDupla* lista) {
    No* atual = lista->cabeca;
    while (atual) {
        printf("Título: %s | Autor: %s | ISBN: %s | Status: %s\n",
               atual->livro.titulo, atual->livro.autor, atual->livro.isbn,
               atual->livro.status == DISPONIVEL ? "Disponível" : "Emprestado");
        atual = atual->proximo;
    }
}

void listarLivrosTras(ListaDupla* lista) {
    No* atual = lista->cauda;
    while (atual) {
        printf("Título: %s | Autor: %s | ISBN: %s | Status: %s\n",
               atual->livro.titulo, atual->livro.autor, atual->livro.isbn,
               atual->livro.status == DISPONIVEL ? "Disponível" : "Emprestado");
        atual = atual->anterior;
    }
}

void removerLivroPorISBN(ListaDupla* lista, const char* isbn) {
    No* atual = buscarLivroPorISBN(lista, isbn);
    if (!atual) return;

    if (atual->anterior)
        atual->anterior->proximo = atual->proximo;
    else
        lista->cabeca = atual->proximo;

    if (atual->proximo)
        atual->proximo->anterior = atual->anterior;
    else
        lista->cauda = atual->anterior;

    free(atual);
    lista->tamanho--;
}

void liberarLista(ListaDupla* lista) {
    No* atual = lista->cabeca;
    while (atual) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->tamanho = 0;
}
