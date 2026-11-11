# ============================================================
# Arquivo: Makefile
# Descrição: Automatiza a compilação do projeto FinHealth AI.
# Uso: make          -> compila tudo
#      make run      -> compila e executa
#      make clean    -> remove arquivos objeto e executável
# Compatível com Windows (mingw32-make) e Linux (make).
# ============================================================

CXX = g++
CXXFLAGS = -Wall -std=c++17 -O2

# Lista dos arquivos objeto que serão gerados.
OBJ = main.o gerenciador_financeiro.o perfil_financeiro.o

# ============================================================
# DETECÇÃO DO SISTEMA OPERACIONAL E DO PYTHON
# ============================================================
ifeq ($(OS), Windows_NT)
    # --- Configurações para WINDOWS (MSYS2) ---
    RM = del /Q
    EXE = app_financeiro.exe
    # Caminho do Python no MSYS2 (ajuste a versão se necessário)
    PY_INC = -IC:/msys64/ucrt64/include/python3.10
    PY_LIB = -LC:/msys64/ucrt64/lib -lpython3.10
else
    # --- Configurações para LINUX ---
    RM = rm -f
    EXE = app_financeiro
    # Caminhos padrão do Linux (usa o pkg-config para descobrir a versão)
    PY_INC = $(shell pkg-config --cflags python3 2>/dev/null)
    PY_LIB = $(shell pkg-config --libs python3 2>/dev/null)
endif

# Bibliotecas extras (SQLite) e inclusões
LIBS = $(PY_LIB) -lsqlite3
INCLUDES = $(PY_INC)

# ============================================================
# ALVOS DE COMPILAÇÃO
# ============================================================

# Alvo padrão: gera o executável.
all: $(EXE)

# O executável depende de todos os objetos.
$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(EXE) $(OBJ) $(LIBS)
	@echo "=============================================="
	@echo " Compilacao concluida com sucesso! "
	@echo " Digite 'make run' para executar. "
	@echo "=============================================="

# Compila main.cpp
main.o: main.cpp gerenciador_financeiro.h perfil_financeiro.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp

# Compila gerenciador_financeiro.cpp
gerenciador_financeiro.o: gerenciador_financeiro.cpp gerenciador_financeiro.h perfil_financeiro.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c gerenciador_financeiro.cpp

# Compila perfil_financeiro.cpp
perfil_financeiro.o: perfil_financeiro.cpp perfil_financeiro.h
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c perfil_financeiro.cpp

# ============================================================
# ALVOS UTILITÁRIOS
# ============================================================

# Roda o programa
run: $(EXE)
ifeq ($(OS), Windows_NT)
	./$(EXE)
else
	./$(EXE)
endif

# Alvo para limpeza: funciona em Windows e Linux.
clean:
	$(RM) *.o $(EXE)
	@echo "Arquivos temporarios e executavel removidos."

# Declara alvos que não são arquivos
.PHONY: all clean run