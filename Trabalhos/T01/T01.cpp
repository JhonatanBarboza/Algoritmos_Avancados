#include <bits/stdc++.h>
using namespace std;

// Estrutura do nó da Trie
struct TrieNode {
    map<char, TrieNode*> children;
    bool isEndOfWord;
    
    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    // Inserir palavra na Trie
    void insert(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                current->children[c] = new TrieNode();
            }
            current = current->children[c];
        }
        current->isEndOfWord = true;
    }
    
    // Verificar se uma palavra existe na Trie
    bool search(const string& word) {
        TrieNode* current = root;
        for (char c : word) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return current->isEndOfWord;
    }
    
    // Verificar se existe alguma palavra que começa com o prefixo
    bool startsWith(const string& prefix) {
        TrieNode* current = root;
        for (char c : prefix) {
            if (current->children.find(c) == current->children.end()) {
                return false;
            }
            current = current->children[c];
        }
        return true;
    }
};

int main(){
    
    // Declaração de variáveis
    int L, C, D;
    set<string> palavrasEncontradas;

    // Array das 8 direções (dx, dy)
    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},  // linha superior: diagonal esq, cima, diagonal dir
        {0, -1},           {0, 1},   // linha meio: esquerda, direita
        {1, -1},  {1, 0},  {1, 1}    // linha inferior: diagonal esq, baixo, diagonal dir
    };

    // Ler o número de linhas e colunas da matriz
    cin >> L >> C;

    // Declaração da matriz
    char matriz[L][C];
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            cin >> matriz[i][j];
        }
    }

    // Ler o número de palavras do dicionário
    cin >> D;

    // Construir a Trie com as palavras do dicionário
    Trie trie;
    for (int i = 0; i < D; i++){
        string palavra;
        cin >> palavra;
        trie.insert(palavra); 
    }

    // Algoritmo para encontrar as palavras na matriz
    for (int i = 0; i < L; i++){
        for (int j = 0; j < C; j++){
            // Explorar cada uma das 8 direções usando o array
            for (int dir = 0; dir < 8; dir++){
                int di = directions[dir][0];
                int dj = directions[dir][1];
                
                string palavra = "";
                int x = i, y = j;
                
                while (x >= 0 && x < L && y >= 0 && y < C){
                    palavra += matriz[x][y];
                    
                    // OTIMIZAÇÃO COM TRIE: Verificar se ainda é possível formar uma palavra
                    if (!trie.startsWith(palavra)) {
                        // Se não existe nenhuma palavra que começa com este prefixo,
                        // pare de explorar nesta direção
                        break;
                    }
                    
                    // Verificar se a palavra atual existe no dicionário
                    if (palavra.length() >= 2 && trie.search(palavra)){ 
                        palavrasEncontradas.insert(palavra);
                    }
                    
                    // Atualiza as coordenadas para a próxima letra na direção atual 
                    x += di;
                    y += dj;
                }
            }
        }
    }

    // Imprimir a quantidade e as palavras encontradas em ordem alfabética
    cout << palavrasEncontradas.size() << endl;
    for (const auto& palavra : palavrasEncontradas){
        cout << palavra << endl;
    }

    return 0;
}