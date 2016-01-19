// =====================================================================================
//
//       Filename:  graph_dfs_recursive.cc
//
//    Description:
//
//        Version:  1.0
//        Created:  01/19/2016 08:51:39 PM
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Jiahao Zhu (JZ), uranus.superz@outlook.com
//   Organization:
//
// =====================================================================================

#include <unordered_set>
#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

typedef unordered_set<int> S; // adjacent vertexs
typedef vector<S> G; // Graph - adjacent list
//typedef vector<int> P; // property
typedef tuple<int, int, int, int> p_tuple;
typedef vector<p_tuple> P; // property - color, pi, d, f
typedef unsigned int uint;
enum {WHITE, BLACK, GRAY};
enum {NIL = -1};
enum {Color = 0, Pi = 1, D = 2, F = 3};

void DFS_VISIT(G const&, P&, int&, int);

void DFS(G const& g) {
    // 1. initialize
    P p(g.size(), p_tuple(WHITE, NIL, NIL, NIL));
    int time = 0;

    // 2. iterate all vertexes
    for (int u = 0; u < static_cast<int>(g.size()); ++u)
        if (get<Color>(p[u]) == WHITE)
            DFS_VISIT(g, p, time, u);
}

void DFS_VISIT(G const& g, P& p, int& time, int u) {
    get<Color>(p[u]) = GRAY;
    get<D>(p[u]) = ++time;
    cout << "visiting " << u << endl;

    for (int v : g[u]) {
        if (get<Color>(p[v]) == WHITE) {
            get<Pi>(p[v]) = u;
            DFS_VISIT(g, p, time, v);
        }
    }

    get<Color>(p[u]) = BLACK;
    get<F>(p[u]) = ++time;
}

void print_graph(const G& g) {
    for (auto adjs : g) {
        for (auto vertex : adjs)
            cout << vertex << " ";

        cout << endl;
    }
}

#include	<stdlib.h>

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
    DFS(graph);
    return EXIT_SUCCESS;
}				// ----------  end of function main  ----------
