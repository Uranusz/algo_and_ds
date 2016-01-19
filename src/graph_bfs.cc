// =====================================================================================
//
//       Filename:  graph.cc
//
//    Description:  represent graph using unordered_set
//
//        Version:  1.0
//        Created:  01/13/2016 11:19:34 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Jiahao Zhu (JZ), uranus.superz@outlook.com
//   Organization:
//
// =====================================================================================

#include <unordered_set>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <queue>

using namespace std;

typedef unordered_set<int> S;
typedef vector<S> G;
typedef vector<int> P; // properties
typedef queue<int> Q; // properties

void print_graph(const G& g) {
    for (G::const_iterator it = g.cbegin(); it != g.cend(); ++it) {
        S::const_iterator it2 = (*it).cbegin();

        for (; it2 != (*it).cend(); ++it2)
            cout << *it2 << " ";

        cout << endl;
    }
}

// ===  FUNCTION  ======================================================================
//         Name:  BFS
//  Description:
// =====================================================================================
void BFS(const G& g, int s) {
    enum {WHITE, GRAY, BLACK};
    enum {NIL = -1};
    P color(g.size(), WHITE);
    P d(g.size(), numeric_limits<int>::max());
    P pi(g.size(), NIL); // -1 means NIL
    // 1. initialize
    color[s] = GRAY;
    d[s] = 0;
    pi[s] = NIL;
    Q queue;
    queue.push(s);

    while (!queue.empty()) {
        int u = queue.front(); // all vertex in Q are gray, they are found but not searched yet
        queue.pop();

        //-----------------------------------------------------------------------------
        //  use c++ 11 syntax instead
        //  for(S::const_iterator it = G[u].cbegin(); it != G[u].cend(); ++it)
        //-----------------------------------------------------------------------------
        for (int v : g[u]) {
            if (color[v] == WHITE) {
                color[v] = GRAY;
                d[v] = d[u] + 1;
                pi[v] = u;
                queue.push(v);
            }
        }

        color[u] = BLACK;
        cout << u << " ";
    }

    cout << endl;
}


// ===  FUNCTION  ======================================================================
//         Name:  print_path
//  Description:  predecessor subgraph - breadth-first tree
// =====================================================================================
void print_path() {
    return ;
}

// ===  FUNCTION  ======================================================================
//         Name:  main
//  Description:
// =====================================================================================
int
main(int argc, char* argv[]) {
    G graph;
    graph.push_back({1, 4});
    graph.push_back({0, 4, 2, 3});
    graph.push_back({1, 3});
    graph.push_back({1, 4, 2});
    graph.push_back({3, 0, 1});
    print_graph(graph);
    cout << "res:" << endl;
    BFS(graph, 1);
    return 0;
}				// ----------  end of function main  ----------
