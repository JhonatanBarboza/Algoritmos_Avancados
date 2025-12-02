#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Estado {
    int vertice;
    set<pair<int, int>> arestas_usadas;
    bool turno_ash; // true se é turno do Ash, false se é do Noir
    
    bool operator<(const Estado& other) const {
        if (vertice != other.vertice) return vertice < other.vertice;
        if (arestas_usadas != other.arestas_usadas) return arestas_usadas < other.arestas_usadas;
        return turno_ash < other.turno_ash;
    }
};

map<Estado, bool> memo;
vector<vector<int>> grafo;

bool pode_vencer(int vertice, set<pair<int, int>>& arestas_usadas, bool turno_ash) {
    Estado estado = {vertice, arestas_usadas, turno_ash};
    
    if (memo.find(estado) != memo.end()) {
        return memo[estado];
    }
    
    // Verifica se há movimentos possíveis
    bool tem_movimento = false;
    for (int vizinho : grafo[vertice]) {
        pair<int, int> aresta = {vertice, vizinho};
        if (arestas_usadas.find(aresta) == arestas_usadas.end()) {
            tem_movimento = true;
            break;
        }
    }
    
    // Se não há movimentos, o jogador atual perde
    if (!tem_movimento) {
        return memo[estado] = false;
    }
    
    // Tenta todos os movimentos possíveis
    for (int vizinho : grafo[vertice]) {
        pair<int, int> aresta = {vertice, vizinho};
        if (arestas_usadas.find(aresta) == arestas_usadas.end()) {
            arestas_usadas.insert(aresta);
            
            // Se o oponente não pode vencer após este movimento, então eu vencerei
            if (!pode_vencer(vizinho, arestas_usadas, !turno_ash)) {
                arestas_usadas.erase(aresta);
                return memo[estado] = true;
            }
            
            arestas_usadas.erase(aresta);
        }
    }
    
    // Se todos os movimentos levam à vitória do oponente, eu perco
    return memo[estado] = false;
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, s;
        cin >> n >> m >> s;
        
        grafo.assign(n, vector<int>());
        memo.clear();
        
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            grafo[u].push_back(v);
        }
        
        set<pair<int, int>> arestas_vazias;
        bool ash_vence = pode_vencer(s, arestas_vazias, true);
        
        if (ash_vence) {
            cout << "Ash" << endl;
        } else {
            cout << "Noir" << endl;
        }
    }
    
    return 0;
}