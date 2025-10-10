#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <climits>
using namespace std;

map<vector<long long>, long long> memo;

long long solve(vector<long long> relics) {
    if (relics.empty()) return 0;
    if (relics.size() == 1) return relics[0];
    
    // Verifica se já foi computado
    if (memo.find(relics) != memo.end()) {
        return memo[relics];
    }
    
    long long minBatidas = LLONG_MAX;
    
    // Tenta desestabilizar cada relíquia
    for (int i = 0; i < relics.size(); i++) {
        long long batidas = relics[i]; // Batidas necessárias para desestabilizar esta relíquia
        
        // Cria as novas colunas após a desestabilização
        vector<long long> coluna1, coluna2;
        
        // Primeira coluna: relíquias abaixo da desestabilizada
        for (int j = 0; j < i; j++) {
            coluna1.push_back(relics[j]);
        }
        
        // Segunda coluna: relíquias acima da desestabilizada (se houver)
        if (i + 1 < relics.size()) {
            for (int j = i + 1; j < relics.size(); j++) {
                coluna2.push_back(relics[j]);
            }
            
            // Aplica o efeito cascata na segunda coluna
            if (!coluna2.empty()) {
                long long danoQueda = i + 1; // altura da relíquia desestabilizada
                int idx = 0;
                
                // Processa a cascata
                while (idx < coluna2.size() && danoQueda > 0) {
                    if (coluna2[idx] <= danoQueda) {
                        // Esta relíquia também se desestabiliza
                        danoQueda = idx + 1; // nova altura para próxima cascata
                        coluna2.erase(coluna2.begin() + idx);
                        idx = 0; // reinicia a verificação
                    } else {
                        // Esta relíquia sobrevive mas sofre dano
                        coluna2[idx] -= danoQueda;
                        break; // para a cascata
                    }
                }
            }
        }
        
        // Resolve recursivamente as duas colunas
        long long batidas1 = solve(coluna1);
        long long batidas2 = solve(coluna2);
        
        minBatidas = min(minBatidas, batidas + batidas1 + batidas2);
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
