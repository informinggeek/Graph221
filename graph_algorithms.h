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
    const typename Graph::vertex_descriptor vd, ParentMap& p) {
    for (auto vertex = g.vertices_cbegin(); vertex != g.vertices_cend(); ++vertex) {
        (*vertex).second->set_label(UNEXPLORED);
    }

    for (auto edge = g.edges_cbegin(); edge != g.edges_cend(); ++edge) {
        (*edge).second->set_label(UNEXPLORED);
    }

    std::queue<typename Graph::vertex_descriptor> q;

    typename Graph::vertex_descriptor current = vd;

    (*g.find_vertex(current)).second->set_label(VISITED);
    q.push(current);

    while (!q.empty()) {
        current = q.front();
        q.pop();

        auto i_curr = g.find_vertex(current);

        for (auto i_e = (*i_curr).second->begin(); i_e != (*i_curr).second->end(); ++i_e) {
            auto n = (*i_e).second->target();
            auto i_n = g.find_vertex(n);
            if ((*i_n).second->get_label() == UNEXPLORED) {
                (*i_n).second->set_label(VISITED);
                p[n] = current;
                q.push((*i_n).second->descriptor());

                (*i_e).second->set_label(DISCOVERY);
            } else if ((*i_n).second->descriptor() != current) {
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
void mst_kruskals(const Graph& g, ParentMap& p)
{
// Initialization and setup //
//////////////////////////////
	std::map<size_t,typename Graph::edge_descriptor> m;

	for(auto i = g.edges.begin(); i != g.edges.end(); ++i)
	{
		m.insert(std::pair<size_t, typename Graph::edge_descriptor>(i->second->property(), i->first));		// inserts the edges into a map that sorts them in ascending order
	}
	if (m.size() != g.edges.size())		// if only one edge is in the map, then all the edges have the same weight (and thus overwrote each other in the map)
	{
		std::cout<<"All edges have the same weight. Therefore, every spanning tree is a mininmum spanning tree.\n";
		return;
	}
	typedef std::vector<typename Graph::vertex_descriptor> cluster;		// defines a cluster as a vector of vertex descriptors

	std::vector<cluster> clusters(g.num_vertices());		// creates a cluster of clusters, (i.e., each vertex has its own vector, so more can be added during the merge process
	std::vector<cluster*>cluster_map(g.num_vertices());		// creates a vector of pointers to each of the clusters

	// assumes vertices are from [0,n-1]; if some have been deleted, this will not work

	for(size_t i = 0; i < g.num_vertices(); ++i )			// for every vertex in g
	{
			clusters[i].push_back(i);			// add the vertex to its own cluster
			cluster_map[i] = &clusters[i];			// set a pointer to that cluster
	}

// Creating the MST using Kruskal's Algorithm //
////////////////////////////////////////////////

	while(p.size()<g.num_vertices()-1)
	{
		auto s = m.begin();
		auto a = m.begin()->first;
		std::pair<size_t,size_t> n = s->second;		// gets the edge to be checked
		m.erase(a);
		if(cluster_map[n.first] != cluster_map[n.second])	// checks if the vertices are in different clusters
		{
			p[n.second] = n.first;			// inserts the edge into the parent map
			if((*cluster_map[n.first]).size() > (*cluster_map[n.second]).size())	// if the first cluster is larger than the second cluster
			{
				auto cl = cluster_map[n.second];
				for(size_t i = 0; i < cl->size(); ++i)
				{
					(*cluster_map[n.first]).push_back((*cluster_map[n.second])[i]);	// takes an element from the smaller cluster, adds it to the larger one (needs cleaning up, probably)
					cluster_map[n.second] = cluster_map[n.first];
				}
			}
			else				// otherwise, use the other cluster
			{
				auto cl = cluster_map[n.first];
				for(size_t i = 0; i < cl->size(); ++i)
				{
					(*cluster_map[n.second]).push_back((*cluster_map[n.first])[i]);	// takes an element from the smaller cluster, adds it to the larger one (needs cleaning up, probably)
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
