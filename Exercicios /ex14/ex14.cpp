#include <iostream>
#include <string>
using namespace std;

string Polimero (string palavra){   
    string resultado = "";
    int n = palavra.size();
    
    for (int len = n - 1; len >= 1; len--) {
        string prefixo = palavra.substr(0, len);
        string sufixo = palavra.substr(n - len, len);
        
        if (prefixo == sufixo) {
            resultado = prefixo;
            break;
        }
    }
    
    return resultado;
}

int main(){
    int x;
    string palavra, resultado;
    cin >> x;
    for (int i=0; i<x; i++){
        cin >> palavra;
        resultado = Polimero(palavra);
        cout << resultado << endl;
    }
    return 0;
}