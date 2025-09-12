#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

struct Solicitacao {
    int cliente;
    int inicio;    // tempo em minutos
    int fim;       // tempo em minutos
    int modelo;
    
    Solicitacao(int c, int i, int f, int m) : cliente(c), inicio(i), fim(f), modelo(m) {}
};

// Converte horário HH:MM para minutos
int horarioParaMinutos(const string& horario) {
    int horas = stoi(horario.substr(0, 2));
    int minutos = stoi(horario.substr(3, 2));
    return horas * 60 + minutos;
}

// Comparador para ordenar por horário de término
bool compararPorFim(const Solicitacao& a, const Solicitacao& b) {
    // Critério principal: ordenar pelo horário de término
    if (a.fim != b.fim) {
        return a.fim < b.fim;
    }
    // Primeiro critério de desempate: ordenar pelo horário de início
    if (a.inicio != b.inicio) {
        return a.inicio < b.inicio;
    }
    // Segundo critério de desempate: ordenar pelo ID do cliente
    return a.cliente < b.cliente;
}

// Algoritmo guloso para máximo de atividades sem sobreposição
vector<int> algoritmoGuloso(vector<Solicitacao>& solicitacoes) {
    if (solicitacoes.empty()) return {};
    
    // Ordena por horário de término
    sort(solicitacoes.begin(), solicitacoes.end(), compararPorFim);
  

    vector<int> selecionados;
    selecionados.push_back(solicitacoes[0].cliente);
    int ultimoFim = solicitacoes[0].fim;
    
    for (size_t i = 1; i < solicitacoes.size(); i++) {
        // Se não há sobreposição (início >= fim anterior)
        if (solicitacoes[i].inicio >= ultimoFim) {
            selecionados.push_back(solicitacoes[i].cliente);
            ultimoFim = solicitacoes[i].fim;
        }
    }

    return selecionados;
}

int main() {
    int X;
    cin >> X;
    
    while (X--) {
        int N, M;
        cin >> N >> M;
        
        // Mapa para agrupar solicitações por modelo
        map<int, vector<Solicitacao>> solicitacoesPorModelo;
        
        for (int i = 0; i < M; i++) {
            int cliente, modelo;
            string inicio, fim;
            cin >> cliente >> inicio >> fim >> modelo;
            
            int inicioMin = horarioParaMinutos(inicio);
            int fimMin = horarioParaMinutos(fim);
            
            solicitacoesPorModelo[modelo].emplace_back(cliente, inicioMin, fimMin, modelo);
        }
        
        vector<string> resultados;
        
        // Para cada modelo de carro (1 a N)
        for (int modelo = 1; modelo <= N; modelo++) {
            if (solicitacoesPorModelo.find(modelo) != solicitacoesPorModelo.end()) {
                vector<Solicitacao> solicitacoes = solicitacoesPorModelo[modelo];
                vector<int> clientesSelecionados = algoritmoGuloso(solicitacoes);
                
                // Monta string do resultado
                stringstream ss;
                ss << modelo << ": " << clientesSelecionados.size() << " = ";
                
                for (size_t i = 0; i < clientesSelecionados.size(); i++) {
                    if (i > 0) ss << ", ";
                    ss << clientesSelecionados[i];
                }
                
                resultados.push_back(ss.str());
            } else {
                // Modelo sem solicitações
                resultados.push_back(to_string(modelo) + ": 0");
            }
        }
        
        // Imprime resultado do caso de teste
        for (size_t i = 0; i < resultados.size(); i++) {
            if (i > 0) cout << " | ";
            cout << resultados[i];
        }
        cout << endl;
    }
    
    return 0;
}
