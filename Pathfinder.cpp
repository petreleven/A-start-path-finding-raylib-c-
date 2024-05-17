#include "Pathfinder.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <sys/types.h>
#include <set>
#include <vector>



static int GetDistance(Node currentNode, Node neighbor){
  int yOffsetNodes = std::abs(int(neighbor.gridY - currentNode.gridY));
  int xOffsetNodes = std::abs(int(neighbor.gridX - currentNode.gridX));    
  int distance=0;
  if(xOffsetNodes > yOffsetNodes){
    distance = 14*yOffsetNodes + 10*(xOffsetNodes-yOffsetNodes);
  }else if (yOffsetNodes > xOffsetNodes) {
    distance = 14*xOffsetNodes + 10*(yOffsetNodes - xOffsetNodes);
  }
  return  distance;
}

Pathfinder::Pathfinder(Grid &_grid) :grid (_grid){};

void Pathfinder::RetracePath(Node *startNode, Node *targetNode){
  std::vector<Node *> path{};
  Node *c = targetNode->parent;
  if(c==nullptr){return;}
  std::cout<<"DEBUGX : "<<"end :("<<c->gridY<<","<<c->gridX<<")"<<" start :("<<startNode->gridY<<","<<startNode->gridX<<")"<<"\n";
  while (!(*c == *startNode)) {  
    c->c = ORANGE;
    path.push_back(c);
    c = c->parent;
    if(c==nullptr){break;}
    std::cout<<c->gridY<<""<<c->gridX<<"\n";
  }
  this->grid.path = path;
  
}

void Pathfinder::FindPath(Vector2 startPos, Vector2 endPos){
  std::vector<Node *> open{};
  std::set<Node *> closed{};
  Node *startNode = this->grid.NodeFromWorldPosition(startPos);
  Node *targetNode = this->grid.NodeFromWorldPosition(endPos);
  startNode->c = BLUE;
  startNode->gcost = 0;
  targetNode->c = BLACK;

  std::cout<<"FINDPATH "<<"startNode "<<startNode->gridY<<", "<<startNode->gridX<<" targetNode"<<targetNode->gridY<<", "<<targetNode->gridX<<"\n";
  open.push_back(startNode);

  while (open.size() != 0) {

    //Find node with lowest fcost
    uint indexToRemove = 0;
    Node *currentNode = open[indexToRemove];
    for (size_t i=1; i<open.size(); i++){
      Node *c = open[i];
      if(c->getFcost() < currentNode->getFcost() || 
        c->getFcost() == currentNode->getFcost() && c->hcost < currentNode->hcost){
        currentNode = c;
        indexToRemove = i;
      }
    }
    //Remove currentnode from open and add to close
    open.erase(open.begin() + indexToRemove);
    closed.insert(currentNode);
    //Check if you arrived;
    if(currentNode == targetNode){
      this->RetracePath(startNode, targetNode);
      return;
    }
    //Get neighbours of currentNode;
    for(Node *neighbor : grid.getNodeNeighbours(currentNode)){
      // if neighbor is not walkable or already visited continue to next neighbor
      auto it = closed.find(neighbor);
      if(!neighbor->walkable || it != closed.end()){
        continue;
      }
      //if neighbor is not in open || path to neighbor is less set costs & parent to  current
      int newCostToNeighbour = currentNode->gcost + GetDistance(*currentNode, *neighbor);
      bool InOpen = false;
      for(auto n : open){
        if((*n)==(*neighbor)){
          InOpen = true;
        }
      }
      if(newCostToNeighbour < neighbor->gcost || !InOpen ){
        //set fcost of neighbor and parent to current
        float gcost = newCostToNeighbour;
        float hcost = GetDistance(*neighbor, *targetNode);
        neighbor->gcost = gcost;
        neighbor->hcost = hcost;
        neighbor->parent = currentNode;
        if(!InOpen){
          open.push_back(neighbor);
        }

      }

    }

  }
}


