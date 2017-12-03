using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace WelshPowell
{
    public class Vertex
    {
        public string id = "";
        public int degree = 0;
        public int color = 0;

        public Vertex(string id)
        {
            this.id = id;
        }
    }
    public class Edge
    {
        public Vertex origin;
        public Vertex destination;

        public Edge(Vertex origin, Vertex destination)
        {
            this.origin = origin;
            this.destination = destination;
        }
    }

    public class Graph
    {
        public List<Vertex> nodes = new List<Vertex>();
        public List<Edge> edges = new List<Edge>();

        public static Graph LoadFromFile(string filePath)
        {
            Graph graph = new Graph();

            FileStream fileStream = new FileStream(filePath, FileMode.Open);
            using (StreamReader reader = new StreamReader(fileStream))
            {
                string line = reader.ReadLine();
                do
                {
                    string[] splitedLine = line.Split(" ");

                    Vertex origin = graph.GetOrCreateNode(splitedLine[0]);
                    Vertex destination = graph.GetOrCreateNode(splitedLine[1]);

                    graph.AddEdge(origin, destination);

                    line = reader.ReadLine();
                } while (!string.IsNullOrEmpty(line));
            }

            return graph;
        }

        public List<Vertex> GetNodeNeighbors(Vertex v)
        {
            List<Vertex> neighbors = new List<Vertex>();

            foreach (Edge e in edges)
            {
                if (e.origin.id == v.id)
                    neighbors.Add(e.destination);
                else if (e.destination.id == v.id)
                    neighbors.Add(e.origin);
            }

            return neighbors;
        }

        public void AddEdge(Vertex origin, Vertex destination)
        {
            origin.degree++;
            destination.degree++;

            edges.Add(new Edge(origin, destination));
        }

        public Vertex GetOrCreateNode(string id)
        {
            Vertex vertex = nodes.FirstOrDefault(v => v.id == id);

            if (vertex != null)
                return vertex;

            vertex = new Vertex(id);
            nodes.Add(vertex);
            return vertex;
        }

        public void PrintNodes()
        {
            Console.WriteLine("Id | Color | Degree");
            foreach (Vertex v in nodes)
                Console.WriteLine($" {v.id}  |   {v.color}   |    {v.degree}");
        }

        public void PrintEdges() 
        {
            foreach(Edge edge in edges)
                Console.WriteLine($"({edge.origin.id}, {edge.destination.id})");
        }
    }
}
