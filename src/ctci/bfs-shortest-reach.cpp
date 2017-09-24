//
// BFS: Shortest Reach in a Graph
// https://www.hackerrank.com/challenges/ctci-bfs-shortest-reach
//
// Consider an undirected graph consisting of  nodes where each node is labeled from  to  and the edge
// between any two nodes is always of length . We define node  to be the starting position for a BFS.
// 
// Given  queries in the form of a graph and some starting node, , perform each query by calculating
// the shortest distance from starting node  to all the other nodes in the graph. Then print a single
// line of  space-separated integers listing node 's shortest distance to each of the  other nodes
// (ordered sequentially by node number); if  is disconnected from a node, print  as the distance to that node.
//

#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
using namespace std;

const int edge_weight = 6;

struct QueryCache {
    unordered_map<long, int> distances;

    int lookup_distance(int start, int end) const {
        if (start == end) return 0;
        auto cached = distances.find(cache_key(start, end));
        return cached == distances.end() ? -1 : cached->second;
    }
    
    int record_distance(int start, int end, int distance) {
        return distances[cache_key(start, end)] = distance;
    }

    long cache_key(int start, int end) const {
        return (start << 16) | end;
    }
};

struct BidirectionalGraph {
    QueryCache& cache;    
    unordered_map<int, unordered_set<int>> edges;

    void add_edge(int u, int v) {
        insert_edge(u, v);
        insert_edge(v, u);
    }
    
  private:
    void insert_edge(int u, int v) {
        edges[u].insert(v);
        cache.record_distance(u, v, edge_weight);
    }
};

struct Query {
    const BidirectionalGraph& g;
    int start;
    int end;
    
    deque<pair<int /* node */, int /* from_start */>> queue;
    unordered_set<int> visited;

    int distance() {
        
        enqueue(start, 0);
        
        while (!queue.empty()) {
            int node, from_start;
            tie(node, from_start) = queue.front();
            if (node == end)
                return from_start;

            queue.pop_front();
            from_start += edge_weight;

            auto edges = g.edges.find(node);
            if (edges == g.edges.end()) continue;            
            for (auto next : edges->second) {
                if (!enqueue(next, from_start))
                    break;
            }
        }
        return -1;
    }
    
    bool enqueue(int node, int from_start) {
        if (!visited.insert(node).second)
            return true;
        int to_end = g.cache.lookup_distance(node, end);
        if (to_end >= 0) {
            queue.push_front(make_pair(end, from_start + to_end));
            g.cache.record_distance(start, end, from_start + to_end);
            return false;
        } else {        
            queue.push_back(make_pair(node, from_start));
            g.cache.record_distance(start, node, from_start);
            return true;
        }
    }
};

int main() {
    int queries; cin >> queries;
    for (int t = 0; t < queries; t++) {
        QueryCache cache;
        
        int n, m; cin >> n; cin >> m;
        BidirectionalGraph graph { cache };
        for (int i = 0; i < m; ++i) {
            int u, v; cin >> u >> v;
            graph.add_edge(u, v);
        }
        
        int start; cin >> start;
        for (int i = 1; i <= n; ++i) {
            if (i != start)
                cout << Query { graph, start, i }.distance() << ' ';
        }
        
        cout << endl;
    }
    return 0;
}
