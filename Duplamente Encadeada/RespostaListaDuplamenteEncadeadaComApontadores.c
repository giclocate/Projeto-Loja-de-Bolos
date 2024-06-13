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
    struct Bolo *ant;
} Bolo;

/* Definição da estrutura da lista */
typedef struct {
    Bolo *inicio;
    Bolo *fim;
} Lista;

/* Função para criar uma nova lista */
Lista* criarLista() {
    Lista *novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista == NULL) {
        printf("Erro ao alocar memoria para a lista.\n");
        exit(1);
    }
    novaLista->inicio = NULL;
    novaLista->fim = NULL;
    return novaLista;
}

/* Função para criar um novo bolo */
Bolo* criarBolo(int id, char *nome, char tamanho, char *dataVencimento, float preco) {
    Bolo *novoBolo = (Bolo*)malloc(sizeof(Bolo));
    if (novoBolo == NULL) {
        printf("Erro ao alocar memoria para o bolo.\n");
        exit(1);
    }
    novoBolo->id = id;
    strcpy(novoBolo->nome, nome);
    novoBolo->tamanho = tamanho;
    strcpy(novoBolo->dataVencimento, dataVencimento);
    novoBolo->preco = preco;
    novoBolo->prox = NULL;
    novoBolo->ant = NULL;
    return novoBolo;
}

/* Função para inserir um novo bolo no final da lista */
void inserirElemento(Lista *lista, Bolo *novoBolo) {
    if (lista->inicio == NULL) {
        lista->inicio = novoBolo;
        lista->fim = novoBolo;
    } else {
        lista->fim->prox = novoBolo;
        novoBolo->ant = lista->fim;
        lista->fim = novoBolo;
    }
    printf("Bolo inserido com sucesso.\n");
}

/* Função para inserir um novo bolo no início da lista */
void inserirElementoInicio(Lista *lista, Bolo *novoBolo) {
    if (lista->inicio == NULL) {
        lista->inicio = novoBolo;
        lista->fim = novoBolo;
    } else {
        novoBolo->prox = lista->inicio;
        lista->inicio->ant = novoBolo;
        lista->inicio = novoBolo;
    }
    printf("Bolo inserido no início com sucesso.\n");
}

/* Função para inserir um novo bolo na posição indicada */
void inserirElementoID(Lista *lista, Bolo *novoBolo, int pos) {
    if (pos == 0) {
        inserirElementoInicio(lista, novoBolo);
        return;
    }

    Bolo *atual = lista->inicio;
    for (int i = 0; i < pos - 1 && atual != NULL; i++) {
        atual = atual->prox;
    }

    if (atual == NULL || atual->prox == NULL) {
        inserirElemento(lista, novoBolo);
    } else {
        novoBolo->prox = atual->prox;
        novoBolo->ant = atual;
        atual->prox->ant = novoBolo;
        atual->prox = novoBolo;
    }
    printf("Bolo inserido na posicao %d com sucesso.\n", pos);
}

/* Função para inserir um novo bolo em ordem alfabética */
void inserirOrdenado(Lista *lista, Bolo *novoBolo) {
    if (lista->inicio == NULL || strcmp(novoBolo->nome, lista->inicio->nome) < 0) {
        inserirElementoInicio(lista, novoBolo);
        return;
    }

    Bolo *atual = lista->inicio;
    while (atual->prox != NULL && strcmp(novoBolo->nome, atual->prox->nome) > 0) {
        atual = atual->prox;
    }

    novoBolo->prox = atual->prox;
    if (atual->prox != NULL) {
        atual->prox->ant = novoBolo;
    } else {
        lista->fim = novoBolo;
    }
    atual->prox = novoBolo;
    novoBolo->ant = atual;
    printf("Bolo inserido em ordem alfabetica com sucesso.\n");
}

/* Função para listar todos os elementos da lista */
void listarElementos(Lista *lista) {
    if (lista->inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    Bolo *atual = lista->inicio;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Tamanho: %c, Data de Vencimento: %s, Preco: %.2f\n",
               atual->id, atual->nome, atual->tamanho, atual->dataVencimento, atual->preco);
        atual = atual->prox;
    }
}

/* Função para listar todos os elementos da lista em ordem inversa */
void listarElementosOrdemInversa(Lista *lista) {
    if (lista->fim == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Bolo *atual = lista->fim;
    while (atual != NULL) {
        printf("ID: %d, Nome: %s, Tamanho: %c, Data de Vencimento: %s, Preco: %.2f\n",
               atual->id, atual->nome, atual->tamanho, atual->dataVencimento, atual->preco);
        atual = atual->ant;
    }
}

/* Função para remover um elemento da lista por posição */
void removerElemento(Lista *lista, int pos) {
    if (lista->inicio == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    Bolo *atual = lista->inicio;
    for (int i = 0; i < pos && atual != NULL; i++) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Posição %d nao encontrada.\n", pos);
        return;
    }

    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    } else {
        lista->inicio = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    } else {
        lista->fim = atual->ant;
    }

    free(atual);
    printf("Bolo removido da posicao %d com sucesso.\n", pos);
}

/* Função para remover um elemento da lista por nome */
void removerElementoNome(Lista *lista, char *nome) {
    if (lista->inicio == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    Bolo *atual = lista->inicio;
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Bolo com nome %s nao encontrado.\n", nome);
        return;
    }

    if (atual->ant != NULL) {
        atual->ant->prox = atual->prox;
    } else {
        lista->inicio = atual->prox;
    }

    if (atual->prox != NULL) {
        atual->prox->ant = atual->ant;
    } else {
        lista->fim = atual->ant;
    }

    free(atual);
    printf("Bolo com nome %s removido com sucesso.\n", nome);
}

/* Função para buscar um elemento da lista por ID */
Bolo* buscarElemento(Lista *lista, int id) {
    Bolo *atual = lista->inicio;
    while (atual != NULL && atual->id != id) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Bolo com ID %d nao encontrado.\n", id);
    }
    return atual;
}

/* Função para atualizar os campos de um elemento da lista */
void atualizar(Lista *lista, int id, char *nome, char tamanho, char *dataVencimento, float preco) {
    Bolo *bolo = buscarElemento(lista, id);
    if (bolo != NULL) {
        strcpy(bolo->nome, nome);
        bolo->tamanho = tamanho;
        strcpy(bolo->dataVencimento, dataVencimento);
        bolo->preco = preco;
        printf("Bolo com ID %d atualizado com sucesso.\n", id);
    }
}

/* Função para obter o tamanho da lista */
int tamanho(Lista *lista) {
    int tam = 0;
    Bolo *atual = lista->inicio;
    while (atual != NULL) {
        tam++;
        atual = atual->prox;
    }
    return tam;
}

/* Função para excluir toda a lista */
void excluirLista(Lista *lista) {
    Bolo *atual = lista->inicio;
    while (atual != NULL) {
        Bolo *proximo = atual->prox;
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
        printf("1. Inserir bolo no final\n");
        printf("2. Inserir bolo no início\n");
        printf("3. Inserir bolo em posição especifica\n");
        printf("4. Inserir bolo em ordem alfabetica\n");
        printf("5. Remover bolo por posicao\n");
        printf("6. Remover bolo por nome\n");
        printf("7. Atualizar bolo\n");
        printf("8. Buscar bolo por ID\n");
        printf("9. Mostrar todos os bolos\n");
        printf("10. Mostrar todos os bolos (ordem inversa)\n");
        printf("11. Tamanho da lista\n");
        printf("12. Excluir lista\n");
        printf("13. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: {
                int id;
                char nome[50];
                char tamanho;
                char dataVencimento[20];
                float preco;

                printf("Digite o ID: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o tamanho do bolo (P, M ou G): ");
                scanf(" %c", &tamanho);
                limparBuffer();

                printf("Digite a data de vencimento (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &preco);
                limparBuffer();

                Bolo *novoBolo = criarBolo(id, nome, tamanho, dataVencimento, preco);
                inserirElemento(lista, novoBolo);
                break;
            }
            case 2: {
                int id;
                char nome[50];
                char tamanho;
                char dataVencimento[20];
                float preco;

                printf("Digite o ID: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o tamanho do bolo (P, M ou G): ");
                scanf(" %c", &tamanho);
                limparBuffer();

                printf("Digite a data de vencimento (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &preco);
                limparBuffer();

                Bolo *novoBolo = criarBolo(id, nome, tamanho, dataVencimento, preco);
                inserirElementoInicio(lista, novoBolo);
                break;
            }
            case 3: {
                int id, pos;
                char nome[50];
                char tamanho;
                char dataVencimento[20];
                float preco;

                printf("Digite o ID: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o tamanho do bolo (P, M ou G): ");
                scanf(" %c", &tamanho);
                limparBuffer();

                printf("Digite a data de vencimento (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &preco);
                limparBuffer();

                printf("Digite a posicao para inserir o bolo: ");
                scanf("%d", &pos);
                limparBuffer();

                Bolo *novoBolo = criarBolo(id, nome, tamanho, dataVencimento, preco);
                inserirElementoID(lista, novoBolo, pos);
                break;
            }
            case 4: {
                int id;
                char nome[50];
                char tamanho;
                char dataVencimento[20];
                float preco;

                printf("Digite o ID: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o tamanho do bolo (P, M ou G): ");
                scanf(" %c", &tamanho);
                limparBuffer();

                printf("Digite a data de vencimento (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o preco: ");
                scanf("%f", &preco);
                limparBuffer();

                Bolo *novoBolo = criarBolo(id, nome, tamanho, dataVencimento, preco);
                inserirOrdenado(lista, novoBolo);
                break;
            }
            case 5: {
                int pos;
                printf("Digite a posicao do bolo a ser removido: ");
                scanf("%d", &pos);
                limparBuffer();
                removerElemento(lista, pos);
                break;
            }
            case 6: {
                char nome[50];
                printf("Digite o nome do bolo a ser removido: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerElementoNome(lista, nome);
                break;
            }
            case 7: {
                int id;
                char nome[50];
                char tamanho;
                char dataVencimento[20];
                float preco;

                printf("Digite o ID do bolo a ser atualizado: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o novo nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o novo tamanho do bolo (P, M ou G): ");
                scanf(" %c", &tamanho);
                limparBuffer();

                printf("Digite a nova data de vencimento (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o novo preco: ");
                scanf("%f", &preco);
                limparBuffer();

                atualizar(lista, id, nome, tamanho, dataVencimento, preco);
                break;
            }
            case 8: {
                int id;
                printf("Digite o ID do bolo a ser buscado: ");
                scanf("%d", &id);
                limparBuffer();

                Bolo *boloBuscado = buscarElemento(lista, id);
                if (boloBuscado != NULL) {
                    printf("Bolo encontrado:\n");
                    printf("ID: %d, Nome: %s, Tamanho: %c, Data de Vencimento: %s, Preco: %.2f\n",
                           boloBuscado->id, boloBuscado->nome, boloBuscado->tamanho, boloBuscado->dataVencimento, boloBuscado->preco);
                }
                break;
            }
            case 9: {
                listarElementos(lista);
                break;
            }
            case 10: {
                listarElementosOrdemInversa(lista);
                break;
            }
            case 11: {
                int tam = tamanho(lista);
                printf("A lista tem %d elementos.\n", tam);
                break;
            }
            case 12: {
                excluirLista(lista);
                lista = criarLista();
                break;
            }
            case 13: {
                printf("Encerrando o programa.\n");
                excluirLista(lista);
                exit(0);
            }
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 13);

    return 0;
}
