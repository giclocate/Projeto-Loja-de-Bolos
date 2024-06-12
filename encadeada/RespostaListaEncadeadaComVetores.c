/****************************************************************** 
 * Nome: Lista encadeada                                          *
 * Descricao: Implementacao de lista encadeada. Esse codigo possui*
 *            as principais operacoes da lista, como:             *
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

/* Include das bibliotecas */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 4

/* Criando a struct Bolo */
typedef struct {
    int codigo;
    char nomeBolo[50];
    char tamanhoBolo;
    char dataVencimento[11];
    float precoBolo;
} Bolo;

// Segunda struct
typedef struct {
    int id;
    Bolo *bolos;
} Lista;

// Funções declaradas para a criação do menu
Lista* criarBolo();
int atualizarBolo(Lista*, int, char[], char, char[], float);
int buscarBolo(Lista*, int);
void excluirListaBolo(Lista*);
int inserirBolo(Lista*, int, char[], char, char[], float);
void limparBuffer();
void imprimirBolo(Lista*);
int removerBolo(Lista*, int);
int inserirElementoID(Lista*, int, int, char[], char, char[], float);
int inserirElementoInicio(Lista*, int, char[], char, char[], float);
void listarElementos(Lista*);
int tamanho(Lista*);

int main() {
    Lista *lista = criarBolo();
    int opcao, codigo, posicao;
    float preco;
    char nomeBolo[50], tamanhoBolo, dataVencimento[11];

    do {
        printf("\n############ BEM VINDOS A NOSSA LOJA DE BOLOS! ############\n");
        printf("\nEscolha uma das opcoes abaixo:\n");
        printf("1. Inserir novo bolo\n");
        printf("2. Remover bolo da lista\n");
        printf("3. Buscar bolo por ID\n");
        printf("4. Listar todos os bolos\n");
        printf("5. Remover lista\n");
        printf("6. Inserir bolo em uma posição especifica\n");
        printf("7. Inserir bolo no inicio da lista\n");
        printf("8. Mostrar quantidade de elementos na lista\n");
        printf("9. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o ID do bolo: ");
                scanf("%d", &codigo);
                limparBuffer();
                printf("Digite o nome do bolo: ");
                scanf("%49[^\n]s", nomeBolo);
                printf("Digite o tamanho do bolo (P/M/G): ");
                limparBuffer();
                scanf("%c", &tamanhoBolo);
                printf("Digite a data de vencimento do bolo (dd/mm/yyyy): ");
                limparBuffer();
                scanf("%10[^\n]s", dataVencimento);
                printf("Digite o preco do bolo: ");
                limparBuffer();
                scanf("%f", &preco);
                inserirBolo(lista, codigo, nomeBolo, tamanhoBolo, dataVencimento, preco);
                printf("\nBolo inserido com sucesso!\n");
                break;
            case 2:
                printf("Digite o ID do bolo a ser removido: ");
                scanf("%d", &codigo);
                removerBolo(lista, codigo);
                printf("\nBolo removido com sucesso!\n");
                break;
            case 3:
                printf("Digite o ID do bolo para buscar: ");
                scanf("%d", &codigo);
                int busca = buscarBolo(lista, codigo);
                if (busca != -1) {
                    printf("Bolo encontrado na posicao %d\n", busca);
                } else {
                    printf("Bolo nao encontrado\n");
                }
                break;
            case 4:
                imprimirBolo(lista);
                break;
            case 5:
                excluirListaBolo(lista);
                lista = criarBolo();
                printf("Lista de bolos removida.\n");
                break;
            case 6:
                printf("Digite a posição para inserir o bolo: ");
                scanf("%d", &posicao);
                printf("Digite o ID do bolo: ");
                scanf("%d", &codigo);
                limparBuffer();
                printf("Digite o nome do bolo: ");
                scanf("%49[^\n]s", nomeBolo);
                printf("Digite o tamanho do bolo (P/M/G): ");
                limparBuffer();
                scanf("%c", &tamanhoBolo);
                printf("Digite a data de vencimento do bolo (dd/mm/yyyy): ");
                limparBuffer();
                scanf("%10[^\n]s", dataVencimento);
                printf("Digite o preco do bolo: ");
                limparBuffer();
                scanf("%f", &preco);
                inserirElementoID(lista, posicao, codigo, nomeBolo, tamanhoBolo, dataVencimento, preco);
                printf("\nBolo inserido na posicao %d com sucesso!\n", posicao);
                break;
            case 7:
                printf("Digite o ID do bolo: ");
                scanf("%d", &codigo);
                limparBuffer();
                printf("Digite o nome do bolo: ");
                scanf("%49[^\n]s", nomeBolo);
                printf("Digite o tamanho do bolo (P/M/G): ");
                limparBuffer();
                scanf("%c", &tamanhoBolo);
                printf("Digite a data de vencimento do bolo (dd/mm/yyyy): ");
                limparBuffer();
                scanf("%10[^\n]s", dataVencimento);
                printf("Digite o preco do bolo: ");
                limparBuffer();
                scanf("%f", &preco);
                inserirElementoInicio(lista, codigo, nomeBolo, tamanhoBolo, dataVencimento, preco);
                printf("\nBolo inserido no inicio da lista com sucesso!\n");
                break;
            case 8:
                printf("Quantidade de elementos na lista: %d\n", tamanho(lista));
                break;
            case 9:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 10);

    return 0;
}

void limparBuffer() {
    char c;
    do {
        c = getchar();
    } while (c != '\n');
}

/* Nome: atualizarElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             codigo - codigo do bolo que sera atualizado
 *             nomeBolo - novo nome do bolo
 *             tamanhoBolo - novo tamanho do bolo
 *             dataVencimento - nova data de vencimento do bolo
 *             preco - novo preco do bolo
 * Retorno: 1 - quando o valor é atualizado e 0 - caso contrário
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int atualizarBolo(Lista *lista, int codigo, char nomeBolo[], char tamanhoBolo, char dataVencimento[], float preco) {
    int i;
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }

    for (i = 0; i < lista->id; ++i) {
        if (lista->bolos[i].codigo == codigo) {
            strcpy(lista->bolos[i].nomeBolo, nomeBolo);
            lista->bolos[i].tamanhoBolo = tamanhoBolo;
            strcpy(lista->bolos[i].dataVencimento, dataVencimento);
            lista->bolos[i].precoBolo = preco;
            printf("Bolo atualizado!\n");
            return 1;
        }
    }
    printf("Bolo nao encontrado!\n");
    return 0;
}

/* Nome: buscarElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            codigo - codigo do bolo que sera buscado na lista
 * Retorno: posicao do bolo encontrado, -1 caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
int buscarBolo(Lista *lista, int codigo) {
    int i;
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    for (i = 0; i < lista->id; ++i) {
        if (lista->bolos[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo prim
 */
Lista* criarBolo() {   
    Lista *novoBolo = (Lista*)malloc(sizeof(Lista));
    
    if (novoBolo == NULL) {
        printf("Nao ha espaco na memoria.\n");
        return NULL;
    }

    novoBolo->id = 0;
    novoBolo->bolos = (Bolo*)malloc(TAM * sizeof(Bolo));
    
    if (novoBolo->bolos == NULL) {
        printf("Nao tem espaco\n");
        free(novoBolo);
        return NULL;
    }

    return novoBolo;
}

/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao responsavel pela exclusao da lista
 */
void excluirListaBolo(Lista *lista) {
    if (lista != NULL) {
        if (lista->bolos != NULL) {
            free(lista->bolos); 
        }
        free(lista);
    }
    printf("Lista de bolo deletada.\n");
}

/* Nome: inserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             codigo - código do bolo que será adicionado na lista
 *             nomeBolo - nome do bolo
 *             tamanhoBolo - tamanho do bolo
 *             dataVencimento - data de vencimento do bolo
 *             preco - preco do bolo
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrário
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
int inserirBolo(Lista *lista, int codigo, char nomeBolo[], char tamanhoBolo, char dataVencimento[], float preco) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if (lista->id < TAM) {
        lista->bolos[lista->id].codigo = codigo;
        strcpy(lista->bolos[lista->id].nomeBolo, nomeBolo);
        lista->bolos[lista->id].tamanhoBolo = tamanhoBolo;
        strcpy(lista->bolos[lista->id].dataVencimento, dataVencimento);
        lista->bolos[lista->id].precoBolo = preco;
        ++(lista->id);
    } else {
        printf("Espaco lotado\n");
        return 0;
    }
    return 1;
}

/* Nome: inserirElementoID
 * Parametros: lista - ponteiro que possui o endereco lista
 *             posicao - posição na lista onde o bolo será inserido
 *             codigo - código do bolo que será adicionado na lista
 *             nomeBolo - nome do bolo
 *             tamanhoBolo - tamanho do bolo
 *             dataVencimento - data de vencimento do bolo
 *             preco - preco do bolo
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrário
 * Descricao: Funcao criada para inserir um elemento em uma posição específica da lista
 */
int inserirElementoID(Lista *lista, int posicao, int codigo, char nomeBolo[], char tamanhoBolo, char dataVencimento[], float preco) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if (posicao < 0 || posicao > lista->id || lista->id >= TAM) {
        printf("Posição inválida ou lista cheia\n");
        return 0;
    }

    for (int i = lista->id; i > posicao; i--) {
        lista->bolos[i] = lista->bolos[i - 1];
    }
    lista->bolos[posicao].codigo = codigo;
    strcpy(lista->bolos[posicao].nomeBolo, nomeBolo);
    lista->bolos[posicao].tamanhoBolo = tamanhoBolo;
    strcpy(lista->bolos[posicao].dataVencimento, dataVencimento);
    lista->bolos[posicao].precoBolo = preco;
    lista->id++;
    return 1;
}

/* Nome: inserirElementoInicio
 * Parametros: lista - ponteiro que possui o endereco lista
 *             codigo - código do bolo que será adicionado na lista
 *             nomeBolo - nome do bolo
 *             tamanhoBolo - tamanho do bolo
 *             dataVencimento - data de vencimento do bolo
 *             preco - preco do bolo
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrário
 * Descricao: Funcao criada para inserir um elemento no início da lista
 */
int inserirElementoInicio(Lista *lista, int codigo, char nomeBolo[], char tamanhoBolo, char dataVencimento[], float preco) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    if (lista->id >= TAM) {
        printf("Lista cheia\n");
        return 0;
    }

    for (int i = lista->id; i > 0; i--) {
        lista->bolos[i] = lista->bolos[i - 1];
    }
    
    lista->bolos[0].codigo = codigo;
    strcpy(lista->bolos[0].nomeBolo, nomeBolo);
    lista->bolos[0].tamanhoBolo = tamanhoBolo;
    strcpy(lista->bolos[0].dataVencimento, dataVencimento);
    lista->bolos[0].precoBolo = preco;
    
    lista->id++;
    return 1;
}

/* Nome: listarElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos os elementos da lista
 */
void listarElementos(Lista *lista) {
    imprimirBolo(lista);
}

/* Nome: tamanho
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: quantidade de elementos na lista
 * Descricao: Funcao criada para retornar a quantidade de elementos na lista
 */
int tamanho(Lista *lista) {
    if (lista == NULL) {
        return 0;
    }
    return lista->id;
}

/* Nome: imprimirElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos elementos presentes na lista
 */
void imprimirBolo(Lista *lista) {
    int i;

    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return;
    }

    if (lista->id == 0) {
        printf("Lista vazia\n");
        return;
    }
    
    printf("\nDados do bolo na lista:\n");
    for (i = 0; i < lista->id; ++i) {
        printf("Bolo %d:\n", i + 1);
        printf("ID do Bolo: %d\n", lista->bolos[i].codigo);
        printf("Nome do Bolo: %s\n", lista->bolos[i].nomeBolo);
        printf("Tamanho do bolo: %c\n", lista->bolos[i].tamanhoBolo);
        printf("Data de Vencimento: %s\n", lista->bolos[i].dataVencimento);
        printf("Preco: R$%.2f\n", lista->bolos[i].precoBolo);
        printf("\n");
    }
}

/* Nome: removerElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            codigo - código do bolo que será removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrário
 * Descricao: Funcao criada para remover um elemento da lista
 */
int removerBolo(Lista *lista, int codigo) {
    if (lista == NULL) {
        printf("A lista nao foi criada\n");
        return 0;
    }
    
    int i;
    for (i = 0; i < lista->id; ++i) {
        if (lista->bolos[i].codigo == codigo) {
            for (int j = i; j < lista->id - 1; j++) {
                lista->bolos[j] = lista->bolos[j + 1];
            }
            lista->id--;
            printf("Bolo foi removido.\n\n");
            return 1;
        }
    }
    
    printf("Bolo com ID '%d' nao encontrado.\n", codigo);
    return 0;
}
