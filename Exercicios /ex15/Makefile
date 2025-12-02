# Compilador
CXX = g++
SRC = ex14.cpp
OUT = ex15
CXXFLAGS = -Wall -g

# Compilar tudo
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Rodar o caso teste 1
test: all
	./$(OUT) < "Casos de Teste - 15/1.in"


# Executar o binário
run: all
	./$(OUT)

# Limpar arquivos gerados
clean:
	rm -f $(OUT)
