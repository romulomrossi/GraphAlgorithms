#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_PATH "inputB"
#define INF 112345678

#include "src/list.h"
#include "src/graph.h"

int main(void)
{
    List graph = newGraph();
    char line[20];
    FILE *file = fopen(INPUT_PATH, "r");

    while (!feof(file))
    {
        int origin, destiny, cost;

        fgets(line, sizeof(line), file);
        sscanf(line, "%d %d %d\n", &origin, &destiny, &cost);

        addGraphEdge(&graph, origin, destiny, cost);
    }

    int action = 0, origin;

    printf("Digite 1 para Dijkstra ou 2 para BFS: ");
    scanf("%d", &action);
    printf("Digite o nó de origem: ");
    scanf("%d", &origin);

    List search;

    if (action == 1)
        search = runDijkstra(&graph, origin);
    
    if (action == 2)
        search = runBfs(&graph, origin);


    searchBacktrack(&search);
    SearchResponse *data;
    Node *current = search.first;
    Node *currentVertex;
    while (current != NULL)
    {
        data = (SearchResponse *)current->data;

        printf("Destino: %d | Custo: %d | Caminho: ", data->destinyNode, data->cost);
        currentVertex = data->path.first;
        while (currentVertex != NULL)
        {
            printf("%d ", *(int *)currentVertex->data);
            currentVertex = currentVertex->next;
        }
        printf("\n");
        current = current->next;
    }

    return 0;
}