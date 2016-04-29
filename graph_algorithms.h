#ifndef _GRAPH_ALGORITHMS_H_
#define _GRAPH_ALGORITHMS_H_

#include <map>
#include <queue>
#include <algorithm>
#include <vector>
#include <iostream>
// This is an example list of the basic algorithms we will work with in class.
//
// In general this is what the following template parameters are:
//
//  - Graph: type of graph, literally your adjacency list graph.
//
//  - ParentMap: associative container between vertex_descriptors and parent
//               vertex_descriptors. This is a representation of the free
//               trees/forests created by these search methods.
//
//  - DistanceMap: associative container between vertex_descriptors and
//                 EdgeProperties. This represents the summation of the path
//                 weights to the vertex itself.
//
// Assume EdgeProperties can be added and compared with less than/less than or
// equal.
//
// Remember that every extra algorithm you implement can earn you bonus.

enum Label {UNEXPLORED, VISITED, DISCOVERY, CROSS, BACK};

///@todo Implement breadth-first search.
template<typename Graph, typename ParentMap>
void breadth_first_search(const Graph& g,
                          const typename Graph::vertex_descriptor vd,
                          ParentMap& p) {

    std::queue<typename Graph::vertex_descriptor> q;
    typename Graph::vertex_descriptor current = vd;

    // Add the root node to our queue
    (*g.find_vertex(current)).second->set_label(VISITED);
    q.push(current);

    while (!q.empty()) {
        // For each node in the queue
        current = q.front();
        q.pop();

        auto i_curr = g.find_vertex(current);

        // Look at each edge of the node
        for (auto i_e = (*i_curr).second->begin();
             i_e != (*i_curr).second->end(); ++i_e) {
            auto n = (*i_e).second->target();
            auto i_n = g.find_vertex(n);

            // If the vertex on the other size of that edge is unexplored,
            // explore it and add it to the queue
            if ((*i_n).second->get_label() == UNEXPLORED) {
                (*i_n).second->set_label(VISITED);
                p[n] = current;
                q.push((*i_n).second->descriptor());

                (*i_e).second->set_label(DISCOVERY);

            // If it goes to an unexplored node, that's either
            } else if ((*i_n).second->descriptor() != current) {
                // Another node in same level, or
                (*i_e).second->set_label(CROSS);

            } else if ((*i_n).second->descriptor() == current) {
                // A self-loop
                (*i_e).second->set_label(CROSS);

            }
        }
    }
}

///@bonus Implement depth-first search.
template<typename Graph, typename ParentMap>
void depth_first_search(const Graph& g,
    const typename Graph::vertex_descriptor vd, ParentMap& p);

///@todo Implement one of the MST or SSSP algorithms.
///@bonus Implement the other algorithms below.
template<typename Graph, typename ParentMap>
void mst_prim_jarniks(const Graph& g, ParentMap& p);

template<typename Graph, typename ParentMap>
void mst_kruskals(const Graph& g, ParentMap& p) {
    // Initialization and setup //
    //////////////////////////////
    std::multimap<size_t,typename Graph::edge_descriptor> m;

    for (auto i = g.edges.begin(); i != g.edges.end(); ++i) {
        // insert the edges into a map that sorts them in ascending order
        m.insert(std::pair<size_t,
                 typename Graph::edge_descriptor>(i->second->property(),
                 i->first));
    }

    auto e = m.end();
    --e;
    std::cout << m.begin()->first << std::endl;
    std::cout << e->first         << std::endl;

    // if only one edge is in the map, then all the edges have the same weight
    // (and thus overwrote each other in the map)
    if (m.begin()->first == e->first) {
        std::cout << "All edges have the same weight.";
        std::cout << "Therefore, every spanning tree is a";
        std::cout << "minimum spanning tree.\n";
        return;
    }

    // defines a cluster as a vector of vertex descriptors
    typedef std::vector<typename Graph::vertex_descriptor> cluster;

    // creates a cluster of clusters, (i.e., each vertex has its own vector,
    // so more can be added during the merge process)
    std::vector<cluster> clusters(g.num_vertices());

    // creates a vector of pointers to each of the clusters
    std::vector<cluster*> cluster_map(g.num_vertices());

    // assumes vertices are from [0,n-1]; if some have been deleted,
    // this will not work

    // for every vertex in g
    for (size_t i = 0; i < g.num_vertices(); ++i ) {
        // add the vertex to its own cluster
        clusters[i].push_back(i);
        // set a pointer to that cluster
        cluster_map[i] = &clusters[i];
    }

    // Creating the MST using Kruskal's Algorithm //
    ////////////////////////////////////////////////

    while (p.size() < g.num_vertices() - 1) {
        std::cout << "Run " << p.size() << " of " << g.num_vertices() - 1;
        std::cout << std::endl;

        auto s = m.begin();
        auto a = m.begin()->first;

        // gets the edge to be checked
        std::pair<size_t,size_t> n = s->second;
        m.erase(a);
        std::cout << n.first << ' ' << n.second << std::endl;

        // checks if the vertices are in different clusters
        if (cluster_map[n.first] != cluster_map[n.second]) {
            // inserts the edge into the parent map
            p.insert(std::pair<size_t,size_t>(n.second, n.first));

            // if the first cluster is larger than the second cluster
            if ((*cluster_map[n.first]).size() > (*cluster_map[n.second]).size()) {
                auto cl = cluster_map[n.second];
                for (size_t i = 0; i < cl->size(); ++i) {
                    // takes an element from the smaller cluster,
                    // adds it to the larger one (needs cleaning up, probably)
                    (*cluster_map[n.first]).push_back((*cluster_map[n.second])[i]);
                    cluster_map[n.second] = cluster_map[n.first];
                }
            }

            // otherwise, use the other cluster
            else {
                auto cl = cluster_map[n.first];
                for (size_t i = 0; i < cl->size(); ++i) {
                    // takes an element from the smaller cluster,
                    // adds it to the larger one (needs cleaning up, probably)
                    (*cluster_map[n.second]).push_back((*cluster_map[n.first])[i]);
                    cluster_map[n.first] = cluster_map[n.second];
                }
            }
        }
    }

}

template<typename Graph, typename ParentMap, typename DistanceMap>
void sssp_dijkstras(const Graph& g, const typename Graph::vertex_descriptor vd,
    ParentMap& p, DistanceMap& d);

template<typename Graph, typename ParentMap, typename DistanceMap>
void sssp_bellman_ford(const Graph& g,
    const typename Graph::vertex_descriptor vd, ParentMap& p, DistanceMap& d);

#endif
