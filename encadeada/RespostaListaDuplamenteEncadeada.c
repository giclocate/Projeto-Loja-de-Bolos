/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definição da estrutura do bolo */
typedef struct Bolo {
    int id;
    char nome[50];
    char tamanho;
    char dataVencimento[20];
    float preco;
    struct Bolo *prox;
} Bolo;

/* Definição da estrutura da lista */
typedef struct {
    Bolo *inicio;
} Lista;

/* Função para criar uma nova lista */
Lista* criarLista() {
    Lista *novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista == NULL) {
        printf("Erro ao alocar memoria para a lista.\n");
        exit(1);
    }
    novaLista->inicio = NULL;
    return novaLista;
}

/* Função para inserir um novo bolo na lista */
void inserirElemento(Lista *lista, Bolo *novoBolo) {
    if (lista == NULL) {
        printf("A lista não foi criada.\n");
        return;
    }
    if (novoBolo == NULL) {
        printf("Erro: Bolo invalido.\n");
        return;
    }
    novoBolo->prox = lista->inicio;
    lista->inicio = novoBolo;
    printf("Bolo inserido com sucesso.\n");
}

/* Função para remover um bolo da lista por ID */
void removerElemento(Lista *lista, int id) {
    if (lista == NULL) {
        printf("A lista nao foi criada.\n");
        return;
    }
    Bolo *atual = lista->inicio;
    Bolo *anterior = NULL;
    while (atual != NULL && atual->id != id) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Bolo com ID %d nao encontrado na lista.\n", id);
        return;
    }
    if (anterior == NULL) {
        lista->inicio = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }
    free(atual);
    printf("Bolo removido com sucesso.\n");
}

/* Função para buscar um bolo por ID na lista */
Bolo* buscarElemento(Lista *lista, int id) {
    if (lista == NULL) {
        printf("A lista não foi criada.\n");
        return NULL;
    }
    Bolo *atual = lista->inicio;
    while (atual != NULL && atual->id != id) {
        atual = atual->prox;
    }
    if (atual == NULL) {
        printf("Bolo com ID %d nao encontrado na lista.\n", id);
        return NULL;
    }
    return atual;
}

/* Função para mostrar todos os bolos da lista */
void mostrarElementos(Lista *lista) {
    if (lista == NULL) {
        printf("A lista nao foi criada.\n");
        return;
    }
    if (lista->inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }
    Bolo *atual = lista->inicio;
    printf("Lista de Bolos:\n");
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Tamanho: %c, Preco: %.2f\n",
            atual->id, atual->nome, atual->tamanho, atual->preco);
        atual = atual->prox;
    }
}

/* Função para liberar a memória alocada para a lista e seus elementos */
void excluirLista(Lista *lista) {
    if (lista == NULL) {
        printf("A lista nao foi criada.\n");
        return;
    }
    Bolo *atual = lista->inicio;
    Bolo *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista);
    printf("Lista excluida com sucesso.\n");
}

/* Função para limpar o buffer de entrada */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Lista *lista = criarLista();

    int opcao;
    do {
        printf("\nSEJAM BEM-VINDOS(AS) A MELHOR LOJA DE BOLOS!\n");
        printf("\nNOSSO MENU:\n");
        printf("1. Inserir bolo\n");
        printf("2. Remover bolo\n");
        printf("3. Buscar bolo\n");
        printf("4. Mostrar todos os bolos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                Bolo *novoBolo = (Bolo*)malloc(sizeof(Bolo));
                printf("\nInforme os dados do bolo:\n");
                printf("Digite o ID: ");
                scanf("%d", &novoBolo->id);
                limparBuffer();
                printf("Digite o nome do bolo: ");
                fgets(novoBolo->nome, sizeof(novoBolo->nome), stdin);
                novoBolo->nome[strcspn(novoBolo->nome, "\n")] = '\0';  // Remove o caractere de nova linha do fgets
                printf("Digite o tamanho do bolo (P, M ou G): ");
                scanf(" %c", &novoBolo->tamanho);  // Espaço antes de %c para consumir a quebra de linha pendente
                fgets(novoBolo->dataVencimento, sizeof(novoBolo->dataVencimento), stdin);
                novoBolo->dataVencimento[strcspn(novoBolo->dataVencimento, "\n")] = '\0';
                printf("Digite o preco do bolo: ");
                scanf("%f", &novoBolo->preco);
                limparBuffer();
                novoBolo->prox = NULL;
                inserirElemento(lista, novoBolo);
                break;
            }
            case 2: {
                int id;
                printf("\nInforme o ID do bolo a ser removido: ");
                scanf("%d", &id);
                limparBuffer();
                removerElemento(lista, id);
                break;
            }
            case 3: {
                int id;
                printf("\nInforme o ID do bolo a ser buscado: ");
                scanf("%d", &id);
                limparBuffer();
                Bolo *boloBuscado = buscarElemento(lista, id);
                if (boloBuscado != NULL) {
                    printf("\nBolo encontrado:\n");
                    printf("ID: %d, Nome: %s, Tamanho: %c, Preco: %.2f\n",
                           boloBuscado->id, boloBuscado->nome, boloBuscado->tamanho, boloBuscado->preco);
                }
                break;
            }
            case 4: {
                mostrarElementos(lista);
                break;
            }
            case 5: {
                printf("\nEncerrando o programa.\n");
                excluirLista(lista);
                exit(0);
            }
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
