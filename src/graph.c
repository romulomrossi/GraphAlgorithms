List newGraph()
{
    List graph = listNew(sizeof(GraphNode));

    return graph;
}

GraphNode newGraphNode(int id)
{
    GraphNode node;

    node.id = id;
    node.adjacency = listNew(sizeof(GraphEdge));
    node.visited = FALSE;
    return node;
}

void addGraphEdge(Graph graph, int idOrigin, int idDestiny, int cost)
{
    GraphNode *node = getGraphNode(graph, idOrigin);
    GraphEdge edge;

    edge.destiny = idDestiny;
    edge.cost = cost;

    if (node == NULL)
    {
        GraphNode newNode = newGraphNode(idOrigin);
        listAppend(&newNode.adjacency, &edge);
        listAppend(graph, &newNode);
    }
    else
        listAppend(&node->adjacency, &edge);

    GraphNode *destinyNode = getGraphNode(graph, idDestiny);

    if (destinyNode == NULL)
    {
        GraphNode newNode = newGraphNode(idDestiny);
        listAppend(graph, &newNode);
    }
}

GraphNode *getGraphNode(Graph graph, int id)
{
    if (graph->count == 0)
        return NULL;

    ListNode *nodeList = graph->first;
    while (nodeList != NULL)
    {
        GraphNode *nodeGraph = (GraphNode *)nodeList->data;

        if (nodeGraph->id == id)
            return nodeGraph;

        nodeList = nodeList->next;
    }

    return NULL;
}

List initializeDijkstra(Graph graph, int originNode)
{
    ListNode *current = graph->first;
    List response = listNew(sizeof(SearchResponse));
    GraphNode *currentGraphNode;

    while (current != NULL)
    {
        currentGraphNode = (GraphNode *)current->data;
        SearchResponse newResponse;
        newResponse.destinyNode = currentGraphNode->id;
        newResponse.cost = currentGraphNode->id == originNode ? 0 : INF;
        newResponse.path = listNew(sizeof(int));
        newResponse.prevNode = NULL;
        newResponse.done = FALSE;

        listAppend(&response, &newResponse);

        current = current->next;
    }

    return response;
}

List runDijkstra(Graph graph, int originNode)
{
    List response = initializeDijkstra(graph, originNode);
    SearchResponse *currentResponse = decideNext(&response);
    GraphNode *currentGraphNode = getGraphNode(graph, currentResponse->destinyNode);

    while (currentGraphNode != NULL && currentResponse != NULL)
    {
        relaxEdges(&response, currentGraphNode, currentResponse);

        currentResponse = decideNext(&response);
        if (currentResponse != NULL)
            currentGraphNode = getGraphNode(graph, currentResponse->destinyNode);
    }
    return response;
}

bool DijkstraCompair(void *a, void *b)
{
    return *((int *)a) == ((SearchResponse *)b)->destinyNode;
}

void relaxEdges(Dijkstra dijkstra, GraphNode *graphNode, SearchResponse *dijkstraPrev)
{
    ListNode *currentEdge = graphNode->adjacency.first;
    GraphEdge *currentEdgeData;
    int newCost = INF;
    SearchResponse *destinyDijkstra;
    while (currentEdge != NULL)
    {
        currentEdgeData = (GraphEdge *)currentEdge->data;
        newCost = dijkstraPrev->cost + currentEdgeData->cost;

        destinyDijkstra = (SearchResponse *)listSearchNode(dijkstra, &currentEdgeData->destiny, &DijkstraCompair)->data;
        if (destinyDijkstra->cost > newCost)
        {
            destinyDijkstra->cost = newCost;
            destinyDijkstra->prevNode = dijkstraPrev;
        }

        currentEdge = currentEdge->next;
    }

    dijkstraPrev->done = TRUE;
}

SearchResponse *decideNext(Dijkstra dijkstra)
{
    ListNode *current = dijkstra->first;
    int bestCost = INF;
    SearchResponse *best = NULL;
    SearchResponse *currentData;

    while (current != NULL)
    {
        currentData = (SearchResponse *)current->data;

        if (currentData->done)
        {
            current = current->next;
            continue;
        }

        if (currentData->cost < bestCost)
        {
            bestCost = currentData->cost;
            best = currentData;
        }

        current = current->next;
    }

    return best;
}

void searchBacktrack(Dijkstra dijkstra)
{
    ListNode *currentNode = dijkstra->first;
    SearchResponse *currentData;
    while (currentNode != NULL)
    {
        currentData = (SearchResponse *)currentNode->data;

        dijkstraGetPath(currentData);

        currentNode = currentNode->next;
    }
}

void dijkstraGetPath(SearchResponse *node)
{
    SearchResponse *prevData = node->prevNode;
    while (prevData != NULL)
    {
        listPreppend(&node->path, &prevData->destinyNode);
        prevData = prevData->prevNode;
    }
}

void printGraph(List *graph)
{
    Node *node = graph->first;
    while (node != NULL)
    {
        GraphNode *graphNode = (GraphNode *)node->data;

        printf("NodeId: %d | ", graphNode->id);
        printf("AdjacencyList: ");
        Node *currentEdge = graphNode->adjacency.first;
        while (currentEdge != NULL)
        {

            GraphEdge *edge = (GraphEdge *)currentEdge->data;

            printf("(%d, %d) ", edge->destiny, edge->cost);

            currentEdge = currentEdge->next;
        }

        printf("\n");
        node = node->next;
    }
}

List runBfs(List *graph, int id)
{
    List queue = listNew(sizeof(SearchResponse *));
    List response = listNew(sizeof(SearchResponse *));
    int distance = 0;

    SearchResponse *first = malloc(sizeof(SearchResponse));
    first->destinyNode = id;
    first->cost = 0;
    first->prevNode = NULL;
    
    listAppend(&queue, &first);
    
    while (queue.count > 0)
    {
        ListNode *currentQueueNode = listPop(&queue, queue.first);
        SearchResponse *current = (SearchResponse *) currentQueueNode->data;
        current->cost = distance;
        current->graphNode = getGraphNode(graph, current->destinyNode);
        listAppend(&response, &current);

        ListNode *currentChildren;

        if(current->graphNode->adjacency.count > 0)
            currentChildren = current->graphNode->adjacency.first;
        while (currentChildren != NULL)
        {
            SearchResponse *nodeResponse = malloc(sizeof(SearchResponse));
            nodeResponse->destinyNode = *(int *)currentChildren->data;
            nodeResponse->prevNode = current;
            nodeResponse->graphNode = getGraphNode(graph, nodeResponse->destinyNode);

            listAppend(&queue, &nodeResponse);
            distance++;            
            currentChildren = currentChildren->next;
        }
    }

    return response;
}