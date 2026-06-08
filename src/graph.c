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

graph_error_t graph_are_adjacent(
    const graph_t *graph,
    size_t vertex1,
    size_t vertex2,
    int *result
)
{
    if (graph == NULL || result == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    if (vertex1 >= graph->vertex_count
        || vertex2 >= graph->vertex_count)
    {
        return GRAPH_INVALID_VERTEX;
    }

    *result = graph_has_edge(graph, vertex1, vertex2);

    return GRAPH_SUCCESS;
}

static graph_error_t remove_from_list(
    graph_node_t **head,
    size_t vertex
)
{
    graph_node_t *current;
    graph_node_t *previous;

    current = *head;
    previous = NULL;

    while (current != NULL)
    {
        if (current->vertex == vertex)
        {
            if (previous == NULL)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            free(current);
            return GRAPH_SUCCESS;
        }

        previous = current;
        current = current->next;
    }

    return GRAPH_EDGE_NOT_FOUND;
}

graph_error_t graph_remove_edge(
    graph_t *graph,
    size_t vertex1,
    size_t vertex2
)
{
    graph_error_t result;

    if (graph == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    if (vertex1 >= graph->vertex_count
        || vertex2 >= graph->vertex_count)
    {
        return GRAPH_INVALID_VERTEX;
    }

    result = remove_from_list(
        &graph->adjacency_lists[vertex1],
        vertex2
    );

    if (result != GRAPH_SUCCESS)
    {
        return result;
    }

    result = remove_from_list(
        &graph->adjacency_lists[vertex2],
        vertex1
    );

    return result;
}

static void dfs_recursive(
    const graph_t *graph,
    size_t vertex,
    int *visited,
    size_t *order,
    size_t *count
)
{
    graph_node_t *current;

    visited[vertex] = 1;

    order[*count] = vertex;
    (*count)++;

    current = graph->adjacency_lists[vertex];

    while (current != NULL)
    {
        if (!visited[current->vertex])
        {
            dfs_recursive(
                graph,
                current->vertex,
                visited,
                order,
                count
            );
        }

        current = current->next;
    }
}

graph_error_t graph_dfs(
    const graph_t *graph,
    size_t start_vertex,
    size_t *order,
    size_t *count
)
{
    int *visited;

    if (graph == NULL || order == NULL || count == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    if (start_vertex >= graph->vertex_count)
    {
        return GRAPH_INVALID_VERTEX;
    }

    visited = calloc(
        graph->vertex_count,
        sizeof(int)
    );

    if (visited == NULL)
    {
        return GRAPH_MEMORY_ERROR;
    }

    *count = 0;

    dfs_recursive(
        graph,
        start_vertex,
        visited,
        order,
        count
    );

    free(visited);

    return GRAPH_SUCCESS;
}

graph_error_t graph_bfs(
    const graph_t *graph,
    size_t start_vertex,
    size_t *order,
    size_t *count
)
{
    int *visited;
    size_t *queue;
    size_t front;
    size_t back;
    size_t vertex;
    graph_node_t *current;

    if (graph == NULL || order == NULL || count == NULL)
    {
        return GRAPH_NULL_POINTER;
    }

    if (start_vertex >= graph->vertex_count)
    {
        return GRAPH_INVALID_VERTEX;
    }

    visited = calloc(graph->vertex_count, sizeof(int));
    queue = malloc(graph->vertex_count * sizeof(size_t));

    if (visited == NULL || queue == NULL)
    {
        free(visited);
        free(queue);
        return GRAPH_MEMORY_ERROR;
    }

    front = 0;
    back = 0;
    *count = 0;

    visited[start_vertex] = 1;
    queue[back++] = start_vertex;

    while (front < back)
    {
        vertex = queue[front++];

        order[*count] = vertex;
        (*count)++;

        current = graph->adjacency_lists[vertex];

        while (current != NULL)
        {
            if (!visited[current->vertex])
            {
                visited[current->vertex] = 1;
                queue[back++] = current->vertex;
            }

            current = current->next;
        }
    }

    free(visited);
    free(queue);

    return GRAPH_SUCCESS;
}