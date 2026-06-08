#include <stdio.h>

#include "graph.h"

int main(void)
{
    graph_t graph;

    size_t v0;
    size_t v1;
    size_t v2;
    size_t v3;

    int adjacent;

    size_t order[10];
    size_t count;
    size_t index;

    graph_init(&graph);

    graph_add_vertex(&graph, &v0);
    graph_add_vertex(&graph, &v1);
    graph_add_vertex(&graph, &v2);
    graph_add_vertex(&graph, &v3);

    graph_add_edge(&graph, v0, v1);
    graph_add_edge(&graph, v0, v2);
    graph_add_edge(&graph, v1, v3);

    graph_are_adjacent(
        &graph,
        v0,
        v1,
        &adjacent
    );

    printf("Adjacent(0, 1): %d\n", adjacent);

    graph_are_adjacent(
        &graph,
        v2,
        v3,
        &adjacent
    );

    printf("Adjacent(2, 3): %d\n", adjacent);

    graph_dfs(
        &graph,
        0,
        order,
        &count
    );

    printf("DFS: ");

    for (index = 0; index < count; index++)
    {
        printf("%zu ", order[index]);
    }

    printf("\n");

    graph_bfs(
        &graph,
        0,
        order,
        &count
    );

    printf("BFS: ");

    for (index = 0; index < count; index++)
    {
        printf("%zu ", order[index]);
    }

    printf("\n");

    graph_remove_edge(
        &graph,
        v0,
        v1
    );

    graph_are_adjacent(
        &graph,
        v0,
        v1,
        &adjacent
    );

    printf("After removing edge (0, 1): %d\n", adjacent);

    graph_destroy(&graph);

    return 0;
}