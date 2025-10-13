#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

// Função para calcular a soma total de pedras no intervalo [i, j]
int somaTotal(const vector<int>& valores, int i, int j) {
    int soma = 0;
    for (int k = i; k <= j; k++) {
        soma += valores[k];
    }
    return soma;
}

// Função de programação dinâmica para calcular a pontuação máxima
int calcularPontuacaoMaxima(const vector<int>& valores, int i, int j, vector<vector<int>>& memo) {
    // Caso base: não há pedras restantes
    if (i > j) {
        return 0;
    }
    
    // Se já calculamos este subproblema, retornamos o resultado
    if (memo[i][j] != -1) {
        return memo[i][j];
    }
    
    // Caso base: apenas uma pedra
    if (i == j) {
        memo[i][j] = valores[i];
        return valores[i];
    }
    
    // Opção 1: Pegar a pedra do inicio (posição i)
    int somaRestante1 = somaTotal(valores, i + 1, j);
    int pontosOponente1 = calcularPontuacaoMaxima(valores, i + 1, j, memo);
    int resultado1 = valores[i] + (somaRestante1 - pontosOponente1);
    
    // Opção 2: Pegar a pedra do final (posição j)
    int somaRestante2 = somaTotal(valores, i, j - 1);
    int pontosOponente2 = calcularPontuacaoMaxima(valores, i, j - 1, memo);
    int resultado2 = valores[j] + (somaRestante2 - pontosOponente2);
    
    // Escolher a melhor opção
    memo[i][j] = max(resultado1, resultado2);
    return memo[i][j];
}

int main() {
    int X; // Número de casos de teste
    cin >> X;
    cin.ignore(); // Ignorar a quebra de linha após o número
    
    for (int caso = 0; caso < X; caso++) {
        int N; // Número de pedras
        cin >> N;
        cin.ignore();
        
        string linha;
        getline(cin, linha);
        
        vector<int> valores(N);
        
        // Processar a linha de entrada
        stringstream ss(linha);
        string pedra;
        int idx = 0;
        
        while (ss >> pedra && idx < N) {
            // Remover parênteses e processar os números
            int a, b;
            char lixo;
            stringstream pedraStream(pedra);
            pedraStream >> lixo >> a >> lixo >> b >> lixo;
            valores[idx] = a + b;
            idx++;
        }
        
        // Criar tabela de memoização
        vector<vector<int>> memo(N, vector<int>(N, -1));
        
        // Calcular a pontuação máxima que Maria pode obter
        int resultado = calcularPontuacaoMaxima(valores, 0, N - 1, memo);
        
        cout << resultado << endl;
    }
    
    return 0;
}