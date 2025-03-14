#include "dijkstras.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph-file>" << endl;
        return 1;
    }

    Graph G;
    file_to_graph(argv[1], G);

    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);

    for (int i = 0; i < G.numVertices; i++) {
        vector<int> path = extract_shortest_path(distance, previous, i);
        if (!path.empty()) {
            print_path(path, distance[i]);
        }
    }
    return 0;
}
