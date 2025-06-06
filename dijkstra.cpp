#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct Aresta {
    int destino;
    int peso;
};

class Grafo {
    int V;
    vector<vector<Aresta>> adj;

public:
    Grafo(int V) : V(V), adj(V) {}

    void adicionarAresta(int u, int v, int peso) {
        adj[u].push_back({v, peso});
    }

    void dijkstra(int origem) {
        vector<int> distancia(V, INF);
        vector<int> anterior(V, -1);
        distancia[origem] = 0;

        // Fila de prioridade (distância, vértice)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> fila;
        fila.push({0, origem});

        while (!fila.empty()) {
            int u = fila.top().second;
            int dist_u = fila.top().first;
            fila.pop();

            if (dist_u > distancia[u]) continue;

            for (const auto& aresta : adj[u]) {
                int v = aresta.destino;
                int peso = aresta.peso;

                if (distancia[u] + peso < distancia[v]) {
                    distancia[v] = distancia[u] + peso;
                    anterior[v] = u;
                    fila.push({distancia[v], v});
                }
            }
        }

        // Mostrar resultado
        cout << "Menores distancias a partir do vertice " << origem << ":\n";
        for (int i = 0; i < V; ++i) {
            cout << "Para " << i << ": ";
            if (distancia[i] == INF) cout << "infinito";
            else cout << distancia[i];
            cout << " | Caminho: ";
            imprimirCaminho(anterior, i);
            cout << "\n";
        }
    }

    void imprimirCaminho(const vector<int>& anterior, int v) {
        if (v == -1) return;
        imprimirCaminho(anterior, anterior[v]);
        if (anterior[v] != -1) cout << " -> ";
        cout << v;
    }
};

// Função principal
int main() {
    Grafo g(7);  // Criação do grafo com 7 vértices

    g.adicionarAresta(0, 1, 2);
    g.adicionarAresta(0, 2, 5);
    g.adicionarAresta(1, 3, 3);
    g.adicionarAresta(2, 3, 2);
    g.adicionarAresta(3, 4, 4);
    g.adicionarAresta(3, 5, 7);
    g.adicionarAresta(4, 5, 2);
    g.adicionarAresta(4, 6, 1);
    g.adicionarAresta(5, 6, 6);

    g.dijkstra(0); // Executa o algoritmo a partir do vértice 0

    return 0;
}