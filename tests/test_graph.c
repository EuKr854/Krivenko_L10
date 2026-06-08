#include <stdio.h>
#include "graph.h"

int main(void)
{
    graph_t graph;

    size_t v0;
    size_t v1;

    int adjacent;

    size_t order[10];
    size_t count;
    size_t index;

    graph_init(&graph);

    graph_add_vertex(&graph, &v0);
    graph_add_vertex(&graph, &v1);

    graph_add_edge(&graph, v0, v1);

    graph_are_adjacent(
        &graph,
        v0,
        v1,
        &adjacent
    );

    printf("Adjacent: %d\n", adjacent);

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

    graph_destroy(&graph);

    return 0;
}