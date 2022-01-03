#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

int LeituraGeo(Arvore Avl,char* bed,char* nomeArq,char* dirSaida,int *nx)
{
    char *pathFile=NULL;
    char *svg=NULL;

    if (bed != NULL)
    {
        pathFile= (char *) malloc((strlen(bed)+strlen(nomeArq)+2) * sizeof(char));
        sprintf(pathFile, "%s/%s", bed, nomeArq);
    }else//Se for nulo
        {
            pathFile= (char *) malloc((strlen(nomeArq)+1)*sizeof(char));
            strcpy(pathFile,nomeArq);//Se nao tiver o -e, vai ser copiado pra pathFile somente o nome do geo, ja que vai estar no mesmo diretorio
        }

    FILE* ArqGeo = fopen(pathFile, "r");
    if(ArqGeo == NULL)
    {
        printf("Nao foi possivel abrir o .geo!\n");
        exit(1);
    }
    char copy_linha[150];
    char linha[150];
    char lixo[8];//Nessa variavel vai o inicio dos comandos

    strtok(nomeArq, ".");//Formata o nome do Geo, tirando o .geo para inserir no arquivo svg inicial

    svg= (char *) malloc((strlen(dirSaida)+strlen(nomeArq)+6) * sizeof(char));//6-> 5 por causa do / .svg + 1 do /0
    sprintf(svg, "%s/%s.svg",dirSaida,nomeArq);//Vai copiar pra svg o diretoriosaida /nome do geo.svg
    iniciaSvg(svg);
    
    char CorPrenche[30];
    char CorBord[30];
    double Px,Py,Largu,Altu;
    char Cep[30],espressura[10];
    int TotalQuadras=0;

    //é copiado pra linha cada linha do geo, ate o gets ser nulo
    printf("\nRealizando leitura do .geo . . .");
    while (fgets(linha, sizeof(linha), ArqGeo) != NULL)//varre o arquivo linha por linha
    {
        sprintf(copy_linha, "%s", linha);//copia pra cpoy_linha o conteudo da linha lida

        if (strcmp(strtok(linha, " "), "nx") == 0)//separa a linha no espaco e compara o comando
            sscanf(copy_linha, "%s %d", lixo, nx);//atribui o valor de nx diretamente no endereco da variavel

        if (strcmp(strtok(linha, " "), "q") == 0)//separa a linha no espaco e compara o comando
        { 
            sscanf(copy_linha, "%s %s %lf %lf %lf %lf", lixo, Cep, &Px, &Py, &Largu, &Altu);//comando que cria uma quadra

            insereArvAVL(Avl,Px,Py,Largu,Altu,espressura,Cep,CorBord,CorPrenche);
            criaRetangulo(Largu, Altu,Px, Py,CorBord,CorPrenche,espressura,svg);
            TextoSvg(Px+1.5,Py+10.5,Cep,svg);
            TotalQuadras++;
        }

        if (strcmp(strtok(linha, " "), "cq") == 0)//separa a linha no espaco e compara o comando
            sscanf(copy_linha, "%s %s %s %s", lixo, espressura, CorPrenche, CorBord);//comando que atribui espressura e as cores das quadras
        
    }
    TextoSvg(-2.0,-4.0,"Pedro Eduardo Garbossa de Almeida",svg);
    finalizaSvg(svg);//finaliza o svg inicial
    fclose(ArqGeo);//Fecha o geo, apos inserir na lista escolhida todos os retangulos
    free(svg);//free do nome do svg
    free(pathFile);//free do path
    printf("\nVariaveis liberadas, saiu do geo!");
    return TotalQuadras;
}

void LeituraPm(HashTable tabela,char* DiretorioEnt,char* nomePm)
{
    char *pathFile=NULL;

    if (DiretorioEnt != NULL)
    {
        pathFile= (char *) malloc((strlen(DiretorioEnt)+strlen(nomePm)+2) * sizeof(char));//2 por causa do / e do /0
        sprintf(pathFile, "%s/%s", DiretorioEnt, nomePm);
    }else//Se for nulo
        {
            pathFile= (char *) malloc((strlen(nomePm)+1)*sizeof(char));
            strcpy(pathFile,nomePm);//Se nao tiver o -e, vai ser copiado pra pathFile somente o nome do pm, ja que vai estar no mesmo diretorio
        }

    FILE* ArqPm = fopen(pathFile, "r");
    if(ArqPm == NULL)
    {
        printf("Nao foi possivel abrir o .pm!\n");
        exit(1);
    }
    char copy_linha[150];
    char linha[150];
    char lixo[2];//Nessa variavel vai o inicio dos comandos, como r,cc,cp
    
    char Cep[20],Cpf[20],nome[30],sobrenome[30],face[6];
    char Data[12],sexo[2],comple[10];
    int numero;

    //é copiado pra linha cada linha do pm, ate o gets ser nulo
    printf("\nRealizando leitura do .pm . . .");
    while (fgets(linha, sizeof(linha), ArqPm) != NULL)//varre o arquivo linha por linha
    {
        sprintf(copy_linha, "%s", linha);//copia pra copy_linha o conteudo da linha lida

        if (strcmp(strtok(linha, " "), "p") == 0)//separa a linha no espaco e compara o comando
        { 
            sscanf(copy_linha, "%s %s %s %s %s %s", lixo, Cpf, nome, sobrenome, sexo, Data);
            insereRegistro(tabela,Cpf,Cpf,"",nome,sobrenome,sexo,Data,"","",-1,"",0,0,-1);
        }

        if (strcmp(strtok(linha, " "), "m") == 0)//separa a linha no espaco e compara o comando
        { 
            sscanf(copy_linha, "%s %s %s %s %d %s", lixo, Cpf, Cep, face, &numero, comple);
            AlteraEndereco(tabela,Cpf,Cep,face,comple,numero);
        }
    }
    fclose(ArqPm);//Fecha o pm, apos fazer leitura
    free(pathFile);//free do path
    printf("\nVariaveis liberadas, saiu do pm!");
}

void LeituraQry(Arvore AVL,HashTable Tabela1,HashTable Tabela2,char* DiretorioEnt,char* nomeQry,char* diretSaida,char* TxtSaida,char svg[],char geo[],char qrySemExt[])
{//Tabela1 eh a de moradores/pessoas e Tabela2 eh a tabela das locacoes
    char* pathQry=NULL;
    if (DiretorioEnt != NULL)
    {
        pathQry= (char *) malloc((strlen(nomeQry)+strlen(DiretorioEnt)+2) * sizeof(char));//2-> 1 pro / e 1 pro \0
        sprintf(pathQry, "%s/%s", DiretorioEnt, nomeQry);//Insere uma / entre o diretorio e o nome do qry 
    }
    else
        {
            pathQry= (char *) malloc((strlen(nomeQry)+1)*sizeof(char));
            strcpy(pathQry,nomeQry);//Se nao tiver o -e, vai ser copiado pra pathQry somente o nome do qry, ja que vai estar no mesmo diretorio
        }
    
    FILE* ArqQry = fopen(pathQry, "r");
    if(ArqQry == NULL)
    {
        printf("Nao foi possivel abrir o .Qry!\n");
        exit(1);
    }
    char CopiaLinha[150];
    char linha[150];
    char lixo[8];//Nessa variavel vai o inicio dos comandos

    //Variaveis do QRY
    char ID[70],sfx[70],auxiliar[50];
    double Px,Py,Largu,Altu,area,X2,Y2,W2,H2,Double_aux=0,varianCia,valor;
    char Cpf[20],cpfAux[20];
    char Cep[30],complemento[10];
    char face[6],faceAux[6];
    int numero,existe;
    Noh nodeAVL;
    nohInterno nodeTabela;
    Lista listaAux;
    
    nodeAVL=GetFirstAVL(AVL);
    AtualizaMinMax(nodeAVL);
    printf("\nRealizando leitura do .qry . . .");
    while (fgets(linha, sizeof(linha), ArqQry) != NULL)//varre o arquivo linha por linha
    {
        sprintf(CopiaLinha, "%s", linha);//Copia tudo da linha pro CopiaLinha

        existe=0;
        if (strcmp(strtok(linha, " "), "del") == 0)
        {
            sscanf(CopiaLinha, "%s %s",lixo, Cep);
            existe=0;
            nodeAVL=GetFirstAVL(AVL);//pega a raiz da arvore
            PegaX_CEP(nodeAVL,Cep,&Px,&existe);//pego o x do cep
            if(existe)
            {
                if(remove_ArvAVL(AVL,Px,Cep,&varianCia,&Py,&Largu,&Altu))//os argumentos com endereco vao receber as coordenadas da quadra removid
                {
                    Saidas(TxtSaida,"Quadra:",Cep,"foi removida!","","",-1,"","","","del",-1);
                    criaLinha((Largu/2.0)+varianCia,(Altu/2.0)+Py,(Largu/2.0)+varianCia,Py-(varianCia/2.0),"red",svg);//cria linha no centro da quadra
                    TextoSvg((Largu/2.0)+varianCia,Py-(varianCia/2.0),Cep,svg);//escreve cep ao lado da linha

                    AnalisaTabela(Tabela1,listaAux,AVL,2,"del",TxtSaida,svg,Cep);//remove as pessoas/moradores e reporta no txt
                    AnalisaTabela(Tabela2,listaAux,AVL,3,"del",TxtSaida,svg,Cep);//remove as locacoes e reporta no txt
                    nodeAVL=GetFirstAVL(AVL);
                    AtualizaMinMax(nodeAVL);//atualiza o min e o max de todos os nohs da arvore
                }
            }else
                Saidas(TxtSaida,"CEP:",Cep,"Não Existe!",".",".",0,".",".",".","del",-1);//cep nao existe
        }

        if (strcmp(strtok(linha, " "), "m?") == 0)//completa
        {
            sscanf(CopiaLinha, "%s %s ",lixo, Cep);
            existe=0;
            nodeAVL=GetFirstAVL(AVL);//pega a raiz da arvore
            ExisteCEP(nodeAVL,Cep,&existe);//verifica se o cep existe na arvore
            if(existe)//o cep passado existe na arvore
                PercorreTabela(Tabela1,Px,Py,Largu,Altu,Cep,".",0,TxtSaida,svg,&existe,"m?",&Double_aux);//percorre a tabela listando os dados de quem morar na quadra cep
            else
                Saidas(TxtSaida,"CEP:",Cep,"Não Existe!",".",".",0,".",".",".","m?",-1);
        }

        if (strcmp(strtok(linha, " "), "dm?") == 0)//completa
        {
            sscanf(CopiaLinha, "%s %s ",lixo, Cpf);
            existe=0;
            PercorreTabela(Tabela1,Px,Py,Largu,Altu,Cep,Cpf,1,TxtSaida,svg,&existe,"dm?",&Double_aux);//vai procurar a pessoa cpf, escrever os dados dela no svg e copiar o cep pra variavel cep
            if(existe)//o cpf passado existe, entao vou procurar os valores de x e y da quadra cep pra desenhar no svg a linha
            {
                existe=0;
                nodeAVL=GetFirstAVL(AVL);//pega a raiz da arvore
                BuscaAVL(nodeAVL,Cep,&Px,&Py,&Largu,&Altu,&existe);//vai percorrer a arvore em busca do cep e vai atribuir pra px e py os valores de x e y da quadra cep
                existe=0;
                PercorreTabela(Tabela1,Px,Py,Largu,Altu,Cep,Cpf,2,TxtSaida,svg,&existe,"dm?",&Double_aux);
            }
        }

        if (strcmp(strtok(linha, " "), "mud") == 0)//completa
        {
            sscanf(CopiaLinha, "%s %s %s %s %d %s ",lixo, Cpf, Cep, face, &numero, complemento);
            existe=0;
            if(existeChave(Tabela1,Cpf))//se a pessoa cpf existe
            {
                nodeAVL=GetFirstAVL(AVL);
                ExisteCEP(nodeAVL,Cep,&existe);//verifica se o cep passado existe
                strcpy(cpfAux,Cpf);//copio pra cpfAux o cpf do morador q vai se mudar
              
                if(existe==1)//caso ele exista realiza a consulta
                {
                    PercorreTabela(Tabela1,Px,Py,Largu,Altu,auxiliar,Cpf,3,TxtSaida,svg,&existe,"mud",&Double_aux);//printo no txt os dados do morador e o endereco antigo
                    Saidas(TxtSaida,"","","","","",numero,complemento,Cep,face,"mud",3);//printo no txt o endereco novo
                    strcpy(faceAux,Cpf);
                    existe=0;
                    nodeAVL=GetFirstAVL(AVL);
                    Px=0;
                    Py=0;
                    Largu=0;
                    Altu=0;
                    BuscaAVL(nodeAVL,auxiliar,&Px,&Py,&Largu,&Altu,&existe);//vai pegar as coordenadas x,y,w,h da quadra cep antigo
                    
                    existe=0;//cpf esta com o valor da face do endereco antigo
                    nodeAVL=GetFirstAVL(AVL);
                    BuscaAVL(nodeAVL,Cep,&X2,&Y2,&W2,&H2,&existe);//vai pegar os valores de x,y,w,h da quadra cep novo
                    DesenhaEndereco(Px,Py,Largu,Altu,0.0,0.0,Double_aux,"",faceAux,1,svg);//cria o circulo no endereco antigo
                    varianCia= (double) numero;//converto o numero da residencia pra double e atribuo a variavel variancia
                    DesenhaEndereco(X2,Y2,W2,H2,0.0,0.0,varianCia,"",face,2,svg);//cria o circulo no endereco novo
                    AlteraEndereco(Tabela1,cpfAux,Cep,face,complemento,numero);//altero o endereco da pessoa cpf pro novo endereco
                    if(strcmp(face,"S")==0){
                        X2=X2+varianCia;
                        Y2=Y2+1.30;
                    }

                    if(strcmp(face,"N")==0){
                        X2=X2+varianCia;
                        Y2=(Y2+H2)-1.30;
                    }

                    if(strcmp(face,"L")==0){
                        X2=X2+1.30;
                        Y2=Y2+varianCia;
                    }

                    if(strcmp(face,"O")==0){
                        X2=(X2+W2)-1.30;
                        Y2=Y2+varianCia;
                    }
                    DesenhaEndereco(Px,Py,Largu,Altu,X2,Y2,Double_aux,"",faceAux,3,svg);//desenha a linha 
                }else
                    Saidas(TxtSaida,"CEP:",Cep,"Não Existe!",".",".",0,".",".",".","mud",-1);//caso o cep nao exista aparece no txt
            }else
                Saidas(TxtSaida,"CPF:",Cpf,"não existe!",".",".",0,".",".",".","mud",-1);
        }

        if (strcmp(strtok(linha, " "), "oloc") == 0)
        {
            sscanf(CopiaLinha, "%s %s %s %s %d %s %lf %lf",lixo, ID, Cep, face, &numero, complemento, &area, &valor);
            insereRegistro(Tabela2,ID,"",Cep,"","",".","",face,complemento,numero,ID,valor,area,0);//insere a locacao na tabela de locacoes
            nodeTabela=GetNohInterno(Tabela2,ID);//pega o noh da tabela q tem o id passado na oloc
            if(nodeTabela != NULL)
                AtribuiPonteiro(AVL,nodeTabela);//atribui o endereco no void pointer, da quadra cep da arvore/lista
        }

        if (strcmp(strtok(linha, " "), "oloc?") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf %lf",lixo, &Px, &Py, &Largu, &Altu);
            listaAux= Create();//crio uma lista pra colocar o cep das quadras que estiverem dentro da regiao
            nodeAVL=GetFirstAVL(AVL);
            PercorreAVL(nodeAVL,listaAux,Px,Py,Largu,Altu);
            AnalisaTabela(Tabela2,listaAux,AVL,1,"oloc?",TxtSaida,svg,".");//percorre a tabela reportando os dados no txt e desenhando moradia do morador
            liberalist(listaAux);//libera a lista temporaria
            criaBoundingBox(Px,Py,Largu,Altu,"red",svg);
        }

        if (strcmp(strtok(linha, " "), "loc") == 0)
        {
            sscanf(CopiaLinha, "%s %s %s",lixo, ID, Cpf);
            loc(Tabela1,Tabela2,ID,Cpf,TxtSaida,svg,0,"loc");
        }

        if (strcmp(strtok(linha, " "), "loc?") == 0)
        {
            sscanf(CopiaLinha, "%s %s",lixo, ID);
            loc(Tabela1,Tabela2,ID,".",TxtSaida,svg,1,"loc?");
        }

        if (strcmp(strtok(linha, " "), "dloc") == 0)
        {
            sscanf(CopiaLinha, "%s %s",lixo, ID);
            loc(Tabela1,Tabela2,ID,".",TxtSaida,svg,2,"dloc");
        }

        if (strcmp(strtok(linha, " "), "hom") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf %lf",lixo, &Px, &Py, &Largu, &Altu);
            listaAux= Create();//crio uma lista pra colocar o cep das quadras que estiverem dentro da regiao
            nodeAVL=GetFirstAVL(AVL);
            PercorreAVL(nodeAVL,listaAux,Px,Py,Largu,Altu);//vai percorrer a arvore inserindo na lista os ceps que estiverem dentro da regiao
            AnalisaTabela(Tabela1,listaAux,AVL,0,"hom",TxtSaida,svg,".");//percorre a tabela reportando os dados no txt e desenhando moradia do morador
            liberalist(listaAux);//libera a lista temporaria
            criaBoundingBox(Px,Py,Largu,Altu,"red",svg);
        }

        if (strcmp(strtok(linha, " "), "mul") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf %lf",lixo, &Px, &Py, &Largu, &Altu);
            listaAux= Create();//crio uma lista pra colocar o cep das quadras que estiverem dentro da regiao
            nodeAVL=GetFirstAVL(AVL);
            PercorreAVL(nodeAVL,listaAux,Px,Py,Largu,Altu);//vai percorrer a arvore inserindo na lista os ceps que estiverem dentro da regiao
            AnalisaTabela(Tabela1,listaAux,AVL,0,"mul",TxtSaida,svg,".");//percorre a tabela reportando os dados no txt e desenhando moradia do morador
            liberalist(listaAux);//libera a lista temporaria
            criaBoundingBox(Px,Py,Largu,Altu,"red",svg);
        }

        if (strcmp(strtok(linha, " "), "dmpt") == 0)//falta só imprimir o cep de algumas quadras, min e max
        {
            sscanf(CopiaLinha, "%s %s",lixo, sfx);
            char* arqDot=NULL;
            arqDot= (char *) malloc((strlen(qrySemExt)+strlen(geo)+strlen(diretSaida)+strlen(sfx)+8) * sizeof(char));
            sprintf(arqDot, "%s/%s-%s-%s.dot",diretSaida,geo,qrySemExt,sfx);//Concantena nome do arquivo txt de saida

            nodeAVL=GetFirstAVL(AVL);
            AtualizaMinMax(nodeAVL);
            ManipulacaoDot(AVL,arqDot);
            free(arqDot);
        }

        if (strcmp(strtok(linha, " "), "catac") == 0)
        {
            sscanf(CopiaLinha, "%s %lf %lf %lf %lf",lixo, &Px, &Py, &Largu, &Altu);
            listaAux= Create();
            nodeAVL=GetFirstAVL(AVL);
            PercorreAVL(nodeAVL,listaAux,Px,Py,Largu,Altu);//percorro a arvore analisando quais quadras estao dentro da regiao
            RemoveQuadrasLista(listaAux,AVL);//percorro a lista dos ceps removendo os ceps da arvore

            nodeAVL=GetFirstAVL(AVL);
            AtualizaMinMax(nodeAVL);
            AnalisaTabela(Tabela1,listaAux,AVL,3,"catac",TxtSaida,svg,Cep);//percorro a tabela das pessoas/moradores removendo quem mora em uma quadra removida
            AnalisaTabela(Tabela2,listaAux,AVL,3,"catac",TxtSaida,svg,Cep);//percorro a tabela de locacoes removendo as ofertas de locacoes
            criaRetangulo(Largu,Altu,Px,Py,"#AA0044","#AB37C8","1.0px",svg);
            liberalist(listaAux);
        }
        
    }//Fim leitura .qry 
    nodeAVL=GetFirstAVL(AVL);
    AtualizaMinMax(nodeAVL);

    nodeAVL=GetFirstAVL(AVL);
    SvgAVL(nodeAVL,svg);//printa as quadras no svg
    fclose(ArqQry);//Fecha o qry, apos ler e realizar as consultas
    free(pathQry);//free no path do qry
    printf("\nVariaveis liberadas, saiu do qry!");
}