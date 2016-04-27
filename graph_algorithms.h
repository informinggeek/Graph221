#ifndef _GRAPH_ALGORITHMS_H_
#define _GRAPH_ALGORITHMS_H_


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

///@todo Implement breadth-first search.
template<typename Graph, typename ParentMap>
void breadth_first_search(const Graph& g,
    const typename Graph::vertex_descriptor vd, ParentMap& p);

///@bonus Implement depth-first search.
template<typename Graph, typename ParentMap>
void depth_first_search(const Graph& g,
    const typename Graph::vertex_descriptor vd, ParentMap& p);

///@todo Implement one of the MST or SSSP algorithms.
///@bonus Implement the other algorithms below.
template<typename Graph, typename ParentMap>				// for the parent map: key = child ID, value = parent ID
void mst_prim_jarniks(const Graph& g, ParentMap& p);

template<typename Graph, typename ParentMap>
void mst_kruskals(const Graph& g, ParentMap& p);

template<typename Graph, typename ParentMap, typename DistanceMap>
void sssp_dijkstras(const Graph& g, const typename Graph::vertex_descriptor vd,
    ParentMap& p, DistanceMap& d);

template<typename Graph, typename ParentMap, typename DistanceMap>
void sssp_bellman_ford(const Graph& g,
    const typename Graph::vertex_descriptor vd, ParentMap& p, DistanceMap& d);

#endif
