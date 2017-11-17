class PrimResponse
{
  public:
    string nodeId;
    string previousNode;
    int cost;

    PrimResponse(){}

    PrimResponse(string nodeId, string prevNode, int cost)
    {
        this->nodeId = nodeId;
        this->previousNode = prevNode;
        this->cost = cost;
    }
};

class Prim
{
  public:
    Graph graph;
    vector<PrimResponse> responses;
    vector<Vertex> openNodes;
    Vertex current;

    Prim(Graph graph, string origin)
    {
        this->graph = graph;
        this->current = graph.GetNodeById(origin);
        openNodes = graph.nodes;
        PrimResponse *x = GetResponseForNode(current);
        x->previousNode = origin;
        x->cost = 0;
    }

    PrimResponse *GetResponseForNode(Vertex v)
    {
        for(int i = 0; i<responses.size(); i++)
        {
            if(responses[i].nodeId == v.id)
                return &(responses[i]);
        }
        responses.push_back(PrimResponse(v.id, "", INF));
        return &(responses.back());
    }

    bool IsOpenNode(string id)
    {
        for(int i = 0; i<openNodes.size(); i++)
            if(openNodes[i].id.compare(id) == 0)
                return true;

        return false;
    }
    
    void CloseVertex()
    {
        for(int i = 0; i<openNodes.size(); i++)
            if(openNodes[i].id == current.id)
                openNodes.erase(openNodes.begin() + i);
    }

    void DecideNext()
    {
        if(openNodes.size()==0)
            return;
        PrimResponse next;
        int min = INF;
        for(int i = 0; i<responses.size(); i++)
        {
            if(responses[i].cost < min && IsOpenNode(responses[i].nodeId))
            {
                next = responses[i];
                min = next.cost;
            }
        }
        current = this->graph.GetNodeById(next.nodeId);
    }

    void Run()
    {
        while(!openNodes.empty())
        {
            vector<Vertex> neighbors = graph.GetNeighborhoodById(current.id);
            for(int ni = 0; ni<neighbors.size(); ni++)
            {
                if(current.id == neighbors[ni].id || !IsOpenNode(neighbors[ni].id))
                    continue;
                PrimResponse *response = GetResponseForNode(neighbors[ni]);
                Edge edge = graph.GetEdgeBetweenNodes(current, neighbors[ni]);
                
                if(edge.weight < response->cost)
                {
                    response->cost = edge.weight;
                    response->previousNode = current.id;
                }
            }
            CloseVertex();
            DecideNext();
        }
    }
    
    void PrintResponse()
    {   
        int sum = 0;
        for(int i = 0; i<responses.size(); i++)
        {
            cout << "(" << responses[i].previousNode << ", " <<
                responses[i].nodeId << ") " << responses[i].cost << "\n";
            sum+=responses[i].cost;
        }
        cout << "Path cost: " << sum;
    }
};