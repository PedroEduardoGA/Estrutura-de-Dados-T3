#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<stdio.h>
#include"HashTable.h"

typedef struct registrado{
    char* key;
    char cpf[20],cep[20],complemento[10],face[6],ID[70];//variaveis tanto pra morador quanto pra locacao
    char nome[30],sobrenome[30],sexo[2],data[12];
    int numero,situacao,tipoVoid;//situacao 0 - disponivel, 1 - alocada, 2 - encerrada
    double area,valor;
    Quadra quad;
    struct registrado *next;//apontador pra outro noh pra qnd ocorre repeticao de chave
}noh;

typedef struct registros{
    noh *reg;
}nohs;

typedef struct tabela{
    int tamanho;
    nohs *reg;
}table;

int hashFunction(char* a, int tabSize)//funcao calcula a posicao dado uma chave a
{
    int primos[] = {2, 3, 5, 7, 11, 13, 17, 23, 29, 31, 37, 41, 43, 47,53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449};
    int somatorio = 0;//uso um vetor com varios numeros primos pra usar na geracao da posicao pra determinada chave, usando numeros primos a chance de colisao é menor
    for(unsigned int i=0;i<strlen(a);i++)
        somatorio += a[i]*primos[i];

    somatorio = somatorio % tabSize;//a posicao vai ser o valor do resto, da divisao do somatorio pelo tamanho da tabela
    return somatorio;
}

HashTable criaTabela(int tam)
{
    if(tam<=0)
        return NULL;//caso o tamanho informado seja menor ou igual zero, retorna null
    
    nohs* registros = (nohs*) malloc(sizeof(nohs) * tam);//aloca memoria pra estrutura dos "nohs" de acordo com o tamanho
    table* tabela = (table*) malloc(sizeof(table));//aloca memoria pra estrutura da tabela

    for(int i=0;i<tam;i++)
        registros[i].reg = NULL;//zera todos os nohs da tabela

    tabela->tamanho = tam;
    tabela->reg = registros;
    for(int i=0;i<tam;i++)
        tabela->reg[i].reg = NULL;//zera todos os registros internos da tabela
    
    return tabela;
}

bool insereRegistro(HashTable tab, char* key,char cpf[], char cep[],char name[],char endname[],char sex[],char date[],char fac[],char compl[],int number,char ID[],double Valor,double Area,int situacao)
{
    table* Tabela= (table*) tab;//cast
    int posic = hashFunction(key, Tabela->tamanho);//calcula a posicao que sera inserido de acordo com a chave

    noh* aux = malloc(sizeof(noh));
    if(!aux)
    {
        printf("\nErro ao alocar memoria para o registro!");
        return false;
    }

    aux->key = malloc(strlen(key)+1);//a chave usada pra geracao das posicoes sera o cpf 
    if(!aux->key)
    {
        printf("\nErro ao alocar memoria para a chave!");
        return false;
    }
    strcpy(aux->key, key);
    strcpy(aux->cpf, cpf);//tabela moradores/pessoas
    strcpy(aux->cep, cep);//tabela locacao
    strcpy(aux->nome, name);//tabela moradores/pessoas
    strcpy(aux->sobrenome, endname);//tabela moradores/pessoas
    strcpy(aux->sexo, sex);//tabela moradores/pessoas
    strcpy(aux->data, date);//tabela moradores/pessoas
    strcpy(aux->face, fac);//tabela locacao e tabela moradores
    strcpy(aux->complemento, compl);//tabela locacao e tabela moradores
    strcpy(aux->ID,ID);//tabela locacao
    aux->numero=number;//tabela locacao e tabela moradores
    aux->valor=Valor;//tabela locacao
    aux->area=Area;//tabela locacao
    aux->situacao=situacao;//-1 se nao for tabela de locacao, 0 se for disponivel pra aluguel, 1 se estiver locada
    aux->tipoVoid=0;//inteiro que vai servir pra diferenciar se o void pointer quadra aponta pra um noh da avl ou da lista
    aux->quad=NULL;
    aux->next = Tabela->reg[posic].reg;//o noh->prox vai receber o noh que ocupava a posicao, basicamente vai ser empurrado pra frente
    Tabela->reg[posic].reg = aux;//posicao vai receber o noh novo com as informacoes novas
    return true;
}

bool existeChave(HashTable tab, char* key)
{
    table* Tabela= (table*) tab;//cast
    int posic = hashFunction(key, Tabela->tamanho);//calcula a posicao da chave
    if(Tabela->reg[posic].reg == NULL)//se o registro naquela posicao eh null entao a chave nao existe na tabela
        return false;
    
    return true;
}

bool removeChave(HashTable tab, char* key)
{
    if(!existeChave(tab, key))//oposto da existechave nesse caso é true, senao existe a chave retorna false e o oposto é true
        return false;
    
    table* Tabela= (table*) tab;//cast
    int posic = hashFunction(key, Tabela->tamanho);//calcula a posicao da chave

    noh *toBeDeleted = Tabela->reg[posic].reg;//o noh que sera deletado recebe o registro da posicao calculada
    if(strcmp(toBeDeleted->key, key)==0)//se a chave no noh deletado eh igual a da chave passada ele eh removido
    {
        Tabela->reg[posic].reg = toBeDeleted->next;//a posicao da tabela vai receber o proximo noh
        free(toBeDeleted->key);//free da chave do noh que sera deletado
        toBeDeleted->key = NULL;
        free(toBeDeleted);//free da estrutura do noh que sera deletado
        toBeDeleted = NULL;
        return true;//retorna a posicao do noh que foi deletado
    }
    
    noh *previous = toBeDeleted;//caso a chave do noh nao seja igual a passada
    while(strcmp(toBeDeleted->key, key) != 0)//percorro a "lista" daquele noh posicao procurando pela chave que desejo remover
    {
        previous = toBeDeleted;
        toBeDeleted = toBeDeleted->next;
        if(toBeDeleted == NULL)//chave nao existe
            return false;
    }

    previous->next = toBeDeleted->next;//encontrou o noh com a chave, atribui pro noh anterior o proximo noh do node que sera removido
    free(toBeDeleted->key);
    toBeDeleted->key = NULL;
    free(toBeDeleted);
    toBeDeleted = NULL;

    return true;//retorna a posicao do noh que foi deletado
}

void ImprimeTabela(HashTable tab)
{
    table* Tabela= (table*) tab;//cast

    int posic;
    noh *node;
    for(posic=0; posic<Tabela->tamanho; posic++)
    {
        node = Tabela->reg[posic].reg;//node vai receber o primeiro noh da posicao
        while(node != NULL)//percorre todos nohs daquela posicao
        {
            printf("\nPos[%d]- ID: %s CEP: %s Tipo: %d End: %p",posic,node->ID,node->cep,node->tipoVoid,node->quad);
            node=node->next;
        }
    }
}

void LiberaHashtable(HashTable tab)
{
    table* Tabela= (table*) tab;//cast
    if(Tabela == NULL){
        return;
    }

    noh *aux, *aux2;
    int posic;
    for(posic=0; posic<Tabela->tamanho; posic++)//percorre todas posicoes da tabela
    {
        nohs registro = Tabela->reg[posic];
        if(registro.reg != NULL)//se a posicao ja esta ocupada
        {
            aux2 = registro.reg;//noh aux vai receber o primeiro noh da posicao
            while(aux2 != NULL)//vai percorrer todos nohs daquela posicao
            {
                aux = aux2;//aux é o noh anterior
                aux2 = aux->next;
                if(aux->key != NULL)//libera o noh anterior ao aux2
                {
                    free(aux->key);
                    free(aux);
                    aux = NULL;
                }
            }
        }
    }
    free(Tabela->reg);//libera os registros da tabela
    Tabela->reg = NULL;
    free(Tabela);//libera a tabela
    Tabela = NULL;
}

void AlteraEndereco(HashTable tab,char* cpf,char CEP[],char facE[],char compl[],int number)
{
    noh *node;
    node=GetNohInterno(tab,cpf);
    if(node==NULL)
        return;
    
    strcpy(node->cep,CEP);
    strcpy(node->face,facE);
    strcpy(node->complemento,compl);
    node->numero=number;//os dados de endereco do noh sao alterados
}

void PercorreTabela(HashTable tab,double x,double y,double x2,double y2,char CEP[],char CPF[],int tipo,char TXT[],char SVG[],int *existe,char type[],double *Dou_aux)
{
    table* Tabela= (table*) tab;//cast
    noh *aux;
    nohs registro;
    char* Dados=NULL;
    int posic;
    double variacao;

    if(tipo==0)
    {
        for( posic=0; posic<Tabela->tamanho; posic++)//percorre todas posicoes da tabela
        {
            registro = Tabela->reg[posic];
            if(registro.reg != NULL)//se a posicao ja esta ocupada
            {
                aux = registro.reg;//noh aux vai receber o primeiro noh da posicao
                while(aux != NULL)//vai percorrer todos nohs daquela posicao
                {
                    if(strcmp(aux->cep,CEP) == 0)//se o cep do morador eh igual ao cep passado
                    {
                        Saidas(TXT,aux->nome,aux->sobrenome,aux->sexo,aux->data,aux->cpf,aux->numero,aux->complemento,aux->cep,aux->face,type,0);
                    }    
                    aux=aux->next;
                }
            }
        }  
    }

    if(tipo==1 || tipo>=2)//procura os nohs ate achar o noh que tiver cpf igual ao cpf passado
    {
        if(existeChave(Tabela,CPF))
        {
            
            posic = hashFunction(CPF,Tabela->tamanho);
            aux=Tabela->reg[posic].reg;//atribui ao node o primeiro noh da posicao
            while(aux != NULL)//percorro a "lista" daquele noh posicao procurando pela chave que desejo remover
            {
                if(strcmp(aux->cpf, CPF)==0)//se o cpf do noh eh igual ao cpf passado 
                {
                    *existe=1;
                    if(tipo==1)//consulta dm primeiro acesso
                    {
                        Saidas(TXT,aux->nome,aux->sobrenome,aux->sexo,aux->data,aux->cpf,aux->numero,aux->complemento,aux->cep,aux->face,type,0);
                        if(aux->situacao==1)
                            Saidas(TXT,".",".","Alugada!",".",".",0,".",".",".","dm?",6);
                        strcpy(CEP,aux->cep);//copia o cep do morador pra variavel cep que eh passada como argumento na funcao    
                    }
                    
                    if(tipo==2)
                    {
                        variacao= (double) aux->numero;//converte pra double o valor do numero
                        Dados= (char *) malloc((strlen(aux->cpf)+strlen(aux->nome)+strlen(aux->sobrenome)+strlen(aux->cep)+strlen(aux->complemento)+20) * sizeof(char));//2-> 1 pro / e 1 pro \0
                        sprintf(Dados,"%s %s %s Quadra: %s %d %s",aux->cpf,aux->nome,aux->sobrenome,aux->cep,aux->numero,aux->complemento);
                        DesenhaEndereco(x,y,x2,y2,0.0,0.0,variacao,Dados,aux->face,0,SVG);
                        free(Dados);
                    }

                    if(tipo==3)//consulta mud, procuro o morador com cpf passado e printo no txt os dados dele
                    {
                        *Dou_aux= (double) aux->numero;//atribui no endereco de dou_aux o valor do numero da residencia convertido pra double
                        Saidas(TXT,aux->nome,aux->sobrenome,aux->sexo,aux->data,aux->cpf,aux->numero,aux->complemento,aux->cep,aux->face,type,2);
                        strcpy(CEP,aux->cep);//copia pra cep o cep antigo do morador
                        strcpy(CPF,aux->face);
                    }
                }//quando achou o noh que tem cpf igual ao cpf passado
                aux=aux->next;//vai percorrer todos nohs daquele registro até encontrar o cpf ou ate ser null
            }

            if(*existe==0)
                Saidas(TXT,"CPF:",CPF,"Não Existe!",".",".",0,".",".",".",type,-1);
        }else
            Saidas(TXT,"CPF:",CPF,"Não Existe!",".",".",0,".",".",".",type,-1);
    }
}

void AtribuiPonteiro(Arvore avl,nohInterno nod)
{
    noh* node= (noh*) nod;
    Noh nodeAVL=GetFirstAVL(avl);
    if(nodeAVL!=NULL)
        procuraPonteiroAVL(nodeAVL,&(node->quad),node->cep,&(node->tipoVoid));//vai atribuir o endereco no void pointer, para o noh da avl ou da lista
}

nohInterno GetNohInterno(HashTable tab,char* key)
{
    table* Tabela= (table*) tab;//cast
    if(existeChave(Tabela,key)==false)  
        return NULL;
    
    int posic = hashFunction(key,Tabela->tamanho);//calcula a posicao da chave

    noh *node;
    node=Tabela->reg[posic].reg;//atribui ao node o primeiro noh da posicao
    while(node != NULL)//percorro a "lista" daquele noh posicao procurando pela chave que desejo remover
    {
        if(strcmp(node->key, key)==0)//se a chave passada eh igual ao cpf encontrado retornara o node
            return node;

        node=node->next;//vai percorrer todos nohs daquele registro até encontrar o cpf ou ate ser null
    }
    return node;//se chegou aki ent vai retornar null
}

int locPessoa(HashTable tab,char* cpf,char CEP[],char facE[],char compl[],int number,char nome[],char endname[],char sex[],char data[],char cpfperson[],char TXT[])
{
    table* Tabela= (table*) tab;//cast
    noh* node;
    node=GetNohInterno(Tabela,cpf);
    if(node == NULL)
    {
        Saidas(TXT,"CPF:",cpf,"não existe!",".",".",0,".",".",".","loc",-1);
        return 0;
    }
    strcpy(node->cep,CEP);//atribui os dados do imovel para o morador
    strcpy(node->face,facE);
    strcpy(node->complemento,compl);
    node->numero=number;

    strcpy(nome,node->nome);
    strcpy(endname,node->sobrenome);
    strcpy(sex,node->sexo);
    strcpy(data,node->data);//atribui os dados do morador pros argumentos, pra essas informacoes serem acessadas em outra funcao
    strcpy(cpfperson,node->cpf);
    Saidas(TXT,node->nome,node->sobrenome,node->sexo,node->data,node->cpf,node->numero,node->complemento,node->cep,node->face,"loc",0);//printa dados do morador e do endereco
    return 1;
}

void loc(HashTable tab1,HashTable tab2,char id[],char cpf[],char TXT[],char SVG[],int tipo,char type[])
{
    table* Tabela1= (table*) tab1;//cast
    table* Tabela2= (table*) tab2;//cast
    noh* node;
    char* Dados=NULL;
    double variacao,X,Y,W,H;
    int i;

    node=GetNohInterno(Tabela2,id);//pega o noh id da tabela das locacoes
    if(node==NULL)
    {
        Saidas(TXT,"ID:",id,"não existe!",".",".",0,".",".",".",type,-1);
        return;
    }

    if(tipo==0)//tipo 0 consulta loc
    {
        i=locPessoa(Tabela1,cpf,node->cep,node->face,node->complemento,node->numero,node->nome,node->sobrenome,node->sexo,node->data,node->cpf,TXT);
        if(i==0)//cpf nao existe
            return;
            
        SaidaLocs(TXT,node->area,node->valor);//até aki parte do txt concluida
        node->situacao=1;//agora esta locacao esta alugada
        variacao= (double) node->numero;//variacao recebe o double do numero
        Dados= (char *) malloc((strlen(node->cpf)+strlen(node->nome)+strlen(node->sobrenome)+strlen(node->cep)+strlen(node->complemento)+strlen(node->face)+60) * sizeof(char));
        sprintf(Dados,"%s %s %s Quadra: %s %d %s Face: %s -A: %lf Valor: %lf",node->cpf,node->nome,node->sobrenome,node->cep,node->numero,node->complemento,node->face,node->area,node->valor);

        if((node->tipoVoid != 0)&&(node->quad != NULL))//voidpointer eh apontado pra um noh da arvore
            GetParameters(node->quad,&X,&Y,&W,&H,node->tipoVoid);

        DesenhaEndereco(X,Y,W,H,0,0,variacao,Dados,node->face,0,SVG);//desenha a linha com os dados do morador
        free(Dados);    
    }

    if(tipo>=1)
    {
        Saidas(TXT,".",".",".",".",".",node->numero,node->complemento,node->cep,node->face,type,5);//reporta os dados da moradia
        if(node->situacao==1)
        {
            Saidas(TXT,node->nome,node->sobrenome,node->sexo,node->data,node->cpf,0,".",".",".",type,4);//reporta dados morador
            if(tipo==1)
                Saidas(TXT,node->nome,node->sobrenome,"Alugada",node->data,node->cpf,0,".",".",".",type,6);//diz se a moradia esta ou nao alugada
        }
        if((node->situacao==0)&&(tipo!=2))
            Saidas(TXT,".",".","Disponível",".",".",0,".",".",".",type,6);

        if((node->tipoVoid != 0)&&(node->quad != NULL))//voidpointer eh apontado pra um noh da arvore
            GetParameters(node->quad,&X,&Y,&W,&H,node->tipoVoid);
        
        variacao= (double) node->numero;
        if(tipo==2)//consulta dloc
        {
            Saidas(TXT,node->nome,node->sobrenome,"Encerrada",node->data,node->cpf,0,".",".",".",type,6);
            if(node->situacao==0)
                Saidas(TXT,"Moradia não"," possui morador!",".",".",".",-1,".",".",".",type,-2);//vai informar que a locacao nao tem morador
            node->situacao=2;//agora esta locacao esta encerrada
            Dados= (char *) malloc((strlen(node->cpf)+strlen(node->nome)+strlen(node->sobrenome)+strlen(node->cep)+strlen(node->complemento)+strlen(node->face)+60) * sizeof(char));
            sprintf(Dados,"%s %s %s Quadra: %s %d %s Face: %s -A: %lf Valor: %lf",node->cpf,node->nome,node->sobrenome,node->cep,node->numero,node->complemento,node->face,node->area,node->valor);

            DesenhaEndereco(X,Y,W,H,0,0,variacao,Dados,node->face,0,SVG);//desenha a linha com os dados do morador
            free(Dados);
            AlteraEndereco(Tabela1,node->cpf,"na","na","na",-1);//tira os dados da locacao da pessoa identificada por cpf
            return;
        }
        if(node->situacao == 0)
            DesenhaEndereco(X,Y,W,H,0,0,variacao,"$",node->face,4,SVG);//desenha o simbolo do estado da moradia

        if(node->situacao == 1)
            DesenhaEndereco(X,Y,W,H,0,0,variacao,"*",node->face,4,SVG);

        if(node->situacao == 2)
            DesenhaEndereco(X,Y,W,H,0,0,variacao,"#",node->face,4,SVG);
    }
}

void AnalisaTabela(HashTable tab,Lista list,Arvore avl,int tipo,char type[],char TXT[],char SVG[],char CEP[])
{
    table* Tabela= (table*) tab;
    nohs registro;
    noh* aux;
    noh* a;
    double X,Y,W,H,variacao;
    //tipo 0 -> consultas hom ou mul, tipo 1 -> consulta oloc, tipo 2 -> consulta del e tipo 3 -> consulta catac

    int posic,existe;
    for( posic=0; posic<Tabela->tamanho; posic++)//percorre todas posicoes da tabela
    {
        registro = Tabela->reg[posic];
        if(registro.reg != NULL)//se a posicao ja esta ocupada
        {
            aux = registro.reg;//noh aux vai receber o primeiro noh da posicao
            while(aux != NULL)//vai percorrer todos nohs daquela posicao
            {
                existe=0;
                if(tipo==0 && strcmp(aux->cep,"") > 0)//se o tipo eh 0 e se a pessoa mora em alguma quadra
                {
                    ExisteCEPList(list,aux->cep,&existe);//se o cep existir na lista existe vai sair valendo 1
                    if(existe)
                    {
                        if((strcmp(aux->sexo,"M")==0) && (strcmp(type,"hom")==0))//se o sexo do morador é masculino e a consulta é hom
                        {
                            Saidas(TXT,aux->nome,aux->sobrenome,aux->sexo,aux->data,aux->cpf,aux->numero,aux->complemento,aux->cep,aux->face,type,0);//reportara os dados do morador e da moradia
                            AtribuiPonteiro(avl,aux);//vai pegar o ponteiro pra quadra cep do morador
                            GetParameters(aux->quad,&X,&Y,&W,&H,aux->tipoVoid);//vai pegar os valores de x,y,w,h do morador
                            variacao= (double) aux->numero;
                            DesenhaEndereco(X,Y,W,H,0,0,variacao,"blue",aux->face,5,SVG);//desenha a elipse azul no endereco
                        }

                        if((strcmp(aux->sexo,"F")==0) && (strcmp(type,"mul")==0))//se o sexo do morador é masculino e a consulta é hom
                        {
                            Saidas(TXT,aux->nome,aux->sobrenome,aux->sexo,aux->data,aux->cpf,aux->numero,aux->complemento,aux->cep,aux->face,type,0);//reportara os dados do morador e da moradia
                            AtribuiPonteiro(avl,aux);//vai pegar o ponteiro pra quadra cep do morador
                            GetParameters(aux->quad,&X,&Y,&W,&H,aux->tipoVoid);//vai pegar os valores de x,y,w,h do morador
                            variacao= (double) aux->numero;
                            DesenhaEndereco(X,Y,W,H,0,0,variacao,"pink",aux->face,5,SVG);//desenha a elipse azul no endereco
                        }
                            
                    }
                }

                if(tipo==1)//consulta oloc
                {
                    ExisteCEPList(list,aux->cep,&existe);//se o cep existir na lista existe vai sair valendo 1
                    if(existe)
                    {
                        GetParameters(aux->quad,&X,&Y,&W,&H,aux->tipoVoid);//vai pegar os valores de x,y,w,h do morador
                        variacao= (double) aux->numero;
                        Saidas(TXT,"","","","","",aux->numero,aux->complemento,aux->cep,aux->face,type,5);//reporta dados moradia
                        SaidaLocs(TXT,aux->area,aux->valor);//reporta dados locacao
                        if(aux->situacao == 0)//disponivel pra locacao
                            DesenhaEndereco(X,Y,W,H,0,0,variacao,"*",aux->face,4,SVG);  
                    }
                }
                    
                if(tipo > 1 && strcmp(aux->cep,"") > 0)
                {
                    a=aux;//copio pra a todos valores de aux
                    if(tipo==2)//consulta del, percorro comparando cep do noh com cep passado, se for igual removo e reporto dados
                    {
                        if(strcmp(a->cep,CEP)==0)//morador/locacao tem que ser removido
                        {
                            if(a->situacao > -1)//tabela de locacao
                            {
                                Saidas(TXT,"","","","","",a->numero,a->complemento,a->cep,a->face,type,-3);//reporta dados da locacao
                                aux->next=a->next;
                                removeChave(Tabela,a->ID);
                            }   
                            else
                                {
                                    Saidas(TXT,a->nome,a->sobrenome,a->sexo,a->data,a->cpf,-1,".",".",".",type,-4);//reporta dados morador
                                    aux->next=a->next;
                                    removeChave(Tabela,a->cpf);
                                }
                        }
                    }

                    if(tipo==3)//consulta catac
                    {
                        ExisteCEPList(list,a->cep,&existe);//se o cep existir na lista existe vai sair valendo 1
                        if(existe)
                        {
                            if(a->situacao > -1)//tabela de locacao
                            {
                                Saidas(TXT,"","","","","",a->numero,a->complemento,a->cep,a->face,type,-3);//reporta dados da locacao
                                aux->next=a->next;
                                removeChave(Tabela,a->ID);
                            }   
                            else
                                {
                                    Saidas(TXT,a->nome,a->sobrenome,a->sexo,a->data,a->cpf,-1,".",".",".",type,-4);//reporta dados morador
                                    aux->next=a->next;
                                    removeChave(Tabela,a->cpf);
                                }
                        }
                    }
                }
                aux=aux->next;
            }
        }
    }
}