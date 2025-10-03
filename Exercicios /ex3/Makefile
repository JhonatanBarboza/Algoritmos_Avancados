# Compilador
CXX = g++
SRC = Guloso.cpp
OUT = Guloso
CXXFLAGS = -Wall -g

# Compilar tudo
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Rodar o teste
teste: all
	./teste.sh

# Executar o binário
run: all
	./$(OUT)

# Limpar arquivos gerados
clean:
	rm -f $(OUT)
