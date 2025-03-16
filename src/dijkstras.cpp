#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    distances[source] = 0;
    previous.assign(G.numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [dist, u] = pq.top(); pq.pop();
        if (dist > distances[u]) continue;

        for (const auto& edge : G[u]) {
            int v = edge.dst, weight = edge.weight;
            int newDist = distances[u] + weight;
            if (newDist < distances[v]) {
                distances[v] = newDist;
                previous[v] = u;
                pq.emplace(newDist, v);
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << endl;
    }
    cout << "Total Weight: " << total << endl;
}
