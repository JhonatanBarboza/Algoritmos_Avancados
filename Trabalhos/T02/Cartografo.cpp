#include <bits/stdc++.h>
using namespace std;

struct Sistema {
    string id;
    double x, y;
    
    Sistema() {}
    Sistema(string id, double x, double y) : id(id), x(x), y(y) {}
};

struct Aresta {
    int u, v;
    double peso;
    
    Aresta(int u, int v, double peso) : u(u), v(v), peso(peso) {}
    
    bool operator<(const Aresta& other) const {
        if (abs(peso - other.peso) < 1e-9) {
            // Em caso de empate no peso, ordenar por índices para determinismo
            if (min(u, v) != min(other.u, other.v)) {
                return min(u, v) < min(other.u, other.v);
            }
            return max(u, v) < max(other.u, other.v);
        }
        return peso < other.peso;
    }
};

// Classe Union-Find para o algoritmo de Kruskal
class UnionFind {
private:
    vector<int> pai, rank;
    
public:
    UnionFind(int n) {
        pai.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            pai[i] = i;
        }
    }
    
    int find(int x) {
        if (pai[x] != x) {
            pai[x] = find(pai[x]); // Path compression
        }
        return pai[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) {
            pai[px] = py;
        } else if (rank[px] > rank[py]) {
            pai[py] = px;
        } else {
            pai[py] = px;
            rank[px]++;
        }
        return true;
    }
};

// Calcular distância euclidiana entre dois sistemas
double calcularDistancia(const Sistema& a, const Sistema& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Parte 1: Malha de Túneis Essencial usando Kruskal (Algoritmo Guloso)
vector<Aresta> malhaDetuneis(const vector<Sistema>& sistemas, int numImportantes, double maxTensao) {
    vector<Aresta> arestas;
    
    // Gerar todas as arestas possíveis entre sistemas importantes
    for (int i = 0; i < numImportantes; i++) {
        for (int j = i + 1; j < numImportantes; j++) {
            double dist = calcularDistancia(sistemas[i], sistemas[j]);
            if (dist <= maxTensao) {
                arestas.push_back(Aresta(i, j, dist));
            }
        }
    }
    
    // Ordenar arestas por peso (algoritmo guloso de Kruskal)
    sort(arestas.begin(), arestas.end());
    
    vector<Aresta> mst;
    UnionFind uf(numImportantes);
    
    // Aplicar algoritmo de Kruskal
    for (const Aresta& aresta : arestas) {
        if (uf.unite(aresta.u, aresta.v)) {
            mst.push_back(aresta);
            if (mst.size() == numImportantes - 1) {
                break; // MST completa
            }
        }
    }
    
    return mst;
}

// Parte 2: Par de pontos mais próximos usando Divisão e Conquista
struct ParMaisProximo {
    int i, j;
    double distancia;
    
    ParMaisProximo(int i, int j, double dist) : i(i), j(j), distancia(dist) {}
};

// Força bruta para casos pequenos
ParMaisProximo forcaBruta(const vector<Sistema>& sistemas, const vector<int>& indices) {
    int n = indices.size();
    ParMaisProximo melhor(indices[0], indices[1], calcularDistancia(sistemas[indices[0]], sistemas[indices[1]]));
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = calcularDistancia(sistemas[indices[i]], sistemas[indices[j]]);
            if (dist < melhor.distancia) {
                melhor = ParMaisProximo(indices[i], indices[j], dist);
            }
        }
    }
    
    return melhor;
}

// Função auxiliar para encontrar pontos próximos à linha divisória
ParMaisProximo pontosMaisProximosNaFaixa(const vector<Sistema>& sistemas, 
                                        const vector<int>& faixa, double menorDist) {
    ParMaisProximo melhor(-1, -1, menorDist);
    
    // Ordenar pontos da faixa por coordenada y
    vector<int> faixaOrdenada = faixa;
    sort(faixaOrdenada.begin(), faixaOrdenada.end(), [&](int a, int b) {
        return sistemas[a].y < sistemas[b].y;
    });
    
    int n = faixaOrdenada.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n && (sistemas[faixaOrdenada[j]].y - sistemas[faixaOrdenada[i]].y) < menorDist; j++) {
            double dist = calcularDistancia(sistemas[faixaOrdenada[i]], sistemas[faixaOrdenada[j]]);
            if (dist < melhor.distancia) {
                melhor = ParMaisProximo(faixaOrdenada[i], faixaOrdenada[j], dist);
            }
        }
    }
    
    return melhor;
}

// Função recursiva de divisão e conquista
ParMaisProximo pontosMaisProximosRec(const vector<Sistema>& sistemas, vector<int>& indices) {
    int n = indices.size();
    
    // Caso base: usar força bruta para poucos pontos
    if (n <= 3) {
        return forcaBruta(sistemas, indices);
    }
    
    // Dividir os pontos
    int meio = n / 2;
    double linhaX = sistemas[indices[meio]].x;
    
    vector<int> esquerda(indices.begin(), indices.begin() + meio);
    vector<int> direita(indices.begin() + meio, indices.end());
    
    // Conquistar recursivamente
    ParMaisProximo melhorEsq = pontosMaisProximosRec(sistemas, esquerda);
    ParMaisProximo melhorDir = pontosMaisProximosRec(sistemas, direita);
    
    // Encontrar o melhor entre os dois lados
    ParMaisProximo melhor = (melhorEsq.distancia < melhorDir.distancia) ? melhorEsq : melhorDir;
    
    // Verificar pontos próximos à linha divisória
    vector<int> faixa;
    for (int idx : indices) {
        if (abs(sistemas[idx].x - linhaX) < melhor.distancia) {
            faixa.push_back(idx);
        }
    }
    
    ParMaisProximo melhorFaixa = pontosMaisProximosNaFaixa(sistemas, faixa, melhor.distancia);
    if (melhorFaixa.i != -1 && melhorFaixa.distancia < melhor.distancia) {
        melhor = melhorFaixa;
    }
    
    return melhor;
}

// Interface principal para a Parte 2
ParMaisProximo pontoDeRessonancia(const vector<Sistema>& sistemas) {
    vector<int> indices(sistemas.size());
    for (int i = 0; i < sistemas.size(); i++) {
        indices[i] = i;
    }
    
    // Ordenar por coordenada x
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return sistemas[a].x < sistemas[b].x;
    });
    
    return pontosMaisProximosRec(sistemas, indices);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int numProblemas;
    cin >> numProblemas;
    
    for (int problema = 0; problema < numProblemas; problema++) {
        int numSistemas, numImportantes;
        double maxTensao;
        
        cin >> numSistemas >> numImportantes >> maxTensao;
        
        vector<Sistema> sistemas(numSistemas);
        for (int i = 0; i < numSistemas; i++) {
            cin >> sistemas[i].id >> sistemas[i].x >> sistemas[i].y;
        }
        
        // Parte 1: Malha de Túneis Essencial
        vector<Aresta> mst = malhaDetuneis(sistemas, numImportantes, maxTensao);
        
        // Não reordenar - manter ordem de Kruskal com índice menor primeiro
        for (const Aresta& aresta : mst) {
            int idx1 = aresta.u, idx2 = aresta.v;
            if (idx1 > idx2) swap(idx1, idx2);
            
            string nome1 = sistemas[idx1].id;
            string nome2 = sistemas[idx2].id;
            
            cout << nome1 << ", " << nome2 << ", " << fixed << setprecision(2) << aresta.peso << endl;
        }
        
        // Parte 2: Ponto de Ressonância
        ParMaisProximo ressonancia = pontoDeRessonancia(sistemas);
        int idx1 = ressonancia.i, idx2 = ressonancia.j;
        if (idx1 > idx2) swap(idx1, idx2);
        
        string nome1 = sistemas[idx1].id;
        string nome2 = sistemas[idx2].id;
        
        cout << "Ponto de Ressonância: " << nome1 << ", " << nome2 << ", " 
             << fixed << setprecision(2) << ressonancia.distancia << endl;
        
        if (problema < numProblemas - 1) {
            cout << endl; // Linha em branco entre problemas
        }
    }
    
    cout << endl; // Linha em branco no final
    
    return 0;
}
