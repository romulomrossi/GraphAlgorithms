class SpanningTree
{
  public:
    Vertex root;
    vector<Edge> members;

    SpanningTree() {}

    SpanningTree(Vertex root, Edge member)
    {
        this->root = root;
        this->AddMember(member);
    }

    void AddMember(Edge member)
    {
        this->members.push_back(member);
    }

    static SpanningTree MergeTrees(SpanningTree a, SpanningTree b)
    {
        SpanningTree origin;
        SpanningTree destination;
        if (a.members.size() < b.members.size())
        {
            origin = a;
            destination = b;
        }
        else
        {
            origin = b;
            destination = a;
        }

        for (int i = 0; i < origin.members.size(); i++)
        {
            Edge edge = origin.members[i];
            destination.AddMember(edge);
        }

        return destination;
    }
};

class Kruskal
{
  public:
    Graph *graph;
    vector<SpanningTree> trees;

    Kruskal(Graph *graph)
    {
        this->graph = graph;
        sort(this->graph->edges.begin(), this->graph->edges.end());
    }

    SpanningTree *SearchSpanningTree(Vertex node)
    {
        for (int i = 0; i < this->trees.size(); i++)
        {
            for (int j = 0; j < trees[i].members.size(); j++)
            {
                if (trees[i].members[j].origin.id.compare(node.id) == 0 || trees[i].members[j].destination.id.compare(node.id) == 0)
                    return &(trees[i]);
            }
        }

        return NULL;
    }

    void RemoveTree(SpanningTree a)
    {
        for (int i = 0; i < this->trees.size(); i++)
        {
            if (trees[i].root.id == a.root.id)
            {
                trees.erase(trees.begin() + i);
                return;
            }
        }
    }

    void Run()
    {
        for (int i = 0; i < graph->edges.size(); i++)
        {
            Edge edge = this->graph->edges[i];
            SpanningTree *originNodeTree = SearchSpanningTree(edge.origin);
            SpanningTree *destinationNodeTree = SearchSpanningTree(edge.destination);

            if (originNodeTree == destinationNodeTree && originNodeTree != NULL)
                continue;

            if (originNodeTree == NULL && destinationNodeTree == NULL)
            {
                trees.push_back(SpanningTree(edge.origin, edge));
                continue;
            }

            if (originNodeTree == NULL && destinationNodeTree != NULL)
            {
                destinationNodeTree->AddMember(edge);
                continue;
            }

            if (destinationNodeTree == NULL && originNodeTree != NULL)
            {
                originNodeTree->AddMember(edge);
                continue;
            }

            if (originNodeTree != destinationNodeTree)
            {
                SpanningTree newTree = SpanningTree::MergeTrees(*originNodeTree, *destinationNodeTree);
                newTree.AddMember(edge);
                this->RemoveTree(*originNodeTree);
                this->RemoveTree(*destinationNodeTree);
                this->trees.push_back(newTree);
            }
        }
    }

    void PrintTrees()
    {
        int weight = 0;

        for (int i = 0; i < this->trees.size(); i++)
        {
            cout << "Root: " << this->trees[i].root.id << "\n";
            for (int j = 0; j < this->trees[i].members.size(); j++)
            {
                weight += trees[i].members[j].weight;
                cout << "(" << trees[i].members[j].origin.id << ", "
                     << trees[i].members[j].destination.id << ") " 
                     << trees[i].members[j].weight << "\n";
            }
        }

        cout << "Path weight: " << weight << "\n";
    }
};