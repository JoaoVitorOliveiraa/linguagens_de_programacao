# ============================================================
# Arquivo: Makefile
# Descrição: Automatiza a compilação do programa.
# Uso: make          -> compila tudo
#      make clean    -> remove arquivos objeto e executável
# Compatível com Windows (mingw32-make) e Linux/Mac (make).
# ============================================================

CXX = g++
CXXFLAGS = -Wall -std=c++11

# Detecta o sistema operacional.
ifeq ($(OS), Windows_NT)
    RM = del /Q
    EXE = programa.exe
else
    RM = rm -f
    EXE = programa
endif

# Lista dos arquivos objeto que serão gerados.
OBJ = main.o vertice.o aresta.o grafo.o

# Alvo padrão: gera o executável.
all: programa

# O executável depende de todos os objetos.
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

# Compila main.cpp.
main.o: main.cpp grafo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila vertice.cpp.
vertice.o: vertice.cpp vertice.h
	$(CXX) $(CXXFLAGS) -c vertice.cpp

# Compila aresta.cpp.
aresta.o: aresta.cpp aresta.h vertice.h
	$(CXX) $(CXXFLAGS) -c aresta.cpp

# Compila grafo.cpp.
grafo.o: grafo.cpp grafo.h vertice.h aresta.h
	$(CXX) $(CXXFLAGS) -c grafo.cpp

# Alvo para limpeza: funciona em Windows e Linux.
clean:
	$(RM) *.o $(EXE)