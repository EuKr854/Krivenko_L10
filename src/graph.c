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