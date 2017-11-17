#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using std::string;

#include "src/graph.cpp"
#include "src/kruskal.cpp"

#define FILE_PATH "input"

int main(void)
{
    Graph graph = Graph::LoadFromFile();
    graph.Print();

    Kruskal kruskal = Kruskal(graph);
}