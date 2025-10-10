#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
using namespace std;

// Hash personalizado para vector<long long>
struct VectorHash {
    size_t operator()(const vector<long long>& v) const {
        size_t seed = v.size();
        for (auto& i : v) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

unordered_map<vector<long long>, long long, VectorHash> memo;

// Função para simular cascata de forma mais eficiente
vector<long long> aplicarCascata(const vector<long long>& coluna, long long danoInicial) {
    if (coluna.empty()) return {};
    
    vector<long long> resultado = coluna;
    long long dano = danoInicial;
    int idx = 0;
    
    while (idx < resultado.size() && dano > 0) {
        if (resultado[idx] <= dano) {
            // Esta relíquia se desestabiliza
            dano = idx + 1; // nova altura para próxima cascata
            resultado.erase(resultado.begin() + idx);
            idx = 0; // reinicia
        } else {
            // Sobrevive mas sofre dano
            resultado[idx] -= dano;
            break;
        }
    }
    
    return resultado;
}

long long solve(vector<long long> relics) {
    if (relics.empty()) return 0;
    if (relics.size() == 1) return relics[0];
    
    // Verifica memoização
    auto it = memo.find(relics);
    if (it != memo.end()) {
        return it->second;
    }
    
    long long minBatidas = LLONG_MAX;
    
    // Para casos muito grandes, usa programação dinâmica diferente
    if (relics.size() > 50) {
        // Heurística: tenta apenas posições estratégicas
        vector<int> posicoes;
        
        // Adiciona posições com valores pequenos
        for (int i = 0; i < relics.size(); i++) {
            if (relics[i] <= 1000) {
                posicoes.push_back(i);
            }
        }
        
        // Se não há valores pequenos suficientes, adiciona algumas posições
        if (posicoes.size() < 20) {
            for (int i = 0; i < relics.size() && posicoes.size() < 30; i += max(1, (int)relics.size()/30)) {
                posicoes.push_back(i);
            }
        }
        
        // Remove duplicatas e ordena
        sort(posicoes.begin(), posicoes.end());
        posicoes.erase(unique(posicoes.begin(), posicoes.end()), posicoes.end());
        
        for (int i : posicoes) {
            long long batidas = relics[i];
            
            vector<long long> coluna1(relics.begin(), relics.begin() + i);
            vector<long long> coluna2;
            
            if (i + 1 < relics.size()) {
                vector<long long> temp(relics.begin() + i + 1, relics.end());
                coluna2 = aplicarCascata(temp, i + 1);
            }
            
            long long batidas1 = solve(coluna1);
            long long batidas2 = solve(coluna2);
            
            minBatidas = min(minBatidas, batidas + batidas1 + batidas2);
        }
    } else {
        // Para casos menores, testa todas as posições
        for (int i = 0; i < relics.size(); i++) {
            long long batidas = relics[i];
            
            vector<long long> coluna1(relics.begin(), relics.begin() + i);
            vector<long long> coluna2;
            
            if (i + 1 < relics.size()) {
                vector<long long> temp(relics.begin() + i + 1, relics.end());
                coluna2 = aplicarCascata(temp, i + 1);
            }
            
            long long batidas1 = solve(coluna1);
            long long batidas2 = solve(coluna2);
            
            minBatidas = min(minBatidas, batidas + batidas1 + batidas2);
        }
    }
    
    memo[relics] = minBatidas;
    return minBatidas;
}

int main() {
    int n;
    cin >> n;
    
    vector<long long> relics(n);
    for (int i = 0; i < n; i++) {
        cin >> relics[i];
    }
    
    cout << solve(relics) << endl;
    
    return 0;
}