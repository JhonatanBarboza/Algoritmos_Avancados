#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct reconstruir{
    int u; // origem
    int v; // destino
    int c; // custo
};

int Kruskal(vector<reconstruir>& arestas, int n, int m, vector<reconstruir>* resultado) {  

    // Ordena as arestas pelo custo (c)
    sort(arestas.begin(), arestas.end(), [](const reconstruir& a, const reconstruir& b) {
        return a.c < b.c;
    });

    vector<int> parent(n + 1);  // +1 para indexação 1-N
    vector<int> rank(n + 1, 0);

    for (int i = 1; i <= n; i++) {  // inicializa de 1 a n
        parent[i] = i;
    }

    function<int(int)> find = [&](int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    };

    auto union_sets = [&](int u, int v) {
        int root_u = find(u);
        int root_v = find(v);
        if (root_u != root_v) {
            if (rank[root_u] < rank[root_v]) {
                parent[root_u] = root_v;
            } else if (rank[root_u] > rank[root_v]) {
                parent[root_v] = root_u;
            } else {
                parent[root_v] = root_u;
                rank[root_u]++;
            }
            return true;  // união foi feita
        }
        return false;  // já estavam conectados
    };

    int custo_total = 0;
    int arestas_adicionadas = 0;
    
    for (const auto& r : arestas) {
        if (find(r.u) != find(r.v)) {
            union_sets(r.u, r.v);
            custo_total += r.c;
            arestas_adicionadas++;
            
            // Garante que o menor identificador fique à esquerda
            reconstruir aresta_formatada;
            if (r.u < r.v) {
                aresta_formatada = {r.u, r.v, r.c};
            } else {
                aresta_formatada = {r.v, r.u, r.c};
            }
            resultado->push_back(aresta_formatada);
            
            // Se já temos n-1 arestas, a MST está completa
            if (arestas_adicionadas == n - 1) {
                break;
            }
        }
    }

    // Retorna -1 se não conseguiu conectar todos os vértices
    if (arestas_adicionadas != n - 1) {
        return -1;
    }
    
    return custo_total;
}

int main() {

    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        int n, m;
        cin >> n >> m;
        vector<reconstruir> arestas;
        vector<reconstruir> resultado;
        
        for (int j = 0; j < m; j++) {
            reconstruir nova_aresta;
            cin >> nova_aresta.u >> nova_aresta.v >> nova_aresta.c;
            arestas.push_back(nova_aresta);
        }
        
        // Verifica se há custos repetidos
        bool tem_repetido = false;
        for (int j = 0; j < m; j++) {
            for (int k = j + 1; k < m; k++) {
                if (arestas[j].c == arestas[k].c) {
                    tem_repetido = true;
                    break;
                }
            }
            if (tem_repetido) { 
                break;
            }
        }
        
        if (tem_repetido) {
            cout << "Esse nao e o caminho correto para a Cidade Perdida de Z." << endl;
        } else {        
            int custo_minimo = Kruskal(arestas, n, m, &resultado);

            if (custo_minimo == -1) {
                cout << "O vale nao pode ser completamente atravessado." << endl;
            } else {
                cout << "Custo minimo: " << custo_minimo << endl;
                cout << "Pontes reconstruidas:" << endl;
                for (const auto& r : resultado) {
                    cout << r.u << " - " << r.v << endl;
                }
            }
        }
        
        cout << endl;
    }

    return 0;
}