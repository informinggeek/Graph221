#include <iostream>
#include <fstream>
#include <map>

#include "graph.h"
#include "graph_algorithms.h"
#include "timer.h"

using namespace std;

int main() {
    timer t;
    t.start();

    // Create a graph.
    graph<int, double> g;
    // g.insert_vertex(5);
    // g.insert_vertex(4);
    // g.insert_edge(0, 1, 0.5);
    //  g.insert_edge(1, 0, 0.25);

    // testing input stream
    ifstream is{"football.g"};
    is>>g;

    t.stop();
    cout << "Creating the graph took " << t.elapsed() / 1e6 << " ms" << endl;
    t.restart();


    cout << "Number of vertices: " << g.num_vertices() << endl;
    cout<< "Number of edges: " << g.num_edges() << endl;
    // Exercise iterators and accessors.
    /* for(auto vi = g.vertices_begin(); vi != g.vertices_end(); ++vi)
        cout << (*vi).second->descriptor() << " " << (*vi).second->property() << endl;

    for(auto vi = g.vertices_cbegin(); vi != g.vertices_cend(); ++vi)
        cout << (*vi).second->descriptor() << " " << (*vi).second->property() << endl;

    for(auto ei = g.edges_begin(); ei != g.edges_end(); ++ei)
        cout << (*ei).second->source() << " " << (*ei).second->target() << " "
                 << (*ei).second->property() << endl;

    for(auto ei = g.edges_cbegin(); ei != g.edges_cend(); ++ei)
        cout << (*ei).second->source() << " " << (*ei).second->target() << " "
                 << (*ei).second->property() << endl;
    */
    // Exercise find
    //  graph<int, double>::edge_descriptor ed(0, 1);
    //cout << (*g.find_vertex(0)).second->property() << " "
    //     << (*g.find_edge(ed)).second->property()
    //     << endl;

    // Exercise erase
    //  g.erase_edge(ed);
    // g.erase_vertex(0);

    // Exercise output
    cout << "output" << endl;
    cout << g;

    t.stop();
    cout << "Exercises took " << t.elapsed() / 1e6 << " ms" << endl;

    map<size_t, size_t> p;
    graph<int, double>::vertex_descriptor vd(1);

    breadth_first_search(g, vd ,p);

   graph<int, double> k;
   ifstream reader{"test.g"};
   reader>>k;
   std::cout<<"Got to Kruskal's. Using input from test.g.\n";
   map<size_t,size_t> m;
   mst_kruskals(k,m);
   std::cout<<"Finished Kruskal's.\n";
}
