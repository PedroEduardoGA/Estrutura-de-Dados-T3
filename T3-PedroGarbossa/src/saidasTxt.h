#ifndef _SAIDASTXT_H
#define _SAIDASTXT_H
//Modulo responsavel por trabalhar com abertura, escrita, leitura e fechamento de arquivos .txt

/*Cria o arquivo TXT caso haja consultas, recebe o nome do arquivo TXT, nao retorna nada! Caso nao seja possivel criar o arquivo o programa é encerrado!*/
void CriaArquivo(char arquivo[]);

/*Cria uma linha no arquivo TXT, reportando que o ID nao existe na lista, recebe o nome do arquivo TXT, um ID e o tipoconsulta, 
nao retorna nada!Caso nao seja possivel abrir o arquivo, o programa sera encerrado!*/
void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[]);

/*Reporta uma saida de acordo com o tipo informado, recebe o nome do arquivo TXT, dados, uma string tipoConsulta e um inteiro tipo, nao retorna
nada!Caso nao seja possivel abrir o arquivo, o programa sera encerrado!*/
void Saidas(char arquivo[],char nome[],char sobrenome[],char sexo[],char data[],char cpf[],int nO,char comple[],char CEP[],char Fac[],char TipoConsulta[],int tipo);

/*Reporta os valores de area e valor da moradia, recebe o nome do arquivo TXT e os parametros double, funcao nao retorna nada!Caso nao
seja possivel abrir o arquivo, o programa sera encerrado!*/
void SaidaLocs(char arquivo[],double area,double valor);

#endif
