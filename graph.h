#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <cstddef>
#include <iostream>
#include <list>
#include <utility>
#include <map>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////
/// A generic adjacency-list graph where each vertex stores a VertexProperty and
/// each edge stores an EdgeProperty.
////////////////////////////////////////////////////////////////////////////////
template<typename VertexProperty, typename EdgeProperty>
class graph {

  // The vertex and edge classes are forward-declared to allow their use in the
  // public section below. Their definitions follow in the private section
  // afterward.
  class vertex;
  class edge;
  class vertex_counter;

  public:

    // Required public types

    /// Unique vertex identifier
    typedef size_t vertex_descriptor;

    /// Unique edge identifier represents pair of vertex descriptors
    typedef std::pair<size_t, size_t> edge_descriptor;

    ///@todo Choose a container for the vertices. It should contain "vertex*" or
    ///      shared_ptr<vertex>.
    /// example:
    //    typedef std::list<vertex*> MyVertexContainer;

    // implemented using a map so the vertexes can be found by their descriptors
    typedef std::map<vertex_descriptor, vertex*> MyVertexContainer;

    ///@todo Choose a container for the edges. It should contain "edge*" or
    ///      shared_ptr<edge>.
    /// example:
    typedef std::map<edge_descriptor, edge*> MyEdgeContainer;

    ///@todo Choose a container for the adjacency lists. It should contain
    ///      "edge*" or shared_ptr<edge>.
    /// example:
    typedef std::map<edge_descriptor, edge*> MyAdjEdgeContainer;

    // Vertex iterators
    typedef typename MyVertexContainer::iterator vertex_iterator;
    typedef typename MyVertexContainer::const_iterator const_vertex_iterator;

    // Edge iterators
    typedef typename MyEdgeContainer::iterator edge_iterator;
    typedef typename MyEdgeContainer::const_iterator const_edge_iterator;

    // Adjacency list iterators
    typedef typename MyAdjEdgeContainer::iterator adj_edge_iterator;
    typedef typename MyAdjEdgeContainer::const_iterator const_adj_edge_iterator;


    // Defined containers
    MyVertexContainer vertices;         // container for vertices
    MyEdgeContainer edges;              // container for edges
    vertex_counter counter;


    // Required graph operations

    ///@todo Define constructor/destructor
    graph() {}

    ~graph() {
        clear();
    }

    graph(const graph&) = delete;             ///< Copy is disabled.
    graph& operator=(const graph&) = delete;  ///< Copy is disabled.

    ///@todo Define vertex iterator operations
    vertex_iterator vertices_begin() {return vertices.begin();}
    const_vertex_iterator vertices_cbegin() const {return vertices.cbegin();}
    vertex_iterator vertices_end() {return vertices.end();}
    const_vertex_iterator vertices_cend() const {return vertices.cend();}

    ///@todo Define edge iterator operations
    edge_iterator edges_begin() {return edges.begin();}
    const_edge_iterator edges_cbegin() const {return edges.cbegin();}
    edge_iterator edges_end() {return edges.end();}
    const_edge_iterator edges_cend() const {return edges.cend();}

    ///@todo Define accessors
    // return the number of vertices in the graph
    size_t num_vertices() const {
       return vertices.size();
    }
    // return the number of edges in the graph
    size_t num_edges() const {
       return edges.size();
    }

    // find a vertex in the graph
    vertex_iterator find_vertex(vertex_descriptor vd) {
        // uses the map's member function find() to search for the desired vertex
        vertex_iterator v = vertices.find(vd);
        return v;
    }

    const_vertex_iterator find_vertex(vertex_descriptor vd) const {
        const_vertex_iterator v = vertices.find(vd);
        return v;
    }

    // find an edge in the graph
    edge_iterator find_edge(edge_descriptor ed) {
    edge_iterator e = edges.find(ed);
        return e;
    }

    const_edge_iterator find_edge(edge_descriptor ed) const {
    const_edge_iterator e = edges.find(ed);
        return e;
    }

    ///@todo Define modifiers
    // insert a new vertex into the graph
    vertex_descriptor insert_vertex(const VertexProperty& vp) {
        // assigns the vertex a value based on the vertex counter
        vertex_descriptor vd = counter.next();
        // inserts a new vertex using the map's []operator
        vertices[vd] = new vertex(vd, vp);
        return vd;
    }

    // insert a new directed edge into the graph
    edge_descriptor insert_edge(vertex_descriptor v1, vertex_descriptor v2,
                                const EdgeProperty& ep) {
        // make an edge descriptor from the two vertices
        edge_descriptor ed = edge_descriptor(v1, v2);
        // find the vertices to make sure they exist
        vertex_iterator va = find_vertex(v1);
        vertex_iterator vb = find_vertex(v2);
        // if they do not exist, add them
        if(va == vertices.end()) {v1 = insert_vertex(v1); va = find_vertex(v1);}
        if(vb == vertices.end()) {v2 = insert_vertex(v2); vb = find_vertex(v2);}
        // create the edge
        edge* e = new edge(v1,v2,ep);
        // add it to the master edge map
        edges[ed] = e;
        // add the edge to the vertices' adjacent edge maps
        va->second->adj_edge[ed] = e;
        vb->second->adj_edge[ed] = e;

        return ed;
    }

    // insert a new undirected edge (two edges connecting the same vertices going in opposite directions)
    void insert_edge_undirected(vertex_descriptor v1, vertex_descriptor v2,
                                const EdgeProperty& ep) {
        // insert two edges, going to and from both vertices
        insert_edge(v1, v2, ep);
        insert_edge(v2, v1, ep);
    }

    // erase a vertex
    void erase_vertex(vertex_descriptor v) {
        // find the desired vertex in the vertex map
        vertex_iterator eraser = vertices.find(v);
        // find its adjacent edge map
        edge_iterator e = eraser->second->adj_edge.begin();
        while(e != eraser->second->adj_edge.end()) {
            // for every edge adjacent to it, delete the edge
            erase_edge(e->first);
            ++e;
        }
    }

    // erase a directed edge
    void erase_edge(edge_descriptor e) {
        vertex_descriptor v1 = e.first;
        vertex_descriptor v2 = e.second;

        // insert error case for vertex not existing?
        // find the source vertex//
        vertex_iterator vv = vertices.find(v1);
        // erase it
        vv->second->adj_edge.erase(e);
        // find the target vertex
        vv = vertices.find(v2);
        // erase it
        vv->second->adj_edge.erase(e);
        // find edge, delete it using an iterator
        // find the actual edge
        auto iterator = edges.find(e);
        // delete it
        delete iterator->second;
        // delete the final pointer from the master edge map
        edges.erase(e);
    }

    // clear all edges and vertices from the graph
    void clear() {
        vertex_iterator v = vertices.begin();
        while(v != vertices.end()) {
           erase_vertex(v->first);
           ++v;
        }
    }

    // Friend declarations for input/output.
    template<typename V, typename E>
    friend std::istream& operator>>(std::istream&, graph<V, E>&);
    template<typename V, typename E>
    friend std::ostream& operator<<(std::ostream&, const graph<V, E>&);


  private:

    // Required internal classes

    ////////////////////////////////////////////////////////////////////////////
    /// Vertices represent the nodes in the graph.
    ///
    /// @todo Specify the internal state of the vertex class and define all of
    ///       the functions declared in its interface.
    ////////////////////////////////////////////////////////////////////////////
    class vertex {

      public:

        vertex(vertex_descriptor vd, const VertexProperty& vp) : desc(vd), prop(vp) {}

        adj_edge_iterator begin() {return adj_edge.begin();}
        const_adj_edge_iterator cbegin() const {return adj_edge.cbegin();}
        adj_edge_iterator end() {return adj_edge.end();}
        const_adj_edge_iterator cend() const {return adj_edge.cend();}

        size_t get_label() const {return label;}
        void set_label(size_t l) {label = l;}

        ///@todo Define accessor operations
        const vertex_descriptor descriptor() const {return desc;}
        VertexProperty& property() {return prop;}
        const VertexProperty& property() const {return prop;}

        MyAdjEdgeContainer adj_edge;

      private:

        ///@todo Specify the internal state of a vertex.
        vertex_descriptor desc;
        VertexProperty prop;
        size_t label;

    };

    class vertex_counter {

        public:

            vertex_counter(vertex_descriptor start = 0) : counter(start) {}

            vertex_descriptor next() {
                vertex_descriptor c = counter;
                ++counter;
                return c;
            }


        private:
            vertex_descriptor counter;
    };


    ////////////////////////////////////////////////////////////////////////////
    /// Edges represent the connections between nodes in the graph.
    ///
    /// @todo Specify the internal state of the edge class and define all of the
    ///       functions declared in its interface.
    ////////////////////////////////////////////////////////////////////////////
    class edge {

      public:

        ///@todo Define constructor
        edge(vertex_descriptor s, vertex_descriptor t, const EdgeProperty& p) :
            start(s), end(t), prop(p) {
                desc = edge_descriptor(s,t);
            }

        ///@todo Define accessor operations
        const vertex_descriptor source() const {return start;}
        const vertex_descriptor target() const {return end;}
        const edge_descriptor descriptor() const {return desc;}
        EdgeProperty& property() {return prop;}
        const EdgeProperty& property() const {return prop;}

        size_t get_label() const {return label;}
        void set_label(size_t l) {label = l;}

      private:

        ///@todo Specify the internal state of an edge.
        vertex_descriptor start;
        vertex_descriptor end;
        edge_descriptor desc;
        EdgeProperty prop;
        size_t label;
    };

};

///@todo Define io operations for the graph.
template<typename V, typename E>
std::istream& operator>>(std::istream& is, graph<V, E>& g) {
    size_t num_vertices = 0;
    size_t num_edges = 0;
    is >> num_vertices >> num_edges;

    V vd;
    E ed;
    for (size_t i = 0; i < num_vertices; ++i) {
       is >> vd;
       g.insert_vertex(vd);
    }

    size_t v1, v2;
    for (size_t i = 0; i < num_edges; ++i) {
       is >> v1 >> v2 >> ed;
       g.insert_edge(v1, v2, ed);
    }

    return is;
}

template<typename V, typename E>
std::ostream& operator<<(std::ostream& os, const graph<V, E>& g) {
    os << g.num_vertices() << ' ' << g.num_edges() << std::endl;

    for (auto v = g.vertices_cbegin(); v != g.vertices_cend(); ++v) {
        os << (*v).second->property() << std::endl;
    }

    for (auto e = g.edges_cbegin(); e != g.edges_cend(); ++e) {
        os << (*e).second->source() << ' ';
        os << (*e).second->target() << ' ';
        os << (*e).second->property() << std::endl;
    }

    return os;
}

#endif
