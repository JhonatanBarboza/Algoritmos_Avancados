#include <bits/stdc++.h>
using namespace std;

struct Ponto {
    double x, y;
    
    Ponto() {}
    Ponto(double x, double y) : x(x), y(y) {}
    
    bool operator<(const Ponto& other) const {
        if (abs(x - other.x) < 1e-9) {
            return y < other.y;
        }
        return x < other.x;
    }
    
    bool operator==(const Ponto& other) const {
        return abs(x - other.x) < 1e-9 && abs(y - other.y) < 1e-9;
    }
};

// Produto vetorial de três pontos
double produtoVetorial(const Ponto& O, const Ponto& A, const Ponto& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Distância euclidiana ao quadrado entre dois pontos
double distanciaQuadrada(const Ponto& a, const Ponto& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

// Algoritmo de Andrew para fecho convexo (monotone chain)
vector<Ponto> fechoConvexo(vector<Ponto> pontos) {
    int n = pontos.size();
    if (n < 3) return pontos;
    
    sort(pontos.begin(), pontos.end());
    
    // Remover pontos duplicados
    pontos.erase(unique(pontos.begin(), pontos.end(), [](const Ponto& a, const Ponto& b) {
        return abs(a.x - b.x) < 1e-9 && abs(a.y - b.y) < 1e-9;
    }), pontos.end());
    
    n = pontos.size();
    if (n < 3) return pontos;
    
    // Construir o fecho convexo inferior
    vector<Ponto> inferior;
    for (int i = 0; i < n; i++) {
        while (inferior.size() >= 2 && 
               produtoVetorial(inferior[inferior.size()-2], inferior[inferior.size()-1], pontos[i]) < 0) {
            inferior.pop_back();
        }
        inferior.push_back(pontos[i]);
    }
    
    // Construir o fecho convexo superior
    vector<Ponto> superior;
    for (int i = n - 1; i >= 0; i--) {
        while (superior.size() >= 2 && 
               produtoVetorial(superior[superior.size()-2], superior[superior.size()-1], pontos[i]) < 0) {
            superior.pop_back();
        }
        superior.push_back(pontos[i]);
    }
    
    // Remover último ponto de cada meio para evitar duplicação
    inferior.pop_back();
    superior.pop_back();
    
    // Combinar inferior e superior para formar sentido anti-horário
    inferior.insert(inferior.end(), superior.begin(), superior.end());
    
    return inferior;
}

// Divisão e Conquista (híbrida)
vector<Ponto> fechoConvexoDivisaoConquista(vector<Ponto> pontos) {
    int n = pontos.size();
    if (n <= 50) {
        return fechoConvexo(pontos);
    }
    
    sort(pontos.begin(), pontos.end());
    
    int meio = n / 2;
    vector<Ponto> esquerda(pontos.begin(), pontos.begin() + meio);
    vector<Ponto> direita(pontos.begin() + meio, pontos.end());
    
    vector<Ponto> fechoEsq = fechoConvexoDivisaoConquista(esquerda);
    vector<Ponto> fechoDir = fechoConvexoDivisaoConquista(direita);
    
    // Mesclar os dois fechos convexos
    vector<Ponto> todosPontos;
    todosPontos.insert(todosPontos.end(), fechoEsq.begin(), fechoEsq.end());
    todosPontos.insert(todosPontos.end(), fechoDir.begin(), fechoDir.end());
    
    return fechoConvexo(todosPontos);
}

// Função para incluir pontos colineares na borda
vector<Ponto> incluirColineares(vector<Ponto> fecho, const vector<Ponto>& todosPontos) {
    if (fecho.size() < 2) return fecho;
    
    vector<Ponto> resultado;
    
    for (int i = 0; i < fecho.size(); i++) {
        resultado.push_back(fecho[i]);
        
        int proximo = (i + 1) % fecho.size();
        vector<Ponto> colineares;
        
        // Encontrar pontos colineares entre fecho[i] e fecho[proximo]
        for (const Ponto& p : todosPontos) {
            if (p == fecho[i] || p == fecho[proximo]) continue;
            
            double produto = produtoVetorial(fecho[i], fecho[proximo], p);
            if (abs(produto) < 1e-9) {
                // Verificar se está no segmento
                double dist1 = distanciaQuadrada(fecho[i], p);
                double dist2 = distanciaQuadrada(p, fecho[proximo]);
                double distTotal = distanciaQuadrada(fecho[i], fecho[proximo]);
                
                if (abs(sqrt(dist1) + sqrt(dist2) - sqrt(distTotal)) < 1e-9) {
                    colineares.push_back(p);
                }
            }
        }
        
        // Ordenar pontos colineares por distância de fecho[i]
        sort(colineares.begin(), colineares.end(), [&](const Ponto& a, const Ponto& b) {
            return distanciaQuadrada(fecho[i], a) < distanciaQuadrada(fecho[i], b);
        });
        
        for (const Ponto& p : colineares) {
            resultado.push_back(p);
        }
    }
    
    return resultado;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int caso = 1; caso <= T; caso++) {
        int N;
        cin >> N;
        
        vector<Ponto> pontos(N);
        for (int i = 0; i < N; i++) {
            cin >> pontos[i].x >> pontos[i].y;
        }
        
        vector<Ponto> fecho;
        
        // Caso especial: verificar se todos os pontos são colineares
        bool todosColineares = true;
        if (N >= 3) {
            for (int i = 2; i < N && todosColineares; i++) {
                if (abs(produtoVetorial(pontos[0], pontos[1], pontos[i])) > 1e-9) {
                    todosColineares = false;
                }
            }
        }
        
        if (todosColineares && N >= 2) {
            // Todos os pontos são colineares, incluir apenas os extremos
            sort(pontos.begin(), pontos.end());
            
            // Remover duplicatas
            pontos.erase(unique(pontos.begin(), pontos.end(), [](const Ponto& a, const Ponto& b) {
                return abs(a.x - b.x) < 1e-9 && abs(a.y - b.y) < 1e-9;
            }), pontos.end());
            
            if (pontos.size() == 1) {
                fecho = pontos;
            } else {
                // Para pontos colineares, incluir todos ordenadamente
                fecho = pontos;
            }
        } else {
            // Calcular fecho convexo normal
            fecho = fechoConvexoDivisaoConquista(pontos);
            fecho = incluirColineares(fecho, pontos);
        }
        
        // Encontrar ponto inicial (menor x, depois menor y)
        int inicio = 0;
        for (int i = 1; i < fecho.size(); i++) {
            if (fecho[i].x < fecho[inicio].x || 
                (abs(fecho[i].x - fecho[inicio].x) < 1e-9 && fecho[i].y < fecho[inicio].y)) {
                inicio = i;
            }
        }
        
        // Reorganizar para começar do ponto inicial
        vector<Ponto> fechoFinal;
        for (int i = 0; i < fecho.size(); i++) {
            fechoFinal.push_back(fecho[(inicio + i) % fecho.size()]);
        }
        
        cout << "Caso " << caso << ":" << endl;
        cout << "Tamanho do colar: " << fechoFinal.size() << endl;
        cout << "Pedras ancestrais: ";
        
        for (int i = 0; i < fechoFinal.size(); i++) {
            if (i > 0) cout << ",";
            cout << "(" << fixed << setprecision(4) << fechoFinal[i].x 
                 << "," << fixed << setprecision(4) << fechoFinal[i].y << ")";
        }
        cout << endl;
        
        if (caso < T) cout << endl;
    }
    
    cout << endl; // Linha em branco no final
    
    return 0;
}