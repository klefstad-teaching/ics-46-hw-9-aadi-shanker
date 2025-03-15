#include "dijkstras.h"
#include <queue>
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distance(n, INF);
    vector<bool> visited(n, false);
    previous.assign(n, -1);

    using Node = pair<int, int>;  // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()){
        auto [dist_u, u] = pq.top();
        pq.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for (const auto &edge : G[u]){
            int v = edge.dst;
            int w = edge.weight;
            if (!visited[v] && dist_u + w < distance[v]){
                distance[v] = dist_u + w;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> path;
    
    if (destination < 0 || destination >= (int)distances.size() || distances[destination] == INF)
        return path;
    
    for (int cur = destination; cur != -1; cur = previous[cur])
        path.push_back(cur);
    
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    for (size_t i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}