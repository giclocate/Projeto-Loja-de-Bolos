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
 * Autor: Giovanna Clócate                                        *
 * Ultima alteracao: 11/05/2024                                   *
 ******************************************************************/

/*Include das bibliotecas*/ 
#include <stdio.h>
#include <stdlib.h>

/*declarando os tipos da estrutura bolo e dos elementos de Bolo*/
typedef struct bolo Bolo;
typedef struct boloNo BoloNo;


/*criando a head bolo*/
struct bolo
{
    BoloNo *prim;
};

/*criando o nó do elemento Bolo*/
struct BoloNo
{
    int idBolo;
    char nomeBolo[50];
    char descricaoBolo[150];
    char tamanhoBolo[1];
    float precoBolo;
    char dataFabricacao[10];
    char dataVencimento[10];

    BoloNo *prox;

};

int main(){

    Bolo *bolo;



}


/* Nome: criarLista
 * Parametro: void 
 * Retorno: endereco do espaco de memoria reservado pelo malloc
 * Descricao: Funcao responsavel pela criacao da lista e inicializacao
 *            do campo prim
 */

Bolo* criarReceita() {
    Bolo *novo = (Bolo*)malloc(sizeof(Bolo));

    if(novo == NULL) {
        printf("Nao tem espaco.");
        return NULL;
    }
    novo->prim = NULL;

    return novo;
}

/* Nome: inserirElemento
 * Parametros: lista - ponteiro que possui o endereco lista
 *             valor - elemento que sera adicionado na lista
 * Retorno: 1 se o elemento foi adicionado, 0 - caso contrario
 * Descricao: Funcao criada para inserir um elemento no final da lista
 */
