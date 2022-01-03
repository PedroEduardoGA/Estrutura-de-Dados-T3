#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"
#include "svg.h"
#include "saidasTxt.h"
#include "ArvoreAVL.h"
#include "HashTable.h"

char *Tratamento(char arq[])
{
    char *auxiliar = strrchr(arq,'/');//procura pela primeira ocorrencia da / e retorna a string posterior a /
    if (auxiliar == NULL) // se eh nulo nao foi encontrada nenhuma /
    {
        return strtok(arq,".");//se encontro retorna a string posterior a / formatada, ou seja sem a extensao
    }
    return strtok(&auxiliar[1],".");//caso nao tenha /, retornara a string atenrior ao "."
}

int main(int argc, char* argv[])
{
    char* diretorioEntrada=NULL;
    char* diretorioSaida=NULL;
    char* geo=NULL;
    char* qry=NULL;
    char* pm=NULL;
    char* SvgConsulta=NULL;
    char* TXT=NULL;
    int Consulta=0,nx=0,Total_Quadras;

    int i=1;
    while(i < argc)
    {
        if(strcmp("-e",argv[i])==0)//se as string são iguais retorna 0, depois do -e vem o path caso exista
        {
            i++;
            diretorioEntrada= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(diretorioEntrada, "%s", argv[i]); //Sprintf copia o valor de argv para diretorioEntrada
    
        } 
        
        if(strcmp("-f", argv[i]) == 0)
        {
            ++i; //A proxima string vai ser o nome do arquivo .geo:
            geo= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(geo, "%s", argv[i]);//Copia o nome do arq .geo pra geo
        }
        
        if(strcmp("-q", argv[i]) == 0)
        {
            ++i;  //A proxima string vai ser o nome do arquivo .qry:
            Consulta=1;//Indica que vai haver consultas
            qry= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(qry, "%s", argv[i]);//Copia o nome do arq qry para variavel qry
        }
        
        if(strcmp("-o", argv[i]) == 0)
        {
            ++i;  //A proxima string vai ser o nome do diretorio de arquivos de saida:
            diretorioSaida= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(diretorioSaida, "%s", argv[i]);//copia pra diretorio saida o diretorio de saida
        } 
        
        if(strcmp("-pm", argv[i]) == 0)
        {
            ++i;
            pm= (char *) malloc((strlen(argv[i])+1)*sizeof(char));
            sprintf(pm, "%s", argv[i]);
        }
        i++;
    }
    Arvore avl= CreateAVL();
    HashTable tab1,tab2;//Tabela1 eh a de moradores/pessoas e Tabela2 eh a tabela das locacoes

    if(diretorioSaida==NULL)//caso nao seja informado diretorio de saida programa eh encerrado
    {
        printf("\nErro! Diretorio de saida nao foi informado!");
        exit(1);
    }

    if(geo==NULL)//caso nao seja informado um arquivo geo programa eh encerrado
    {
        printf("\nErro! Arquivo .geo nao foi informado!");
        exit(1);
    }

    Total_Quadras=LeituraGeo(avl,diretorioEntrada,geo,diretorioSaida,&nx);//usar totalquadras pra criar tabela para as locacoes
    tab1= criaTabela(nx);//cria tabela moradores/pessoas
    tab2= criaTabela(Total_Quadras);//cria tabela locacoes

    if(pm!=NULL)
        LeituraPm(tab1,diretorioEntrada,pm);

    if(Consulta==1)
    {
        char* QRYSemExtensao=NULL;
        char* aux=NULL;//Variavel temporaria pra ser passado pro nome do arquivo txt o nome de qry sem a extensao .qry
        aux= (char *) malloc((strlen(qry)+1)*sizeof(char));
        
        strcpy(aux,qry);//copiado pra variavel aux o nome passado apos o -q
        QRYSemExtensao= Tratamento(aux);//qry sem extensao recebera so o nome do qry
    
        TXT= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));
        sprintf(TXT, "%s/%s-%s.txt",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo txt de saida
        SvgConsulta= (char *) malloc((strlen(QRYSemExtensao)+strlen(geo)+strlen(diretorioSaida)+7) * sizeof(char));//7 pra caber o / e o .svg/0
        sprintf(SvgConsulta, "%s/%s-%s.svg",diretorioSaida,geo,QRYSemExtensao);//Concantena nome do arquivo svg de saida
        
        CriaArquivo(TXT);
        iniciaSvg(SvgConsulta);//vai iniciar o svg final com as consultas
        LeituraQry(avl,tab1,tab2,diretorioEntrada,qry,diretorioSaida,TXT,SvgConsulta,geo,QRYSemExtensao);
        free(aux);//free da variavel temporaria

        TextoSvg(-2.0,-4.0,"Pedro Eduardo Garbossa de Almeida",SvgConsulta);
        finalizaSvg(SvgConsulta);//finaliza o svg final
        printf("\nNome do txt de saida: %s",TXT);
        printf("\nNome do svg de saida: %s",SvgConsulta);
        free(qry);
        free(TXT);
        free(SvgConsulta);
    }//free das variaveis!
    if(pm!=NULL)//arquivo .pm eh opcional entao caso tenha sido informado ocorre o free
        free(pm);

    Noh node=GetFirstAVL(avl);//pego o primeiro noh da arvore

    node=GetFirstAVL(avl);
    Libera(node);//libera a memoria da arvore

    LiberaHashtable(tab1);
    LiberaHashtable(tab2);
    
    free(avl);//libera a memoria da raiz da arvore
    free(geo);
    free(diretorioEntrada);
    free(diretorioSaida);

    printf("\nMemoria Liberada e Programa Finalizado!\n");
    return 0;
}