#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

/**
 * @brief Error codes of graph library.
 */
typedef enum
{
    GRAPH_SUCCESS = 0,
    GRAPH_NULL_POINTER,
    GRAPH_MEMORY_ERROR,
    GRAPH_INVALID_VERTEX,
    GRAPH_EDGE_EXISTS,
    GRAPH_EDGE_NOT_FOUND
} graph_error_t;

/**
 * @brief Graph adjacency list node.
 */
typedef struct graph_node
{
    size_t vertex;
    struct graph_node *next;
} graph_node_t;

/**
 * @brief Undirected graph represented by adjacency lists.
 */
typedef struct
{
    graph_node_t **adjacency_lists;
    size_t vertex_count;
} graph_t;

/**
 * @brief Initialize graph.
 *
 * @param graph Graph object.
 *
 * @return Error code.
 */
graph_error_t graph_init(graph_t *graph);

/**
 * @brief Free all graph memory.
 *
 * @param graph Graph object.
 *
 * @return Error code.
 */
graph_error_t graph_destroy(graph_t *graph);

/**
 * @brief Add new vertex to graph.
 *
 * @param graph Graph object.
 * @param vertex_index Index of created vertex.
 *
 * @return Error code.
 */
graph_error_t graph_add_vertex(
    graph_t *graph,
    size_t *vertex_index
);

/**
 * @brief Add edge between two vertices.
 *
 * @param graph Graph object.
 * @param vertex1 First vertex.
 * @param vertex2 Second vertex.
 *
 * @return Error code.
 */
graph_error_t graph_add_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
);

/**
 * @brief Remove edge between two vertices.
 *
 * @param graph Graph object.
 * @param vertex1 First vertex.
 * @param vertex2 Second vertex.
 *
 * @return Error code.
 */
graph_error_t graph_remove_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
);

/**
 * @brief Check whether two vertices are adjacent.
 *
 * @param graph Graph object.
 * @param vertex1 First vertex.
 * @param vertex2 Second vertex.
 * @param result Adjacency check result.
 *
 * @return Error code.
 */
graph_error_t graph_are_adjacent(
    const graph_t *graph,
    size_t vertex1,
    size_t vertex2,
    int *result
);

/**
 * @brief Perform depth-first search.
 *
 * @param graph Graph object.
 * @param start_vertex Starting vertex.
 * @param order Traversal order array.
 * @param count Number of visited vertices.
 *
 * @return Error code.
 */
graph_error_t graph_dfs(
    const graph_t *graph,
    size_t start_vertex,
    size_t *order,
    size_t *count
);

/**
 * @brief Perform breadth-first search.
 *
 * @param graph Graph object.
 * @param start_vertex Starting vertex.
 * @param order Traversal order array.
 * @param count Number of visited vertices.
 *
 * @return Error code.
 */
graph_error_t graph_bfs(
    const graph_t *graph,
    size_t start_vertex,
    size_t *order,
    size_t *count
);

#endif