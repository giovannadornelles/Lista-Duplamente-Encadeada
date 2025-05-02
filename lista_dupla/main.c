#include <stdio.h>
#include "lista_dupla.h"

int main() {
    ListaDupla lista;
    inicializarLista(&lista);

    int opcao;
    Livro livro;
    char isbn[14];
    char nome_usuario[100];
    char data[11];

// --- Inserções automáticas ---
Livro l;
for (int i = 0; i < 9; i++) {
    sprintf(l.titulo, "Livro %d", i + 1);
    sprintf(l.autor, "Autor %d", i + 1);
    l.ano = 2000 + i;
    sprintf(l.isbn, "00000000000%d", i + 1);
    l.status = DISPONIVEL;
    l.nome_usuario[0] = '\0';
    l.data_emprestimo[0] = '\0';

    if (i < 3)
        inserirLivroPosicao(&lista, l, 0);                  // Início
    else if (i < 6)
        inserirLivroPosicao(&lista, l, lista.tamanho / 2);  // Meio
    else
        inserirLivroPosicao(&lista, l, lista.tamanho);      // Fim
}


    do {
        printf("\n--- MENU BIBLIOTECA ---\n");
        printf("1. Cadastrar Livro\n2. Consultar por ISBN\n3. Emprestar Livro\n4. Devolver Livro\n");
        printf("5. Listar Livros (Frente)\n6. Listar Livros (Trás)\n7. Remover Livro\n0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                printf("Título: "); fgets(livro.titulo, 100, stdin); strtok(livro.titulo, "\n");
                printf("Autor: "); fgets(livro.autor, 100, stdin); strtok(livro.autor, "\n");
                printf("Ano: "); scanf("%d", &livro.ano); getchar();
                printf("ISBN: "); fgets(livro.isbn, 14, stdin); strtok(livro.isbn, "\n");
                livro.status = DISPONIVEL;
                livro.nome_usuario[0] = '\0';
                livro.data_emprestimo[0] = '\0';
                cadastrarLivro(&lista, livro);
                break;

            case 2:
                printf("ISBN: "); fgets(isbn, 14, stdin); strtok(isbn, "\n");
                No* no = buscarLivroPorISBN(&lista, isbn);
                if (no)
                    printf("Livro encontrado: %s (%s)\n", no->livro.titulo, no->livro.autor);
                else
                    printf("Livro não encontrado.\n");
                break;

            case 3:
                printf("ISBN: "); fgets(isbn, 14, stdin); strtok(isbn, "\n");
                printf("Nome do usuário: "); fgets(nome_usuario, 100, stdin); strtok(nome_usuario, "\n");
                printf("Data (DD/MM/AAAA): "); fgets(data, 11, stdin); strtok(data, "\n");
                if (emprestarLivro(&lista, isbn, nome_usuario, data))
                    printf("Empréstimo realizado com sucesso.\n");
                else
                    printf("Erro no empréstimo.\n");
                break;

            case 4:
                printf("ISBN: "); fgets(isbn, 14, stdin); strtok(isbn, "\n");
                if (devolverLivro(&lista, isbn))
                    printf("Livro devolvido com sucesso.\n");
                else
                    printf("Erro na devolução.\n");
                break;

            case 5:
                listarLivrosFrente(&lista);
                break;

            case 6:
                listarLivrosTras(&lista);
                break;

            case 7:
                printf("ISBN do livro a remover: "); fgets(isbn, 14, stdin); strtok(isbn, "\n");
                removerLivroPorISBN(&lista, isbn);
                break;
        }
    } while (opcao != 0);

    liberarLista(&lista);
    return 0;
}
