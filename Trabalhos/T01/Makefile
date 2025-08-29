# Makefile para o projeto T01
# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2
TARGET = T01
SOURCE = T01.cpp

# Target padrão
all: $(TARGET)

# Compilar o programa
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos gerados
clean:
	rm -f $(TARGET)

# Recompilar tudo (clean + compile)
rebuild: clean all

# Targets que não são arquivos
.PHONY: all run clean rebuild