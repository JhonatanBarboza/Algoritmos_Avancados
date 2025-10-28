#include <iostream>
using namespace std;

// Função para verificar se um número é primo
bool isPrime(long long num) {
    if (num < 2) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (long long i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return false;
    }
    return true;
}

// Função para encontrar o próximo primo após n
long long nextPrime(long long n) {
    long long candidate = n + 1;
    while (!isPrime(candidate)) {
        candidate++;
    }
    return candidate;
}

// Algoritmo euclidiano estendido para encontrar o inverso multiplicativo
long long extendedGCD(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    long long x1, y1;
    long long gcd = extendedGCD(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}

// Função para calcular o inverso multiplicativo de t módulo p
long long modInverse(long long t, long long p) {
    long long x, y;
    long long gcd = extendedGCD(t, p, x, y);
    
    // Se gcd != 1, então não existe inverso multiplicativo
    if (gcd != 1) return -1;
    
    // Garantir que x seja positivo
    return (x % p + p) % p;
}

int main() {
    long long n, t;
    cin >> n >> t;
    
    // Encontrar o próximo primo após n
    long long p = nextPrime(n);
    
    // Calcular o inverso multiplicativo de t módulo p
    long long a = modInverse(t, p);
    
    cout << a << endl;
    
    return 0;
}