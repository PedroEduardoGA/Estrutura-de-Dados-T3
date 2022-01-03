#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dinamica.h"

typedef struct N{ //Onde guarda infos como, cor borda, preenchimento...
    char Cep[30],espressura[10];
    char CorPrenche[30];
    char CorBord[30];
    double PontoX;
    double PontoY;
    double Largura;
    double Altura;

    struct N *ant;
    struct N *prox;
}no;

typedef struct L{
    no *primeiro; //primeiro elemento da list
    no *ultimo;   //ultimo elemento da list
    int tamanho;
}list;

Lista Create()//Aloca uma list
{
    list* lista = (list*) malloc(sizeof(list));//alloca, cria variavel e faz cast de list* lista
    lista->primeiro= NULL;
    lista->ultimo= NULL;
    lista->tamanho=0;

    return lista;//retorna uma lista sem no interno
}

void insert(Lista l, char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura,char espre[10])//info é o que passa pra inserir na lista e l eh uma lista!
{
    no* node = (no*) malloc(sizeof(no));//faz cast de node com no e eh alocado struct do tipo no-node tem [*ant][informacao][*prox]
    list* lista = (list*) l;//cast de list com l, cria variavel lista do tipo [primeiro][ultimo]

    strcpy(node->Cep,CEP);//Copia pra variavel id da lista o id do retangulo!
    strcpy(node->CorPrenche,Prenche);
    strcpy(node->CorBord,Borda);
    strcpy(node->espressura,espre);
  
    node->PontoX= PontoX;
    node->PontoY= PontoY;
    node->Largura= Largura;
    node->Altura= Altura;

    if(lista->primeiro==NULL)//Verifica se ja existe um no da lista, se for null vai ser criado o primeiro no
    {
        node->ant=NULL;//o campo [ant] do primeiro no recebe NULL pois eh o primeiro no da lista
        
        lista->primeiro=node;
        //lista eh do tipo [primeiro][ultimo] que apontam para o primeiro no e o ultimo no da lista
        
    }else//se ja existe um no
        {
            lista->ultimo->prox= node;//vai armazenar no campo [prox] do ultimo no o endereco para o no atual
            node->ant =lista->ultimo;//vai armazenar no campo[ant]do no atual o endereco para o no anterior
        }
    node->prox=NULL;//vai armazenar no campo [proximo]do no atual o NULL
    lista->ultimo=node;//o [ultimo] de lista recebe o endereco do no atual criado
    lista->tamanho++;//incrementa o tamanho da lista
}

void print(Lista l)
{
    list* lista = (list*) l;//Cast da variavel lista com list*
    no* node= lista->primeiro;//struct node recebe endereco para o primeiro no da lista
    
    while(node!=NULL)//enquanto nao chega no ultimo no vai imprimindo
    {
        printf("\nCep: %s X: %lf e Y: %lf",node->Cep,node->PontoX,node->PontoY);
        node= node->prox;//percorre todos os nos da lista
    }
}

void RemoveElemento(Lista l, char cep[],double *CoordX,double *CoordY,double *wid,double *high)
{
    list *lista = (list *) l;//faz cast de l com a struct de list e nomeia l de lista
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;

    while((strcmp(node->Cep,cep)!=0)&&(node!=NULL))//Quando encontrar o elemento vai parar no noh em que o elemento se encontra
    {
        if(node->ant!=NULL)
            aux=node;//aux recebe noh anterior

        node = node->prox;// atribui a node o proximo noh
    }

    if(node == NULL)//id nao existe na lista
        return;
    
    *CoordX=node->PontoX;
    *CoordY=node->PontoY;
    *wid=node->Largura;
    *high=node->Altura;
    if(lista->primeiro == node)//elemento eh o primeiro da lista eh o primeiro noh da lista tratamento diferente
    {
        
        if(node->prox == NULL)//indica que esse eh o unico noh da lista
        {
            lista->primeiro=NULL;
            lista->ultimo=NULL;
            lista->tamanho--;

            free(node);
            return;
        }
        aux=node->prox;//aux eh o segundo elemento da lista
        aux->ant=NULL;
        lista->primeiro=aux;//Primeiro elemento da lista vai apontar para o proximo
        lista->tamanho--;

        free(node);
        return;
    }

    if(lista->ultimo == node)//elemento eh o ultimo da lista
    {
        //eh o primeiro noh da lista tratamento diferente
        aux=node->ant;//aux eh o noh anterior
        aux->prox=NULL;
        lista->ultimo=aux;//Ultimo elemento da lista vai apontar para o anterior
        lista->tamanho--;

        free(node);
        return;
    }

    if(strcmp(node->Cep,cep)==0)//caso o elemento esteja no meio da lista
    {
        node->ant->prox=node->prox;
        node->prox->ant=node->ant;//Campo anterior do proximo noh vai receber o noh aux
        lista->tamanho--;
        free(node);
    }
}

void liberalist(Lista l)
{
    list *lista = (list *) l;//faz cast de l com a struct de list
    no *node = lista->primeiro;//criado um node do tipo no, que aponta pro primeiro elemento da lista
    no *aux;//criado um aux do tipo no

    while(node != NULL)
    {
        aux = node;//atribui a aux o valor de node atual
        node = node->prox;// atribui a node o proximo noh

        free(aux);//free no noh atual de aux
    }
    free(node);
    free(lista);//libera a malloc da lista
}

void InsereAfter(Lista L,char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if(i<0)
        return;
    
    while ((x<i)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }

    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->Cep,CEP);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    aux->prox=node->prox;//prox de aux recebe o endereco do proximo do noh
    node->prox=aux;
    aux->ant=node;
    lista->tamanho++;
    if(node == lista->ultimo)//se i for a ultima posicao da lista
        lista->ultimo=aux;
}

void InsereBefore(Lista L,char CEP[30], char Prenche[30], char Borda[30], double PontoX, double PontoY, double Largura, double Altura, int i)
{
    list *lista = (list *) L;//faz cast de l com a struct de list e nomeia l de lista
    no *node=lista->primeiro;
    int x=0;

    if(i<0)
        return;
    
    while ((x<i)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }

    if(node==lista->primeiro)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->Cep,CEP);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->ant=node->ant;
        node->ant=aux;
        aux->prox=node;
        lista->primeiro=aux;
        lista->tamanho++;
        return;
    }

    if(node==lista->ultimo)//caso queira inserir antes do primeiro elemento
    {
        no* aux= (no*) malloc(sizeof(no));
        strcpy(aux->Cep,CEP);//Copia pra variavel id da lista o id do retangulo!
        strcpy(aux->CorPrenche,Prenche);
        strcpy(aux->CorBord,Borda);

        aux->PontoX= PontoX;
        aux->PontoY= PontoY;
        aux->Largura= Largura;
        aux->Altura= Altura;//aux eh o novo q sera inserido
        aux->prox=node;//prox de aux recebe o endereco do noh atual
        aux->ant=node->ant;
        node->ant->prox=aux;
        node->ant=aux;
        lista->tamanho++;
        return;
    }    
    no* aux= (no*) malloc(sizeof(no));
    strcpy(aux->Cep,CEP);//Copia pra variavel id da lista o id do retangulo!
    strcpy(aux->CorPrenche,Prenche);
    strcpy(aux->CorBord,Borda);

    aux->PontoX= PontoX;
    aux->PontoY= PontoY;
    aux->Largura= Largura;
    aux->Altura= Altura;//aux eh o novo q sera inserido
    //Trocas
    aux->prox=node;//prox de aux recebe o endereco do noh atual
    aux->ant=node->ant;
    node->ant->prox=aux;
    node->ant=aux;
    lista->tamanho++;
}

int TamanhoLista(Lista L)
{
    list *lista = (list *) L;
    return lista->tamanho;
}

No GetLast(Lista L)
{
    list *lista = (list *) L;
    return lista->ultimo;
}

No GetFirst(Lista L)
{
    list *lista = (list *) L;
    return lista->primeiro;
}

No GetNext(Lista L,int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    int x=0;
    if(lista->primeiro==NULL)
        return NULL;

    while((x<pos)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }
    return node->prox;
}

No GetPrevious(Lista L, int pos)
{
    list *lista = (list *) L;
    no* node= lista->primeiro;
    if(node==NULL)//lista vazia
        return NULL;

    int x=0;
    while((x<pos)&&(node!=NULL))
    {
        node=node->prox;
        x++;
    }
    return node->ant;
}

No GetElemento(Lista L,char CEP[30])//Util
{
    list *lista = (list *) L;
    no* node= lista->primeiro;

    if(node==NULL)//lista vazia
        return NULL;

    while((strcmp(node->Cep,CEP)!=0)&&(node!=NULL))
        node=node->prox;
    
    if(node==NULL)//elemento nao existe na lista
        return NULL;

    return node;
}

int ListaNaoVazia(Lista L)
{
    list *lista = (list *) L;
    if(lista->primeiro != NULL)
        return 1;
    else
        return 0;
}

void PegaFirst(Lista l,double *X,double *Y,double *W,double *H,char cep[],char corBord[],char corFill[],char espre[])
{
    list *lista = (list *) l;
    no *node= lista->primeiro;
    no *aux;
    if(node==NULL)
        return;
        
    strcpy(cep,node->Cep);//copio pros argumentos os valores do elemento da lista
    strcpy(corBord,node->CorBord);
    strcpy(corFill,node->CorPrenche);
    strcpy(espre,node->espressura);
    *X=node->PontoX;
    *Y=node->PontoY;
    *W=node->Largura;
    *H=node->Altura;

    if(node->prox == NULL)//removo o primeiro elemento da lista
    {
        lista->primeiro=NULL;
        lista->ultimo=NULL;
        lista->tamanho--;

        free(node);
        return;
    }

    aux=node->prox;//aux eh o segundo elemento da lista
    aux->ant=NULL;
    lista->primeiro=aux;//Primeiro elemento da lista vai apontar para o proximo
    lista->tamanho--;

    free(node);
}

//==============================================FuncoesConsultas=======================================================================
void SvgQry(Lista L, char nomeSvG[])//Funcao que gera o svg final, pos consultas!
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node!=NULL)
    {
        criaRetangulo(node->Largura,node->Altura,node->PontoX,node->PontoY,node->CorBord,node->CorPrenche,node->espressura,nomeSvG);
        TextoSvg(node->PontoX+1.5,node->PontoY+10.5,node->Cep,nomeSvG);
        node=node->prox;
    }
}

void PercorreLista(Lista L,char CEP[],double *x,double *y, double *w, double *h,int *existe)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node != NULL)
    {
        if(strcmp(node->Cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *existe=1;//entao cep existe
            *x=node->PontoX;
            *y=node->PontoY;
            *w=node->Largura;
            *h=node->Altura;
        }
        node=node->prox; 
    }
}

void ExisteCEPList(Lista L,char CEP[],int *existe)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node != NULL)
    {
        if(strcmp(node->Cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *existe=1;//entao cep existe
            return;
        }
        node=node->prox; 
    }
}

void procuraPonteiroLista(Lista L,void** quad,char CEP[],int *type)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node != NULL)
    {
        if(strcmp(node->Cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *type=2;//entao cep existe e esta na lista
            *quad=node;
            return;
        }
        node=node->prox; 
    }
}

void GetParametersList(No nodi,double *x,double *y,double *w,double *h)
{
    no* node= (no*) nodi;//cast
    if(node != NULL)
    {
        *x=node->PontoX;
        *y=node->PontoY;
        *w=node->Largura;
        *h=node->Altura;    
    }
}

void PegaAlgunsCEP(Lista L,char cep1[],char cep2[])
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    if(node!=NULL)
        strcpy(cep1,node->Cep);
    else
        {
            strcpy(cep1,"-");
            strcpy(cep2,"-");
            return;
        }
        
    node=node->prox;
    if(node!=NULL)
        strcpy(cep2,node->Cep);
    else
        strcpy(cep2,"-");
}

void PegaX_CepList(Lista L,char CEP[],double* X,int *existe)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    while(node != NULL)
    {
        if(strcmp(node->Cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *existe=1;
            *X=node->PontoX;//entao cep existe
            return;
        }
        node=node->prox; 
    }
}

void VerificaCoordenadas(Lista listAux,Lista L,double X,double Y,double X2,double Y2)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    double xQ,yQ;
    while(node!=NULL)
    {
        xQ=node->PontoX+node->Largura;//x2 do noh da arvore
        yQ=node->PontoY+node->Altura;//y2 do noh da arvore
        if((node->PontoX >= X)&&(xQ < X2)&&(node->PontoY >= Y)&&(yQ < Y2))//se for verdade esta totalmente contido no retangulo passado
            insert(listAux,node->Cep,"@","@",(node->PontoX),0,0,0,".");//insiro o cep da quadra na lista
            
        node=node->prox;    
    }
    
}

void RemoveQuadrasLista(Lista L,void* avl)
{
    list *lista = (list *) L;
    no *node= lista->primeiro;
    double x2,y2,w2,h2;

    while (node!=NULL)//percorro a lista dos ceps que serao removidos da arvore
    {
        remove_ArvAVL(avl,node->PontoX,node->Cep,&x2,&y2,&w2,&h2);
        node=node->prox;
    }
    
}