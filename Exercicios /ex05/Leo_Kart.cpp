#include <bits/stdc++.h>
using namespace std;

// Estrutura para armazenar jogador com posições inicial e final
struct Jogador {
    int inicial, final, indice;
};

// Função para contar inversões usando merge sort
long long mergeAndCount(vector<int>& arr, int temp[], int left, int mid, int right) {
    int i = left, j = mid, k = left;
    long long inv_count = 0;
    
    while ((i <= mid - 1) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);
        }
    }
    
    while (i <= mid - 1) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = left; i <= right; i++) arr[i] = temp[i];
    
    return inv_count;
}

// Função para realizar merge sort e contar inversões
long long mergeSortAndCount(vector<int>& arr, int temp[], int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;
        
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);
        inv_count += mergeAndCount(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

// Função para calcular ultrapassagens em um trecho
long long calcularUltrapassagens(vector<Jogador>& jogadores) {
    int n = jogadores.size();
    
    // Ordenar por posição inicial
    sort(jogadores.begin(), jogadores.end(), [](const Jogador& a, const Jogador& b) {
        return a.inicial < b.inicial;
    });
    
    // Extrair posições finais na ordem das posições iniciais
    vector<int> posicoes_finais(n);
    for (int i = 0; i < n; i++) {
        posicoes_finais[i] = jogadores[i].final;
    }
    
    // Contar inversões nas posições finais (invrersões = ultrapassagens)
    vector<int> temp(n);
    return mergeSortAndCount(posicoes_finais, temp.data(), 0, n - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<pair<int, long long>> resultados; // pair<trecho, ultrapassagens>
    
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j;
        
        vector<Jogador> jogadores(j);
        
        for (int k = 0; k < j; k++) {
            cin >> jogadores[k].inicial >> jogadores[k].final;
            jogadores[k].indice = k;
        }
        
        long long ultrapassagens = calcularUltrapassagens(jogadores);
        resultados.push_back({i, ultrapassagens});
    }
    
    // Ordenar por número de ultrapassagens (decrescente)
    sort(resultados.begin(), resultados.end(), [](const pair<int, long long>& a, const pair<int, long long>& b) {
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });
    
    // Imprimir resultado
    for (const auto& resultado : resultados) {
        cout << resultado.first << " " << resultado.second << "\n";
    }
    
    return 0;
}