#include <stdio.h>
#include <stdlib.h>
#include "saidasTxt.h"

void CriaArquivo(char arquivo[])
{
    FILE *arq;
    
    arq = fopen(arquivo, "w");
    if (arq == NULL){ 
        printf("Nao foi possivel Criar o Txt!");
        exit(1);
    }
    fprintf(arq, "Pedro Eduardo Garbossa, Saida TXT:\n");
    
    fclose(arq);
}

void IdInexiste(char arquivo[],char IDE[],char TipoConsulta[])
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        exit(1);
    }
    fprintf(arq, "%s:\nRetangulo com ID:%s Nao Encontrado!\n",TipoConsulta,IDE);
    
    fclose(arq);
}

void Saidas(char arquivo[],char nome[],char sobrenome[],char sexo[],char data[],char cpf[],int nO,char comple[],char CEP[],char Fac[],char TipoConsulta[],int tipo)
{
    //tipo -1 -> algum dado nao existe: cep,cpf,etc
    //tipo 0-> saida m? ou dm?
    //tipo 2-> saida mud

    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        exit(1);
    }
    if(tipo == -1)
        fprintf(arq,"\nConsulta %s: \n%s %s %s",TipoConsulta,nome,sobrenome,sexo);//"tipoConsulta": "Cep/Cpf" "node->cep/cpf" "nao existe!"
    
    if(tipo == -2)
        fprintf(arq,"\n%s %s",nome,sobrenome);//saida dloc quando moradia nao possui morador

    if(tipo == -3)
        fprintf(arq,"\nConsulta %s:\nLocacao de Cep: %s nº %d Complemento: %s Face: %s foi removida!",TipoConsulta,CEP,nO,comple,Fac);//saida que reporta locao que foi removida

    if(tipo == -4)
        fprintf(arq, "\nConsulta %s:\nMorador %s %s -CPF: %s\nSexo: %s - Data de nascimento: %s foi removido",TipoConsulta,nome,sobrenome,cpf,sexo,data);
    
    if(tipo==0)//saida m? ou dm?
        fprintf(arq, "\nConsulta %s:\nNome Completo: %s %s -CPF: %s\nSexo: %s - Data de nascimento: %s\nEndereço: Cep %s nº %d Complemento: %s Face: %s",TipoConsulta,nome,sobrenome,cpf,sexo,data,CEP,nO,comple,Fac);

    if(tipo >= 2)//consulta mud
    {
        if(tipo==2)
            fprintf(arq, "\nConsulta %s:\nNome Completo: %s %s -CPF: %s\nSexo: %s - Data de nascimento: %s\nEndereço Antigo: Cep %s nº %d Complemento: %s Face: %s",TipoConsulta,nome,sobrenome,cpf,sexo,data,CEP,nO,comple,Fac);
        
        if(tipo==3)
            fprintf(arq, "\nEndereço Novo: Cep %s nº %d Complemento: %s Face: %s",CEP,nO,comple,Fac);

        if(tipo==4)//parte de reportar dados do morador na consulta loc?
            fprintf(arq, "\nNome Completo: %s %s -CPF: %s\nSexo: %s - Data de nascimento: %s",nome,sobrenome,cpf,sexo,data);

        if(tipo==5)
            fprintf(arq,"\nConsulta %s:\nMoradia: Cep %s nº %d Complemento: %s Face: %s",TipoConsulta,CEP,nO,comple,Fac);

        if(tipo==6)
            fprintf(arq,"\nMoradia esta %s!",sexo);//printa se esta alocada ou nao
    }
    fclose(arq);
}

void SaidaLocs(char arquivo[],double area,double valor)
{
    FILE* arq;
	
    arq = fopen(arquivo, "a");
     if (arq == NULL){
        printf("Nao foi possivel Abrir o arquivo Txt!");
        exit(1);
    }
    fprintf(arq,"\nLocação com área de %lfm2 no valor de: %lf",area,valor);
    
    fclose(arq);
}
