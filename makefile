PROJ_NAME=runSimGerenciadorProcessos

HEADERS=$(wildcard headers/*.h)

SOURCES=$(wildcard sources/*.c)

MAIN=main.c

all:
	@ gcc $(MAIN) $(SOURCES) -o $(PROJ_NAME)
	@ ./$(PROJ_NAME)
