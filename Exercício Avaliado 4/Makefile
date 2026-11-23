# ============================================================
# Arquivo: Makefile
# Descricao: Automatiza a compilacao do programa da Biblioteca.
# Uso: make          -> compila tudo (Linux / Mac)
#      mingw32-make  -> compila tudo (Windows)
#      make clean    -> remove arquivos objeto e executavel
# Compativel com Windows (mingw32-make) e Linux/Mac (make).
# ============================================================

CXX = g++
CXXFLAGS = -Wall -std=c++11

# Detecta o sistema operacional para definir comandos de limpeza e extensao.
ifeq ($(OS), Windows_NT)
    RM = del /Q
    EXE = programa.exe
else
    RM = rm -f
    EXE = programa
endif

# Lista dos arquivos objeto que serao gerados na compilacao.
OBJ = main.o item_acervo.o livro.o periodico.o dvd.o biblioteca.o

# Alvo padrao: gera o executavel final.
all: programa

# O executavel depende de todos os arquivos objeto.
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

# Compila main.cpp.
main.o: main.cpp biblioteca.h lista.h item_acervo.h livro.h periodico.h dvd.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila item_acervo.cpp.
item_acervo.o: item_acervo.cpp item_acervo.h
	$(CXX) $(CXXFLAGS) -c item_acervo.cpp

# Compila livro.cpp.
livro.o: livro.cpp livro.h item_acervo.h
	$(CXX) $(CXXFLAGS) -c livro.cpp

# Compila periodico.cpp.
periodico.o: periodico.cpp periodico.h item_acervo.h
	$(CXX) $(CXXFLAGS) -c periodico.cpp

# Compila dvd.cpp.
dvd.o: dvd.cpp dvd.h item_acervo.h
	$(CXX) $(CXXFLAGS) -c dvd.cpp

# Compila biblioteca.cpp.
biblioteca.o: biblioteca.cpp biblioteca.h lista.h item_acervo.h livro.h periodico.h dvd.h
	$(CXX) $(CXXFLAGS) -c biblioteca.cpp

# Alvo para limpeza: funciona tanto no Windows quanto no Linux/Mac.
clean:
	$(RM) *.o $(EXE)