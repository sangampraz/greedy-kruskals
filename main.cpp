/***
 * Author: Sangam Prajapati
 * Course: CSC 3430 - Algorithm Design and Analysis
 * Date: 03/11/2026
 * Project: Greedy Algorithms - Kruskal's Algorithm
 */

 /***
  * Description:
  * This program implements Kruskal's algorithm to compute the 
  * Minimum Spanning Tre of a weighted, undirected graph. The 
  * algorithm uses the union-find data structure to efficiently 
  * detect cycles while selecting edges withthe smallest weights. 
  */

#include <iostream>
#include <vector>
#include <algorithm>


struct Edge {
    int u;                  // starting vertex
    int v;                  // ending vertex
    int weight;             // weight/cost of the edge
};


/***
 * findSet()
 * finds the representative of the set containing vertex x
 */
int findSet(int x, std::vector<int>& parent) {
    if (parent[x] != x) {
        parent[x] = findSet(parent[x], parent);
    }
    return parent[x];
}


/***
 * unionSet()
 * merges two sets by connecting the root of the one set to the other
 * used after an edge is added tothe MST to combine components
 */
void unionSet(int u, int v, std::vector<int>& parent) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);
    parent[rootU] = rootV;
}


/***
 * kruskal()
 * implements kruskal's algorithm to find the MST
 */
std::vector<Edge> kruskal(std::vector<Edge>& edges, int n) {
    std::vector<Edge> T;                // store the edges of MST
    std::vector<int> parent(n + 1);     // parent array for union-find struct

    for (int u = 0; u <= n; u++) {      // initialize each vertex as its own parent (singelton)
        parent[u] = u;
    }

    // sort edges in ascending order of weight
    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge&b) {
        return a.weight < b.weight;
    });

    // process edges in sorted order
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        // if vertices belong to different sets, add the edge (will not create cycle)
        if (findSet(u, parent) != findSet(v, parent)) {
            T.push_back(edges[i]);
            unionSet(u, v, parent);
        }
    }

    return T;
}


int main() {
    int n = 6;              // number of vertices in the graph

    // list of edges (u, v, weight)
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

    // compute the minimum spanning tree using Kruskal's algorithm
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