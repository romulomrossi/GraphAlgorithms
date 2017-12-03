using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace WelshPowell
{
    public class WelshPowell
    {
        Graph graph = null;
        List<Vertex> blankNodes = new List<Vertex>();

        public WelshPowell(Graph graph)
        {
            this.graph = graph;

            foreach (Vertex v in graph.nodes)
                blankNodes.Add(v);

            blankNodes.Sort(delegate (Vertex v1, Vertex v2) { return v1.degree.CompareTo(v2.degree); });

        }

        public void Run()
        {
            int currentColor = 1;
            while (blankNodes.Count > 0)
            {
                foreach (Vertex v in blankNodes)
                {
                    v.color = currentColor;
                    foreach (Vertex neighbor in graph.GetNodeNeighbors(v))
                        if (neighbor.color == currentColor)
                            v.color = 0;                            
                }

                blankNodes.RemoveAll(v => v.color == currentColor);
                currentColor++;
            }
        }
    }
}
