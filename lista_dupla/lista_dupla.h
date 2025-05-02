#ifndef LISTA_DUPLA_H
#define LISTA_DUPLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { DISPONIVEL, EMPRESTADO } Status;

typedef struct Livro {
    char titulo[100];
    char autor[100];
    int ano;
    char isbn[14];
    Status status;
    char nome_usuario[100];
    char data_emprestimo[11];
} Livro;

typedef struct No {
    Livro livro;
    struct No* proximo;
    struct No* anterior;
} No;

typedef struct {
    No* cabeca;
    No* cauda;
    int tamanho;
} ListaDupla;

// Prototipação das funções
void inicializarLista(ListaDupla* lista);
void cadastrarLivro(ListaDupla* lista, Livro livro);
No* buscarLivroPorISBN(ListaDupla* lista, const char* isbn);
int emprestarLivro(ListaDupla* lista, const char* isbn, const char* nome_usuario, const char* data);
int devolverLivro(ListaDupla* lista, const char* isbn);
void listarLivrosFrente(ListaDupla* lista);
void listarLivrosTras(ListaDupla* lista);
void removerLivroPorISBN(ListaDupla* lista, const char* isbn);
void liberarLista(ListaDupla* lista);

#endif
