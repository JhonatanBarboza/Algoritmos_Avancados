#include <bits/stdc++.h>
using namespace std;

// ------------------------ ESTRUTURAS DE DADOS ------------------------

// Estrutura para armazenar os dados dos jogadores
struct Jogador {
    string nome;
    double latitude;
    double longitude;
    double distancia;
};

// ------------------------ FUNÇÕES AUXILIARES ------------------------


/*
    Função: Melhor_Palpite

    Descrição: Calcula a distância entre o jogador e o ponto correto, e exibe o nome do jogador
               com a menor distância.

    Parâmetros: Jogador, latitude e longitude do ponto correto.
    Retorno: Nenhum.
*/
void Melhor_Palpite (Jogador& jogador, double LatC, double LonC, double& melhor_palpite){ 
    // Converte graus para radianos
    double lat1_rad = LatC * M_PI / 180.0;
    double lat2_rad = jogador.latitude * M_PI / 180.0;
    double lon1_rad = LonC * M_PI / 180.0;
    double lon2_rad = jogador.longitude * M_PI / 180.0;
    
    // Calcula as diferenças
    double delta_lat = lat2_rad - lat1_rad;
    double delta_lon = lon2_rad - lon1_rad;
    
    // Aplica a fórmula de Haversine correta
    double a = sin(delta_lat / 2.0) * sin(delta_lat / 2.0) + 
              cos(lat1_rad) * cos(lat2_rad) * 
              sin(delta_lon / 2.0) * sin(delta_lon / 2.0);
    
    double distancia = 6371.0 * 2.0 * asin(sqrt(a));
    
    jogador.distancia = distancia;

    // Verifica se a distância é menor que a melhor palpite atual
    if (distancia < melhor_palpite || melhor_palpite == 0) melhor_palpite = distancia;
    
    // Exibe o palpite do jogador
    printf("> [AVISO] MELHOR PALPITE: %.3fkm\n", melhor_palpite);
}

int main (){

    // Declaração de variáveis
    int num_jogadores = 0;
    double melhor_palpite = 0.0;
    double LatC = 0.0, LonC = 0.0;

    // Entrada da quantidade de jogadores, latitude e longitude do ponto correto
    cin >> num_jogadores >> LatC >> LonC;
    
    // Declara um vetor de Jogador com o tamanho especificado
    vector<Jogador> jogadores(num_jogadores);

    // Entrada dos dados dos jogadores
    for (int i = 0; i < num_jogadores; i++) {
        cin >> jogadores[i].nome >> jogadores[i].latitude >> jogadores[i].longitude;
        Melhor_Palpite (jogadores[i], LatC, LonC, melhor_palpite);
    }

    cout << "\n" << "RANKING" << "\n-------" << endl;

    // Ordena os jogadores pela distância
    sort(jogadores.begin(), jogadores.end(), [](const Jogador& a, const Jogador& b) {
        return a.distancia < b.distancia;
    });
    
    // Exibe o ranking dos jogadores
    for (const auto& jogador : jogadores) {
        int posicao = &jogador - &jogadores[0] + 1;
        
        // Formatação corrigida para números de 1 ou 2 dígitos
        if (posicao < 10) {
            printf(" %d. %-20s : %6.3f km", posicao, jogador.nome.c_str(), jogador.distancia);
        } else {
            printf("%d. %-20s : %6.3f km", posicao, jogador.nome.c_str(), jogador.distancia);
        }

        if (jogador.distancia < 0.050) {
            printf(" [FANTASTICO]");
        }
        printf("\n");
    }

    return 0;
}