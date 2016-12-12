//Programmer: Ethan Yi Chiang
//Programmer ID: 1538719

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
using namespace std;

struct Node
{
  string name;

  bool isVisited;
  list<int> neighbors;
};

queue<int> BFS(int iOriginNode, vector<Node>& database)
{
  queue<int> searchOrder; // return this queue of indices
  queue<int> toDo;

  // initialization
  for(int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
  }

  // mark start node
  database[iOriginNode].isVisited = true;
  // push to result
  searchOrder.push(iOriginNode);
  // push to "to do" list
  toDo.push(iOriginNode);

  while(!toDo.empty())
  {
    int i = toDo.front();
    toDo.pop();
    list<int> neighbors = database[i].neighbors;

    for(list<int>::const_iterator it = neighbors.begin(); it != neighbors.end(); ++it)
    {
      if(!database[*it].isVisited)
      {
        database[*it].isVisited = true;
        searchOrder.push(*it);
        toDo.push(*it);
      }
    }
  }
  return searchOrder;
}

int main()
{
  cout << "Programmer: Ethan Chiang\n"
       << "Programmer's ID: 1538719\n"
       << "File: " << __FILE__ << "\n\n";

  ifstream fin;
  fin.open("cities.txt");
  if(!fin.good()) throw "I/O error";

  // process the input file
  vector<Node> database;
  while(fin.good()) // EOF loop
  {
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator

    // add vertices for new cities included in the edge
    int iToNode = -1, iFromNode = -1, i;
    for(i = 0; i < database.size(); i++) // seek "to" city
      if(database[i].name == fromCity)
        break;
    if(i == database.size()) // not in database yet
    {
      // store the node if it is new
      Node fromNode = {fromCity};
      database.push_back(fromNode);
    }
    iFromNode = i;

    for(i = 0; i < database.size(); i++) // seek "from" city
      if(database[i].name == toCity)
        break;
    if(i == database.size()) // not in vector yet
    {
      // store the node if it is new
      Node toNode = {toCity};
      database.push_back(toNode);
    }
    iToNode = i;

    // store bi-directional edges
    database[iFromNode].neighbors.push_back(iToNode);
    database[iToNode].neighbors.push_back(iFromNode);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while(true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if(startCity.length() == 0) break;

    // find the start city
    int i;
    for(i = 0; i < database.size(); i++)
      if(database[i].name == startCity)
        break;

    // BFS result by copy-pop
    cout << "BFS";
    for(queue<int> q = BFS(i, database); !q.empty(); q.pop())
      cout  << '-'<< database[q.front()].name;
    cout << endl;
  }
}
