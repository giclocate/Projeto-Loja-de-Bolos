/*ATIVIDADE FILA COM VETORES
    
    As funções dessa atividade será:
- criarFila
- enqueue (insere o elemento na fila) 
- dequeue (remove o elemento da fila) 
- excluirFila (apaga todos os elementos e a fila)
- main (usando como uma aplicação e chamando todas as funções anteriores)

OBSERVAÇÕES:
Antes de enviar, verifique se o código encontra-se indentado e comentado.
Não enviar código copiado.

ALUNAS: Giovanna Clócate e Kátia Rocha
PROFESSOR: Mayrton Dias de Queiroz 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 4

/* Definindo a estrutura Bolo */
typedef struct {
    int id;
    char nomeBolo[50];
    char tamanhoBolo;
    char dataVencimento[11];
    float precoBolo;
} Bolo;

/* Definindo a estrutura da Fila */
typedef struct {
    int inicio;
    int fim;
    int capacidade;
    Bolo* bolos[TAM];
} Fila;

/* Função criarFila */
Fila* criarFilaBolo() {
    Fila* novaFila = (Fila*)malloc(sizeof(Fila));

    if (novaFila == NULL) {
        printf("Erro ao alocar memoria para a fila.\n");
        exit(1);
    }

    novaFila->inicio = 0;
    novaFila->fim = 0;
    novaFila->capacidade = TAM;

    return novaFila;
}

/* Função para enfileirar um novo bolo (enqueue) */
void enqueue(Fila* fila, Bolo* bolo) {
    if (fila == NULL) {
        printf("Fila nao foi criada.\n");
        return;
    }

    if ((fila->fim + 1) % fila->capacidade == fila->inicio) {
        printf("Fila esta cheia\n");
        return;
    }

    fila->bolos[fila->fim] = bolo;
    fila->fim = (fila->fim + 1) % fila->capacidade;
}

/* Função para desenfileirar um elemento da fila (dequeue) */
Bolo* dequeue(Fila* fila) {
    if (fila == NULL || fila->inicio == fila->fim) {
        printf("Fila esta vazia.\n");
        return NULL;
    }

    Bolo* bolo = fila->bolos[fila->inicio];
    fila->inicio = (fila->inicio + 1) % fila->capacidade;

    return bolo;
}

/* Função para excluir a fila */
void excluirFila(Fila* fila) {
    if (fila != NULL) {
        for (int i = fila->inicio; i != fila->fim; i = (i + 1) % fila->capacidade) {
            free(fila->bolos[i]);
        }
        free(fila);
    }
}

/* Função para limpar o buffer de entrada */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Função principal */
int main() {
    Fila* fila = criarFilaBolo();
    int opcao;

    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Excluir todos os bolos da fila\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Bolo* novoBolo = (Bolo*)malloc(sizeof(Bolo));
                if (novoBolo == NULL) {
                    printf("Erro ao alocar memoria para o bolo.\n");
                    break;
                }
                printf("Digite o ID do bolo: ");
                scanf("%d", &novoBolo->id);
                limparBuffer();
                printf("Digite o nome do bolo: ");
                scanf("%49[^\n]s", &novoBolo->nomeBolo);
                printf("Digite o tamanho do bolo (P/M/G): ");
                limparBuffer();
                scanf("%c", &novoBolo->tamanhoBolo);
                printf("Digite a data de vencimento do bolo (dd/mm/yyyy): ");
                limparBuffer();
                scanf("%10[^\n]s", &novoBolo->dataVencimento);
                printf("Digite o preco do bolo: ");
                limparBuffer();
                scanf("%f", &novoBolo->precoBolo);

                enqueue(fila, novoBolo);
                printf("\nBolo inserido com sucesso.\n");
                break;
            }
            case 2: {
                Bolo* boloRemovido = dequeue(fila);
                if (boloRemovido != NULL) {
                    printf("Bolo removido: ID %d, Nome: %s, Tamanho do bolo: %c, Data de vencimento: %s, Preco: %f \n", boloRemovido->id, boloRemovido->nomeBolo, boloRemovido->tamanhoBolo, boloRemovido->dataVencimento, boloRemovido->precoBolo);
                    free(boloRemovido);
                }
                break;
            }
            case 3:
                excluirFila(fila);
                fila = criarFilaBolo();
                printf("Fila de bolos excluida.\n");
                break;
            case 4:
                excluirFila(fila);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 4);

    return 0;
}
