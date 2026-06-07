#ifndef GRAPH_H
#define GRAPH_H

#include <stddef.h>

typedef enum
{
    GRAPH_SUCCESS = 0,
    GRAPH_NULL_POINTER,
    GRAPH_MEMORY_ERROR,
    GRAPH_INVALID_VERTEX,
    GRAPH_EDGE_EXISTS,
    GRAPH_EDGE_NOT_FOUND
} graph_error_t;

typedef struct graph_node
{
    size_t vertex;
    struct graph_node *next;
} graph_node_t;

typedef struct
{
    graph_node_t **adjacency_lists;
    size_t vertex_count;
} graph_t;

graph_error_t graph_init(graph_t *graph);

graph_error_t graph_destroy(graph_t *graph);

graph_error_t graph_add_vertex(
    graph_t *graph,
    size_t *vertex_index
);

graph_error_t graph_add_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
);

graph_error_t graph_remove_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
);

graph_error_t graph_are_adjacent(
    const graph_t *graph,
    size_t vertex1,
    size_t vertex2,
    int *result
);

#endif