# ============================================================
# Arquivo: Makefile
# Descrição: Automatiza a compilação do programa de Estoque.
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
OBJ = main.o estoque.o

# Alvo padrão: gera o executável.
all: programa

# O executável depende de todos os objetos.
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

# Compila main.cpp.
main.o: main.cpp estoque.h componente.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila estoque.cpp.
estoque.o: estoque.cpp estoque.h componente.h
	$(CXX) $(CXXFLAGS) -c estoque.cpp

# Alvo para limpeza: funciona em Windows e Linux.
# Nota: Adicionando o estoque.txt aqui para que o 'make clean' 
# também apague o arquivo de persistência, permitindo testar o 
# programa do zero.
clean:
	$(RM) *.o $(EXE) estoque.txt