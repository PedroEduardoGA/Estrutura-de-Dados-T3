#nome do executável
PROGRAMA = t1

#arquivos .c
C_FILES = $(wildcard *.c)
#wildcard é usado para listar todos os arquivos-fonte no diretório atual
#Se der erro trocar o diretorio antes do *.c, exemplo projeto 1 ficou (wildcard src/*.c)

#arquivos .h
H_FILES = $(wildcard *.h)

OBJ = $(C_FILES:.c=.o)
#gera a lista de arquivos-objeto usando a lista de arquivos-fonte

#compilador
CC = gcc

#flags para o compilador
FLAGS = -Wall -ansi -pedantic -std=c99 -fstack-protector-all -g

#-Wall: ativa vários avisos que não são ativados normalmente. Pode dar alguns conselhos úteis.
#-ansi: compila seu programa estritamente de acordo com o padrão ANSI, desativando qualquer extensão específica do gcc.
#-pedantic: ativa alguns avisos que existem de acordo com o padrão C mas que são desativados normalmente por extensões do gcc.
#-g: inclui no arquivo executável os elementos utilizados pelos programas de depuração, como o gdb ou ddd.


#ligação com as bibliotecas
LINKER_FLAGS = -lm

#
#linking e compilaçao
#

all: $(PROGRAMA)

$(PROGRAMA): $(OBJ)
	$(CC) -o $@ $^ $(FLAGS) $(LINKER_FLAGS)

%.o: %.c %.h
	$(CC) -o $@ $< -c $(FLAGS) $(LINKER_FLAGS)

main.o: main.c $(H_FILES)
	$(CC) -o $@ $< -c $(FLAGS)

clean:
	rm -rf *.o $(PROGRAMA) *~

run: $(PROGRAMA)
	./$(PROGRAMA)

#*~: arquivos de backup
#$@ equivale ao nome completo do target
#$? dependências que são mais novas que o target
#$* string que corresponde ao % no target
#$< equivale ao primeiro elemento na lista de dependências
#$^ lista de todas as dependências, separadas por espaço
#%: pega o stem (tronco) do nome, que é utilizado de referência no pré-requisito. Por exemplo, se o target é helloWorld.o, o stem será helloWorld, consequentemente o pré-requisito será helloWorld.c e helloWorld.h.

