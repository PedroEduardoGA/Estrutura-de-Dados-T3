# Projeto T3 - Estrutura de Dados II
*Foi utilizado o sistema operacional Windows 7 no desenvolvimento do projeto, para o funcionamento do mesmo, todos os arquivos.c e arquivos.h são compilados executando o comando make no terminal, então o makefile será executado realizando a compilação de todos os códigos e gerando um executável para o projeto: **t1**, t1 pois foi o primeiro trabalho desenvolvido na disciplina de Estrutura de Dados II, para utilizar o projeto é necessário informar parâmetros de entrada via argumentos pela linha de comando no terminal, cmd ou PowerShell, exemplo:*

### ./t1 -e DiretórioEntrada -f nome_arquivo.geo -q SubDiretório/nome_arquivo.qry -pm nome_arquivo.pm -o DiretórioSaida
---
*Em resumo o projeto recebe um arquivo .geo que contém coordenadas para geração de retângulos(Quadras), um arquivo .pm que contém coordenadas e dados de circulos(Pessoas/moradores) e um arquivo .qry que contém consultas para serem realizadas com estes dados informados no arquivo .geo e no arquivo .pm, o projeto utiliza as seguintes estruturas de dados: **Arvore KD**, **Lista Dinâmica** e **HashTable**, o projeto gera no diretório de saída arquivos .svg e .txt para mostrar os resultados das consultas realizadas ao longo da execução. Alguns exemplos de consultas são remoções de retângulos, deslocamento de circulos(com animação) para dentro de retângulos de acordo com a nova localidade informada, desenho da arvore e seu estado atual em um arquivo .dot e consultas informativas.*

*No arquivo.geo temos como argumentos:*
- **nx** (Informa a estimativa de pessoas a ser informadas no arquivo .pm, este valor nx é usado para alocação dinâmica da HashTable)
- **q** (Informa os parâmetros de um retângulo a ser inserido na Arvore KD)
- **cq** (Informa as cores de preenchimento e de borda a serem usadas nos retângulos e uma espressura)  
*Após a leitura do .geo os retângulos informados são inseridos na arvore KD e é gerado um arquivo .svg inicial que contém os retângulos desenhados.*

*No arquivo.pm temos como argumentos:*
- **p** (Informa os dados de uma pessoa, os dados são inseridos em uma HashTable)
- **m** (Informa o cpf de um morador, então será buscado o cpf na HashTable e nesse registro será armazenados as informações de moradia informadas) 

*No arquivo.qry temos 13 consultas:*
- **del** (Informa um CEP e a quadra que tiver esse CEP e todos seus moradores e locações serão removidos)
- **m?** (Informa um CEP e  vai listar os dados de todos moradores que residirem nessa quadra CEP)
- **dm?** (Informa um CPF, vai listar todos dados da pessoa/morador que possuir esse CPF informado)
- **mud** (É informado um CPF e dados de moradia, a pessoa/morador que possuir esse CPF se mudará para a nova localização informada, os dados no registro serão alterados)
- **oloc** (Cria uma nova oferta de locação, são informados dados de moradia como CEP, nº, complemento e valores)
- **oloc?** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa vai informar as ofertas de locação disponíveis nessa região)
- **loc** (É informado um *id* e um *CPF*, então a pessoa/morador identificado pelo  CPF vai ser o novo "inquelino" do imóvel identificado pelo ID)
- **loc?** (Informa um *id* e programa mostra os dados do imóvel identificado por esse ID)
- **dloc** (Informa um *id* e o imóvel identificado por esse ID é removido)
- **hom** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa vai listar todos moradores do sexo *masculino* que residirem nessa região)
- **mul** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa vai listar todos moradores do sexo *feminino* que residirem nessa região)
- **dmpt** (Informa um "sufixo" que será usado para nomear um arquivo .dot que vai exibir o estado atual da Arvore KD que estiver sendo usada em um arquivo de saida com o nome no formato: nome_arquivoQRY-sufixo.dot)
- **catac** (Informa uma região(Coordenadas x,y e dimensões de largura e altura) e o programa vai remover todas as quadras, ofertas de locação e moradores que estiverem dentro dessa região informada)

### Resumo dos Parâmetros do programa:
|  Argumento  | Opcional  |    Descrição   |
| :---         |     :---:      |          ---: |
| -e diretórioEntrada   | Sim     | Informa o caminho para o diretório de entrada(Caso exista) que contém os arquivos de entrada do programa    |
| -f nome_arquivo.geo    | Não      | Informa o nome do arquivo.geo que contém os dados iniciais para execução do programa      |
| -q Subdir/nome_arquivo.qry   | Sim    | Informa o subdiretório(Caso esteja em um) e o nome do arquivo.qry que contém os parâmetros de consulta para ser utilizado com um arquivo.geo informado posteriormente    |
| -pm nome_arquivo.pm    | Sim      | Informa o nome do arquivo.pm que contém os dados das pessoas/moradores para execução do programa, não pode estar em um subdiretório, deve estar no mesmo diretório do arquivo.geo      |
| -o diretórioSaída   | Não     | Informa o caminho para o diretório de saída que será usado para armazenas os arquivos gerados ao longo da execução do programa    |



