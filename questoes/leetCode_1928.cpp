#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(int tempoMaximo, vector<vector<int>>& arestas, vector<int>& taxasDePassagem) {
        int quantidadeCidades = taxasDePassagem.size();
        vector<vector<pair<int,int>>> grafo(quantidadeCidades);

        construirGrafo(arestas, grafo);
        return dijkstra(grafo, 0, quantidadeCidades - 1, tempoMaximo, taxasDePassagem);
    }

private:
    void construirGrafo(const vector<vector<int>>& arestas, vector<vector<pair<int,int>>>& grafo) {
        for (const auto& aresta : arestas) {
            int u = aresta[0];
            int v = aresta[1];
            int tempo = aresta[2];
            grafo[u].emplace_back(v, tempo);
            grafo[v].emplace_back(u, tempo);
        }
    }

    int dijkstra(const vector<vector<pair<int,int>>>& grafo,
                         int origem, int destino,
                         int tempoMaximo, const vector<int>& taxasDePassagem) {
        int n = grafo.size();
        const int INF = INT_MAX;
        vector<int> custo(n, INF);
        vector<int> menorTempo(n, tempoMaximo + 1);

        custo[origem] = taxasDePassagem[origem];
        menorTempo[origem] = 0;

        using Tupla = tuple<int,int,int>;
        priority_queue<Tupla, vector<Tupla>, greater<>> filaPrioridade;
        filaPrioridade.emplace(custo[origem], menorTempo[origem], origem);

        while (!filaPrioridade.empty()) {
            auto [cAtual, tAtual, cidade] = filaPrioridade.top();
            filaPrioridade.pop();

            if (cidade == destino) {
                return custo[destino];
            }
            if (tAtual > menorTempo[cidade] && cAtual > custo[cidade]) {
                continue;
            }

            for (auto [vizinho, tViajem] : grafo[cidade]) {
                int novoTempo = tAtual + tViajem;
                if (novoTempo > tempoMaximo) 
                    continue;

                int novoCusto = cAtual + taxasDePassagem[vizinho];
                if (novoCusto < custo[vizinho]) {
                    custo[vizinho] = novoCusto;
                    menorTempo[vizinho] = novoTempo;
                    filaPrioridade.emplace(novoCusto, novoTempo, vizinho);
                } else if (novoTempo < menorTempo[vizinho]) {
                    menorTempo[vizinho] = novoTempo;
                    filaPrioridade.emplace(cAtual + taxasDePassagem[vizinho], novoTempo, vizinho);
                }
            }
        }

        return -1; 
    }
};
