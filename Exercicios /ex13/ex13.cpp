#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct caminhos{
    int a; 
    int b; 
    long long c;
};

bool BFS(vector<vector<long long>>& grafo_residual, int fonte, int sumidouro, vector<int>& parent) {
    int n = grafo_residual.size();
    vector<bool> visitado(n, false);
    queue<int> fila;
    
    fila.push(fonte);
    visitado[fonte] = true;
    parent[fonte] = -1;
    
    while (!fila.empty()) {
        int u = fila.front();
        fila.pop();
        
        for (int v = 0; v < n; v++) {
            if (!visitado[v] && grafo_residual[u][v] > 0) {
                fila.push(v);
                visitado[v] = true;
                parent[v] = u;
                
                if (v == sumidouro) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

long long EdmondsKarp(vector<caminhos>& grafo, int n, int m) {
    // Criar matriz de adjacência (grafo residual)
    vector<vector<long long>> grafo_residual(n, vector<long long>(n, 0));
    
    // Preencher o grafo residual com as capacidades originais
    for (int i = 0; i < m; i++) {
        int u = grafo[i].a - 1; // Converter para índice base 0
        int v = grafo[i].b - 1; // Converter para índice base 0
        long long cap = grafo[i].c;
        grafo_residual[u][v] += cap; 
    }
    
    int fonte = 0;       
    int sumidouro = n - 1; 
    long long max_flow = 0;
    vector<int> parent(n);
    
    // Loop principal do algoritmo Edmonds-Karp
    while (BFS(grafo_residual, fonte, sumidouro, parent)) {
        // Encontrar o fluxo mínimo no caminho encontrado
        long long path_flow = LLONG_MAX;
        for (int v = sumidouro; v != fonte; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, grafo_residual[u][v]);
        }
        
        // Atualizar o grafo residual
        for (int v = sumidouro; v != fonte; v = parent[v]) {
            int u = parent[v];
            grafo_residual[u][v] -= path_flow;  // Diminuir capacidade direta
            grafo_residual[v][u] += path_flow;  // Aumentar capacidade reversa
        }
        
        // Adicionar o fluxo deste caminho ao fluxo total
        max_flow += path_flow;
    }
    
    return max_flow;
}

int main(){
    int n, m;
    cin >> n >> m;
    vector<caminhos> grafo(m);
    
    for (int i = 0; i < m; i++){
        cin >> grafo[i].a >> grafo[i].b >> grafo[i].c;
    }

    // Algoritmo de Edmonds-Karp para fluxo máximo
    long long fluxo_maximo = EdmondsKarp(grafo, n, m);
    cout << fluxo_maximo << endl;

    return 0;
}