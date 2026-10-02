# ============================================================
# Arquivo: Makefile
# Descricao: Automatiza a compilacao do programa.
# Uso: mingw32-make         -> compila tudo
#      mingw32-make clean   -> remove arquivos objeto e executavel
# ============================================================

CXX = g++
CXXFLAGS = -Wall -std=c++11

# Lista dos arquivos objeto que serao gerados
OBJ = main.o leitura_sensor.o estacao.o sistema_meteorologico.o

# Alvo padrao: gera o executavel "programa"
all: programa

# O executavel depende dos objetos
programa: $(OBJ)
	$(CXX) $(CXXFLAGS) -o programa $(OBJ)

# Compila main.cpp, dependendo do cabecalho
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

# Alvo para limpeza: remove os .o e o executavel
clean:
	del /Q *.o programa.exe 2>nul