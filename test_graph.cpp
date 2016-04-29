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

    // testing input stream
    ifstream is{"football.g"};
    is >> g;

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
    cout << "Exercises took " << t.elapsed() / 1e6 << " ms" << endl << endl;


    map<size_t, size_t> p;
    graph<int, double>::vertex_descriptor vd(1);

    cout << "Starting BFS" << endl;
    for (auto v = g.vertices_begin(); v != g.vertices_end(); ++v) {
        (*v).second->set_label(UNEXPLORED);
    }
    for (auto e = g.edges_begin(); e != g.edges_end(); ++e) {
        (*e).second->set_label(UNEXPLORED);
    }

    for (auto v = g.vertices_begin(); v != g.vertices_end(); ++v) {
        if ((*v).second->get_label() == UNEXPLORED) {
            breadth_first_search(g, (*v).second->descriptor(), p);
        }
    }

    bool success = true;
    for (auto v = g.vertices_begin(); v != g.vertices_end(); ++v) {
        if ((*v).second->get_label() == UNEXPLORED) {
            success = false;
        }
    }

    if (!success) {
        cout << "Unlabeled vertex!" << endl;
    } else {
        cout << "BFS labelled all vertices." << endl;
    }

    success = true;
    cout << "Unlabelled edges:" << endl;
    for (auto e = g.edges_begin(); e != g.edges_end(); ++e) {
        if ((*e).second->get_label() == UNEXPLORED) {
            cout << '(';
            cout << (*e).second->source();
            cout << ", ";
            cout << (*e).second->target();
            cout << ')' << endl;
            success = false;
        }
    }

    if (success) {
        cout << "none" << endl;
        cout << "BFS labelled all edges." << endl << endl;
    }


   graph<int, double> k;
   ifstream reader{"test.g"};
   reader >> k;

   cout << "Running Kruskal's. Using input from football.g.\n";
   multimap<size_t,size_t> m;
   mst_kruskals(g,m);
   cout << "Finished Kruskal's for football.g.\n";
   if(g.num_vertices()-1 == m.size()) {
	cout<< "Proper number of edges have been added to the MST.\n";
   }
   else if(m.size() == 0)
   {
	cout << "All edges have the same weight. ";
	cout << "Therefore, every spanning tree is a minimum spanning tree.\n\n";
	success = false;
   }
   else {
	cout<< "Incorrect number of edges.\n\n";
	success = false;
   }
   if(success) {
	cout << "Kruskal's ran successfully.\n\n";
   }

   success = true;

   cout << "Running Kruskal's. Using input from test.g.\n";
   multimap<size_t,size_t> m2;
   mst_kruskals(k,m);
   cout << "Finished Kruskal's for test.g.\n";
   if(k.num_vertices()-1 == m.size()) {
	cout<< "Proper number of edges have been added to the MST.\n";
   }
   else if(m.size() == k.num_edges())
   {
	cout << "All edges have the same weight. ";
	cout << "Therefore, every spanning tree is a minimum spanning tree.\n\n";
   }
   else {
	cout<< "Incorrect number of edges.\n\n";
	success = false;
   }
   if(success) {
	cout << "Kruskal's ran successfully.\n\n";
   }
}
