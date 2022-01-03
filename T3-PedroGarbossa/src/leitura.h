#ifndef LEITURA_H_
#define LEITURA_H_
//Modulo responsavel por trabalhar com abertura, leitura e fechamento dos arquivos .geo,.pm e .qry
//Na leituraGeo armazena os dados na arvore e cria um svg inicial
//Na leituraQry realiza consultas que produzem saidas .txt e .svg
#include "svg.h"
#include "saidasTxt.h"
#include "ArvoreAVL.h"
#include "HashTable.h"
#include "Dinamica.h"

/* Funcao: LeituraGeo recebe 5 parametros: 
    "Arvore" void pointer que uso pra apontar pra uma arvore AVL, que uso pra armazenar as quadras!
    "bed" eh o diretorio caso informado o -e, entao sera passado pra bed o diretorio de entrada, caso nao seja informado o -e
    bed valera NULL!
    "nomeArq" eh o nome do arquivo geo informado logo apos o -f, caso nome do arquivo seja invalido saira do programa!
    "dirSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir o svg inicial nesse diretorio!
    "*nx" recebe o endereco de uma variavel int que le o numero aproximado de pessoas a serem informados
    A funcao abre o arquivo .geo, le todos comandos e armazena na arvore os respectivos dados, x,y,cor de preenchimento e cor de borda,
    insere no svg inicial os retangulos, svg inicial que sera criado no diretorio de saida com o nome do arquivo geo 
    informado Ex: nomegeo.svg! Caso nao seja possivel abrir o arquivo saira do programa! Funcao retorna quantidade total de quadras!*/
int LeituraGeo(Arvore Avl,char* bed,char* nomeArq,char* dirSaida,int *nx);

/* Funcao: LeituraPm recebe 3 parametros: 
    "HashTable" void pointer que uso pra apontar pra uma tabela hash, onde serao armazenados os moradores/pessoas!
    "DiretorioEnt" eh o diretorio caso informado o -e, entao sera passado pra variavel o diretorio de entrada, caso nao seja informado o -e
    DiretorioEnt valera NULL!
    "nomePm" eh o nome do arquivo .pm informado logo apos o -pm, caso nome do arquivo seja invalido saira do programa!
    A funcao abre o arquivo .pm, le todos comandos linha por linha e realiza as devidas ações, caso não seja possivel abrir o arquivo saira
    do programa, a função não retorna nada!*/
void LeituraPm(HashTable tabela,char* DiretorioEnt,char* nomePm);

/* Funcao: LeituraQry recebe 10 parametros: 
    "Arvore" void pointer que uso pra apontar pra uma arvore avl, onde estao armazenados as quadras!
    "HashTable" void pointer que uso pra apontar pra uma tabela hash, Tabela1: onde estao armazenados os moradores/pessoas, Tabela2: onde
    serao armazenadas as locaçoes!
    "DiretorioEnt" eh o diretorio caso informado o -e, entao sera passado pra variavel o diretorio de entrada, caso nao seja informado o -e
    DiretorioEnt valera NULL!
    "nomeQry" eh o nome do arquivo qry informado logo apos o -q, caso nome do arquivo seja invalido saira do programa!
    "diretSaida" eh o diretorio de saida informado apos o -o, diretorio sera usado pra produzir os .txt das consultas nesse diretorio!
    "TxtSaida" recebera o nome do txt formatado como: nomegeo-nomeqry.txt
    "svg" recebera o nome do .svg formatado como: nomegeo-nomeqry.svg
    "geo" recebera o nome do .geo formatado sem a extensão .geo
    "qrySemExt" recebera o nome do .qry formatado sem a extensão .qry
    A funcao abre o arquivo .qry, le todos comandos linha por linha e realiza a consulta, dependendo da consulta o efeito muda, algumas
    atualizam os dados da arvore, outras removem, outras adicionam na tabela, cada consulta produz algum resultado no arquivo txt, no diretorio de 
    saida com o nome Ex: nomegeo-nomeqry.txt! Caso nao seja possivel abrir o arquivo o programa sera encerrado! A Funcao nao retorna nada!*/
void LeituraQry(Arvore AVL,HashTable Tabela1,HashTable Tabela2,char* DiretorioEnt,char* nomeQry,char* diretSaida,char* TxtSaida,char svg[],char geo[],char qrySemExt[]);

#endif