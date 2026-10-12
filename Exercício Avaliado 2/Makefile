# ============================================================
# Arquivo: Makefile
# Descrição: Automatiza a compilação do programa.
# Uso: mingw32-make         -> compila tudo
#      mingw32-make clean   -> remove arquivos objeto e executável
# ============================================================

CXX = g++                                # Compilador a ser usado.
CXXFLAGS = -Wall -std=c++11              # Flags: avisos + padrão C++11.

# Lista dos arquivos objeto que serão gerados.
OBJ = main.o vertice.o aresta.o grafo.o

# Alvo padrão: gera o executável "programa".
all: programa

# O executável depende de todos os objetos.
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o programa $(OBJ)

# Compila main.cpp, dependendo do cabeçalho grafo.h.
main.o: main.cpp grafo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila vertice.cpp, dependendo do cabeçalho vertice.h.
vertice.o: vertice.cpp vertice.h
	$(CXX) $(CXXFLAGS) -c vertice.cpp

# Compila aresta.cpp, dependendo de aresta.h e vertice.h.
aresta.o: aresta.cpp aresta.h vertice.h
	$(CXX) $(CXXFLAGS) -c aresta.cpp

# Compila grafo.cpp, dependendo de grafo.h, vertice.h e aresta.h.
grafo.o: grafo.cpp grafo.h vertice.h aresta.h
	$(CXX) $(CXXFLAGS) -c grafo.cpp

# Alvo para limpeza: remove os .o e o executável no Windows.
clean:
	del /Q *.o programa.exe 2>nul