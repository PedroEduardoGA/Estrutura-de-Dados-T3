#ifndef _DINAMICA_H
#define _DINAMICA_H
//Modulo responsavel pela manipulacao da lista dinamica
#include "saidasTxt.h"
#include "svg.h"
#include "ArvoreAVL.h"

typedef void* No; //void pointer
typedef void* Lista; //void pointer

//Cria uma lista vazia, retorna uma lista vazia, nao recebe nada como parametro!
Lista Create();

//Insere os parametros dos retangulos, necessita de uma lista para insercao dos parametros, retorna a lista com as informacoes!
void insert(Lista l, char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura,char espre[10]);

//Imprimi todos elementos da lista, precisa de uma lista com pelo menos 1 elemento, nao retorna nada!
void print(Lista l);

//Desaloca a memoria da lista, recebe uma lista, nao retorna nada!
void liberalist(Lista l);

//Remove o elemento com id informado, precisa de uma lista e um id, nao retorna nada!
void RemoveElemento(Lista l, char cep[],double *CoordX,double *CoordY,double *wid,double *high);

//Insere os parametros, apos tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para ser 
//inserido apos ela, nao retorna nada!
void InsereAfter(Lista L,char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Insere os parametros, anteriormente tal posicao, necessita de uma lista e as informacoes que serao inseridas, e uma posicao para 
//ser inserido anterior a ela, nao retorna nada!
void InsereBefore(Lista L,char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i);

//Retorna o tamanho da lista informada
int TamanhoLista(Lista L);

//Pega o ultimo noh da lista, recebe uma lista, retorna o ultimo noh da lista, caso a lista esteja vazia, retorna NULL!
No GetLast(Lista L);

//Pega o primeiro noh da lista, recebe uma lista, retorna o primeiro noh da lista caso a lista esteja vazia, retorna NULL!
No GetFirst(Lista L);

//Pega o noh posterior a posicao informada da lista, recebe uma lista, retorna o noh posterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetNext(Lista L,int pos);

//Pega o noh anterior a posicao informada da lista, recebe uma lista, retorna o noh anterior da posicao, caso a posicao seja maior
//que o tamanho da lista retorna NULL, caso posicao seja 0 retorna NULL, pois o eh o elemento anterior do primeiro noh, caso a lista 
//esteja vazia, retorna NULL!
No GetPrevious(Lista L, int pos);

//Pega o noh do elemento com Id igual ao informado, recebe uma lista e um Id, retorna o noh com Id informado, caso Id nao exista na lista
//retorna NULL, caso a lista esteja vazia, retorna NULL!
No GetElemento(Lista L,char CEP[30]);

//Insere no svg os elementos contidos na lista, recebe a lista e o nome do arquivo .svg
//Funcao nao retorna nada, caso nao seja possivel abrir o arquivo .svg eh informado na tela e a funcao eh interrompida!
void SvgQry(Lista L, char nomeSvG[]);

//Verifica se o cep existe na lista, recebe a lista, o cep e um ponteiro inteiro, funcao nao retorna nada, caso cep exista sera atribuito
//valor 1 no ponteiro!
void ExisteCEPList(Lista L,char CEP[],int *existe);

//Atribui os valores do noh que possuir cep igual ao cep passado no argumento nos ponteiros recebidos, recebe uma lista, um cep, ponteiros
//pra double e um ponteiro inteiro, funcao nao retorna nada!
void PercorreLista(Lista L,char CEP[],double *x,double *y, double *w, double *h,int *existe);

//Atribui os valores do noh passado para os ponteiros passados como argumento, recebe um noh e ponteiros para double, funcao nao retorna nada!
void GetParametersList(No nodi,double *x,double *y,double *w,double *h);

//Funcao copia os valores de 2 ceps contidos na lista pros ceps passados, recebe uma lista e 2 strings, funcao nao retorna nada!
void PegaAlgunsCEP(Lista L,char cep1[],char cep2[]);

//Funcao procura o noh que possui o cep igual ao cep passado e atribui o endereco dele pro void pointer, recebe a lista, ponteiro duplo
//void, o cep e um ponteiro int, funcao nao retorna nada!
void procuraPonteiroLista(Lista L,void** quad,char CEP[],int *type);

//Funcao verifica se a lista esta vazia ou nao, recebe a lista e retorna 1 caso a lista tenha pelo menos 1 elemento ou 0 caso esteja vazia
int ListaNaoVazia(Lista L);//levar pra cima

//Funcao atribui os valores do primeiro elemento da lista no endereco dos argumentos recebidos, recebe a lista, ponteiros pra double e 4 strings
//funcao nao retorna nada!
void PegaFirst(Lista l,double *X,double *Y,double *W,double *H,char cep[],char corBord[],char corFill[],char espre[]);//levar pra cima

//Funcao pega o valor do X do noh que possuir cep igual ao cep passado como argumento, recebe a lista, o cep, um ponteiro double e um ponteiro int,
//funcao nao retorna nada!
void PegaX_CepList(Lista L,char CEP[],double* X,int *existe);

//Funcao percorre a lista verificando quais retangulos estao inteiramente contidos na regiao especificada, recebe 2 listas e as coordenadas da regiao,
//funcao nao retorna nada!
void VerificaCoordenadas(Lista listAux,Lista L,double X,double Y,double X2,double Y2);

//Funcao remove os elementos da arvore que possuirem cep contidos na lista, recebe a lista e um ponteiro void, funcao nao retorna nada!
void RemoveQuadrasLista(Lista L,void* avl);

#endif
