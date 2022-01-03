#ifndef _ARVOREAVL_H
#define _ARVOREAVL_H
//modulo responsavel pela manipulacao da arvore e algumas consultas
#include <stdbool.h>
#include "svg.h"
#include "Dinamica.h"

typedef void* Arvore;
typedef void* Noh;

//Funcao aloca memoria para a arvore e retorna a arvore!
Arvore CreateAVL();

//Funcao desaloca a memoria ocupada pelos nós da arvore, funcao nao retorna nada!
void Libera(Noh nod);

//Funcao retorna a altura do noh passado como argumento, caso o noh seja NULL retorna -1!
int altura_NO(Noh nod);

//Funcao retorna o fator de balanceamento do noh!
int fatorBalanceamento_NO(Noh nod);

//Funcao retorna o maior inteiro entre x e y passados como argumento!
int maior(int x, int y);

//4 funcoes de rotação, recebem a arvore e o noh, realizam as rotações necessarias para deixar a arvore balanceada!
void RotacaoLL(Arvore t,Noh nod);
void RotacaoRR(Arvore t,Noh nod);
void RotacaoLR(Arvore t,Noh nod);
void RotacaoRL(Arvore t,Noh nod);

//Funcao que verifica se o valor passado existe na arvore, retorna true caso exista, retorna false caso contrario
bool ExisteValor(Arvore arv,double valor);

//Funcao que verifica se a arvore esta vazia, retorna true caso esteja, retorna false caso contrario
bool isEmpty(Arvore t);

//Funcao que retorna o noh de menor valor do noh passado como argumento
Noh procuraMenor(Noh nod);

//Funcao que retorna o noh que possui o valor == o valor passado como argumento, se o valor nao existir na arvore retorna NULL
Noh GetNodeAVL(Arvore arv,double valor);

//Funcao que retorna a raiz da arvore
Noh GetFirstAVL(Arvore arv);

//Funcao que insere as informacoes em um noh e insere esse noh na arvore, retorna true caso seja inserido com sucesso, retorna false caso contrario
bool insereArvAVL(Arvore t,double Px,double Py,double largu,double altu,char espre[10],char CEP[30],char CorBord[30],char corFill[30]);

//Funcao remove o noh que possuir o valor = valorX passado como argumento, retorna true caso tenha sido removido, ou false caso contrario
bool remove_ArvAVL(Arvore t, double valorX,char CEP[],double *CoordX,double *CoordY,double *wid,double *high);

//Funcao que imprime a arvore na ordem, funcao não retorna nada!
void emOrdem_ArvAVL(Noh nod);

//Funcao que abre o arquivo .dot e que chama a funcao EscritaDot, apos isso, encerra e fecha o arquivo, funcao nao retorna nada,
//caso nao seja possivel abrir o arquivo o programa é encerrado!
void ManipulacaoDot(Arvore t,char arquivo[]);

//Funcao escreve as informacoes do noh no arquivo .dot e chama recursivamente outras chamadas dessa mesma funcao, 
//recebe um noh e um ponteiro para o arquivo, funcao nao retorna nada!
void EscritaDot(Noh nod,FILE* arq);

//Funcao que busca recursivamente o noh que tenha o cep igual o cep passado e atribui o valor dos dados do noh nas variaveis passadas 
//como argumento, funcao nao retorna nada, recebe um noh, um cep, e ponteiros de double e um ponteiro inteiro!
void BuscaAVL(Noh nod,char CEP[],double *x,double *y, double *w, double *h,int *existe);

//Funcao que atribui os valores do noh recebido nas variaveis recebidas como argumento, funcao nao retorna nada, recebe um noh, ponteiros
//para double e um inteiro type que define se a atribuicao ocorre na arvore ou na lista interna do noh da arvore!
void GetParameters(Noh nod,double *x,double *y,double *w,double *h,int type);

//Funcao que printa recursivamente os retangulos armazenados na arvore, funcao nao retorna nada, recebe um noh e o nome do svg! 
void SvgAVL(Noh nod,char arquivo[]);

//Funcao informa se o cep existe ou nao na arvore ou na lista interna do noh, funcao nao retorna nada, recebe um noh, o cep e um ponteiro pra
//inteiro, caso exista o cep na arvore o conteudo do ponteiro sera 1, caso exista na lista interna do noh o conteudo do ponteiro sera 2!
void ExisteCEP(Noh nod,char CEP[],int *existe);

//Funcao que atribui o endereco do noh que possui cep igual ao cep passado no ponteiro void, funcao nao retorna nada, recebe um noh, um void
//pointer e um ponteiro int!
void procuraPonteiroAVL(Noh nod,void** quad,char CEP[],int *type);

//Funcao calcula o valor de minX e maxX do noh recebido, funcao nao retorna nada, recebe um noh e ponteiros double!
void CalculaMinMax(Noh nod,double* min,double* max);

//Funcao atualiza os valores de minX e maxX de cada noh, chamando para cada noh a CalculaMinMax e chama recursivamente Atualiza pra atualizar
//dos nohs seguintes, funcao nao retorna nada, recebe somente um noh como argumento!
void AtualizaMinMax(Noh nod);

//Funcao pega o valor de X da quadra CEP, funcao nao retorna nada, recebe um noh, o cep, ponteiro double e um ponteiro int!
void PegaX_CEP(Noh nod,char CEP[],double* X,int *existe);

//Funcao percorre a arvore analisando quais nohs se encontram inteiramente dentro da regiao especificada, funcao nao retorna nada, recebe um
//noh, um void pointer pra uma lista e as coordenadas!
void PercorreAVL(Noh nod,void* listaAux,double X,double Y,double W,double H);

#endif