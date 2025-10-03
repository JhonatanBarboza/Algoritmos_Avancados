# 🏎️ Leo Kart - Contador de Ultrapassagens

Uma solução otimizada para contar ultrapassagens em corridas de kart, desenvolvida para a disciplina **SCC0218 - Algoritmos Avançados e Aplicações** da USP.

![Image](https://github.com/user-attachments/assets/a9d93341-691d-4d8e-aadc-a596f151a297)

## 📋 Descrição do Problema

Dado um conjunto de trechos de corrida, cada um com jogadores que possuem posições inicial e final, o objetivo é:

1. **Contar** o número de ultrapassagens em cada trecho
2. **Ordenar** os trechos por quantidade de ultrapassagens (decrescente)
3. **Exibir** o resultado no formato: `trecho ultrapassagens`

Uma **ultrapassagem** ocorre quando dois jogadores se encontram em uma mesma posição durante a corrida (assumindo velocidade constante).

## 🧠 Como Funciona o Algoritmo

### Conceito Principal: Inversões
O problema de contar ultrapassagens é equivalente a **contar inversões**:
- Se jogador A estava atrás de B no início, mas termina à frente de B → **ultrapassagem!**

### Algoritmo Otimizado
```cpp
1. Ordenar jogadores por posição inicial
2. Extrair posições finais nesta ordem  
3. Contar inversões usando Merge Sort
```

**Complexidade:** `O(J log J)` por trecho, onde J = número de jogadores

### Exemplo Visual
```
Posições Iniciais: [0, 1, 2]
Jogadores:         [A, B, C]  
Posições Finais:   [6, 4, 5]

Inversões: A ultrapassou B (6 > 4) = 1 ultrapassagem
```

## 🚀 Como Usar

### Código C++

1. **Compilar:**
```bash
g++ -o leokart Leo_Kart.cpp
```

2. **Executar:**
```bash
./leokart
```

3. **Formato de Entrada:**
```
2                    # Número de trechos
2                    # Jogadores no trecho 1
0 6                  # Jogador 1: posição inicial 0, final 6  
1 4                  # Jogador 2: posição inicial 1, final 4
3                    # Jogadores no trecho 2
6 8                  # Jogador 1: posição inicial 6, final 8
0 9                  # Jogador 2: posição inicial 0, final 9  
2 5                  # Jogador 3: posição inicial 2, final 5
```

4. **Saída Esperada:**
```
1 2                  # Trecho 1: 2 ultrapassagens
0 1                  # Trecho 0: 1 ultrapassagem  
```

### Simulação Interativa (HTML)

1. **Abrir** o arquivo `leo_kart_animation.html` no navegador
2. **Configurar** número de jogadores e suas posições
3. **Ajustar** velocidade da animação (1x - 10x)
4. **Iniciar** a corrida e observar as ultrapassagens
5. **Ver** o resultado calculado pelo algoritmo otimizado

#### Funcionalidades da Simulação:
- ✅ Animação visual da corrida (direita → esquerda)
- ✅ Configuração personalizável de jogadores
- ✅ Controle de velocidade da animação
- ✅ Cálculo automático usando o algoritmo otimizado
- ✅ Interface moderna e responsiva

## 📊 Performance

| Método | Complexidade | Para J=100.000 |
|--------|-------------|----------------|
| Força Bruta | O(J²) | ~10¹⁰ operações |
| **Otimizado** | **O(J log J)** | **~17 operações** |

**Speedup:** ~6×10⁸ vezes mais rápido! 🚀