# Compilador
CXX = g++
SRC = ex7_DP.cpp
OUT = ex7
CXXFLAGS = -Wall -g

# Compilar tudo
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Rodar o caso teste 1
test1: all
	./$(OUT) < "Casos de Teste - Ex7/2.in"


# Executar o binário
run: all
	./$(OUT)

# Limpar arquivos gerados
clean:
	rm -f $(OUT)
