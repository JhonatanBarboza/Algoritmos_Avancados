#include <bits/stdc++.h>
using namespace std;

// Estrutura para representar um sistema estelar
struct Sistema {
    string id;
    double x, y;
    
    Sistema() {}
    Sistema(string id, double x, double y) : id(id), x(x), y(y) {}
};

// Estrutura para representar uma aresta no grafo
struct Aresta {
    int u, v;
    double peso;
    
    Aresta(int u, int v, double peso) : u(u), v(v), peso(peso) {}
    
    // Operador de comparação para ordenação (usado no algoritmo de Kruskal)
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
// Implementa estrutura de dados para detectar ciclos eficientemente
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
    
    // Encontra o representante do conjunto com compressão de caminho
    int find(int x) {
        if (pai[x] != x) {
            pai[x] = find(pai[x]); // Path compression
        }
        return pai[x];
    }
    
    // Une dois conjuntos usando união por rank
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

// Calcula a distância euclidiana entre dois sistemas estelares
double calcularDistancia(const Sistema& a, const Sistema& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

/**
 * PARTE 1: Malha de Túneis Essencial usando algoritmo de Kruskal (Algoritmo Guloso)
 * Encontra a Árvore Geradora Mínima (MST) dos sistemas importantes
 * Complexidade: O(E log E) onde E é o número de arestas
 */
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
    
    // Aplicar algoritmo de Kruskal para construir MST
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

/**
 * PARTE 2: Par de pontos mais próximos usando Divisão e Conquista
 * Complexidade: O(n log n) onde n é o número de sistemas
 */
struct ParMaisProximo {
    int i, j;
    double distancia;
    
    ParMaisProximo(int i, int j, double dist) : i(i), j(j), distancia(dist) {}
};

/**
 * Algoritmo de força bruta para encontrar par mais próximo em casos pequenos
 * Usado como caso base da recursão (n <= 3)
 * Aplica critério de desempate por índices quando distâncias são iguais
 */
ParMaisProximo forcaBruta(const vector<Sistema>& sistemas, const vector<int>& indices) {
    int n = indices.size();
    ParMaisProximo melhor(indices[0], indices[1], calcularDistancia(sistemas[indices[0]], sistemas[indices[1]]));
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = calcularDistancia(sistemas[indices[i]], sistemas[indices[j]]);
            if (dist < melhor.distancia) {
                melhor = ParMaisProximo(indices[i], indices[j], dist);
            } else if (abs(dist - melhor.distancia) < 1e-9) {
                // Em caso de empate, aplicar critério de desempate por índices
                int idx1 = indices[i], idx2 = indices[j];
                int melhor_idx1 = melhor.i, melhor_idx2 = melhor.j;
                
                if (min(idx1, idx2) < min(melhor_idx1, melhor_idx2) ||
                    (min(idx1, idx2) == min(melhor_idx1, melhor_idx2) && max(idx1, idx2) < max(melhor_idx1, melhor_idx2))) {
                    melhor = ParMaisProximo(indices[i], indices[j], dist);
                }
            }
        }
    }
    
    return melhor;
}

/**
 * Função auxiliar para verificar pontos na faixa próxima à linha divisória
 * Otimização: só verifica pontos com diferença em Y menor que a distância atual
 */
ParMaisProximo pontosMaisProximosNaFaixa(const vector<Sistema>& sistemas, 
                                        const vector<int>& faixa, double menorDist) {
    ParMaisProximo melhor(-1, -1, menorDist);
    
    // Ordenar pontos da faixa por coordenada y para otimização
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
            } else if (melhor.i != -1 && abs(dist - melhor.distancia) < 1e-9) {
                // Em caso de empate, aplicar critério de desempate por índices
                int idx1 = faixaOrdenada[i], idx2 = faixaOrdenada[j];
                int melhor_idx1 = melhor.i, melhor_idx2 = melhor.j;
                
                if (min(idx1, idx2) < min(melhor_idx1, melhor_idx2) ||
                    (min(idx1, idx2) == min(melhor_idx1, melhor_idx2) && max(idx1, idx2) < max(melhor_idx1, melhor_idx2))) {
                    melhor = ParMaisProximo(faixaOrdenada[i], faixaOrdenada[j], dist);
                }
            }
        }
    }
    
    return melhor;
}

/**
 * Função recursiva principal do algoritmo de divisão e conquista
 * Divide o problema em dois subproblemas menores e combina os resultados
 */
ParMaisProximo pontosMaisProximosRec(const vector<Sistema>& sistemas, vector<int>& indices) {
    int n = indices.size();
    
    // Caso base: usar força bruta para poucos pontos
    if (n <= 3) {
        return forcaBruta(sistemas, indices);
    }
    
    // DIVIDIR: separar pontos em duas metades
    int meio = n / 2;
    double linhaX = sistemas[indices[meio]].x;
    
    vector<int> esquerda(indices.begin(), indices.begin() + meio);
    vector<int> direita(indices.begin() + meio, indices.end());
    
    // CONQUISTAR: resolver recursivamente cada metade
    ParMaisProximo melhorEsq = pontosMaisProximosRec(sistemas, esquerda);
    ParMaisProximo melhorDir = pontosMaisProximosRec(sistemas, direita);
    
    // COMBINAR: encontrar o melhor entre os dois lados
    ParMaisProximo melhor = melhorEsq;
    if (melhorEsq.distancia < melhorDir.distancia) {
        melhor = melhorEsq;
    } else if (melhorDir.distancia < melhorEsq.distancia) {
        melhor = melhorDir;
    } else {
        // Em caso de empate, aplicar critério de desempate por índices
        int esq_min = min(melhorEsq.i, melhorEsq.j), esq_max = max(melhorEsq.i, melhorEsq.j);
        int dir_min = min(melhorDir.i, melhorDir.j), dir_max = max(melhorDir.i, melhorDir.j);
        
        if (esq_min < dir_min || (esq_min == dir_min && esq_max < dir_max)) {
            melhor = melhorEsq;
        } else {
            melhor = melhorDir;
        }
    }
    
    // Verificar pontos que cruzam a linha divisória (otimização crucial)
    vector<int> faixa;
    for (int idx : indices) {
        if (abs(sistemas[idx].x - linhaX) < melhor.distancia) {
            faixa.push_back(idx);
        }
    }
    
    ParMaisProximo melhorFaixa = pontosMaisProximosNaFaixa(sistemas, faixa, melhor.distancia);
    if (melhorFaixa.i != -1) {
        if (melhorFaixa.distancia < melhor.distancia) {
            melhor = melhorFaixa;
        } else if (abs(melhorFaixa.distancia - melhor.distancia) < 1e-9) {
            // Em caso de empate, aplicar critério de desempate por índices
            int faixa_min = min(melhorFaixa.i, melhorFaixa.j), faixa_max = max(melhorFaixa.i, melhorFaixa.j);
            int atual_min = min(melhor.i, melhor.j), atual_max = max(melhor.i, melhor.j);
            
            if (faixa_min < atual_min || (faixa_min == atual_min && faixa_max < atual_max)) {
                melhor = melhorFaixa;
            }
        }
    }
    
    return melhor;
}

/**
 * Interface principal para encontrar o par de pontos mais próximos
 * Prepara os dados e chama o algoritmo de divisão e conquista
 */
ParMaisProximo pontoDeRessonancia(const vector<Sistema>& sistemas) {
    vector<int> indices(sistemas.size());
    for (int i = 0; i < sistemas.size(); i++) {
        indices[i] = i;
    }
    
    // Pré-ordenar por coordenada x para o algoritmo de divisão e conquista
    sort(indices.begin(), indices.end(), [&](int a, int b) {
        return sistemas[a].x < sistemas[b].x;
    });
    
    return pontosMaisProximosRec(sistemas, indices);
}

/**
 * Função principal do programa
 * Lê múltiplos casos de teste e aplica os dois algoritmos:
 * 1. Kruskal para MST (Malha de Túneis)
 * 2. Divisão e Conquista para par mais próximo (Ponto de Ressonância)
 */
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
        
        // Manter ordem de Kruskal com índice menor primeiro
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
            cout << endl;
        }
    }
    
    cout << endl;
    
    return 0;
}
