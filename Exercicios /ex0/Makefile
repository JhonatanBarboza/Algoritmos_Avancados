# Compilador
CXX = g++

# Arquivo fonte
SRC = Quitanda.cpp

# Executável
OUT = Quitanda

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
