/*
    Author: Rômulo Rossi
    Email: romulomrossi@hotmail.com
    Entity: UFFS - Chapecó
*/
typedef Node ListNode;
typedef List *Graph;    //List of GraphNode elements
typedef List *Dijkstra; //List of SearchResponse elements

typedef struct _adj
{
    int destiny;
    int cost;
} GraphEdge;

typedef struct _graphNode
{
    int id;
    bool visited;
    List adjacency; //List of graphEdges
} GraphNode;

typedef struct _SearchResponse
{
    int destinyNode;
    int cost;
    struct _SearchResponse *prevNode;
    bool done;
    List path; //List of integers
    GraphNode *graphNode;
} SearchResponse;

List newGraph();
GraphNode newGraphNode(int id);

void addGraphEdge(Graph graph, int idOrigin, int idDestiny, int cost);
GraphNode *getGraphNode(Graph graph, int id);

List initializeDijkstra(Graph graph, int originNode);
List runDijkstra(Graph graph, int originNode);
SearchResponse *decideNext(Dijkstra dijkstra);
void searchBacktrack(Dijkstra SearchResponse);
void relaxEdges(Dijkstra dijkstra, GraphNode *graphNode, SearchResponse *SearchResponse);
void dijkstraGetPath(SearchResponse *node);

void printGraph(List *graph);

#include "graph.c"