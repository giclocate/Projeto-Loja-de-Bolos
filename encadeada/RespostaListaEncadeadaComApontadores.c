/****************************************************************** 
 * Nome: Lista encadeada com apontadores                          *
 * Descricao: Implementacao de lista encadeada com vetores. Esse  * 
 *            codigo possui as principais operacoes da lista,     * 
 *            como:                                               *
 *            criar lista,                                        *
 *            inserir elemento,                                   *
 *            remover elemento,                                   *
 *            buscar elemento,                                    *
 *            mostrar elementos,                                  *
 *            atualizar elementos,                                *
 *            excluir lista.                                      *
 * Autor: Giovanna Clócate e Kátia Rocha                          *
 * Ultima alteracao: 11/05/2024                                   *
 ******************************************************************/

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
ListaNo* buscarElemento(Lista *lista, int valor);
int inserirElemento(Lista *lista);
int removerElemento(Lista *lista, int valor);
int atualizarElemento(Lista *lista, int id);
void mostrarElementos(Lista *lista);
void excluirLista(Lista *lista);
int inserirElementoID(Lista *lista, int posicao);
int inserirElementoInicio(Lista *lista);
int tamanho(Lista *lista);

/* Função principal */
int main() {
    Lista *lista = criarLista();
    int opcao, id, posicao;

    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Inserir novo bolo\n");
        printf("2. Inserir bolo no inicio\n");
        printf("3. Inserir bolo na posicao\n");
        printf("4. Remover bolo\n");
        printf("5. Buscar bolo por ID\n");
        printf("6. Mostrar todos os bolos\n");
        printf("7. Mostrar quantidade de bolos\n");
        printf("8. Atualizar bolo\n"); 
        printf("9. Excluir lista\n");
        printf("10. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirElemento(lista);
                break;
            case 2:
                inserirElementoInicio(lista);
                break;
            case 3:
                printf("Digite a posicao onde o bolo sera inserido: ");
                scanf("%d", &posicao);
                inserirElementoID(lista, posicao);
                break;
            case 4:
                if (lista == NULL || lista->prim == NULL) {
                    printf("A lista esta vazia.\n");
                }
                else{
                    printf("Digite o ID do bolo a ser removido: ");
                    scanf("%d", &id);
                    removerElemento(lista, id);
                }
                break;
            case 5:
                printf("Digite o ID do bolo a ser buscado: ");
                scanf("%d", &id);
                buscarElemento(lista, id);
                break;
            case 6:
                mostrarElementos(lista);
                break;
            case 7:
                printf("Quantidade de bolos na lista: %d\n", tamanho(lista));
                break;
            case 8:
                printf("Digite o ID do bolo a ser atualizado: ");
                scanf("%d", &id);
                atualizarElemento(lista, id);
                break;
            case 9:
                excluirLista(lista);
                lista = criarLista();
                printf("Lista de bolos excluida.\n");
                break;
            case 10:
                printf("Programa encerrado.\n");
                printf("Obrigado por usar o programa.\n");
                printf("--------------------------------\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 10);

    return 0;
}

/* Função para limpar o buffer */
void limparBuffer () {
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
    fgets(novoBolo->nomeBolo, 50, stdin);
    strtok(novoBolo->nomeBolo, "\n");
    printf("\nDigite o tamanho do bolo (P, M ou G):\n");
    scanf(" %c", &novoBolo->tamanhoBolo);
    limparBuffer();
    printf("\nDigite a data de vencimento do bolo:\n");
    fgets(novoBolo->dataVencimento, 20, stdin);
    strtok(novoBolo->dataVencimento, "\n");
    printf("\nDigite o preco do bolo:\n");
    scanf("%f", &novoBolo->precoBolo);

    return novoBolo;
}

/* Função para mostrar os detalhes de um bolo */
void mostrarBolo(Bolo *bolo) {
    printf("\nID: %d\n", bolo->id);
    printf("Nome: %s\n", bolo->nomeBolo);
    printf("Tamanho: %c\n", bolo->tamanhoBolo);
    printf("Data de Vencimento: %s\n", bolo->dataVencimento);
    printf("Preco: %.2f\n", bolo->precoBolo);
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

/* Função para buscar um bolo por ID na lista */
ListaNo* buscarElemento(Lista *lista, int valor) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return NULL;
    }

    for (p = lista->prim; p != NULL; p = p->prox) {
        if (p->bolo->id == valor) {
            printf("\nBolo encontrado:\n");
            mostrarBolo(p->bolo);
            return p;
        }
    }
    printf("Bolo nao encontrado.\n");
    return NULL;
}

/* Função para inserir um bolo na lista */
int inserirElemento(Lista *lista) {
    Bolo *novoBolo = criarFilaBolo();
    inserirBolo(lista, novoBolo);
    printf("Bolo inserido com sucesso.\n");
    return 1;
}

/* Função para mostrar todos os bolos da lista */
void mostrarElementos(Lista *lista) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("\nLISTA DE BOLOS: \n");
    printf("----------------\n");
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

/* Função para inserir um bolo na lista em uma posição específica */
int inserirElementoID(Lista *lista, int posicao) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    Bolo *novoBolo = criarFilaBolo();
    ListaNo *novoNo = (ListaNo*)malloc(sizeof(ListaNo));
    if (novoNo == NULL) {
        printf("Erro ao alocar memoria para o no da lista.\n");
        exit(1);
    }
    novoNo->bolo = novoBolo;
    novoNo->prox = NULL;

    if (posicao <= 1 || lista->prim == NULL) {
        novoNo->prox = lista->prim;
        lista->prim = novoNo;
        if (lista->ult == NULL) {
            lista->ult = novoNo;
        }
    } else {
        ListaNo *p = lista->prim;
        for (int i = 1; i < posicao - 1 && p->prox != NULL; i++) {
            p = p->prox;
        }
        novoNo->prox = p->prox;
        p->prox = novoNo;
        if (novoNo->prox == NULL) {
            lista->ult = novoNo;
        }
    }

    printf("Bolo inserido na posicao %d com sucesso.\n", posicao);
    return 1;
}

/* Função para inserir um bolo no início da lista */
int inserirElementoInicio(Lista *lista) {
    return inserirElementoID(lista, 1);
}

/* Função para obter o tamanho da lista */
int tamanho(Lista *lista) {
    int count = 0;
    ListaNo *p = lista->prim;
    while (p != NULL) {
        count++;
        p = p->prox;
    }
    return count;
}

/* Função para atualizar os dados de um bolo na lista */
int atualizarElemento(Lista *lista, int id) {
    ListaNo *no = buscarElemento(lista, id);
    if (no == NULL) {
        printf("Bolo nao encontrado.\n");
        return 0;
    }

    Bolo *bolo = no->bolo;
    printf("\nAtualizando o bolo com ID %d:\n", bolo->id);

    printf("\nDigite o novo nome do bolo (deixe em branco para nao alterar):\n");
    limparBuffer();
    char nomeBolo[50];
    fgets(nomeBolo, 50, stdin);
    if (strcmp(nomeBolo, "\n") != 0) {
        strtok(nomeBolo, "\n");
        strcpy(bolo->nomeBolo, nomeBolo);
    }

    printf("\nDigite o novo tamanho do bolo (P, M ou G) (deixe em branco para nao alterar):\n");
    char tamanhoBolo;
    if (scanf(" %c", &tamanhoBolo) == 1) {
        bolo->tamanhoBolo = tamanhoBolo;
    }
    limparBuffer();

    printf("\nDigite a nova data de vencimento do bolo (deixe em branco para nao alterar):\n");
    char dataVencimento[20];
    fgets(dataVencimento, 20, stdin);
    if (strcmp(dataVencimento, "\n") != 0) {
        strtok(dataVencimento, "\n");
        strcpy(bolo->dataVencimento, dataVencimento);
    }

    printf("\nDigite o novo preco do bolo (deixe em branco para nao alterar):\n");
    char precoBoloStr[20];
    fgets(precoBoloStr, 20, stdin);
    if (strcmp(precoBoloStr, "\n") != 0) {
        float precoBolo = atof(precoBoloStr);
        bolo->precoBolo = precoBolo;
    }

    printf("Bolo atualizado com sucesso.\n");
    return 1;
}