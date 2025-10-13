/*
 * Problema: Destruição de Relíquias com Cascata
 * 
 * Descrição:
 * Dadas n relíquias com valores v[i], queremos destruir todas elas com custo mínimo.
 * Ao atacar uma relíquia i com custo v[i], ela pode causar dano em cascata nas 
 * relíquias seguintes. O dano decresce conforme a distância.
 * 
 * Estratégia de Programação Dinâmica:
 * dp[i][0] = custo mínimo para destruir as primeiras i relíquias SEM usar cascata em i
 * dp[i][1] = custo mínimo para destruir as primeiras i relíquias USANDO cascata em i
 * 
 * Transições:
 * - dp[i][0]: ataque direto na relíquia i
 *   = min(dp[i-1][0], dp[i-1][1]) + v[i]
 * 
 * - dp[i][1]: usar o efeito cascata da relíquia i
 *   = min(dp[i-1][1] + (v[i] - 1), dp[i-1][0] + max(0, v[i] - (i-1)))
 *   
 *   Onde:
 *   - (v[i] - 1): custo reduzido se já havia cascata anterior
 *   - max(0, v[i] - (i-1)): custo considerando alcance da cascata
 * 
 * Complexidade: O(n)
 * Espaço: O(n)
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 100005;
long long v[MAXN];        // v[i] = valor/força da relíquia i
long long dp[MAXN][2];    // dp[i][j] = custo mínimo para destruir relíquias até i

int main() {
    // Leitura da entrada
    int n; 
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }

    /*
     * Caso base (posição 0 - antes da primeira relíquia):
     * dp[0][0] = 0: nenhuma relíquia destruída, sem cascata ativa
     * dp[0][1] = 1: valor fictício para representar estado com cascata
     *               (usado para facilitar as transições)
     */
    dp[0][0] = 0;
    dp[0][1] = 1;

    // Processa cada relíquia da esquerda para a direita
    for(int i = 1; i <= n; i++){
        /*
         * Opção 1: dp[i][0] - Ataque direto na relíquia i
         * 
         * Escolhemos o menor custo entre:
         * - dp[i-1][0] + v[i]: vinha sem cascata, ataca diretamente
         * - dp[i-1][1] + v[i]: vinha com cascata, ataca diretamente
         * 
         * Em ambos os casos, pagamos o custo total v[i] pois não há
         * redução de custo quando não usamos cascata.
         */
        dp[i][0] = min(dp[i-1][0], dp[i-1][1]) + v[i];

        /*
         * Opção 2: dp[i][1] - Usar efeito cascata na relíquia i
         * 
         * Escolhemos o menor custo entre:
         * 
         * 1) dp[i-1][1] + (v[i] - 1):
         *    Se já havia cascata ativa (estado [1] anterior), o custo
         *    para manter a cascata é reduzido em 1.
         * 
         * 2) dp[i-1][0] + max(v[i] - (i-1), 0):
         *    Se não havia cascata (estado [0] anterior), o custo depende
         *    do alcance da cascata.
         *    - v[i] - (i-1): representa o custo ajustado pelo alcance
         *    - max(..., 0): garante que o custo não seja negativo
         * 
         * O termo (i-1) representa a distância máxima que a cascata
         * pode ter percorrido até a posição i.
         */
        dp[i][1] = min(dp[i-1][1] + (v[i] - 1LL), 
                       dp[i-1][0] + max(v[i] - (long long)(i-1), 0LL));
    }

    /*
     * Resposta final: mínimo entre terminar com ou sem cascata ativa
     * dp[n][0]: destruiu todas sem cascata na última
     * dp[n][1]: destruiu todas com cascata na última
     */
    cout << min(dp[n][0], dp[n][1]) << "\n";
    
    return 0;
}