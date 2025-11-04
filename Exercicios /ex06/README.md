# Problema do Fecho Convexo e Algoritmo de Andrew

Este repositório contém implementações e visualizações relacionadas ao problema do **Fecho Convexo**, um conceito fundamental em geometria computacional.

## 1. O que é o Fecho Convexo? (Noção Intuitiva)

Imagine que você tem um conjunto de pregos espalhados em uma placa de madeira. Agora, pegue um elástico, estique-o e solte-o de forma que ele envolva todos os pregos. A forma que o elástico assume é o **fecho convexo**.

![Image](https://github.com/user-attachments/assets/a6b2a25a-f217-4c53-8a06-dbfc7c588f98)

De forma mais técnica, o fecho convexo de um conjunto de pontos `P` é o menor polígono convexo que contém todos os pontos de `P`. Os vértices deste polígono são sempre um subconjunto dos pontos originais.

## 2. O Algoritmo de Andrew (Monotone Chain)

O algoritmo de Andrew é um método eficiente para encontrar o fecho convexo de um conjunto de pontos. Ele funciona construindo as partes superior e inferior do fecho de forma independente.

Aqui está o passo a passo:

1.  **Ordenação dos Pontos**:
    *   Primeiro, todos os pontos são ordenados com base em suas coordenadas. A ordenação principal é pela coordenada **X** (da esquerda para a direita). Em caso de empate, a ordenação é feita pela coordenada **Y** (de baixo para cima).

2.  **Construção do Fecho Inferior**:
    *   Iteramos através dos pontos ordenados, da esquerda para a direita.
    *   Mantemos uma lista de pontos que formam o fecho inferior até o momento.
    *   Para cada novo ponto, verificamos se ele forma uma "curva à esquerda" com os dois últimos pontos do nosso fecho inferior.
        *   Se sim, o ponto é adicionado ao fecho.
        *   Se não (forma uma "curva à direita" ou é colinear), o último ponto do fecho é removido. Repetimos essa verificação até que a condição de "curva à esquerda" seja satisfeita.

3.  **Construção do Fecho Superior**:
    *   O processo é quase idêntico, mas desta vez iteramos através dos pontos na ordem **inversa** (da direita para a esquerda).
    *   Isso constrói a parte de cima do fecho, usando a mesma lógica de verificação de curvas.

4.  **Combinação**:
    *   Finalmente, o fecho inferior e o fecho superior são combinados para formar o fecho convexo completo. Os pontos inicial e final são duplicados no processo, então removemos as duplicatas.

O resultado é um polígono que representa o fecho convexo dos pontos originais.

## 3. Como Utilizar os Códigos

### `Colar.cpp`

Este arquivo é uma implementação em C++ que resolve o problema do "Colar de Pedras Ancestrais", uma variação do fecho convexo que também lida com pontos colineares na borda.

**Para compilar e executar:**

1.  **Compilação**: Abra um terminal no diretório do arquivo e execute o seguinte comando para compilar o código.
    ```bash
    g++ Colar.cpp -o Colar -std=c++11
    ```

2.  **Execução**: Após a compilação, execute o programa:
    ```bash
    ./Colar
    ```

3.  **Entrada de Dados**: O programa espera a entrada no seguinte formato:
    *   A primeira linha contém `T`, o número de casos de teste.
    *   Cada caso de teste começa com `N`, o número de pontos.
    *   Seguem `N` linhas, cada uma com as coordenadas `x` e `y` de um ponto.

    **Exemplo de Entrada:**
    ```
    1
    7
    1 1
    2 5
    3 3
    4 2
    5 4
    6 1
    7 3
    ```

4.  **Saída**: O programa imprimirá o tamanho do "colar" (o número de pontos no fecho) e as coordenadas das "pedras ancestrais" (os pontos do fecho).

### `animacao_andrew.html`

Este é um arquivo HTML que contém uma animação interativa e didática do algoritmo de Andrew.

**Para visualizar a animação:**

1.  **Servidor Local (Recomendado)**: Para garantir que tudo funcione corretamente, você pode iniciar um servidor web local simples. Abra um terminal no diretório do arquivo e execute:
    ```bash
    python3 -m http.server 8080
    ```
    Se você não tiver o Python 3, pode tentar com o Python 2:
    ```bash
    python -m SimpleHTTPServer 8080
    ```

2.  **Acesse no Navegador**: Abra seu navegador de internet (Chrome, Firefox, etc.) e acesse o seguinte endereço:
    ```
    http://localhost:8080/animacao_andrew.html
    ```
    *Observação: O nome do arquivo no URL deve ser exatamente o mesmo que está no seu sistema.*

3.  **Alternativa (Abrir Diretamente)**: Você também pode simplesmente clicar com o botão direito no arquivo `animacao_andrew.html` e escolher "Abrir com" -> "Seu Navegador".

**Funcionalidades da Animação:**

*   **Grade Interativa**: Clique na grade para adicionar seus próprios pontos.
*   **Carregar Exemplo**: Carrega um conjunto de pontos pré-definido.
*   **Controles de Animação**:
    *   `Iniciar`: Começa a animação passo a passo.
    *   `Próximo` / `Anterior`: Navega manualmente pelos passos do algoritmo.
    *   `Auto`: Inicia a execução automática.
    *   `Pausar`: Pausa a execução automática.
    *   `2X`: (Aparece no modo Auto) Acelera a animação.
*   **Painel de Explicação**: Um texto descreve o que está acontecendo em cada passo do algoritmo.
*   **Resetar**: Limpa a tela e reinicia a animação.
