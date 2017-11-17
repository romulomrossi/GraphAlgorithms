#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using std::string;

#define INF 112345678

#include "src/graph.cpp"
#include "src/kruskal.cpp"
#include "src/prim.cpp"

int main(void)
{
    Graph graph = Graph::LoadFromFile();

    
    cout << "Kruskal Algorithm: \n";
    Kruskal kruskal = Kruskal(&graph);
    
    cout << "Input: \n";
    graph.Print();
    
    cout << "\n------------------- \nResult: \n";
    
    kruskal.Run();
    kruskal.PrintTrees();

    cout << "\n------------------------------\n";

    cout << "Prim's Algorithm: \n";
    Prim prim = Prim(graph, "0");
    prim.Run();
    prim.PrintResponse();
}