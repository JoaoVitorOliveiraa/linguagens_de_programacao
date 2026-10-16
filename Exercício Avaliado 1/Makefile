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
OBJ = main.o leitura_sensor.o estacao.o sistema_meteorologico.o

# Alvo padrão: gera o executável.
all: programa

# O executavel depende dos objetos
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

# Compila main.cpp
main.o: main.cpp sistema_meteorologico.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila leitura_sensor.cpp
leitura_sensor.o: leitura_sensor.cpp leitura_sensor.h
	$(CXX) $(CXXFLAGS) -c leitura_sensor.cpp

# Compila estacao.cpp
estacao.o: estacao.cpp estacao.h leitura_sensor.h
	$(CXX) $(CXXFLAGS) -c estacao.cpp

# Compila sistema_meteorologico.cpp
sistema_meteorologico.o: sistema_meteorologico.cpp sistema_meteorologico.h estacao.h
	$(CXX) $(CXXFLAGS) -c sistema_meteorologico.cpp

# Alvo para limpeza: funciona em Windows e Linux.
clean:
	$(RM) *.o $(EXE)