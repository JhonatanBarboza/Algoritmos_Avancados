# Compilador
CXX = g++

# Arquivo fonte
SRC = ex2.cpp

# Executável
OUT = ex2

# Opções de compilação
CXXFLAGS = -Wall -g

# Compilar (regra padrão)
make: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Executar
run: $(OUT)
	./$(OUT)

# Limpar arquivos gerados
clean:
	rm -f $(OUT)
