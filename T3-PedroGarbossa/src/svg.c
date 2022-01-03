#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "svg.h"

void iniciaSvg(char arq[])//recebe nome do svg
{
    FILE *arquivo;
    
    arquivo = fopen(arq, "w");
    if (arquivo == NULL)
    { 
        printf("Nao foi possivel criar o arquivo .svg!");
        exit(1);
    }
    fprintf(arquivo, "<svg xmlns='http://www.w3.org/2000/svg'>");//Link para visualizacao na web
    
    fclose(arquivo);
}

void finalizaSvg(char arq[])//recebe nome do svg
{
	FILE* arquivo;
	
    arquivo = fopen(arq, "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo .svg para finalização!");
        exit(1);
    }
    fseek(arquivo, 0, SEEK_END);//leva o ponteiro pro final do arquivo
    fprintf(arquivo, "\n</svg>");
    
    fclose(arquivo);
}

void criaLinha(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" style=\"stroke:%s\" />\n", x1, y1, x2, y2, cor);//cria uma linha de x1,y1 ate x2,y2
    fclose(arq);
}

void criaRetangulo(double largura, double altura, double x, double y, char cor1[], char cor2[],char espressura[], char svg[])//Cor2 Preenche
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"%s\" stroke=\"%s\" border-radius=\"%s\" fill-opacity=\"0.7\"/>\n", x, y, largura, altura, cor2, cor1,espressura);
    fclose(arq);
}

void CriaPontinho(double x,double y, double raio,char Contorno[],char Preenchimento[],char svg[])
{   
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" stroke-width=\"1\" fill=\"%s\"/>\n",x,y,raio,Contorno,Preenchimento);
    fclose(arq);
}


void criaBoundingBox(double x, double y,double largura, double altura, char cor1[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" fill=\"none\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",x, y, largura, altura, cor1);
    fclose(arq);
}

void TextoSvg(double x, double y, char texto[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if(arq == NULL)
    {
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
    }
    fprintf(arq, "\n\t<text x=\"%lf\" y=\"%lf\" fill=\"black\">%s</text>", x, y, texto);
    fclose(arq);
}

void LinhaTracejada(double x1, double y1, double x2, double y2, char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>\n", x1, y1, x2, y2, cor);
    fclose(arq);
}

void criaCircVazio(double x, double y,double rai, char cor1[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" fill=\"none\" stroke=\"%s\" fill-opacity=\"0\" stroke-width=\"2\" stroke-dasharray=\"5\" />\n",x, y,rai,cor1);
    
    fclose(arq);
}

void criaElipse(double x,double y,char cor[], char svg[])
{
    FILE *arq;
    
    arq = fopen(svg, "a");
    if (arq == NULL){
        printf("Erro ao abrir o arquivo .svg!");
        exit(1);
	}
	fprintf(arq, "\t<ellipse style=\"fill: %s; stroke: black; stroke-width: 2\" cx=\"%lf\" cy=\"%lf\" rx=\"5\" ry=\"3.5\" />\n",cor,x, y);

    
    fclose(arq);
}

void DesenhaEndereco(double x1,double y1,double w1,double h1,double x2,double y2,double variacao1,char Dados[],char Face[],int tipo, char svg[])
{
    //x2 e y2 serve pra criacao da linha
    if(strcmp(Face,"S")==0)//face da residencia eh pro sul
    {
        if(tipo==0)
        {
            criaLinha(x1+variacao1,y1+1.5,x1+variacao1,-8.0-variacao1,"red",svg);
            TextoSvg(x1+variacao1,-8.0-variacao1,Dados,svg);    
        }

        if(tipo==1)//endereco antigo
            CriaPontinho(x1+variacao1,y1+1.30,4.5,"white","red",svg);//crio um circulo vermelho no endereco antigo
        
        if(tipo==2)
            CriaPontinho(x1+variacao1,y1+1.30,4.5,"white","blue",svg);//criou um circulo azul no endereco novo

        if(tipo==3)//cria a linha do endereco antigo ate o endereco novo
            LinhaTracejada(x1+variacao1,y1+1.30,x2,y2,"red",svg);

        if(tipo==4)//cria o texto no endereco da locacao
            TextoSvg(x1+variacao1,y1+8.7,Dados,svg);

        if(tipo==5)//consulta hom ou mul
            criaElipse(x1+variacao1,y1+2.8,Dados,svg);
    }
                            
    if(strcmp(Face,"N")==0)//face da residencia eh pro norte
    {
        if(tipo==0)
        {
            criaLinha(x1+variacao1,(y1+h1)-1.5,x1+variacao1,-8.0-variacao1,"red",svg);
            TextoSvg(x1+variacao1,-8.0-variacao1,Dados,svg);   
        }

        if(tipo==1)//endereco antigo
            CriaPontinho(x1+variacao1,(y1+h1)-1.30,4.5,"white","red",svg);//crio um circulo vermelho no endereco antigo
        
        if(tipo==2)
            CriaPontinho(x1+variacao1,(y1+h1)-1.30,4.5,"white","blue",svg);//criou um circulo azul no endereco novo 

        if(tipo==3)
            LinhaTracejada(x1+variacao1,(y1+h1)-1.30,x2,y2,"red",svg); 

        if(tipo==4)//cria o texto no endereco da locacao
            TextoSvg(x1+variacao1,(y1+h1)-6.5,Dados,svg);//-6.5 pois o texto no svg fica mais pra frente do ponto x entao pra encaixar direito fiz -6.5

        if(tipo==5)//consulta hom ou mul
            criaElipse(x1+variacao1,(y1+h1)-2.8,Dados,svg);
    }
                            
    if(strcmp(Face,"L")==0)//face da residencia eh pro leste
    {
        if(tipo==0)
        {
            criaLinha(x1+1.25,y1+variacao1,x1+1.5,-8.0-variacao1,"red",svg);
            TextoSvg(x1+1.30,-8.0-variacao1,Dados,svg);   
        }

        if(tipo==1)//endereco antigo
            CriaPontinho(x1+1.30,y1+variacao1,4.5,"white","red",svg);//crio um circulo vermelho no endereco antigo
        
        if(tipo==2)
            CriaPontinho(x1+1.30,y1+variacao1,4.5,"white","blue",svg);//criou um circulo azul no endereco novo  

        if(tipo==3)
            LinhaTracejada(x1+1.30,y1+variacao1,x2,y2,"red",svg);

        if(tipo==4)//cria o texto no endereco da locacao
            TextoSvg(x1+4.5,y1+variacao1,Dados,svg);

        if(tipo==5)//consulta hom ou mul
            criaElipse(x1+2.8,(y1+variacao1),Dados,svg);
    }
                            
    if(strcmp(Face,"O")==0)//face da residencia eh pro oeste
    {
        if(tipo==0)
        {
            criaLinha((x1+w1)-1.25,y1+variacao1,(x1+w1)-1.5,-8.0-variacao1,"red",svg);
            TextoSvg(x1+w1,-8.0-variacao1,Dados,svg);
        }  
        
        if(tipo==1)//endereco antigo
            CriaPontinho((x1+w1)-1.30,y1+variacao1,4.5,"white","red",svg);//crio um circulo vermelho no endereco antigo
        
        if(tipo==2)
            CriaPontinho((x1+w1)-1.30,y1+variacao1,4.5,"white","blue",svg);//criou um circulo azul no endereco novo

        if(tipo==3)
            LinhaTracejada((x1+w1)-1.3,y1+variacao1,x2,y2,"red",svg);   

        if(tipo==4)//cria o texto no endereco da locacao
            TextoSvg((x1+w1)-6.5,y1+variacao1,Dados,svg);  

        if(tipo==5)//consulta hom ou mul
            criaElipse((x1+w1)-2.8,(y1+variacao1),Dados,svg);              
    }
}
