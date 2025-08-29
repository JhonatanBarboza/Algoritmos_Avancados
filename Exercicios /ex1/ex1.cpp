#include <bits/stdc++.h>
using namespace std;

struct Pessoa {
    int id;
    string confirmacao;
    int pai;
    int mae;
};

int main() {
    int X; // Número de casos de teste
    cin >> X;
    
    for (int i = 0; i < X; i++) {
        int N; // Quantidade de pessoas na árvore genealógica
        cin >> N;
        
        vector<Pessoa> pessoas(N);
        map<int, int> idParaIndice; // Mapeia ID para índice no vetor
        
        // Lê os dados das pessoas
        for (int j = 0; j < N; j++) {
            cin >> pessoas[j].id >> pessoas[j].confirmacao >> pessoas[j].pai >> pessoas[j].mae;
            idParaIndice[pessoas[j].id] = j; // Mapeia ID para índice
        }
        
        int count = 0;
        
        // Verifica cada pessoa
        for (int j = 0; j < N; j++) {
            if (pessoas[j].confirmacao == "sim") {
                bool paiTemDiabetes = false;
                bool maeTemDiabetes = false;
                
                // Verifica se o pai existe e tem diabetes
                if (pessoas[j].pai != -1 && idParaIndice.find(pessoas[j].pai) != idParaIndice.end()) {
                    int indicePai = idParaIndice[pessoas[j].pai];
                    if (pessoas[indicePai].confirmacao == "sim") {
                        paiTemDiabetes = true;
                    }
                }
                
                // Verifica se a mãe existe e tem diabetes
                if (pessoas[j].mae != -1 && idParaIndice.find(pessoas[j].mae) != idParaIndice.end()) {
                    int indiceMae = idParaIndice[pessoas[j].mae];
                    if (pessoas[indiceMae].confirmacao == "sim") {
                        maeTemDiabetes = true;
                    }
                }
                
                // Se pelo menos um dos pais tem diabetes, conta essa pessoa
                if (paiTemDiabetes || maeTemDiabetes) {
                    count++;
                }
            }
        }
        
        cout << count << endl;
    }
    
    return 0;
}