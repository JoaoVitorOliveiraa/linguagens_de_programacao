# ============================================================
# Arquivo: Makefile
# Descricao: Automatiza a compilacao do programa.
# Uso: mingw32-make         -> compila tudo
#      mingw32-make clean   -> remove arquivos objeto e executavel
# ============================================================

CXX = g++                                # Compilador a ser usado.
CXXFLAGS = -Wall -std=c++11              # Flags: avisos + padrao C++11.

# Lista dos arquivos objeto que serao gerados.
OBJ = main.o vertice.o aresta.o grafo.o

# Alvo padrao: gera o executavel "programa".
all: programa

# O executavel depende de todos os objetos.
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o programa $(OBJ)

# Compila main.cpp, dependendo do cabecalho grafo.h.
main.o: main.cpp grafo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila vertice.cpp, dependendo do cabecalho vertice.h.
vertice.o: vertice.cpp vertice.h
	$(CXX) $(CXXFLAGS) -c vertice.cpp

# Compila aresta.cpp, dependendo de aresta.h e vertice.h.
aresta.o: aresta.cpp aresta.h vertice.h
	$(CXX) $(CXXFLAGS) -c aresta.cpp

# Compila grafo.cpp, dependendo de grafo.h, vertice.h e aresta.h.
grafo.o: grafo.cpp grafo.h vertice.h aresta.h
	$(CXX) $(CXXFLAGS) -c grafo.cpp

# Alvo para limpeza: remove os .o e o executavel no Windows.
clean:
	del /Q *.o programa.exe 2>nul