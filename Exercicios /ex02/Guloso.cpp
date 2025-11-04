#include <bits/stdc++.h>
using namespace std;

// ---------------- Estruturas ----------------

struct Ganhos {
    string data; 
    float valor;
};

// ---------------- Funções axiliares ----------------

// Função para converter string para tupla (ano, mês, dia)
tuple<int,int,int> parseData(const string& data) {
    int d, m, y;
    sscanf(data.c_str(), "%d/%d/%d", &d, &m, &y);
    return make_tuple(y, m, d);
}

// ---------------- Função principal ----------------

int main() {

    // Declaração de variaveis 
    int X, N;
    float total = 0, soma = 0;
    vector<Ganhos> ganhos;

    // Leitura dos dados
    cin >> X;
    for (int i = 0; i < X; i++) {
        cin >> N;
        for (int j = 0; j < N; j++) {
            Ganhos g;
            cin >> g.data >> g.valor;
            ganhos.push_back(g);
            total += g.valor;
        }
        // Ordena o vetor 'ganhos' em ordem decrescente de valor
        sort(ganhos.begin(), ganhos.end(), [](const Ganhos& a, const Ganhos& b) {
            return a.valor > b.valor; 
        });

        // Cálculo da soma dos ganhos e compara com o total 
        for (int i=0; i < N; i++){
            soma += ganhos[i].valor;
            total -= ganhos[i].valor;
            
            if (soma >= total) {
                // Imprime as informações solicitadas
                printf("%d dias (", i + 1);
                for (int j = 0; j <= i; j++) {
                    // Ordenar as datas dos i primeiros elementos
                    sort(ganhos.begin(), ganhos.begin() + i + 1, [](const Ganhos& a, const Ganhos& b) {
                        return parseData(a.data) < parseData(b.data);
                    });
                    printf("%s", ganhos[j].data.c_str());
                    if (j < i) printf(", ");
                }
                printf(") | soma=%.2f | %.2f%% dos dias totais\n", soma, ((i+1)/(float)N * 100));
                break;
            }
        }
        // Reseta as variaveis para a próxima iteração
        soma = 0;
        total = 0;
        ganhos.clear();
    }

    return 0;
}