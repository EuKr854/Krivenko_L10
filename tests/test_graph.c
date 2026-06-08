#include <stdio.h>
#include "graph.h"

int main(void)
{
    graph_t graph;
    size_t v0;
    size_t v1;
    int adjacent;

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

    graph_destroy(&graph);

    return 0;
}