#!/usr/bin/env python3
"""
Visualizador - Executa Guloso.cpp e gera timeline
"""

import matplotlib.pyplot as plt
import matplotlib.patches as patches
import subprocess
import re
import os
import sys

class Visualizador:
    def __init__(self):
        self.multiplicadores = {
            "Aprendiz": 0.75,
            "Aventureiro": 1.0,
            "Cavaleiro": 1.2,
            "Mestre": 1.5,
            "Lenda": 2.0
        }
    
    def executar_guloso(self, entrada=None):
        """Executa o programa Guloso.cpp"""
        try:
            # Verificar se executável existe
            executavel = None
            if os.path.exists("Guloso"):
                executavel = "./Guloso"
            elif os.path.exists("Guloso.exe"):
                executavel = "Guloso.exe"
            else:
                print("⚠️ Executável não encontrado. Tentando compilar...")
                result = subprocess.run(
                    ['g++', '-o', 'Guloso', 'Guloso.cpp', '-std=c++17', '-O2'],
                    capture_output=True, text=True
                )
                if result.returncode != 0:
                    print(f"❌ Erro na compilação: {result.stderr}")
                    return None
                executavel = "./Guloso" if os.name != 'nt' else "Guloso.exe"
                print("✅ Compilação bem-sucedida!")
            
            # Se não foi fornecida entrada, usar exemplo padrão
            if entrada is None:
                entrada = self.exemplo_padrao()
            
            # Armazenar entrada para extrair dados depois
            self.ultima_entrada = entrada
            
            # Executar
            result = subprocess.run(
                [executavel],
                input=entrada,
                capture_output=True,
                text=True,
                timeout=10
            )
            
            if result.returncode != 0:
                print(f"❌ Erro na execução: {result.stderr}")
                return None
                
            return result.stdout
            
        except Exception as e:
            print(f"❌ Erro: {e}")
            return None
    
    def exemplo_padrao(self):
        """Exemplo padrão de entrada"""
        return """1
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
"""
    
    def parse_saida(self, saida):
        """Extrai dados da saída do programa"""
        herois = {}
        tempo_minimo = 0.0
        
        for linha in saida.strip().split('\n'):
            linha = linha.strip()
            
            if '=' in linha and 'Tempo mínimo' not in linha:
                nome = linha.split('=')[0].strip()
                tarefas_str = linha.split('{')[1].split('}')[0].strip()
                
                tarefas = []
                if tarefas_str:
                    tarefas = [int(x.strip()) for x in tarefas_str.split(',') if x.strip()]
                
                herois[nome] = tarefas
                
            elif 'Tempo mínimo' in linha:
                numero = re.findall(r'[\d.]+', linha)
                if numero:
                    tempo_minimo = float(numero[0])
        
        return herois, tempo_minimo
    
    def extrair_dados_entrada(self, entrada):
        """Extrai dados das missões e heróis da entrada"""
        linhas = [l.strip() for l in entrada.strip().split('\n') if l.strip()]
        
        dependencias = {}
        herois_niveis = {}
        
        try:
            casos = int(linhas[0])
            idx = 1
            
            for caso in range(casos):
                n, m = map(int, linhas[idx].split())
                idx += 1
                
                # Ler heróis
                for i in range(n):
                    nome, nivel = linhas[idx].split()
                    herois_niveis[nome] = nivel
                    idx += 1
                
                # Ler missões
                for i in range(m):
                    partes = linhas[idx].split()
                    indice = int(partes[0])
                    tempo = int(partes[1])
                    deps = []
                    
                    if len(partes) > 2:
                        for dep_str in partes[2:]:
                            dep = int(dep_str)
                            if dep != 0:
                                deps.append(dep)
                    
                    dependencias[indice] = {"tempo": tempo, "deps": deps}
                    idx += 1
                
        except Exception as e:
            print(f"⚠️ Erro ao extrair dados: {e}")
            # Fallback para exemplo padrão
            dependencias = {
                1: {"tempo": 10, "deps": []},
                2: {"tempo": 15, "deps": []},
                3: {"tempo": 5, "deps": [1]},
                4: {"tempo": 20, "deps": [2]},
                5: {"tempo": 10, "deps": [3, 4]},
                6: {"tempo": 8, "deps": [1]},
                7: {"tempo": 12, "deps": [6]},
                8: {"tempo": 25, "deps": [5, 7]}
            }
            herois_niveis = {
                "Arthas": "Lenda",
                "Luna": "Aprendiz", 
                "Mira": "Cavaleiro",
                "Theo": "Mestre"
            }
        
        return dependencias, herois_niveis
    
    def calcular_timeline(self, herois, dependencias, herois_niveis):
        """Calcula timeline real respeitando dependências"""
        timeline = {nome: [] for nome in herois.keys()}
        tempo_conclusao = {}
        tempo_livre = {nome: 0.0 for nome in herois.keys()}
        
        # Ordenação topológica das tarefas atribuídas
        todas_tarefas = []
        for nome, tarefas in herois.items():
            for tarefa in tarefas:
                todas_tarefas.append((nome, tarefa))
        
        # Função auxiliar para ordenação topológica
        def ordenar_tarefas():
            visitado = set()
            ordem = []
            
            def dfs(tarefa):
                if tarefa in visitado:
                    return
                visitado.add(tarefa)
                
                for dep in dependencias[tarefa]["deps"]:
                    if dep in [t for _, t in todas_tarefas]:
                        dfs(dep)
                
                ordem.append(tarefa)
            
            for _, tarefa in todas_tarefas:
                if tarefa not in visitado:
                    dfs(tarefa)
            
            return ordem
        
        ordem = ordenar_tarefas()
        
        # Processar tarefas na ordem topológica
        for tarefa in ordem:
            # Encontrar herói responsável
            heroi_executor = None
            for nome, tarefas_heroi in herois.items():
                if tarefa in tarefas_heroi:
                    heroi_executor = nome
                    break
            
            if heroi_executor is None:
                continue
            
            # Calcular tempos
            tempo_base = dependencias[tarefa]["tempo"]
            nivel = herois_niveis[heroi_executor]
            multiplicador = self.multiplicadores[nivel]
            tempo_execucao = tempo_base / multiplicador
            
            # Tempo de início (dependências)
            tempo_deps = 0.0
            for dep in dependencias[tarefa]["deps"]:
                if dep in tempo_conclusao:
                    tempo_deps = max(tempo_deps, tempo_conclusao[dep])
            
            # Tempo de início (disponibilidade do herói)
            tempo_inicio = max(tempo_deps, tempo_livre[heroi_executor])
            tempo_fim = tempo_inicio + tempo_execucao
            
            # Adicionar à timeline
            timeline[heroi_executor].append({
                "tarefa": tarefa,
                "inicio": tempo_inicio,
                "fim": tempo_fim,
                "duracao": tempo_execucao
            })
            
            # Atualizar estados
            tempo_livre[heroi_executor] = tempo_fim
            tempo_conclusao[tarefa] = tempo_fim
        
        # Ordenar por tempo de início
        for nome in timeline:
            timeline[nome].sort(key=lambda x: x["inicio"])
        
        return timeline
    
    def plotar(self, herois, tempo_minimo, entrada=None):
        """Gera gráfico da timeline"""
        # Extrair dados da entrada
        if entrada is None:
            entrada = getattr(self, 'ultima_entrada', self.exemplo_padrao())
        
        dependencias, herois_niveis = self.extrair_dados_entrada(entrada)
        
        cores = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#96CEB4', '#FFEAA7', '#DDA0DD']
        timeline = self.calcular_timeline(herois, dependencias, herois_niveis)
        
        fig, ax = plt.subplots(figsize=(15, 8))
        
        y_pos = 0
        nomes_herois = list(herois.keys())
        tempo_max = 0
        
        for i, nome in enumerate(nomes_herois):
            cor = cores[i % len(cores)]
            
            if not timeline[nome]:
                ax.text(1, y_pos, "(sem tarefas)", ha='left', va='center', 
                       style='italic', color='gray', fontsize=10)
            else:
                for tarefa_info in timeline[nome]:
                    inicio = tarefa_info["inicio"]
                    duracao = tarefa_info["duracao"]
                    tarefa = tarefa_info["tarefa"]
                    
                    # Barra da tarefa
                    rect = patches.Rectangle(
                        (inicio, y_pos - 0.35), duracao, 0.7,
                        facecolor=cor, edgecolor='darkblue',
                        alpha=0.8, linewidth=1.5
                    )
                    ax.add_patch(rect)
                    
                    # Texto da tarefa
                    ax.text(inicio + duracao/2, y_pos, f"T{tarefa}",
                           ha='center', va='center', fontweight='bold',
                           color='white', fontsize=9)
                    
                    # Tempos
                    ax.text(inicio, y_pos - 0.5, f"{inicio:.1f}h",
                           ha='center', va='top', fontsize=7, color='gray')
                    ax.text(inicio + duracao, y_pos - 0.5, f"{inicio + duracao:.1f}h",
                           ha='center', va='top', fontsize=7, color='gray')
                    
                    tempo_max = max(tempo_max, inicio + duracao)
            
            y_pos += 1
        
        # Linha do tempo objetivo
        if tempo_minimo > 0:
            ax.axvline(x=tempo_minimo, color='red', linestyle='--', linewidth=2, alpha=0.7)
            ax.text(tempo_minimo + 0.5, len(herois) - 0.5, 
                   f'Tempo Final: {tempo_minimo:.1f}h',
                   color='red', fontweight='bold', fontsize=10,
                   bbox=dict(boxstyle="round,pad=0.3", facecolor='white', alpha=0.8))
        
        # Configurações
        ax.set_yticks(range(len(herois)))
        ax.set_yticklabels(nomes_herois, fontsize=11, fontweight='bold')
        ax.set_xlabel('Tempo (horas)', fontsize=12, fontweight='bold')
        ax.set_title('Timeline de Execução - Algoritmo Guloso', 
                    fontsize=14, fontweight='bold', pad=20)
        
        ax.grid(True, alpha=0.3)
        ax.set_xlim(-1, max(tempo_max * 1.1, tempo_minimo * 1.2, 10))
        ax.set_ylim(-0.7, len(herois) - 0.3)
        
        plt.tight_layout()
        return fig
    
    def executar_com_entrada_personalizada(self):
        """Permite entrada personalizada"""
        print("📝 Digite a entrada (termine com Ctrl+D):")
        entrada = sys.stdin.read()
        return self.executar_guloso(entrada)
    
    def main(self):
        """Função principal com duas opções"""
        print("🎯 Visualizador - Sistema de Alocação de Tarefas")
        print("=" * 50)
        print("Escolha uma opção:")
        print("1. Executar Guloso.cpp com entrada (executa o programa)")
        print("2. Fornecer entrada + saída diretamente (apenas visualizar)")
        print("-" * 50)
        
        try:
            opcao = input("Digite sua opção (1 ou 2): ").strip()
        except (EOFError, KeyboardInterrupt):
            print("\n👋 Cancelado pelo usuário")
            return
        
        if opcao == "1":
            self.opcao_executar_programa()
        elif opcao == "2":
            self.opcao_entrada_saida_manual()
        else:
            print("❌ Opção inválida! Use 1 ou 2")
    
    def opcao_executar_programa(self):
        """Opção 1: Executa o programa Guloso.cpp"""
        print("\n🚀 Opção 1: Executando Guloso.cpp")
        print("📝 Digite a entrada (termine com uma linha vazia):")
        
        linhas = []
        try:
            while True:
                linha = input()
                if linha.strip() == "":
                    break
                linhas.append(linha)
        except (EOFError, KeyboardInterrupt):
            pass
        
        entrada = '\n'.join(linhas)
        
        if not entrada.strip():
            print("❌ Entrada vazia!")
            return
        
        print("\n⚡ Executando programa...")
        saida = self.executar_guloso(entrada)
        
        if not saida:
            print("❌ Falha na execução")
            return
        
        print("\n📊 Saída do programa:")
        print("-" * 30)
        print(saida)
        print("-" * 30)
        
        self.processar_e_plotar(saida, entrada)
    
    def opcao_entrada_saida_manual(self):
        """Opção 2: Entrada e saída fornecidas pelo usuário"""
        print("\n📋 Opção 2: Entrada e Saída Manual")
        print("📝 Digite a ENTRADA do problema:")
        
        linhas_entrada = []
        try:
            while True:
                linha = input()
                if linha.strip() == "":
                    break
                linhas_entrada.append(linha)
        except (EOFError, KeyboardInterrupt):
            pass
        
        entrada = '\n'.join(linhas_entrada)
        
        print("\n📊 Digite a SAÍDA do programa:")
        
        linhas_saida = []
        try:
            while True:
                linha = input()
                if linha.strip() == "":
                    break
                linhas_saida.append(linha)
        except (EOFError, KeyboardInterrupt):
            pass
        
        saida = '\n'.join(linhas_saida)
        
        if not saida.strip():
            print("❌ Saída vazia!")
            return
        
        print("\n📊 Saída fornecida:")
        print("-" * 30)
        print(saida)
        print("-" * 30)
        
        self.processar_e_plotar(saida, entrada)
    
    def processar_e_plotar(self, saida, entrada=None):
        """Processa saída e gera visualização"""
        # Parse e visualização
        herois, tempo_minimo = self.parse_saida(saida)
        
        if not herois:
            print("❌ Nenhum herói encontrado na saída")
            return
        
        print(f"\n👥 Heróis: {list(herois.keys())}")
        print(f"⏱️ Tempo final: {tempo_minimo:.2f}h")
        
        # Plotar
        print("\n📈 Gerando visualização...")
        fig = self.plotar(herois, tempo_minimo, entrada)
        
        print("✅ Visualização pronta!")
        plt.show()

if __name__ == "__main__":
    visualizador = Visualizador()
    visualizador.main()