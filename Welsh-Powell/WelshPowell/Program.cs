using System;

namespace WelshPowell
{
    class Program
    {
        static void Main(string[] args)
        {
            Graph graph = Graph.LoadFromFile("input");
            Console.WriteLine("Loaded graph: \nVertexs:");
            graph.nodes.Sort(delegate (Vertex v1, Vertex v2) { return v1.id.CompareTo(v2.id); });
            graph.PrintNodes();
            Console.WriteLine("\nEdges:");
            graph.PrintEdges();
            Console.WriteLine("----------------------------\n");
            WelshPowell algorithm = new WelshPowell(graph);
            algorithm.Run();
            Console.WriteLine("Vertexs's colors after Welsh-Powell: ");
            graph.PrintNodes();
        }
    }
}
