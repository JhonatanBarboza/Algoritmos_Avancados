CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = Cartografo
SOURCE = Cartografo.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test: $(TARGET)
	@echo "Testando com caso de exemplo..."
	./$(TARGET) < teste.in

test-oficial: $(TARGET)
	@echo "Testando com todos os casos oficiais..."
	@for i in 1 2 3 4 5; do \
		echo "=== Teste $$i ==="; \
		./$(TARGET) < "Casos de Teste - Trabalho 02_ Projeto Cartografo Cosmico, Uma Tarefa para Lovelace/$$i.in" > temp_out; \
		if diff temp_out "Casos de Teste - Trabalho 02_ Projeto Cartografo Cosmico, Uma Tarefa para Lovelace/$$i.out" > /dev/null; then \
			echo "✓ Passou"; \
		else \
			echo "✗ Falhou"; \
			echo "--- Saída esperada ---"; \
			cat "Casos de Teste - Trabalho 02_ Projeto Cartografo Cosmico, Uma Tarefa para Lovelace/$$i.out"; \
			echo "--- Nossa saída ---"; \
			cat temp_out; \
			echo "--- Diferença ---"; \
			diff "Casos de Teste - Trabalho 02_ Projeto Cartografo Cosmico, Uma Tarefa para Lovelace/$$i.out" temp_out; \
		fi; \
	done
	@rm -f temp_out

clean:
	rm -f $(TARGET) temp_out

.PHONY: test test-oficial clean