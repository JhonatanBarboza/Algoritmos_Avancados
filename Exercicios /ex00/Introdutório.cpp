#include <bits/stdc++.h>
using namespace std;

// ------------------------ FUNÇÕES AUXILIARES ------------------------

/*
    Função: Formato

    Descrição: Valida o formato do código do produto #XXXX.

    Parâmetros: Código do produto (string).
    Retorno: Verdadeiro se o formato for válido, falso caso contrário.
*/
bool Formato (const string& codigo){
    // Verifica se o codigo esta no formato #XXXX
    if (codigo.length() < 5 || codigo[0] != '#' || !isdigit(codigo[1]) || !isdigit(codigo[2]) || !isdigit(codigo[3]) || !isdigit(codigo[4])) {
        cout << "Código inválido: o código deve começar com '#' seguido por 4 dígitos. Ajuste o código e tente novamente." << endl;
        return false;
    }
    return true;
}


// ---------------------- FUNÇÕES PRINCIPAIS -------------------------


/*
    Função: Cadastro_Produtos

    Descrição: Lê a quantidade de produtos a serem cadastrados, valida o formato dos códigos,
               verifica duplicidade e armazena os produtos em um mapa.

    Parâmetros: Nenhum.
    Retorno: Mapa contendo os produtos cadastrados e seus preços.
*/
map<string, double> Cadastro_Produtos() {

    // Mapa para armazenar os produtos e seus preços
    map<string, double> produtos;

    // Quantidade de itens a serem cadastrados
    int n;
    cin >> n;

    // Verifica se a quantidade de itens é válida
    if (n < 1 || n > 10000) {
        cout << "Quantidade inválida: o mínimo é 1 e o máximo é 10.000 itens. Ajuste a quantidade e tente novamente." << endl;
        Cadastro_Produtos();
    }

    // Lê os produtos e seus preços
    for (int i = 0; i < n; i++) {
        string codigo;
        double preco;
        cin >> codigo >> preco;

        if (!Formato(codigo)) {
            i--; // Decrementa i para repetir a leitura deste produto
            continue; // Pula para a próxima iteração do loop
        }

        // Verifica se o produto já está cadastrado
        if (produtos.find(codigo) != produtos.end()) {
            cout << "Produto com código " << codigo << " já cadastrado." << endl;
        } else {
            produtos[codigo] = preco;
        }
    }

    return produtos;
}

/*
    Função: Registro_Compras

    Descrição: Lê as compras realizadas, valida o formato dos códigos, verifica a existência dos produtos
               e calcula o total da compra.

    Parâmetros: Mapa contendo os produtos cadastrados e seus preços.
    Retorno: Nenhum.
*/
void Registro_Compras(const map<string, double>& produtos) {

    // Quantidade de itens a serem comprados
    int m;
    // Total da compra
    double totalCompra = 0.0;

    // Processa compras até receber -1
    while (cin >> m && m != -1) {
        
        // Processa itens da compra
        for (int i = 0; i < m; i++) {
            string codigo;
            double peso;
            cin >> codigo >> peso;

            if (!Formato(codigo)) {
                i--; // Decrementa i para repetir a leitura deste produto
                continue; // Pula para a próxima iteração do loop
            }

            // Verifica se produto existe
            if (produtos.find(codigo) != produtos.end()) {
                double valor = produtos.at(codigo) * peso;
                totalCompra += valor;
            } else {
                cout << "Produto com código " << codigo << " não cadastrado." << endl;
            }
        }
        
        printf("R$%.2f\n", totalCompra); // Exibe o total formatado com duas casas decimais
        totalCompra = 0.0; // Reseta o total para a próxima compra
    }
}

// Função principal que coordena o fluxo do programa
int main() {

    // Cadastro dos produtos
    map<string, double> produtos = Cadastro_Produtos();

    // Registro das compras
    Registro_Compras(produtos);

    return 0;
}