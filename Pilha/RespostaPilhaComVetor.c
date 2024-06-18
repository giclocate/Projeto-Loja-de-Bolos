/*
    PILHA COM VETORES
    ALUNAS: GIOVANNA CLÓCATE E KÁTIA ROCHA
    PROFESSOR: MAYRTON DIAS DE QUEIROZ    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAMANHO 100

/* Definição da estrutura do bolo */
typedef struct Bolo {
    int id;
    char nome[50];
    char tamanho;
    char dataVencimento[20];
    float preco;
} Bolo;

/* Definição da estrutura da pilha */
typedef struct {
    Bolo bolos[MAX_TAMANHO];
    int topo;
} Pilha;

/* Função para criar uma nova pilha */
Pilha* criarPilha() {
    Pilha *novaPilha = (Pilha*)malloc(sizeof(Pilha));
    if (novaPilha == NULL) {
        printf("\nErro ao alocar memoria para a pilha.\n");
        exit(1);
    }
    novaPilha->topo = -1;
    return novaPilha;
}

/* Função para verificar se a pilha está vazia */
int ehVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

/* Função para empilhar um novo bolo */
void push(Pilha *pilha, Bolo novoBolo) {
    if (pilha->topo == MAX_TAMANHO - 1) {
        printf("\nErro: Pilha cheia.\n");
        return;
    }
    pilha->bolos[++pilha->topo] = novoBolo;
    printf("\nBolo inserido com sucesso.\n");
}

/* Função para desempilhar um bolo */
Bolo pop(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("\nErro: Pilha vazia.\n");
        Bolo boloVazio = {0};
        return boloVazio;
    }
    return pilha->bolos[pilha->topo--];
}

/* Função para ver o conteúdo do topo da pilha */
Bolo verTopo(Pilha *pilha) {
    if (ehVazia(pilha)) {
        printf("\nErro: Pilha vazia.\n");
        Bolo boloVazio = {0};
        return boloVazio;
    }
    return pilha->bolos[pilha->topo];
}

/* Função para excluir a pilha */
void excluirPilha(Pilha *pilha) {
    free(pilha);
    printf("\nPilha excluida com sucesso.\n");
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
        printf("3. Ver topo\n");
        printf("4. Excluir pilha\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                if (pilha->topo == MAX_TAMANHO - 1) {
                    printf("\nErro: Pilha cheia.\n");
                    break;
                }
                Bolo novoBolo;
                printf("\nInforme os dados do bolo:\n");
                printf("ID: ");
                scanf("%d", &novoBolo.id);
                limparBuffer();
                printf("Nome do bolo: ");
                fgets(novoBolo.nome, sizeof(novoBolo.nome), stdin);
                novoBolo.nome[strcspn(novoBolo.nome, "\n")] = '\0';  // Remove o caractere de nova linha do fgets
                printf("Tamanho(P/M/G): ");
                scanf(" %c", &novoBolo.tamanho);  // Espaço antes de %c para consumir a quebra de linha pendente
                limparBuffer();
                printf("Data de Vencimento (DD/MM/AAAA): ");
                fgets(novoBolo.dataVencimento, sizeof(novoBolo.dataVencimento), stdin);
                novoBolo.dataVencimento[strcspn(novoBolo.dataVencimento, "\n")] = '\0';
                printf("Preco: ");
                scanf("%f", &novoBolo.preco);
                limparBuffer();
                push(pilha, novoBolo);
                break;
            }
            case 2: {
                if (ehVazia(pilha)) {
                    printf("\nErro: Pilha vazia.\n");
                } else {
                    Bolo boloRemovido = pop(pilha);
                    printf("\nBolo removido:\n");
                    printf("ID: %d, Nome: %s, Tamanho(P/M/G): %c, Data de Vencimento(DD/MM/AAAA): %s, Preco: %.2f\n",
                        boloRemovido.id, boloRemovido.nome, boloRemovido.tamanho, boloRemovido.dataVencimento, boloRemovido.preco);
                }
                break;
            }
            case 3: {
                if (ehVazia(pilha)) {
                    printf("\nErro: Pilha vazia.\n");
                } else {
                    Bolo topo = verTopo(pilha);
                    printf("\nTopo da pilha:\n");
                    printf("ID: %d, Nome: %s, Tamanho(P/M/G): %c, Data de Vencimento(DD/MM/AAAA): %s, Preco: %.2f\n",
                        topo.id, topo.nome, topo.tamanho, topo.dataVencimento, topo.preco);
                }
                break;
            }
            case 4: {
                excluirPilha(pilha);
                pilha = criarPilha();
                break;
            }
            case 5:
                printf("\nEncerrando o programa.\n");
                printf("Obrigado por utilizar a nossa loja de bolos!\n");
                printf("Volte sempre!\n");
                printf("--------------------------------------------\n");
                break;
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
