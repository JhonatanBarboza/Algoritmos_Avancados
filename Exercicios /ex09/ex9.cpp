#include <iostream>
#include <vector>
using namespace std;

#define MAXN 5005
#define inf 1000000000
#define max(a,b) ((a) > (b) ? (a) : (b))

int main(){

    int X;
    cin >> X;
    for (int i=0; i<X ; i++){
        int D, N;
        cin >> D >> N;

        vector<int> v(N);
        for (int j=0; j<N ; j++) cin >> v[j];
        
        long long dp[3] = {D, -inf, -inf}, newdp[3];
        for (int i = 0; i < N; i++) {
            newdp[0] = newdp[1] = newdp[2] = -inf;

            // Livre
            newdp[0] = max(newdp[0], dp[0]);
            newdp[0] = max(newdp[0], dp[2]); // descanso acabou
            if (dp[0] - v[i] >= 0) newdp[1] = max(newdp[1], dp[0] - v[i]); // comprar

            // Tem passe
            newdp[1] = max(newdp[1], dp[1]); // não faz nada
            newdp[2] = max(newdp[2], dp[1] + v[i]); // garimpa -> descanso

            // Descansando -> já tratado acima no próximo loop
            for (int j = 0; j < 3; j++) dp[j] = newdp[j];
        }

        long long resp = max(dp[0], max(dp[1], dp[2]));
        cout << resp << endl;
    }

    return 0;
}