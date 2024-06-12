/*ATIVIDADE FILA COM APONTADORES
    
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

/* Definindo a estrutura Bolo */
typedef struct {
    int id;
    char nomeBolo[50];
    char tamanhoBolo;
    char dataVencimento[11];
    float precoBolo;
} Bolo;

/* Definindo a estrutura do Nó */
typedef struct BoloNo {
    Bolo bolo;
    struct BoloNo* prox;
} BoloNo;

/* Definindo a estrutura da Fila */
typedef struct {
    BoloNo* inicio;
    BoloNo* fim;
} Fila;

/* Função criarFila */
Fila* criarFilaBolo() {
    Fila* novo = (Fila*)malloc(sizeof(Fila));

    if (novo == NULL) {
        printf("Erro ao alocar memoria para a fila.\n");
        exit(1);
    }

    novo->inicio = NULL;
    novo->fim = NULL;

    return novo;
}

/* Função para enfileirar um novo bolo (enqueue) */
int enqueue(Fila* fila, Bolo* bolo) {
    BoloNo* novoNo = (BoloNo*)malloc(sizeof(BoloNo));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o bolo.\n");
        return 0;
    }

    novoNo->bolo = *bolo;  // Copia o conteúdo de bolo para novoNo->bolo
    novoNo->prox = NULL;
    if (fila->inicio == NULL) {
        fila->inicio = novoNo;
    } else {
        fila->fim->prox = novoNo;
    }

    fila->fim = novoNo;
    return 1;
}

/* Função para desenfileirar um elemento da fila (dequeue) */
Bolo* dequeue(Fila* fila) {
    if (fila == NULL) {
        printf("Fila nao foi criada.\n");
        return NULL;
    }

    if (fila->inicio == NULL) {
        printf("Fila esta vazia.\n");
        return NULL;
    }

    BoloNo* temp = fila->inicio;
    Bolo* bolo = (Bolo*)malloc(sizeof(Bolo));
    if (bolo == NULL) {
        printf("Erro ao alocar memoria para o bolo removido.\n");
        return NULL;
    }

    *bolo = temp->bolo;  // Copia o conteúdo de temp->bolo para bolo
    fila->inicio = fila->inicio->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);
    return bolo;
}

/* Função para excluir a fila */
void excluirFila(Fila* fila) {
    while (fila->inicio != NULL) {
        dequeue(fila);
    }
    free(fila);
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
                printf("Digite o nome do bolo: ");
                scanf(" %[^\n]", novoBolo->nomeBolo);
                printf("Digite o tamanho do bolo (P/M/G): ");
                scanf(" %c", &novoBolo->tamanhoBolo);
                printf("Digite a data de vencimento (dd/mm/yyyy): ");
                scanf("%s", novoBolo->dataVencimento);
                printf("Digite o preco do bolo: ");
                scanf("%f", &novoBolo->precoBolo);

                if (enqueue(fila, novoBolo)) {
                    printf("\nBolo inserido com sucesso.\n");
                }
                free(novoBolo);
                break;
            }
            case 2: {
                Bolo* boloRemovido = dequeue(fila);
                if (boloRemovido != NULL) {
                    printf("Bolo removido: ID %d, Nome: %s, Tamanho do bolo: %c, Data de vencimento: %s, Preco: %f\n",
                           boloRemovido->id, boloRemovido->nomeBolo, boloRemovido->tamanhoBolo,
                           boloRemovido->dataVencimento, boloRemovido->precoBolo);
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
