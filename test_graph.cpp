#include <iostream>

#include "graph.h"
#include "graph_algorithms.h"
#include "timer.h"

using namespace std;

int main() {
  timer t;
  t.start();

  // Create a graph.
  graph<int, double> g;
  g.insert_vertex(5);
  g.insert_vertex(4);
  g.insert_edge(0, 1, 0.5);
  g.insert_edge(1, 0, 0.25);

  t.stop();
  cout << "Creating the graph took " << t.elapsed() / 1e6 << " ms" << endl;
  t.restart();

  // Exercise iterators and accessors.
  for(auto vi = g.vertices_begin(); vi != g.vertices_end(); ++vi)
    cout << (*vi)->descriptor() << " " << (*vi)->property() << endl;

  for(auto vi = g.vertices_cbegin(); vi != g.vertices_cend(); ++vi)
    cout << (*vi)->descriptor() << " " << (*vi)->property() << endl;

  for(auto ei = g.edges_begin(); ei != g.edges_end(); ++ei)
    cout << (*ei)->source() << " " << (*ei)->target() << " "
         << (*ei)->property() << endl;

  for(auto ei = g.edges_cbegin(); ei != g.edges_cend(); ++ei)
    cout << (*ei)->source() << " " << (*ei)->target() << " "
         << (*ei)->property() << endl;

  // Exercise find
  graph<int, double>::edge_descriptor ed(0, 1);
  cout << (*g.find_vertex(0))->property() << " "
       << (*g.find_edge(ed))->property()
       << endl;

  // Exercise erase
  g.erase_edge(ed);
  g.erase_vertex(0);

  // Exercise output
  cout << g;

  t.stop();
  cout << "Exercises took " << t.elapsed() / 1e6 << " ms" << endl;
}
