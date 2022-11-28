#include <iostream>
#include <set>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
#include <queue>
#define INF (int)1e9

struct Graph {  
    int numberOfVertices;
    std::vector<std::vector<std::pair<int, int> > > edges;
    Graph(int n = 1) : numberOfVertices(n) {
        edges = std::vector<std::vector<std::pair<int, int> > >(n);
    }
};

class DijkstraAlgorithm {
    Graph* g;
    std::vector<int> d;
    std::vector<bool> u;
    int startVertice;
public:
    DijkstraAlgorithm(Graph* graph, int s) : startVertice(s) {
        d = std::vector<int>(graph->numberOfVertices, INF);
        d[startVertice] = 0;
        u = std::vector<bool>(graph->numberOfVertices, false);
        g = graph;
    }
    void Execute() {
        int n = g->numberOfVertices;
        int minVertice, to, w;
        for (int iter = 0; iter < n; ++iter) {
            minVertice = -1;
            for (int i = 0; i < n; ++i) {
                if (!u[i] && (minVertice == -1 || d[i] < d[minVertice])) {
                    minVertice = i;
                }
            }
            if (d[minVertice] == INF) break;
            u[minVertice] = true;
            for (auto & i : g->edges[minVertice]) {
                if (d[minVertice] + i.second < d[i.first]) {
                    d[i.first] = d[minVertice] + i.second;
                }
            }
        }
    }
};


std::vector<std::vector<bool> > generateDigraph(int n, int m) {
    std::vector<std::vector<bool> > digraph(n);
    for (int i = 0; i < n; ++i) {
        digraph[i] = std::vector<bool>(n);
    }

    std::mt19937 rng(time(0));
    std::uniform_int_distribution<int> uid(0, n - 1);
    int numberOfEdges = m;
    int i = 0, j = 0;
    while (numberOfEdges--) {
        while (i == j || digraph[i][j] == true) {
            i = uid(rng);
            j = uid(rng);
        }
        digraph[i][j] = true;
    }
    return digraph;
}

Graph generateGraph(int n) {
    Graph g(n);

    std::mt19937 rng(time(0));
    std::uniform_int_distribution<int> uid(0, INF - 1);
    // random digraph
    //std::vector<std::vector<bool> > edges = generateDigraph(n, n*(n-1));
    // fixed digraph
    std::vector<std::vector<bool> > edges(n);
    for (int i = 0; i < n; ++i) {
        edges[i].resize(n);
        for (int j = 0; j < n; ++j) {
            if (i != j) edges[i][j] = true;
            else edges[i][j] = false;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (edges[i][j]) {
                g.edges[i].push_back(std::make_pair(j, uid(rng)));
            }
        }
    }
    return g;
}


int64_t launchTest(Graph* g, int s) {
    DijkstraAlgorithm DA(g, s);
    auto start = std::chrono::high_resolution_clock::now();
    DA.Execute();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();    
}

void startTesting() {
    Graph g;
    std::mt19937 rng(time(0));
    std::ofstream table("table.csv");
    for (int numOfVertices = 20; numOfVertices <= 270; numOfVertices += 5) {
        std::uniform_int_distribution<int> uid(0, numOfVertices - 1);
        g = generateGraph(numOfVertices);
        long long averageDuration = 0.;
        int startVertice = uid(rng);
        for (int iter = 0; iter < 30; ++iter) {
            averageDuration += launchTest(&g, startVertice);
        }
        table << numOfVertices << " " << averageDuration / 30 << '\n';
    }
    table.close();
}


int main() {
    startTesting();
    return 0;
}