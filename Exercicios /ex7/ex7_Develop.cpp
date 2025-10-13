#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 100005;
long long v[MAXN];
long long dp[MAXN][2];

int main() {
    int n; 
    cin >> n;

    for(int i = 1; i <= n; i++){
        cin >> v[i];
    }

    // Caso base
    dp[0][1] = 1;
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++){
        // dp[i][0] = não usar cascata na relíquia i (ataque direto)
        dp[i][0] = min(dp[i-1][0], dp[i-1][1]) + v[i];

        // dp[i][1] = usar cascata na relíquia i
        dp[i][1] = min(dp[i-1][1] + (v[i] - 1LL), dp[i-1][0] + max(v[i] - (long long)(i-1), 0LL));
    }

    cout << min(dp[n][0], dp[n][1]) << "\n";
    
    return 0;
}