# 🎯 Visualizador de Timeline - Sistema de Alocação de Tarefas

Um visualizador Python que executa algoritmos de alocação de tarefas (como `Guloso.cpp`) e gera uma timeline visual mostrando como as tarefas são distribuídas entre os heróis ao longo do tempo.

## 📋 Funcionalidades

- **Execução automática** de programas C++ (compila se necessário)
- **Visualização em timeline** com gráfico de Gantt
- **Cálculo de dependências** respeitando pré-requisitos entre tarefas
- **Sistema de multiplicadores** baseado no nível dos heróis
- **Duas modalidades de uso**: execução direta ou entrada manual

## 🚀 Como usar

### Pré-requisitos

```bash
pip install matplotlib
```

### Modalidade 1: Executar programa C++

```bash
python time_line.py
```

Escolha a opção `1` e forneça a entrada do problema. O script irá:
1. Compilar `Guloso.cpp` (se necessário)
2. Executar o programa com sua entrada
3. Processar a saída
4. Gerar a visualização

### Modalidade 2: Entrada e saída manual

Escolha a opção `2` para fornecer diretamente:
1. A entrada do problema
2. A saída esperada do algoritmo

## 📊 Formato de Entrada

```
<número_de_casos>
<n_herois> <m_missoes>
<nome_heroi_1> <nivel_1>
<nome_heroi_2> <nivel_2>
...
<id_missao> <tempo_base> <dependencia_1> <dependencia_2> ...
```

### Exemplo Prático

```
1
4 8
Arthas Lenda
Luna Aprendiz
Mira Cavaleiro
Theo Mestre
1 10 0
2 15 0
3 5 1
4 20 2
5 10 3 4
6 8 1
7 12 6
8 25 5 7
```

**Explicação:**
- **1 caso de teste**
- **4 heróis, 8 missões**
- **Heróis e níveis:**
  - Arthas (Lenda) - multiplicador 2.0x
  - Luna (Aprendiz) - multiplicador 0.75x
  - Mira (Cavaleiro) - multiplicador 1.2x
  - Theo (Mestre) - multiplicador 1.5x

- **Missões e dependências:**
  - Missão 1: 10h base (sem dependências)
  - Missão 2: 15h base (sem dependências)
  - Missão 3: 5h base (depende da missão 1)
  - Missão 4: 20h base (depende da missão 2)
  - Missão 5: 10h base (depende das missões 3 e 4)
  - Missão 6: 8h base (depende da missão 1)
  - Missão 7: 12h base (depende da missão 6)
  - Missão 8: 25h base (depende das missões 5 e 7)

## 🎮 Sistema de Níveis

| Nível | Multiplicador | Efeito |
|-------|---------------|---------|
| Aprendiz | 0.75x | +33% tempo |
| Aventureiro | 1.0x | Tempo normal |
| Cavaleiro | 1.2x | -17% tempo |
| Mestre | 1.5x | -33% tempo |
| Lenda | 2.0x | -50% tempo |

## 📈 Saída Esperada

O programa deve gerar uma saída no formato:
```
NomeHeroi = {missao1, missao2, ...}
Tempo mínimo = XX.X
```

**Exemplo de saída:**
```
Arthas = {1, 3, 4, 5, 8}
Luna = {}
Mira = {6}
Theo = {2, 7}
Tempo mínimo = 37.5
```

## 🎨 Visualização

O script gera uma timeline mostrando:

- **Barras coloridas** para cada tarefa
- **Tempos de início e fim** de cada atividade
- **Linha vermelha tracejada** indicando o tempo final
- **Identificação visual** das tarefas (T1, T2, etc.)
- **Heróis sem tarefas** marcados como "(sem tarefas)"

### Exemplo de Timeline

A imagem mostra a execução do exemplo acima, onde:
- **Arthas** (vermelho) executa as missões mais críticas
- **Theo** (verde) trabalha em paralelo com missões independentes
- **Mira** (azul) executa uma missão específica
- **Luna** não recebe tarefas nesta solução
- **Tempo final**: 37.5 horas

<img width="1505" height="796" alt="Image" src="https://github.com/user-attachments/assets/6902959d-f357-420c-8c0f-d3f0270d948e" />

## 🔧 Estrutura do Código

```python
class Visualizador:
    - executar_guloso()      # Executa programa C++
    - parse_saida()          # Processa saída do algoritmo
    - calcular_timeline()    # Calcula cronograma real
    - plotar()              # Gera visualização
    - main()                # Interface principal
```

## 📝 Recursos Avançados

- **Ordenação topológica** das tarefas respeitando dependências
- **Cálculo automático** de tempos de início baseado em pré-requisitos
- **Compilação automática** do código C++ se necessário
- **Tratamento de erros** robusto para entradas inválidas
- **Interface interativa** com opções claras

## 🛠️ Solução de Problemas

### Erro de compilação
- Certifique-se que `g++` está instalado
- Verifique se `Guloso.cpp` existe no diretório

### Erro na visualização
- Confirme que `matplotlib` está instalado
- Verifique o formato da saída do programa

### Timeline incorreta
- Confirme se as dependências estão corretas na entrada
- Verifique se os nomes dos heróis coincidem entre entrada e saída

## 🤝 Contribuições

Sinta-se à vontade para contribuir com melhorias, correções de bugs ou novas funcionalidades!

---

**Desenvolvido para auxiliar na visualização e análise de algoritmos de escalonamento de tarefas.**