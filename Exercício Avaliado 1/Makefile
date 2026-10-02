# ============================================================
# Arquivo: Makefile
# Descricao: Automatiza a compilacao do programa.
# Uso: make          -> compila tudo
#      make clean    -> remove arquivos objeto e executavel
# ============================================================

CXX = g++                        # Compilador a ser usado.
CXXFLAGS = -Wall -std=c++11      # Flags: avisos + padrao C++11.

# Lista dos arquivos objeto que serao gerados.
OBJ = main.o leitura_sensor.o estacao.o sistema_meteorologico.o

all: programa                    # Alvo padrao: gera o executavel "programa".

# Linka todos os objetos em um unico executavel.
programa: $(OBJ)                 # O executavel depende dos objetos.
	$(CXX) $(CXXFLAGS) -o programa $(OBJ)

# Compila main.cpp, dependendo do cabecalho.
main.o: main.cpp sistema_meteorologico.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Compila leitura_sensor.cpp.
leitura_sensor.o: leitura_sensor.cpp leitura_sensor.h
	$(CXX) $(CXXFLAGS) -c leitura_sensor.cpp

# Compila estacao.cpp.
estacao.o: estacao.cpp estacao.h leitura_sensor.h
	$(CXX) $(CXXFLAGS) -c estacao.cpp

# Compila sistema_meteorologico.cpp.
sistema_meteorologico.o: sistema_meteorologico.cpp sistema_meteorologico.h estacao.h
	$(CXX) $(CXXFLAGS) -c sistema_meteorologico.cpp

clean:                           # Alvo para limpeza.
	rm -f *.o programa           # Remove todos os objetos e o executavel.