#include "Grid.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <raylib.h>
#include <sys/types.h>
#include <vector>
Grid::Grid(int nodeRadius, float width, float height){
  this->nodeRadius = nodeRadius;
  this->position.x = 100;
  this->position.y = 10;
  this->gridWorldSize.x = width;
  this->gridWorldSize.y = height;
  this->gridSizeX = std::trunc((this->gridWorldSize.x)/(this->nodeRadius*2));
  this->gridSizeY = std::trunc((this->gridWorldSize.y)/(this->nodeRadius*2));
  CreateGrid();

}


void Grid::CreateGrid(){    
  float nodesep = 50;
  Vector3 currentNodePos = {this->position.x + nodeRadius, this->position.y + nodeRadius};
  for(int i = 0; i<gridSizeY; i++){
    gridnodes.push_back(std::vector<Node>{});
    for (int j=0; j<gridSizeX; j++){
      bool walkable = true;
      int x = rand()%4 + 2;
      Color c = GREEN;
      if(x % 3 == 0){
        walkable=false;
        c=RED;
      }

      this->gridnodes[i].push_back(Node (walkable, {currentNodePos.x, currentNodePos.y, 0.f}, i, j, c));

      currentNodePos.x += nodeRadius + nodesep;
    }
    currentNodePos.x = this->position.x + nodeRadius;
    currentNodePos.y += nodeRadius +nodesep;
  }

}
Node *Grid::NodeFromWorldPosition(Vector2 worldPos){
  float rel_x = worldPos.x - this->position.x;
  float rel_y = worldPos.y - this->position.y;
  uint row = static_cast<uint>(std::trunc(rel_y /(nodeRadius*2)));
  uint col = static_cast<uint>(std::trunc(rel_x / (nodeRadius*2)));

  const uint low=0;
  const uint highX = gridSizeX-1;
  const uint highY = gridSizeY-1;
  row = std::clamp(row, low, highY);
  col = std::clamp(col, low, highX);
  std::cout<<"row :"<<row<<"\n";
  std::cout<<"col :"<<col<<"\n";
  return &this->gridnodes[row][col]; 
 }


std::vector<Node *> Grid::getNodeNeighbours(Node *node){
  std::vector<Node *> neigbours{};
  for(int i=-1; i<=1; i++){
    for(int j=-1; j<=1; j++){
      if(i==0 && j==0){continue;}
      bool rowInBounds = (node->gridY+i >= 0 && node->gridY+i < gridSizeY) ;
      bool colInBounds = (node->gridX+j >= 0 && node->gridX+j < gridSizeX) ;
      if(rowInBounds && colInBounds){
        Node *n = &(this->gridnodes[node->gridY + i][node->gridX + j]);
        neigbours.push_back(n);
      }
    }
  }
  return  neigbours;
}

void Grid::DrawGizmos(bool leftClick ,bool rightClick, Vector2 mousePos){
  if(leftClick){
    Node *selected = NodeFromWorldPosition(mousePos);
    selected->c = BLACK;
    }

  if (this->gridnodes.size() != 0){
    for (std::vector<Node> row : this->gridnodes){
      for(Node n : row){
        DrawRectangle(n.worldposition.x - nodeRadius, 
                   n.worldposition.y-nodeRadius, nodeRadius*2, 
                   nodeRadius*2, n.c);
    }
  }
}
}
