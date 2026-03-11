/***
 * Author: Sangam Prajapati
 * Course: CSC 3430 - Algorithm Design and Analysis
 * Date: 03/11/2026
 * Project: Greedy Algorithms - Kruskal's Algorithm
 */


#include <iostream>
#include <vector>
#include <algorithm>

struct Edge {
    int u;
    int v;
    int weight;
};

int findSet(int x, std::vector<int>& parent) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x], parent);
    }
    return parent[x];
}

void unionSet(int u, int v, std::vector<int>& parent) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);
    parent[rootU] = rootV;
}

std::vector<Edge> kruskal(std::vector<Edge>& edges, int n) {
    std::vector<Edge> T;
    std::vector<int> parent(n + 1);

    for (int u = 0; u <= n; u++) {
        parent[u] = u;
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge&b) {
        return a.weight < b.weight;
    });

    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        
        if (findSet(u, parent) != findSet(v, parent)) {
            T.push_back(edges[i]);
            unionSet(u, v, parent);
        }
    }

    return T;
}


int main() {
    int n = 6;

    std::vector<Edge> edges = {
        {1,2,6},
        {1,3,1},
        {1,4,5},
        {2,3,5},
        {2,5,3},
        {3,4,5},
        {3,5,6},
        {3,6,4},
        {4,6,2},
        {5,6,6}
    };

    std::vector<Edge> T = kruskal(edges, n);

    int totalWeight = 0;
    std::cout << "Edges in the MST:\n";
    for (int i = 0; i < T.size(); i++) {
        std::cout << T[i].u << "-" << T[i].v << "-" << T[i].weight << "\n";
        totalWeight += T[i].weight;
    }

    std::cout << "Total weight = " << totalWeight << "\n";

    return 0;
}