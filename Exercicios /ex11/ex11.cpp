#include <iostream>
#include <vector>
#include <functional>
using namespace std;

typedef struct Ligacoes {
    int u, v;
} ligacoes;

int moleculas(vector<ligacoes> &l, int n, int m){
    vector<bool> visited(n + 1, false);
    vector<vector<int>> adj(n + 1);

    // Construir a lista de adjacência
    for (int i = 0; i < m; i++){
        adj[l[i].u].push_back(l[i].v);
        adj[l[i].v].push_back(l[i].u);
    }

    int componentes = 0;

    // Função DFS para explorar o grafo
    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor);
            }
        }
    };

    // Contar componentes conectados
    for (int i = 1; i <= n; i++){
        if (!visited[i]){
            dfs(i);
            componentes++;
        }
    }

    return componentes;
}

int main (){
    int x, n, m, u, v;
    cin >> x;
    for (int i = 0; i < x; i++){
        cin >> n >> m;
        vector<ligacoes> l(m);
        for (int j = 0; j < m; j++){
            cin >> u >> v; 
            l[j].u = u;
            l[j].v = v;
        }
        cout << moleculas(l, n, m) << endl;
    }
    return 0;
}