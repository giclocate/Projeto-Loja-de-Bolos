#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definindo a estrutura Bolo */
typedef struct {
    int id;
    char nomeBolo[50];
    char tamanhoBolo;
    char dataVencimento[20];
    float precoBolo;
} Bolo;

/* Definindo a estrutura Lista e o elemento da lista */
typedef struct listaNo ListaNo;
typedef struct {
    ListaNo *prim;
    ListaNo *ult;
} Lista;

struct listaNo {
    Bolo *bolo;
    ListaNo *prox;
};

/* Funções relacionadas ao Bolo */
Bolo* criarFilaBolo();
void mostrarBolo(Bolo *bolo);
void destruirBolo(Bolo *bolo);
void limparBuffer();

/* Funções relacionadas à Lista */
Lista* criarLista();
void inserirBolo(Lista *lista, Bolo *novoBolo);
void inserirElementoInicio(Lista *lista, Bolo *novoBolo);
void inserirElementoID(Lista *lista, Bolo *novoBolo, int pos);
ListaNo* buscarElemento(Lista *lista, int valor);
int inserirElemento(Lista *lista, int valor);
int removerElemento(Lista *lista, int valor);
int removerElementoNome(Lista *lista, char *nome);
void mostrarElementos(Lista *lista);
void atualizar(Lista *lista, int id, char *novoNome, char novoTamanho, char *novaDataVencimento, float novoPreco);
int tamanho(Lista *lista);
void excluirLista(Lista *lista);

/* Função principal */
int main() {
    Lista *lista = criarLista();
    int opcao, id;
    char nome[50];
    char tamanhoBolo;
    char dataVencimento[11];
    float preco;

    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Inserir novo bolo\n");
        printf("2. Inserir bolo no inicio\n");
        printf("3. Inserir bolo na posicao\n");
        printf("4. Remover bolo\n");
        printf("5. Remover bolo por nome\n");
        printf("6. Buscar bolo por ID\n");
        printf("7. Atualizar bolo\n");
        printf("8. Mostrar todos os bolos\n");
        printf("9. Mostrar tamanho da lista\n");
        printf("10. Excluir lista\n");
        printf("11. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirElemento(lista, lista->ult != NULL ? lista->ult->bolo->id + 1 : 1);
                break;
            case 2:
                inserirElementoInicio(lista, criarFilaBolo());
                printf("\nBolo inserido no inicio com sucesso.\n");
                break;
            case 3:
                printf("Digite a posicao para inserir o bolo: ");
                int pos;
                scanf("%d", &pos);
                inserirElementoID(lista, criarFilaBolo(), pos);
                printf("\nBolo inserido na posicao %d com sucesso.\n", pos);
                break;
            case 4:
                printf("Digite o ID do bolo a ser removido: ");
                scanf("%d", &id);
                removerElemento(lista, id);
                break;
            case 5:
                printf("Digite o nome do bolo a ser removido: ");
                limparBuffer();
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerElementoNome(lista, nome);
                break;
            case 6:
                printf("Digite o ID do bolo a ser buscado: ");
                scanf("%d", &id);
                buscarElemento(lista, id);
                break;
            case 7:
                printf("Digite o ID do bolo a ser atualizado: ");
                scanf("%d", &id);
                limparBuffer();

                printf("Digite o novo nome do bolo: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';

                printf("Digite o novo tamanho do bolo: ");
                scanf("%c", &tamanho);
                limparBuffer();

                printf("Digite a nova data de vencimento do bolo (DD/MM/AAAA): ");
                fgets(dataVencimento, sizeof(dataVencimento), stdin);
                dataVencimento[strcspn(dataVencimento, "\n")] = '\0';

                printf("Digite o novo preço do bolo: ");
                scanf("%f", &preco);
                limparBuffer();

        atualizar(lista, id, nome, tamanho, dataVencimento, preco);
        break;
            case 8:
                mostrarElementos(lista);
                break;
            case 9:
                printf("Tamanho da lista: %d\n", tamanho(lista));
                break;
            case 10:
                excluirLista(lista);
                printf("\nLista excluida.\n");
                lista = criarLista();  
                break;
            case 11:
                excluirLista(lista);
                printf("\nPrograma encerrado. Volte sempre!\n");
                printf("--------------\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente!\n");
        }
    } while (opcao != 11);

    return 0;
}

/* Função para limpar o buffer de entrada */
void limparBuffer() {
    char c;
    do {
        c = getchar();
    } while (c != '\n');
}

/* Função para criar um novo bolo */
Bolo* criarFilaBolo() {
    Bolo *novoBolo = (Bolo*)malloc(sizeof(Bolo));
    if (novoBolo == NULL) {
        printf("Erro ao alocar memoria para o bolo.\n");
        exit(1);
    }

    printf("\nDigite o ID do bolo:\n");
    scanf("%d", &novoBolo->id);
    limparBuffer();
    printf("\nDigite o nome do bolo:\n");
    scanf("%49[^\n]s", novoBolo->nomeBolo);
    limparBuffer();
    printf("\nDigite o tamanho do bolo (P, M ou G):\n");
    scanf(" %c", &novoBolo->tamanhoBolo);
    limparBuffer();
    printf("\nDigite a data de vencimento do bolo:\n");
    scanf("%10[^\n]s", novoBolo->dataVencimento);
    printf("\nDigite o preco do bolo:\n");
    limparBuffer();
    scanf("%f", &novoBolo->precoBolo);

    return novoBolo;
}

/* Função para mostrar os detalhes de um bolo */
void mostrarBolo(Bolo *bolo) {
    printf("ID: %d\n", bolo->id);
    printf("Nome: %s\n", bolo->nomeBolo);
    printf("Tamanho: %c\n", bolo->tamanhoBolo);
    printf("Data de Vencimento: %s\n", bolo->dataVencimento);
    printf("Preco: %.2f\n", bolo->precoBolo);
    printf("\n");
}

/* Função para destruir um bolo */
void destruirBolo(Bolo *bolo) {
    free(bolo);
}

/* Função para criar uma nova lista */
Lista* criarLista() {
    Lista *novaLista = (Lista*)malloc(sizeof(Lista));
    if (novaLista == NULL) {
        printf("Erro ao alocar memoria para a lista.\n");
        exit(1);
    }
    novaLista->prim = NULL;
    novaLista->ult = NULL;
    return novaLista;
}

/* Função para inserir um novo bolo na lista */
void inserirBolo(Lista *lista, Bolo *novoBolo) {
    ListaNo *novoNo = (ListaNo*)malloc(sizeof(ListaNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o no da lista.\n");
        exit(1);
    }
    novoNo->bolo = novoBolo;
    novoNo->prox = NULL;

    if (lista->prim == NULL) {
        lista->prim = novoNo;
    } else {
        lista->ult->prox = novoNo;
    }
    lista->ult = novoNo;
}

/* Função para inserir um novo bolo no início da lista */
void inserirElementoInicio(Lista *lista, Bolo *novoBolo) {
    ListaNo *novoNo = (ListaNo*)malloc(sizeof(ListaNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o no da lista.\n");
        exit(1);
    }
    novoNo->bolo = novoBolo;
    novoNo->prox = lista->prim;
    lista->prim = novoNo;

    if (lista->ult == NULL) {
        lista->ult = novoNo;
    }
}

/* Função para inserir um novo bolo na posição indicada da lista */
void inserirElementoID(Lista *lista, Bolo *novoBolo, int pos) {
    if (pos == 0) {
        inserirElementoInicio(lista, novoBolo);
        return;
    }

    ListaNo *p = lista->prim;
    int count = 0;

    while (p != NULL && count < pos - 1) {
        count++;
        p = p->prox;
    }

    if (p == NULL) {
        printf("Posicao invalida.\n");
        return;
    }

    ListaNo *novoNo = (ListaNo*)malloc(sizeof(ListaNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o no da lista.\n");
        exit(1);
    }
    novoNo->bolo = novoBolo;
    novoNo->prox = p->prox;
    p->prox = novoNo;

    if (novoNo->prox == NULL) {
        lista->ult = novoNo;
    }
}

/* Função para buscar um bolo por ID na lista */
ListaNo* buscarElemento(Lista *lista, int valor) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return NULL;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->bolo->id == valor) {
            printf("Bolo encontrado:\n");
            mostrarBolo(p->bolo);
            return p;
        }
    }
    printf("Bolo nao encontrado.\n");
    return NULL;
}

/* Função para inserir um bolo na lista */
int inserirElemento(Lista *lista, int valor) {
    Bolo *novoBolo = criarFilaBolo();
    inserirBolo(lista, novoBolo);
    printf("\nBOLO INSERIDO COM SUCESSO!\n");
    printf("\n");
    return 1;
}

/* Função para mostrar todos os bolos da lista */
void mostrarElementos(Lista *lista) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("\nLISTA DE BOLOS:\n");
    printf("---------------\n");
    for (p = lista->prim; p != NULL; p = p->prox) {
        mostrarBolo(p->bolo);
    }
}

/* Função para remover um bolo da lista por ID */
int removerElemento(Lista *lista, int valor) {
    ListaNo *p, *ant = NULL;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return 0;
    }

    for (p = lista->prim; p != NULL; ant = p, p = p->prox) {
        if (p->bolo->id == valor) {
            if (ant == NULL) {
                lista->prim = p->prox;
            } else {
                ant->prox = p->prox;
            }

            if (lista->ult == p) {
                lista->ult = ant;
            }

            destruirBolo(p->bolo);
            free(p);
            printf("Bolo removido com sucesso.\n");
            return 1;
        }
    }

    printf("Bolo nao encontrado.\n");
    return 0;
}

/* Função para remover um bolo da lista por nome */
int removerElementoNome(Lista *lista, char *nome) {
    ListaNo *p, *ant = NULL;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return 0;
    }

    for (p = lista->prim; p != NULL; ant = p, p = p->prox) {
        if (strcmp(p->bolo->nomeBolo, nome) == 0) {
            if (ant == NULL) {
                lista->prim = p->prox;
            } else {
                ant->prox = p->prox;
            }

            if (lista->ult == p) {
                lista->ult = ant;
            }

            destruirBolo(p->bolo);
            free(p);
            printf("Bolo removido com sucesso.\n");
            return 1;
        }
    }

    printf("Bolo nao encontrado.\n");
    return 0;
}

/* Função para atualizar um bolo na lista */
void atualizar(Lista *lista, int id, char *novoNome, char novoTamanho, char *novaDataVencimento, float novoPreco) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista está vazia.\n");
        return;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->bolo->id == id) {
            strncpy(p->bolo->nomeBolo, novoNome, sizeof(p->bolo->nomeBolo) - 1);
            p->bolo->nomeBolo[sizeof(p->bolo->nomeBolo) - 1] = '\0';

            p->bolo->tamanhoBolo = novoTamanho;
            strncpy(p->bolo->dataVencimento, novaDataVencimento, sizeof(p->bolo->dataVencimento) - 1);
            p->bolo->dataVencimento[sizeof(p->bolo->dataVencimento) - 1] = '\0';
            p->bolo->precoBolo = novoPreco;

            printf("Bolo atualizado com sucesso.\n");
            printf("Nome: %s\n", p->bolo->nomeBolo);
            printf("Tamanho: %c\n", p->bolo->tamanhoBolo);
            printf("Data de Vencimento: %s\n", p->bolo->dataVencimento);
            printf("Preço: %.2f\n", p->bolo->precoBolo);
            return;
        }
    }

    printf("Bolo não encontrado.\n");
}

/* Função para obter o tamanho da lista */
int tamanho(Lista *lista) {
    int count = 0;
    ListaNo *p;

    for (p = lista->prim; p != NULL; p = p->prox) {
        count++;
    }

    return count;
}

/* Função para excluir toda a lista de bolos */
void excluirLista(Lista *lista) {
    ListaNo *p, *aux;

    if (lista == NULL || lista->prim == NULL) {
        return;
    }

    for (p = lista->prim; p != NULL; p = aux) {
        aux = p->prox;
        destruirBolo(p->bolo);
        free(p);
    }

    free(lista);
}
