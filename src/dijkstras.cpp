#include "dijkstras.h"
#include <queue>
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);

    using Node = pair<int, int>;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [dist_u, u] = pq.top();
        pq.pop();

        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (const auto& edge : G[u]) {
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && dist_u + w < distance[v]) {
                distance[v] = dist_u + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}