class Vertex
{
    public:
        string id;
        
    Vertex(){}
        
    Vertex(string id)
    {
        this->id = id;
    }

};

class Edge
{
    public:
        Vertex* origin;
        Vertex* destination;
        int weight;

    Edge(Vertex* origin, Vertex* destination, int weight)
    {
        this->origin = origin;
        this->weight = weight;
        this->destination = destination;
    }
};

class Graph
{
    public:
        vector<Edge> edges;
        vector<Vertex> nodes;

    static Graph LoadFromFile()
    {
        Graph graph = Graph();
        Vertex *origin, *destiny;

        FILE *file = fopen("input", "r");
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

    Vertex* ForceGetGraphNode(string id)
    {
        for(int i=0; i<nodes.size(); i++)
        {
            if(nodes[i].id.compare(id) == 0)
                return &(nodes[i]);
        }
        Vertex newVertex = Vertex(id);
        nodes.push_back(newVertex);
        return &(nodes.back());
    }

    Vertex* GetGraphNode(string id)
    {
        for(int i=0; i<nodes.size(); i++)
        {
            if(nodes[i].id.compare(id) == 0)
                return &(nodes[i]);
        }
        return NULL;
    }

    void Print()
    {
        for(int i=0; i<edges.size(); i++)
        {
            Edge edge = edges[i];
            cout << edge.origin->id << " " << edge.destination->id << " " << edge.weight << "\n";
        }
    }

};