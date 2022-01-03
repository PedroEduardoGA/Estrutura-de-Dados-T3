#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvoreAVL.h"

typedef struct N{ //Onde guarda infos como, cor borda, preenchimento...
    double x,y,w,h,minX,maxX;
    int altura;
    char cep[30],corBorda[30],corFill[30],espressura[10];
    Lista lista;
    
    struct N *Pai;
    struct N *Filho_esq;
    struct N *Filho_dir;
}no;

typedef struct T{
    no *Raiz; //primeiro elemento da list
    
}tree;

Arvore CreateAVL()//Aloca uma list
{
    tree* arvore = (tree*) malloc(sizeof(tree));//alloca, cria variavel e faz cast de list* lista
    arvore->Raiz=NULL;

    return arvore;//retorna uma lista sem no interno
}

void Libera(Noh nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        Libera(node->Filho_dir);
        Libera(node->Filho_esq);
        liberalist(node->lista);//libera a lista do noh
        free(node);
    }
}

int altura_NO(Noh nod)
{//recebe um noh
    no* node = (no*) nod;
    if(node == NULL)//se o noh é null retorna -1
        return -1;
    else
        return node->altura;//senao, retorna a altura desse noh
}

int fatorBalanceamento_NO(Noh nod)
{
    no* node = (no*) nod;
    return (altura_NO(node->Filho_esq) - altura_NO(node->Filho_dir));//retorna o modulo da altura do noh esq - noh dir
}

int maior(int x, int y)//serve pra compara qual filho possui uma altura maior
{
    if(x > y)
        return x;
    else
        return y;
}

void emOrdem_ArvAVL(Noh nod)//imprime arvore em ordem
{
    no* node = (no*) nod;
    if(node != NULL)
    {
        emOrdem_ArvAVL(node->Filho_esq);
        printf("No %lf :fb(%d)\n",node->x,fatorBalanceamento_NO(node));
        emOrdem_ArvAVL(node->Filho_dir);
    }
}

void RotacaoLL(Arvore t,Noh nod)
{//LL
    tree* arvore = (tree*) t;
    no* nodeA = (no*) nod;
    no* nodeB;
    int filho=0;

    if(nodeA->Pai!=NULL)//nodeA nao eh raiz da arvore
    {
        if(nodeA->Pai->Filho_dir == nodeA)
                filho=1;
            else
                filho=-1;
    }

    nodeB=nodeA->Filho_esq;
    
    if(nodeB->Filho_dir!=NULL)
        nodeB->Filho_dir->Pai=nodeA;
  
    nodeA->Filho_esq=nodeB->Filho_dir;
    nodeB->Filho_dir=nodeA;
    
    if(arvore->Raiz == nodeA)//caso o noh passado pra balancear fosse a raiz da arvore
    {
        arvore->Raiz=nodeB;
        nodeB->Pai=NULL;
    }else
        {
            nodeB->Pai=nodeA->Pai;
            if(filho==1)
                nodeA->Pai->Filho_dir=nodeB;
           
            if (filho == -1)
                nodeA->Pai->Filho_esq=nodeB;
        }
    nodeA->Pai=nodeB;
    nodeA->altura = maior(altura_NO(nodeA->Filho_esq),altura_NO(nodeA->Filho_dir)) + 1;
    nodeB->altura = maior(altura_NO(nodeB->Filho_esq),nodeA->altura) + 1;
}

void RotacaoRR(Arvore t,Noh nod)
{//RR
    tree* arvore = (tree*) t;
    no* nodeA = (no*) nod;
    no* nodeB;
    int filho=0;

    if(nodeA->Pai!=NULL)//nodeA nao eh raiz da arvore
    {
        if(nodeA->Pai->Filho_dir == nodeA)
                filho=1;
            else
                filho=-1;
    }
    nodeB=nodeA->Filho_dir;
    
    if(nodeB->Filho_esq!=NULL)
        nodeB->Filho_esq->Pai=nodeA;

    nodeA->Filho_dir=nodeB->Filho_esq;
    nodeB->Filho_esq=nodeA;
    
    if(arvore->Raiz == nodeA)//caso o noh passado pra balancear fosse a raiz da arvore
    {
        arvore->Raiz=nodeB;
        nodeB->Pai=NULL;
    }else
        {
            nodeB->Pai=nodeA->Pai; 
            if(filho==1)
                nodeA->Pai->Filho_dir=nodeB;
           
            if (filho == -1)
                nodeA->Pai->Filho_esq=nodeB;           
        }
    nodeA->Pai=nodeB;
    nodeA->altura = maior(altura_NO(nodeA->Filho_esq),altura_NO(nodeA->Filho_dir)) + 1;
    nodeB->altura = maior(altura_NO(nodeB->Filho_dir),nodeA->altura) + 1;
}

void RotacaoLR(Arvore t,Noh nod)
{//LR
    no* nodeA = (no*) nod;
    RotacaoRR(t,nodeA->Filho_esq);
    RotacaoLL(t,nodeA);
}

void RotacaoRL(Arvore t,Noh nod)
{//RL
    no* nodeA = (no*) nod;  
    RotacaoLL(t,nodeA->Filho_dir);
    RotacaoRR(t,nodeA);
}

Noh GetFirstAVL(Arvore arv)
{
    tree* arvore = (tree*) arv;
    return arvore->Raiz;
}

bool ExisteValor(Arvore arv,double valor)
{
    tree* arvore = (tree*) arv;
    no* aux;

    aux=arvore->Raiz;
    while ((aux!=NULL)&&(aux->x!=valor))
    {
        if(valor < aux->x)
            aux=aux->Filho_esq;
        else
            aux=aux->Filho_dir;
    }
    if(aux==NULL)//arvore vazia ou valor n existe
        return false;

    if(aux->x == valor)
        return true;
    else
        return false;  
}

bool insereArvAVL(Arvore t,double Px,double Py,double largu,double altu,char espre[10],char CEP[30],char CorBord[30],char corFill[30])
{
    int inserido=0;
    no* anterior;
    tree* arvore = (tree*) t;

    no* novo = (no*) malloc(sizeof(no));
    novo->x=Px;
    novo->y=Py;
    novo->w=largu;
    novo->h=altu;
    novo->Filho_dir=NULL;
    novo->Filho_esq=NULL;
    novo->altura=0;
    novo->minX=Px;
    novo->maxX=0;
    strcpy(novo->cep,CEP);
    strcpy(novo->espressura,espre);
    strcpy(novo->corBorda,CorBord);
    strcpy(novo->corFill,corFill);
    
    if(ExisteValor(arvore,Px)==false)//valor de x nao existe na arvore
        novo->lista= Create();//cria a lista do noh, que sera inserido

    if(arvore->Raiz==NULL)
    { 
        novo->Pai=NULL;
        arvore->Raiz=novo;
        anterior=NULL;
        inserido=2;//inserido eh 2 pq foi inserida a raiz
    }else
        anterior=arvore->Raiz;
    
    while ((anterior!=NULL)&&(inserido != 1))
    {
        if(Px == anterior->x)//o x passado ja existe na arvore, entao a quadra sera inserida na lista dentro do noh
        {
            insert(anterior->lista,CEP,corFill,CorBord,Px,Py,largu,altu,espre);
            free(novo);
            inserido=-1;//inserido -1 pq foi inserido na lista de um noh ja existente entao nao precisa calcular fator de balanceamento dos nohs anteriores
            return true;
        }

        if(Px < anterior->x)//vai pra esquerda por ser menor
        {
            if(anterior->Filho_esq==NULL)
            {
                anterior->Filho_esq=novo;
                novo->Pai=anterior;
                inserido=1;
            }else
                anterior=anterior->Filho_esq;
        }

        if(Px > anterior->x)//vai pra direita por ser maior
        {
            if(anterior->Filho_dir==NULL)
            {
                anterior->Filho_dir=novo;
                novo->Pai=anterior;
                inserido=1;
            }else
                anterior=anterior->Filho_dir;
        }
    }//acabou a parte da inserção
    
    if(inserido==1)
    {
        while(anterior!=NULL)//vou percorrer a arvore atualizando a altura dos nohs anteriores
        {
            if(Px < anterior->x)
            {
                if(fatorBalanceamento_NO(anterior) >= 2 || fatorBalanceamento_NO(anterior) <= -2)
                {
                    if(Px < anterior->Filho_esq->x )
                        RotacaoLL(t,anterior);
                    else
                        RotacaoLR(t,anterior);
                }
            }else
                {
                    if(Px > anterior->x)
                    {
                        if(fatorBalanceamento_NO(anterior) >= 2 || fatorBalanceamento_NO(anterior) <= -2)
                        {
                            if(anterior->Filho_dir->x < Px)
                                RotacaoRR(t,anterior);
                            else
                                RotacaoRL(t,anterior);
                        }
                    }
                }
            anterior->altura = maior(altura_NO(anterior->Filho_esq),altura_NO(anterior->Filho_dir)) + 1;
            anterior=anterior->Pai;
        }
    }
    if(inserido!=0)
        return true;
    else
        return false;
}

bool isEmpty(Arvore t)//retorna verdade se a arvore esta vazia
{
    tree* arvore = (tree*) t;
    if(arvore->Raiz==NULL)
        return true;
    else
        return false;
}

Noh procuraMenor(Noh nod)//funcao retorna o menor nó a esquerda
{
    no* node = (no*) nod;
    no* nodeProx= node->Filho_esq;
    while(nodeProx != NULL)
    {
        node=nodeProx;
        nodeProx=nodeProx->Filho_esq;
    }
    return node;
}

Noh GetNodeAVL(Arvore arv,double valor)
{
    tree* arvore = (tree*) arv;
    no* aux;
    
    if(isEmpty(arvore))
        return NULL;//arvore esta vazia

    aux=arvore->Raiz;
    while ((aux!=NULL)&&(aux->x!=valor))
    {
        if(valor < aux->x)
            aux=aux->Filho_esq;
        else
            aux=aux->Filho_dir;
    }
    
    if(aux==NULL)
        return NULL;
    
    if(aux->x == valor)
        return aux;
    else 
        return NULL;
}

bool remove_ArvAVL(Arvore t, double valorX,char CEP[],double *CoordX,double *CoordY,double *wid,double *high)//funcao funciona perfeitamente
{
    tree* arvore = (tree*) t;
    int removido=0,lado=0,Possuiafilhos=0;
	if(isEmpty(arvore))
        return false;//arvore esta vazia

    no* node;
    no* anterior;
    no* aux;
    node= GetNodeAVL(arvore,valorX);//retorna o noh que possui o x igual o valor passado

    if(node==NULL)
        return false;
    

    if(strcmp(node->cep,CEP)!=0)//cep nao esta no noh da arvore
    {
        RemoveElemento(node->lista,CEP,CoordX,CoordY,wid,high);//remove o elemento da lista
        return true;
    }

    if(strcmp(node->cep,CEP)==0)//cep do noh eh igual ao do noh
    {
        *CoordX=node->x;
        *CoordY=node->y;
        *wid=node->w;
        *high=node->h;
        if(ListaNaoVazia(node->lista))//se a lista do noh nao esta vazia eu pego o primeiro elemento e atribuo nos dados da quadra
        {
            PegaFirst(node->lista,&(node->x),&(node->y),&(node->w),&(node->h),node->cep,node->corBorda,node->corFill,node->espressura);
            removido= 1;//o x pode ser alterado entao talvez seja necessario balanceamento
            aux=node->Pai;
        }   
    }
    
    if(removido==0)
    {
        if(node->Pai!=NULL)
        {
            if(node->Pai->Filho_esq == node)
                lado=-1;//node atual é o filho esquerdo do pai
            else
                lado=1;//node atual é o filho direito do pai
        }

        if(node->Filho_esq==NULL || node->Filho_dir==NULL)//tem 1 ou nenhum filho
        {
            anterior=node->Pai;
            if(node->Filho_esq != NULL)//filho esquerdo nao eh nulo
            {
                if(lado == 1)
                    anterior->Filho_dir=node->Filho_esq;
                
                if(lado == -1)
                    anterior->Filho_esq=node->Filho_esq;

                if(lado==0)
                    arvore->Raiz=node->Filho_esq;

                Possuiafilhos=1;
            }

            if(node->Filho_dir != NULL)//filho esquerdo nao eh nulo
            {
                if(lado == 1)
                    anterior->Filho_dir=node->Filho_dir;
                
                if(lado == -1)
                    anterior->Filho_esq=node->Filho_dir;

                if(lado==0)
                    arvore->Raiz=node->Filho_dir;

                Possuiafilhos=1;
            }

            if(Possuiafilhos==0)
            {
                if(node->Pai!=NULL)
                {
                    if(lado == 1)
                        anterior->Filho_dir=NULL;//noh removido era filho direito do noh pai
                    else
                        anterior->Filho_esq=NULL;//noh removido era filho esquerdo do noh pai    
                }else
                    arvore->Raiz=NULL;
            }
            aux=anterior;
            liberalist(node->lista);//libera a lista do noh
            free(node);
            removido=1;
        }

        if((node->Filho_esq!=NULL) && (node->Filho_dir!=NULL) && (removido==0))//noh tem 2 filhos
        {
            anterior=procuraMenor(node->Filho_dir);//anterior é o menor valor da subarvore direita
            if(anterior != node->Filho_dir)//o noh direito possuia menor valor
            {
                if(anterior->Pai->Filho_esq == anterior)
                    lado=-1;//node anterior é o filho esquerdo do pai
                else
                    lado=1;

                if(lado == 1)
                    anterior->Pai->Filho_dir=anterior->Filho_dir;//atribui o filho direito do noh anterior pro pai
                
                if(lado == -1)
                    anterior->Pai->Filho_esq=anterior->Filho_dir;

                node->x=anterior->x;//copia os valores do menor noh do filho direito
                node->y=anterior->y;
                node->w=anterior->w;
                node->h=anterior->h;
                strcpy(node->cep,anterior->cep);
                strcpy(node->corBorda,anterior->corBorda);
                strcpy(node->corFill,anterior->corFill);
                strcpy(node->espressura,anterior->espressura);
                node->lista=anterior->lista;

                aux=anterior->Pai;//atribui o pai do menor noh pro aux
                free(anterior);//libera a memoria alocada pelo menor noh
                removido=1;
            }

            if((anterior == node->Filho_dir)&&(removido==0))//o filho direito nao possui sub arvore esquerda
            {
                node->x=anterior->x;//copia os valores do menor noh do filho direito
                node->y=anterior->y;
                node->w=anterior->w;
                node->h=anterior->h;
                strcpy(node->cep,anterior->cep);
                strcpy(node->corBorda,anterior->corBorda);
                strcpy(node->corFill,anterior->corFill);
                strcpy(node->espressura,anterior->espressura);
                node->lista=anterior->lista;
                node->Filho_dir=NULL;
                aux=anterior->Pai;//atribui o pai do menor noh pro aux
                free(anterior);//libera a memoria alocada pelo menor noh
                removido=1;
            }
        }
    }//chegou aqui o valor que seria removido da arvore ja foi removido

    if(removido==1)
    {
        while(aux!=NULL)//vou percorrer a arvore atualizando a altura dos nohs auxes
        {
            if(valorX <= aux->x)
            {
                if(fatorBalanceamento_NO(aux) >= 2 || fatorBalanceamento_NO(aux) <= -2)
                {
                    if(valorX < aux->Filho_esq->x )
                        RotacaoLL(t,aux);
                    else
                        RotacaoLR(t,aux);
                }
            }else
                {
                    if(valorX >= aux->x)
                    {
                        if(fatorBalanceamento_NO(aux) >= 2 || fatorBalanceamento_NO(aux) <= -2)
                        {
                            if(aux->Filho_dir->x < valorX)
                                RotacaoRR(t,aux);
                            else
                                RotacaoRL(t,aux);
                        }
                    }
                }
            aux->altura = maior(altura_NO(aux->Filho_esq),altura_NO(aux->Filho_dir)) + 1;
            aux=aux->Pai;
        }//finalWhile
        return true;    
	}else
        return false;
}

void ManipulacaoDot(Arvore t,char arquivo[])
{
    tree* arvore = (tree*) t;
    FILE* ArqDot = fopen(arquivo, "w");
    if(ArqDot == NULL)
    {
        printf("Nao foi possivel criar o arquivo .dot!\n");
        exit(1);
    }

    fprintf(ArqDot,"digraph Arvore {\nsize=\"350\";\nnode [color=gray, style=filled];\n ");
    if(arvore->Raiz==NULL)
        return;
    
    EscritaDot(arvore->Raiz,ArqDot);//passa pra funcao o primeiro noh da arvore e o ponteiro pro arquivo .dot
    fprintf(ArqDot,"\n}");

    fclose(ArqDot);//fecha o arquivo
}

void EscritaDot(Noh nod,FILE* arq)
{
    no* node = (no*) nod;

    if(node==NULL)
        return;

    char linha[450],cep1[30],cep2[30],cep1P[30],cep2P[30];
    char *seta= " -> ";
    if(node->Filho_esq!=NULL)
    {
        PegaAlgunsCEP(node->lista,cep1,cep2);//pega alguns cep da lista do noh pai
        strcpy(cep1P,cep1);
        strcpy(cep2P,cep2);
        PegaAlgunsCEP(node->Filho_esq->lista,cep1,cep2);//pega alguns cep da lista do noh filho esq
        sprintf(linha,"\"X:%lf\nQuadras:%d\nfb:%d\nCep1:%s\nCep2:%s\nXmin:%lf-Xmax:%lf\"%s\"X:%lf\nQuadras:%d\nfb:%d\nCep1:%s\nCep2:%s\nXmin:%lf-Xmax:%lf\";\n",node->x,TamanhoLista(node->lista),fatorBalanceamento_NO(node),cep1P,cep2P,node->minX,node->maxX,seta,node->Filho_esq->x,TamanhoLista(node->Filho_esq->lista),fatorBalanceamento_NO(node->Filho_esq),cep1,cep2,node->Filho_esq->minX,node->Filho_esq->maxX);
        fprintf(arq,linha);
    }

    if(node->Filho_dir!=NULL)
    {
        PegaAlgunsCEP(node->lista,cep1,cep2);//pega alguns cep da lista do noh pai
        strcpy(cep1P,cep1);
        strcpy(cep2P,cep2);
        PegaAlgunsCEP(node->Filho_dir->lista,cep1,cep2);//pega alguns cep da lista do noh filho esq
        sprintf(linha,"\"X:%lf\nQuadras:%d\nfb:%d\nCep1:%s\nCep2:%s\nXmin:%lf-Xmax:%lf\"%s\"X:%lf\nQuadras:%d\nfb:%d\nCep1:%s\nCep2:%s\nXmin:%lf-Xmax:%lf\";\n",node->x,TamanhoLista(node->lista),fatorBalanceamento_NO(node),cep1P,cep2P,node->minX,node->maxX,seta,node->Filho_dir->x,TamanhoLista(node->Filho_dir->lista),fatorBalanceamento_NO(node->Filho_dir),cep1,cep2,node->Filho_dir->minX,node->Filho_dir->maxX);
        fprintf(arq,linha);
    }
    EscritaDot(node->Filho_esq,arq);
    EscritaDot(node->Filho_dir,arq);
}

void BuscaAVL(Noh nod,char CEP[],double *x,double *y, double *w, double *h,int *existe)//funcao que busca o cep na arvore e retorna 1 se existe ou 0 senao
{
    no* node = (no*) nod;
    
    if(node!=NULL)
    {
        if(strcmp(node->cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *existe=1;//entao cep existe
            *x=node->x;
            *y=node->y;
            *w=node->w;
            *h=node->h;
        }else
            PercorreLista(node->lista,CEP,x,y,w,h,existe);

        if(*(existe) != 1)//nao foi encontrado o noh com o cep se eh que cep existe
        {
            BuscaAVL(node->Filho_esq,CEP,x,y,w,h,existe);
            BuscaAVL(node->Filho_dir,CEP,x,y,w,h,existe);
        }
    }//if node != NULL
}

void procuraPonteiroAVL(Noh nod,void** quad,char CEP[],int *type)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        if(strcmp(node->cep,CEP)==0)//o noh atual tem o cep igual o cep passado
        {
            *type=1;//entao cep existe
            *quad=node;//atribui no endereco de quad o endereco do node atual
            return;
        }else
            procuraPonteiroLista(node->lista,quad,CEP,type);

        if(*type == 0)//nao foi encontrado o noh com o cep se eh que cep existe
        {
            procuraPonteiroAVL(node->Filho_esq,quad,CEP,type);
            procuraPonteiroAVL(node->Filho_dir,quad,CEP,type);
        }else
            return;
    }
}

void SvgAVL(Noh nod,char arquivo[])
{
    no* node = (no*) nod;
    if(node != NULL)
    {
        criaRetangulo(node->w,node->h,node->x,node->y,node->corBorda,node->corFill,node->espressura,arquivo);//imprime os retangulos da arvore
        TextoSvg(node->x+1.5,node->y+10.5,node->cep,arquivo);//printa o cep da quadra
        SvgQry(node->lista,arquivo);//imprime os retangulos de cada noh da arvore 

        SvgAVL(node->Filho_esq,arquivo);
        SvgAVL(node->Filho_dir,arquivo);
    }
}

void GetParameters(Noh nod,double *x,double *y,double *w,double *h,int type)//serve para pegar os parametros da funcao
{
    if(type==1)//noh passado eh da arvore
    {
        no* node = (no*) nod;
        *x=node->x;
        *y=node->y;
        *w=node->w;
        *h=node->h;
        return; 
    }else
        GetParametersList(nod,x,y,w,h);//noh passado eh da lista
}

void ExisteCEP(Noh nod,char CEP[],int *existe)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        if(strcmp(node->cep,CEP)==0)
        {
            *existe=1;
            return;
        }else
            ExisteCEPList(node->lista,CEP,existe);

        if(*existe==0)
        {
            ExisteCEP(node->Filho_esq,CEP,existe);
            ExisteCEP(node->Filho_dir,CEP,existe);
        }
    }
}

void AtualizaMinMax(Noh nod)
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        node->minX=node->x;
        node->maxX=node->x+node->w;
        CalculaMinMax(node,&(node->minX),&(node->maxX));//calcula o minX

        AtualizaMinMax(node->Filho_esq);//chamo recursivamente pra atualizar os valores do restante da arvore
        AtualizaMinMax(node->Filho_dir);
    }
}

void CalculaMinMax(Noh nod,double* min,double* max)
{
    no* node = (no*) nod;
    no *aux=node;//salvo o node no aux
    double soma;
    if(node!=NULL)
    {
        while(node!=NULL)//buscando minX
        {
            *min=node->x;//minimo vai receber o valor do x do noh mais a esquerda da arvore
            node=node->Filho_esq;
        }
        
        node=aux;
        while(node!=NULL)//buscando maxX
        {
            soma=node->x+node->w;
            if(soma > *max)//se a soma for maior que o x max, maxX passa a valer soma
                *max=soma;

            node=node->Filho_dir;
        }
    }
}

void PegaX_CEP(Noh nod,char CEP[],double* X,int *existe)//vai pegar a coordenada x da quadra cep
{
    no* node = (no*) nod;
    if(node!=NULL)
    {
        if(strcmp(node->cep,CEP)==0)
        {
            *existe=1;
            *X=node->x;
            return;
        }else
            PegaX_CepList(node->lista,CEP,X,existe);

        if(*existe==0)
        {
            PegaX_CEP(node->Filho_esq,CEP,X,existe);
            PegaX_CEP(node->Filho_dir,CEP,X,existe);
        }
    }
}

void PercorreAVL(Noh nod,void* listaAux,double X,double Y,double W,double H)
{
    no* node = (no*) nod;
    double X2,Y2,xQ,yQ;
    X2=X+W;
    Y2=Y+H;

    if(node != NULL)
    {
        xQ=node->x+node->w;//x2 do noh da arvore
        yQ=node->y+node->h;//y2 do noh da arvore
        if((node->x >= X)&&(xQ < X2)&&(node->y >= Y)&&(yQ < Y2))//se for verdade esta totalmente contido no retangulo passado
            insert(listaAux,node->cep,"@","@",(node->x),0,0,0,".");
             
        VerificaCoordenadas(listaAux,node->lista,X,Y,X2,Y2);//vai verificar a lista do noh quais quadras estao dentro da regiao e inserir o cep na lista
        
        if(node->Filho_esq!=NULL)
        {
            if((node->Filho_esq->maxX >= X || node->Filho_esq->minX <= X2))//verifica pelo minX e maxX se o filho_esq é um noh promissor, senao poda ele
                PercorreAVL(node->Filho_esq,listaAux,X,Y,W,H);
        }
       
        if(node->Filho_dir!=NULL)
        {
            if((node->Filho_dir->maxX >= X || node->Filho_dir->minX <= X2))//verifica pelo minX e maxX se o filho_dir é um noh promissor, senao poda ele
                PercorreAVL(node->Filho_dir,listaAux,X,Y,W,H);
        }
    }
}
