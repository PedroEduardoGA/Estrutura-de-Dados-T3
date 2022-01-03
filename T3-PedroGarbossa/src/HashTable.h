#ifndef HASHTABLE_H_
#define HASHTABLE_H_
//Modulo responsavel por manipular as tabelas hashs
#include<stdbool.h>
#include "saidasTxt.h"
#include "svg.h"
#include "ArvoreAVL.h"
#include "Dinamica.h"

typedef void* HashTable;//void pointer que vai apontar pra uma tabela
typedef void* nohInterno;//void pointer pra apontar pra um noh interno da tabela
typedef void* Quadra;//void pointer pra apontar prum noh da avl ou da lista interna da avl

//Cria uma tabela com n tamanho, retorna uma tabela vazia, recebe um inteiro "n" que sera o tamanho da tabela!
HashTable criaTabela(int n);

//Insere o registro na tabela, retorna 'true' caso seja inserido, 'false' caso contrario, recebe void pointer pra tabela e os dados que serao inseridos!
bool insereRegistro(HashTable tab, char* key,char cpf[], char cep[],char name[],char endname[],char sex[],char date[],char fac[],char compl[],int number,char ID[],double Valor,double Area,int situacao);

//Remove o registro que tiver a key igual a key passada, retorna 'true' caso consiga remover, 'false' caso contrario, recebe a tabela e a key como parametro!
bool removeChave(HashTable, char* key);

//Imprime as informacoes da tabela, funcao nao retorna nada, recebe a tabela como parametro!
void ImprimeTabela(HashTable tab);

//Verifica se a key existe na tabela, retorna 'true' caso exista ou 'false' caso nao exista, recebe a tabela e a chave como parametro!
bool existeChave(HashTable, char* key);

//Libera memoria da tabela e todos seus registros internos, funcao nao retorna nada, recebe a tabela como parametro!
void LiberaHashtable(HashTable tab);

//Altera as variaveis de endereco do registro da tabela que tiver o cpf igual ao passado, funcao nao retorna nada, recebe a tabela, o cpf
//e os dados que serao alterados no registro!
void AlteraEndereco(HashTable tab,char* cpf,char CEP[],char facE[],char compl[],int number);

//Funcao executa varias tarefas de acordo com o inteiro tipo passado, em geral reporta dados nas saidas txt, funcao nao retorna nada, recebe
//a tabela, coordenadas, parametros cep e cpf, nome do txt e svg de saida, um ponteiro de inteiro, um inteiro tipo, uma string type e um ponteiro pra double!
void PercorreTabela(HashTable tab,double x,double y,double x2,double y2,char CEP[],char CPF[],int tipo,char TXT[],char SVG[],int *existe,char type[],double *Dou_aux);

//Atribui um endereco no campo void pointer do registro da tabela, funcao nao retorna nada, recebe a arvore e um registro da tabela!
void AtribuiPonteiro(Arvore avl,nohInterno nod);

//Retorna o registro que tiver a key igual a key passada, funcao retorna o endereco pro registro, recebe a tabela e a key!
nohInterno GetNohInterno(HashTable tab,char* key);

//Atribui os dados pro registro e copia pros argumentos outros dados do registro e reporta dados no txt, funcao retorna 1 caso seja executada 
//com excito, retorna 0 caso nao exista o cpf na tabela, recebe a tabela, os dados e o nome do txt de saida! 
int locPessoa(HashTable tab,char* cpf,char CEP[],char facE[],char compl[],int number,char nome[],char endname[],char sex[],char data[],char cpfperson[],char TXT[]);

//Reporta diferentes tipos de dados no txt de saida, seu tipo de execucao depende do inteiro tipo, funcao nao retorna nada, recebe 2 
//tabelas, dados de id e cpf, nome dos arquivos txt e svg de saida, um inteiro tipo e uma string type! 
void loc(HashTable tab1,HashTable tab2,char id[],char cpf[],char TXT[],char SVG[],int tipo,char type[]);

//Funcao percorre a tabela inteira executando tipos diferentes de tarefas dependendo do valor do inteiro tipo, funcao nao retorna nada,
//recebe uma tabela, uma lista, uma arvore, um inteiro tipo, uma string tipo, nome do txt e do svg e um cep!
void AnalisaTabela(HashTable tab,Lista list,Arvore avl,int tipo,char type[],char TXT[],char SVG[],char CEP[]);

#endif