//
//  graph.cpp
//  Project4
//
//  Created by Bein, Doina on 4/21/18.
//  Copyright © 2018 Bein, Doina. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
using namespace std;

//Default Constructor 
Graph::Graph()
{
  for(int i = 0; i<100; i++)
  {
    vertex[i] = 0;
    for(int j = 0; j<100; j++)
    {
      adjmatrix[i][j] = 0;
    }
  }
  vertexCounter = 0;
  edgeCounter = 0;
  budget = 0;
}

// constructor with two arguments representing the number of nodes "intial budget"
Graph::Graph(int rno, float rbudget)
{
  //nested for loop used to set all default values
  for(int i = 0; i<100; i++)
  {
    vertex[i] = 0;
    for(int j = 0; j<100; j++)
    {
      //sets each edge on the adjacency matrix to 0 to show that none of the vertices are adjacent
      adjmatrix[i][j] = 0;
    }
  }
  //set the numbers of nodes
  vertexCounter = rno;
  //no edges
  edgeCounter = 0;
  //sets the budget
  budget = rbudget;
}

void Graph::addEdge(int node1, int node2) //adds an edge between two nodes in the graph node1 and node2
{
  //if nodes are not the same
  if (node1 != node2)
  {
    //then you add the edge to the adjacency matrix
    adjmatrix[node1][node2] = 1;
    adjmatrix[node2][node1] = 1;
    //Add edge, increase counter
    edgeCounter++;
  }
}

void Graph::setValue(int node, float rval) //sets value for int node
{
  //set value of node
  vertex[node] = rval;
}

void Graph::setBudget(float rbu) //set intial budget
{
 //sets budget
  budget = rbu;
}

int Graph::getNSize()// return num of nodes
{
  return vertexCounter;
}

int Graph::getESize() // return num of edges
{
 return edgeCounter; 
}

float Graph::getBudget() //return current budget
{
  return budget;
}

float Graph::getValue(int node) //return value of node
{
  return vertex[node];
}

void Graph::readData(string fileName) //reads data in from specific file
{
  //open file
  ifstream inFile(fileName);
  //if the file is open
  if(inFile.is_open())
  {
    //Leading two instances of data 
    //to set numnode (number of vertices) and the budget
    int numNode;
    float budget;
    inFile >> numNode;
    inFile >> budget;
    setBudget(budget);
    vertexCounter = numNode;
    //Next sets of data is value for each node
    for(int i = 0; i < numNode; i++)
    {
      int tempValue;
      inFile >> tempValue;
      setValue(i, tempValue);
    }
    //Remaining data is edges connecting vertices
    int firstNode;
    int secondNode;
    while(inFile >> firstNode)
    {
      inFile >> secondNode;
      addEdge(firstNode, secondNode);
    }
    
    //close the file
    inFile.close();
  }
  else
  {
    //close the file
    inFile.close();
  }
}

int Graph::DFS(int startNode) //return num of nodes visited using BFS at startNode and 
//adds values at each node as long as the budget is a positive float
{
	//Use interative DFS algorithm
	int nodeCounter = 1; //tracks visited node (start at one for starting node)
  float tempBud = budget;// assign max budget value to temp budget as to not tamper with private
  stack<int> s; //stack algorithm for ability to traverse reverse
  
//Vector initialized to be exact amount of vertices on the list, and all values are false until visited.
  vector<bool> visitedList (vertexCounter, false);
  //push startNode
  s.push(startNode);
  while(!s.empty()){
    int v = s.top();
    s.pop();
    
    if(!visitedList[v])
    {
     //visit node
      visitedList[v] = true;
      //check if running budget + value vertex is greater than zero
      if(tempBud+vertex[v] >0 )
      {
        tempBud+=vertex[v];
        nodeCounter++;
      }
      else
      {
	// Stops if budget is zero and returns
        return nodeCounter;
      }
      for(int w = vertexCounter-1; w>= 0; --w)
      {
        if(adjmatrix[v][w] == 1)
          s.push(w);
      }
    }
  }
  return nodeCounter;
}

// return the starting node that gives a longest DFS run before running out of budget
// if there are multiple nodes with the same DFS run length, return the smallest node
int Graph::bestStartVertex()
{
  //keeps track of the best starting node which is 0
  int bestStart = 0;
  //keeps track of the best DFS run which is 0
  int bestRun = 0;
  for(int i = 0; i<vertexCounter; i++)
  {
    if(bestRun < DFS(i))
    {
      bestRun = DFS(i);
      bestStart = i;
    }
  }
  return bestStart;
}
