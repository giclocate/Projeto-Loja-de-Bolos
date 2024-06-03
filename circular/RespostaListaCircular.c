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
Bolo* criarBolo();
void mostrarBolo(Bolo *bolo);
void destruirBolo(Bolo *bolo);
void limparBuffer();

/* Funções relacionadas à Lista */
Lista* criarLista();
void inserirBolo(Lista *lista, Bolo *novoBolo);
ListaNo* buscarElemento(Lista *lista, int valor);
int inserirElemento(Lista *lista, int valor);
int removerElemento(Lista *lista, int valor);
void mostrarElementos(Lista *lista);
void excluirLista(Lista *lista);

/* Função principal */
int main() {
    Lista *lista = criarLista();
    int opcao, id;

    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Inserir novo bolo\n");
        printf("2. Remover bolo\n");
        printf("3. Buscar bolo por ID\n");
        printf("4. Mostrar todos os bolos\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirElemento(lista, lista->ult != NULL ? lista->ult->bolo->id + 1 : 1);
                break;
            case 2:
                printf("Digite o ID do bolo a ser removido: ");
                scanf("%d", &id);
                removerElemento(lista, id);
                break;
            case 3:
                printf("Digite o ID do bolo a ser buscado: ");
                scanf("%d", &id);
                buscarElemento(lista, id);
                break;
            case 4:
                mostrarElementos(lista);
                break;
            case 5:
                excluirLista(lista);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}

/* Função para criar um novo bolo */

void limparBuffer () {
    
    char c;
    do {
        c = getchar();
    } while (c != '\n');
}

Bolo* criarBolo() {
    Bolo *novoBolo = (Bolo*)malloc(sizeof(Bolo));
    if (novoBolo == NULL) {
        printf("Erro ao alocar memoria para o bolo.\n");
        exit(1);
    }

    printf("\nDigite o ID do bolo:\n");
    scanf("%d", &novoBolo->id);
    printf("\nDigite o nome do bolo:\n");
    scanf("%s", novoBolo->nomeBolo);
    printf("\nDigite o tamanho do bolo (P, M ou G):\n");
    scanf(" %c", &novoBolo->tamanhoBolo);
    printf("\nDigite a data de vencimento do bolo:\n");
    scanf("%s", novoBolo->dataVencimento);
    printf("\nDigite o preco do bolo:\n");
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
    Bolo *novoBolo = criarBolo();
    inserirBolo(lista, novoBolo);
    printf("Bolo inserido com sucesso.\n");
    return 1;
}

/*
/* Função para mostrar todos os bolos da lista */
void mostrarElementos(Lista *lista) {
    ListaNo *p;

    if (lista == NULL || lista->prim == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    printf("Lista de Bolos:\n");
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






