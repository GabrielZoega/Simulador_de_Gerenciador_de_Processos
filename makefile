PROJ_NAME=runSimGerenciadorProcessos

HEADERS=$(wildcard headers/*.h)

SOURCES=$(wildcard sources/*.c)

MAIN=main.c

all:
	gcc $(MAIN) $(HEADERS) $(SOURCES) -o $(PROJ_NAME)