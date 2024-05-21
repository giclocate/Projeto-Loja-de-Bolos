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
 * Autor: Mayrton Dias                                            *
 * Ultima alteracao: 07/05/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>

/*Definicao da estrutura Lista e do elemento da lista*/ 
typedef struct lista Lista;
typedef struct listaNo ListaNo;

struct lista{
    ListaNo *prim;
};

struct listaNo{
    int valor;
    ListaNo *prox;
};

/*Funcoes implementadas*/
int atualizarElemento(Lista*, int, int);
ListaNo* buscarElemento(Lista*, int);
Lista* criarLista();
int inserirElemento(Lista*, int);
void imprimirElementos(Lista *lista);
int removerElemento(Lista*, int);
Lista* excluirLista(Lista* lista);

int main(){
    /*Ponteiro usado para a criacao da lista*/
    Lista *lista;
    ListaNo *pesquisa;

    /*exemplo de chamada da funcoes*/
    lista = criarLista();
    
    imprimirElementos(lista);
    inserirElemento(lista, 5);
    imprimirElementos(lista);
    inserirElemento(lista, 4);
    imprimirElementos(lista);
    inserirElemento(lista, 1);
    imprimirElementos(lista);
    inserirElemento(lista, 2);
    imprimirElementos(lista);
    inserirElemento(lista, 7);
    imprimirElementos(lista);
    inserirElemento(lista, 9);
    imprimirElementos(lista);
    inserirElemento(lista, 15);
    imprimirElementos(lista);

    pesquisa = buscarElemento(lista, 9);
    if(pesquisa == NULL){
        printf("Elemento nao encontrado\n");
    }else{
        printf("Elemento %d\n", pesquisa->valor);
    }
    printf("Removendo o 5\n");
    removerElemento(lista, 5);
    imprimirElementos(lista);
    atualizarElemento(lista, 7, 8);
    imprimirElementos(lista);

    lista = excluirLista(lista);
    imprimirElementos(lista);

    
    return 0;
}

/* Nome: atualizarElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             busca - elemento que sera buscado na lista
 *             valor - novo valor do elemento que sera alterado 
 * Retorno: 1 - quando o valor e atualizado e 0 - caso contrario
 * Descricao: Funcao responsavel por atualizar um elemento
 *            da lista, caso o mesmo esteja na lista indicada
 */
int atualizarElemento(Lista *lista, int busca, int valor){
    ListaNo *p;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /*percorrendo todos os elementos presentes na lista*/
    for(p = lista->prim; p != NULL; p = p->prox){
        /*condicao que verifica se o elemento da lista e igual a busca*/
        if(p->valor == busca){
            /*atualizando o elemento*/
            p->valor = valor;
            return 1;
        }
    }
    return 0;
}


/* Nome: buscarElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            valor - elemento que sera buscado na lista
 * Retorno: ponteiro com endereco do elemento encontrado, NULL caso contrario
 * Descricao: Funcao criada para buscar um elemento na lista
 */
ListaNo* buscarElemento(Lista *lista, int valor){
    ListaNo *p;
    
    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return NULL;
    }

    /*Percorrendo todos os elementos presentes na lista*/
    for(p = lista->prim; p != NULL; p = p->prox){
        /*Verificando se o elemento atual e igual ao valor buscado*/
        if(p->valor == valor){
            return p;
        }
    }
    return NULL;
}


/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo prim
 */
Lista* criarLista(){
    /*solicitando espaco para a lista*/
    Lista *nova = (Lista*)malloc(sizeof(Lista));
    
    /*Verificando se o espaco foi resevado*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return NULL;
    }
    /*Preparando os dados iniciais da lista*/
    nova->prim = NULL;

    /*Retonando o espaco resevado*/
    return nova;
}


/* Nome: excluirLista
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: NULL para indicar que a lista foi excluida
 * Descricao: Funcao responsavel pela exclusao da lista
 */
Lista* excluirLista(Lista* lista){
    ListaNo *aux;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return NULL;
    }

    /*Liberando o espaco que foi reservado para os elementos*/
    while(lista->prim != NULL){
        aux = lista->prim;
        lista->prim = lista->prim->prox;
        free(aux);
    }
    
    /*Liberando o espaco que foi reservado para a lista*/
    free(lista);
    
    return NULL;
}


/* Nome: inserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             valor - elemento que sera adicionado na lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
int inserirElemento(Lista *lista, int valor){
    ListaNo *p; 

    /*Solicitando espaco para criar um no da lista*/
    ListaNo *nova = (ListaNo*) malloc(sizeof(ListaNo));
    
    /*Verificando se o espaco foi reservado corretamente*/
    if(nova == NULL){
        printf("Sem espaco\n");
        return 0;
    }

    /*Preparando as informacoes inciais do elemento a ser inserido*/
    nova->valor = valor;
    nova->prox = NULL;

    /*Tratamento para inserir um elemento quando a lista esta vazia*/
    if(lista->prim == NULL){
        lista->prim = nova;
        return 1;
    }

    /*Procurando o ultimo ponteiro da lista para receber o novo elemento*/
    for(p = lista->prim; p->prox != NULL; p = p->prox);

    /*Inserindo o elemento na ultima posicao da lista*/
    p->prox = nova;

    return 1;
}


/* Nome: imprimirElementos
 * Parametro: lista - ponteiro que possui o endereco lista
 * Retorno: void
 * Descricao: Funcao criada para apresentar todos elementos presentes na lista
 */
void imprimirElementos(Lista *lista){
    ListaNo *p;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return ;
    }

    /*Verificando se a lista possui elementos*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return ;
    }

    /*Mostrando cada elemento presente na lista*/
    for(p = lista->prim; p != NULL; p = p->prox){
        printf("%d ", p->valor);
    }
    printf("\n");
}


/* Nome: removerElemento
 * Parametro: lista - ponteiro que possui o endereco lista
 *            valor - elemento que sera removido da lista
 * Retorno: 1 se o elemento foi removido, 0 - caso contrario
 * Descricao: Funcao criada para remover um elemento da lista
 */
int removerElemento(Lista *lista, int valor){
    ListaNo *p, *aux;

    /*Verificando se a lista foi criada*/
    if(lista == NULL){
        printf("A lista nao foi criada\n");
        return 0;
    }

    /*Verificando se a lista foi criada*/
    if(lista->prim == NULL){
        printf("A lista esta vazia\n");
        return 0;
    }

    /*Removendo o elemento caso ele esteja na primeira posicao da lista*/
    if( lista->prim->valor == valor){
        p = lista->prim;
        lista->prim = lista->prim->prox;
        free(p);
        return 1;
    }

    /*Passando por todos os elementos em busca do elemento que sera removido*/
    for(p = lista->prim; p->prox->prox != NULL; p = p->prox){
        /*Verificando se e o elemento que sera removido da lista*/
        if(p->prox->valor == valor){
            aux = p->prox;
            p->prox = p->prox->prox;
            free(aux);
            return 1;
        }
    }

    /*Tratamento da exclusao quando o elemento se encontra na ultima posicao da lista*/
    if(p->prox->valor == valor){
        aux = p->prox;
        p->prox = NULL;
        free(aux);
        return 1;
    }
    
    return 0;
}
