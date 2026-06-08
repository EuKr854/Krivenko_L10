#include "graph.h"

#include <stdlib.h>

graph_error_t graph_init(graph_t *graph)
{
    if (graph == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    graph->adjacency_lists = NULL;
    graph->vertex_count = 0;

    return GRAPH_SUCCESS;
}

graph_error_t graph_destroy(graph_t *graph)
{
    size_t index;
    graph_node_t *current;
    graph_node_t *next;

    if (graph == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    for (index = 0; index < graph->vertex_count; index++)
    {
        current = graph->adjacency_lists[index];

        while (current != NULL)
        {
            next = current->next;
            free(current);
            current = next;
        }
    }

    free(graph->adjacency_lists);

    graph->adjacency_lists = NULL;
    graph->vertex_count = 0;

    return GRAPH_SUCCESS;
}

graph_error_t graph_add_vertex(
    graph_t *graph,
    size_t *vertex_index
)
{
    graph_node_t **new_lists;

    if (graph == NULL || vertex_index == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    new_lists = realloc(
        graph->adjacency_lists,
        (graph->vertex_count + 1) * sizeof(graph_node_t *)
    );

    if (new_lists == NULL)
    {
        return GRAPH_MEMORY_ERROR;
    }

    graph->adjacency_lists = new_lists;

    graph->adjacency_lists[graph->vertex_count] = NULL;

    *vertex_index = graph->vertex_count;

    graph->vertex_count++;

    return GRAPH_SUCCESS;
}

static int graph_has_edge(
    const graph_t *graph,
    size_t vertex1,
    size_t vertex2
)
{
    graph_node_t *current;

    current = graph->adjacency_lists[vertex1];

    while (current != NULL)
    {
        if (current->vertex == vertex2)
        {
            return 1;
        }

        current = current->next;
    }

    return 0;
}

graph_error_t graph_add_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
)
{
    graph_node_t *node1;
    graph_node_t *node2;

    if (graph == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    if (vertex1 >= graph->vertex_count
        || vertex2 >= graph->vertex_count)
    {
        return GRAPH_INVALID_VERTEX;
    }

    if (graph_has_edge(graph, vertex1, vertex2))
    {
        return GRAPH_EDGE_EXISTS;
    }

    node1 = malloc(sizeof(graph_node_t));

    if (node1 == NULL)
    {
        return GRAPH_MEMORY_ERROR;
    }

    node2 = malloc(sizeof(graph_node_t));

    if (node2 == NULL)
    {
        free(node1);
        return GRAPH_MEMORY_ERROR;
    }

    node1->vertex = vertex2;
    node1->next = graph->adjacency_lists[vertex1];

    graph->adjacency_lists[vertex1] = node1;

    node2->vertex = vertex1;
    node2->next = graph->adjacency_lists[vertex2];

    graph->adjacency_lists[vertex2] = node2;

    return GRAPH_SUCCESS;
}