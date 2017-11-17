class Vertex
{
  public:
    string id;
    int cost;
    string prevNodeId;

    Vertex() {}

    Vertex(string id)
    {
        this->id = id;
        this->cost = INF;
    }
};

class Edge
{
  public:
    Vertex origin;
    Vertex destination;
    int weight;

    bool operator<(const Edge &other)
    {
        return weight < other.weight;
    }

    Edge(Vertex origin, Vertex destination, int weight)
    {
        this->origin = origin;
        this->destination = destination;
        this->weight = weight;
    }
};

class Graph
{
  public:
    vector<Edge> edges;
    vector<Vertex> nodes;
    bool oriented;
    
    static Graph LoadFromFile(char filename[20])
    {
        Graph graph = Graph();
        Vertex origin, destiny;

        FILE *file = fopen(filename, "r");
        char line[20];
        while (!feof(file))
        {
            char originId[20], destinyId[20];
            int weight;

            fgets(line, sizeof(line), file);
            sscanf(line, "%s %s %d\n", originId, destinyId, &weight);

            origin = graph.ForceGetGraphNode(string(originId));
            destiny = graph.ForceGetGraphNode(string(destinyId));

            graph.edges.push_back(Edge(origin, destiny, weight));
        }
        return graph;
    }

    Vertex ForceGetGraphNode(string id)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].id.compare(id) == 0)
                return nodes[i];
        }
        Vertex newVertex = Vertex(id);
        nodes.push_back(newVertex);
        return nodes.back();
    }

    Edge GetEdgeBetweenNodes(Vertex a, Vertex b)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].origin.id == a.id && edges[i].destination.id == b.id)
                return edges[i];

            if (edges[i].origin.id == b.id && edges[i].destination.id == a.id)
                return edges[i];
        }

        return Edge(a, b, -1);
    }

    Vertex GetNodeById(string id)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].id.compare(id) == 0)
                return nodes[i];
        }
    }

    void Print()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            Edge edge = edges[i];
            cout << edge.origin.id << " " << edge.destination.id << " " << edge.weight << "\n";
        }
    }

    vector<Vertex> GetNeighborhoodById(string id)
    {
        vector<Vertex> neighbors;
        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].destination.id == id || edges[i].origin.id == id)
            {
                if(edges[i].origin.id != id)
                    neighbors.push_back(edges[i].origin);
                else
                    neighbors.push_back(edges[i].destination);
            }
        }
        return neighbors;
    }
};