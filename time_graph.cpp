#include <climits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <unordered_map>
#include <string>
#include <utility>

#include "graph.h"
#include "graph_algorithms.h"
#include "timer.h"


using namespace std;

// Create a complete graph of size n.
void initialize_complete_graph(graph<int, double>& g, size_t n) {
  // Add vertices.
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  // Add edges.
  for(auto vi1 = g.vertices_cbegin(); vi1 != g.vertices_cend(); ++vi1)
    for(auto vi2 = g.vertices_cbegin(); vi2 != g.vertices_cend(); ++vi2)
      if((*vi1)->descriptor() != (*vi2)->descriptor())
        g.insert_edge((*vi1)->descriptor(), (*vi2)->descriptor(),
            double(rand()) / RAND_MAX);
}

// Create a mesh graph of size ~n.
void initialize_mesh_graph(graph<int, double>& g, size_t n) {
  // Make n a square number.
  size_t rootn = sqrt(n);
  n = rootn*rootn;

  // Add vertices.
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  // Add edges.
  for(size_t i = 0; i < n; ++i) {
    size_t x = i + 1;
    size_t y = i + rootn;

    if(x % rootn != 0)
      g.insert_edge_undirected(i, x, double(rand()) / RAND_MAX);

    if(y < n)
      g.insert_edge_undirected(i, y, double(rand()) / RAND_MAX);
  }
}

// Create a random of size n.
void initialize_random_graph(graph<int, double>& g, size_t n) {
  // add vertices
  for(size_t i = 0; i < n; ++i)
    g.insert_vertex(i);

  // add edges for connectivity
  for(size_t i=0; i < n - 1; ++i)
    g.insert_edge_undirected(i, i+1, double(rand()) / RAND_MAX);

  size_t num_edges = n*sqrt(n)/2;
  for(size_t i=0; i < num_edges; ++i) {
    size_t s = rand() % n;
    size_t t = rand() % n;
    if(s != t)
      g.insert_edge_undirected(s, t, double(rand()) / RAND_MAX);
    else
      --i;
  }
}

// Run a timed test suite with one of the above initializers.
template<typename Initializer>
void time_graph(Initializer i, size_t n) {
  timer t;
  t.start();

  // Create graph, which tests insertion.

  typedef graph<int, double> graph_id;
  graph_id g;
  i(g, n);

  t.stop();
  cout << "\tCreate: " << t.elapsed() / 1e6 << " ms" << endl;
  t.restart();

  // Test BFS.

  typedef graph_id::vertex_descriptor vertex_descriptor;

  unordered_map<vertex_descriptor, vertex_descriptor> parent_map;
  breadth_first_search(g, parent_map);

  t.stop();
  cout << "\tBFS: " << t.elapsed() / 1e6 << " ms" << endl;
  t.restart();

  // Test find operations.

  double sum = 0;
  for(size_t i = 0; i < g.num_edges() / 2; ++i) {
    if(rand()%2)
      sum += (*g.find_vertex(rand() % g.num_vertices()))->property();
    else {
      graph_id::edge_descriptor ed =
        make_pair(rand() % g.num_vertices(), rand() % g.num_vertices());
      graph_id::edge_iterator ei = g.find_edge(ed);
      if(ei != g.edges_end())
        sum += (*ei)->property();
    }
  }

  t.stop();
  cout << "\tFind: " << t.elapsed() / 1e6 << " ms" << endl;
  t.restart();

  // Test erase operations.

  size_t quarter_edge = g.num_edges() / 4;
  for(size_t i = 0; i < quarter_edge; ++i) {
      graph_id::edge_iterator ei = g.find_edge(
          make_pair(rand() % g.num_vertices(), rand() % g.num_vertices())
          );
      if(ei != g.edges_end())
        g.erase_edge((*ei)->descriptor());
      else
        --i;
  }
  size_t quarter_nodes = g.num_vertices() / 4;
  for(size_t i = 0; i < quarter_nodes; ++i) {
      graph_id::vertex_iterator vi = g.find_vertex(rand() % g.num_vertices());
      if(vi != g.vertices_end())
        g.erase_vertex((*vi)->descriptor());
      else
        --i;
  }

  t.stop();
  cout << "\tErase: " << t.elapsed() / 1e6 << " ms" << endl;
  t.restart();

  // Run BFS again on smaller graph.

  parent_map.clear();
  breadth_first_search(g, parent_map);

  t.stop();
  cout << "\tBFS2: " << t.elapsed() / 1e6 << " ms" << endl;
}

/// @brief Control timing of a single function
/// @tparam Func Function type
/// @param f Function taking a single size_t parameter
/// @param max_size Maximum size of test. For linear - 2^23 is good, for
///                 quadrati - 2^18 is probably good enough, but its up to you.
/// @param name Name of function for nice output
///
/// Essentially this function outputs timings for powers of 2 from 2 to
/// max_size. For each timing it repeats the test at least 10 times to ensure
/// a good average time.
template<typename Func>
void time_function(Func f, size_t graph_size, string name) {
  cout << "Testing " << name << " graph..." << endl;

  // create a clock
  timer t;
  t.start();

  time_graph(f, graph_size);

  // calculate time
  t.stop()
  cout << "test took " << t.elapsed() / 1e6 << " ms" << endl << endl;
}


/// @brief Main function to time all your functions
int main(int argc, char** argv) {
  if(argc != 4) {
    cerr << "Error. Wrong number of arguments. Run program like:" << endl
         << "./timing.o <complete_graph_size> <mesh_graph_size> "
         << "<random_graph_size>" << endl
         << "Example: ./timing.o 300 1750 800" << endl;
    exit(-1);
  }

  srand(0);

  size_t complete_size = atoi(argv[1]);
  size_t     mesh_size = atoi(argv[2]);
  size_t   random_size = atoi(argv[3]);

  time_function(initialize_complete_graph, complete_size, "complete");
  time_function(    initialize_mesh_graph,     mesh_size,     "mesh");
  time_function(  initialize_random_graph,   random_size,   "random");
}
