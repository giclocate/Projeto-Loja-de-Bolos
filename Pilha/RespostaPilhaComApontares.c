/*
    PILHA COM APONTADORES
    ALUNAS: GIOVANNA CLÓCATE E KÁTIA ROCHA
    PROFESSOR: MAYRTON DIAS DE QUEIROZ    
*/


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

/* Definição da estrutura da pilha */
typedef struct {
    Bolo *topo;
} Pilha;

/* Função para criar uma nova pilha */
Pilha* criarPilha() {
    Pilha *novaPilha = (Pilha*)malloc(sizeof(Pilha));
    if (novaPilha == NULL) {
        printf("Erro ao alocar memoria para a pilha.\n");
        exit(1);
    }
    novaPilha->topo = NULL;
    return novaPilha;
}

/* Função para verificar se a pilha está vazia */
int ehVazia(Pilha *pilha) {
    return pilha->topo == NULL;
}

/* Função para empilhar um novo bolo */
void push(Pilha *pilha, Bolo *novoBolo) {
    if (novoBolo == NULL) {
        printf("Erro: Bolo invalido.\n");
        return;
    }
    novoBolo->prox = pilha->topo;
    pilha->topo = novoBolo;
    printf("Bolo inserido com sucesso.\n");
}

/* Função para desempilhar um bolo */
Bolo* pop(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("Erro: Pilha vazia.\n");
        return NULL;
    }
    Bolo *boloRemovido = pilha->topo;
    pilha->topo = pilha->topo->prox;
    return boloRemovido;
}

/* Função para ver o conteúdo do topo da pilha */
Bolo* verTopo(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("Erro: Pilha vazia.\n");
        return NULL;
    }
    return pilha->topo;
}

/* Função para mostrar todos os bolos da pilha */
void mostrarElementos(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("A pilha esta vazia.\n");
        return;
    }
    Bolo *atual = pilha->topo;
    printf("Lista de Bolos:\n");
    while (atual != NULL) {
        printf("ID: %d, Nome do bolo: %s, Tamanho(P/M/G): %c, Data de Vencimento(DD/MM/AAAA): %s, Preco: %.2f\n",
            atual->id, atual->nome, atual->tamanho,atual->dataVencimento, atual->preco);
        atual = atual->prox;
    }
}

/* Função para excluir a pilha */
void excluirPilha(Pilha *pilha) {
    Bolo *atual = pilha->topo;
    Bolo *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(pilha);
    printf("Pilha excluida com sucesso.\n");
}

/* Função para limpar o buffer de entrada */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    Pilha *pilha = criarPilha();

    int opcao;
    do {
        printf("\nSEJAM BEM-VINDOS(AS) A MELHOR LOJA DE BOLOS!\n");
        printf("\nNOSSO MENU:\n");
        printf("1. Inserir bolo\n");
        printf("2. Remover bolo\n");
        printf("3. Mostrar todos os bolos\n");
        printf("4. Ver topo\n");
        printf("5. Excluir pilha\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                Bolo *novoBolo = (Bolo*)malloc(sizeof(Bolo));
                if (novoBolo == NULL) {
                    printf("Erro ao alocar memoria para o bolo.\n");
                    break;
                }
                printf("\nInforme os dados do bolo:\n");
                printf("ID: ");
                scanf("%d", &novoBolo->id);
                limparBuffer();
                printf("Nome do bolo: ");
                fgets(novoBolo->nome, sizeof(novoBolo->nome), stdin);
                novoBolo->nome[strcspn(novoBolo->nome, "\n")] = '\0';  // Remove o caractere de nova linha do fgets
                printf("Tamanho(P/M/G): ");
                scanf(" %c", &novoBolo->tamanho);  // Espaço antes de %c para consumir a quebra de linha pendente
                limparBuffer();
                printf("Data de Vencimento (DD/MM/AAAA): ");
                fgets(novoBolo->dataVencimento, sizeof(novoBolo->dataVencimento), stdin);
                novoBolo->dataVencimento[strcspn(novoBolo->dataVencimento, "\n")] = '\0';
                printf("Preco: ");
                scanf("%f", &novoBolo->preco);
                limparBuffer();
                novoBolo->prox = NULL;
                push(pilha, novoBolo);
                break;
            }
            case 2: {
                Bolo *boloRemovido = pop(pilha);
                if (boloRemovido != NULL) {
                    printf("\nBolo removido:\n");
                    printf("ID: %d, Nome: %s, Tamanho(P/M/G): %c, Data de Vencimento(DD/MM/AAAA): %s, Preco: %.2f\n",
                           boloRemovido->id, boloRemovido->nome, boloRemovido->tamanho, boloRemovido->dataVencimento, boloRemovido->preco);
                    free(boloRemovido);  // Libera a memória do bolo removido
                }
                break;
            }
            case 3: {
                mostrarElementos(pilha);
                break;
            }
            case 4: {
                Bolo *topo = verTopo(pilha);
                if (topo != NULL) {
                    printf("\nTopo da pilha:\n");
                    printf("ID: %d, Nome: %s, Tamanho(P/M/G): %c, Data de Vencimento(DD/MM/AAAA): %s, Preco: %.2f\n",
                           topo->id, topo->nome, topo->tamanho,topo->dataVencimento, topo->preco);
                }
                break;
            }
            case 5: {
                excluirPilha(pilha);
                printf("\n");
                pilha = criarPilha();
                break;
            }
            case 6:
                printf("\nEncerrando o programa.\n");
                exit(0);
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}

