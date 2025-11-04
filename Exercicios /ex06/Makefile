CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra
TARGET = Colar
SOURCE = Colar.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

test: $(TARGET)
	@echo "Testando todos os casos..."
	@for i in 1 2 3 4 5 6 7 8; do \
		echo "=== Teste $$i ==="; \
		./$(TARGET) < "Casos de Teste - Exercicio 06_ O Colar Ancestral/$$i.in" > temp_out; \
		if diff temp_out "Casos de Teste - Exercicio 06_ O Colar Ancestral/$$i.out" > /dev/null; then \
			echo "✓ Passou"; \
		else \
			echo "✗ Falhou"; \
		fi; \
	done
	@rm -f temp_out

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) temp_out

.PHONY: test clean run
