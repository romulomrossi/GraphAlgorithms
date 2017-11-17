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

#define PRIM_FILE "inputPrim"
#define KRUSKAL_FILE "inputKruskal"

#include "src/graph.cpp"
#include "src/kruskal.cpp"
#include "src/prim.cpp"

int main(void)
{
    int option = 0;
    printf("Tap 1 for prim's or 2 for kruskal's algorithm: ");
    scanf("%d", &option);
    if(option == 2)
    {
        Graph graph = Graph::LoadFromFile("inputKruskal");
        
        cout << "Kruskal Algorithm: \n";
        Kruskal kruskal = Kruskal(&graph);
        cout << "Input: \n";
        graph.Print();
        
        cout << "\n------------------- \nResult: \n";
        
        kruskal.Run();
        kruskal.PrintTrees();
    
        cout << "\n------------------------------\n";    
    }
    else if(option == 1)
    {
        Graph graph = Graph::LoadFromFile("inputPrim");
        cout << "Input: \n";
        graph.Print();
        
        cout << "\n------------------- \nResult: \n";        

        cout << "Prim's Algorithm: \n";
        Prim prim = Prim(graph, "0");
        prim.Run();
        prim.PrintResponse();
        printf("\n");
        
    }

    }