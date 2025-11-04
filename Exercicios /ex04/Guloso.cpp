#include <bits/stdc++.h>
using namespace std;

struct Heroi{
    string nome;
    string nivel;
    bool disponivel = true;
};

struct Missao{
    int indice;
    int tempo;
    vector<int> dependencias;
    bool realizada = false;
};

// Função para obter multiplicador de produtividade
auto getMultiplicador = [](const string& nivel) -> float {
    if (nivel == "Aprendiz") return 0.75;
    if (nivel == "Aventureiro") return 1.0;
    if (nivel == "Cavaleiro") return 1.2;
    if (nivel == "Mestre") return 1.5;
    if (nivel == "Lenda") return 2.0;
    return 1.0;
};

int main(){
    int x, n, m;

    // Numero de casos teste 
    cin >> x;
    for (int i = 0; i < x; i++){
        cin >> n >> m;

        // ler nome e nivel dos herois 
        vector<Heroi> herois(n);
        for (int j = 0; j < n; j++){
            cin >> herois[j].nome >> herois[j].nivel;
        }
        
        // ler o indice, tempo e dependencias de cada missao
        vector<Missao> missoes(m);
        for (int j = 0; j < m; j++){
            cin >> missoes[j].indice >> missoes[j].tempo;
            // ler dependencias que tem tamanho indefinido
            string linha;
            getline(cin, linha);
            stringstream ss(linha);
            int dep;
            while (ss >> dep){
                if (dep != 0) { // 0 significa sem dependências
                    missoes[j].dependencias.push_back(dep - 1); // Converter para índice 0-based
                }
            }
        }

        // Topological Sort para garantir que dependências sejam respeitadas
        vector<int> ordem_topologica;
        vector<int> grau_entrada(m, 0);
        vector<vector<int>> grafo(m);
        
        // Construir o grafo e calcular grau de entrada
        for (int j = 0; j < m; j++){
            for (int dep : missoes[j].dependencias){
                grafo[dep].push_back(j);
                grau_entrada[j]++;
            }
        }
        
        // Ordenação topológica (FIFO para manter ordem original quando possível)
        queue<int> fila;

        // Adicionar todas as missões sem dependências
        for (int j = 0; j < m; j++){
            if (grau_entrada[j] == 0){ 
                fila.push(j);
            }
        }        

        // Processar ordenação topológica
        while (!fila.empty()){
            int u = fila.front();
            fila.pop();
            ordem_topologica.push_back(u);
            
            // Para cada missão que pode ser desbloqueada
            for (int vizinho : grafo[u]){
                grau_entrada[vizinho]--;
                if (grau_entrada[vizinho] == 0){
                    fila.push(vizinho);
                }
            }
        }   

        // Algoritmo guloso para alocação otimizada
        vector<vector<int>> atribuicoes(n); 
        vector<float> tempo_livre_heroi(n, 0.0); 
        vector<float> tempo_conclusao_quest(m, 0.0); 
        
        // Processar quests na ordem topológica
        for (int quest_idx : ordem_topologica) {
            // Calcular quando esta quest pode começar (após todas suas dependências)
            float tempo_inicio_minimo = 0.0;
            for (int dep : missoes[quest_idx].dependencias) {
                tempo_inicio_minimo = max(tempo_inicio_minimo, tempo_conclusao_quest[dep]);
            }

            // ESTRATÉGIA GULOSA: Encontrar o herói que MINIMIZA o tempo de conclusão desta quest
            int melhor_heroi = -1;
            float melhor_tempo_conclusao = INFINITY;
            
            for (int h = 0; h < n; h++) {
                // Calcular tempo de execução considerando produtividade do herói
                float multiplicador = getMultiplicador(herois[h].nivel);
                float tempo_execucao = missoes[quest_idx].tempo / multiplicador;
                
                // Momento mais cedo que este herói pode começar esta quest
                float inicio_possivel = max(tempo_inicio_minimo, tempo_livre_heroi[h]);
                
                // Tempo total de conclusão se atribuirmos a este herói
                float conclusao_possivel = inicio_possivel + tempo_execucao; 
                
                // Critério guloso: escolher herói que conclui a quest mais cedo
                // Em caso de empate, escolher o primeiro herói da lista (critério de desempate)
                if (conclusao_possivel < melhor_tempo_conclusao) {
                    melhor_tempo_conclusao = conclusao_possivel;
                    melhor_heroi = h;
                }
            }

            // Atribuir quest ao melhor herói encontrado
            atribuicoes[melhor_heroi].push_back(quest_idx + 1); // +1 para índice 1-based na saída
            
            // Atualizar quando este herói ficará livre novamente
            tempo_livre_heroi[melhor_heroi] = melhor_tempo_conclusao;
            
            // Registrar quando esta quest será concluída
            tempo_conclusao_quest[quest_idx] = melhor_tempo_conclusao;
        }
        
        // Saída no formato especificado
        for (int h = 0; h < n; h++) {
            cout << herois[h].nome << " = {";
            for (size_t j = 0; j < atribuicoes[h].size(); j++) {
                if (j > 0) cout << ",";
                cout << atribuicoes[h][j];
            }
            cout << "}" << endl;
        }
        
        // Tempo mínimo total = tempo da quest que termina por último
        float tempo_total = 0.0;
        for (int j = 0; j < m; j++) {
            tempo_total = max(tempo_total, tempo_conclusao_quest[j]);
        }
        
        cout << fixed << setprecision(2) << "Tempo mínimo: " << tempo_total << endl;
        if (i < x - 1) cout << endl;
    }
    
    return 0; 
}