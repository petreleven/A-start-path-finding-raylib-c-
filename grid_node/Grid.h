#ifndef GRID_H
#define GRID_H  
#include "Node.h"
#include <raylib.h>
#include <vector>

class Grid{
  public:
   Grid(int nodeRadius, float width, float height);
   Vector3 position;    
   Vector2 gridWorldSize;
   float nodeRadius;
   std::vector<Node> unwalkable_nodes;
   void DrawGizmos(bool rightClick, bool leftClick, Vector2 mousepos);
   void CreateGrid();
   Node *NodeFromWorldPosition(Vector2 worldPos);
   std::vector<Node *> getNodeNeighbours(Node *node);
   std::vector<Node *> path{};
   std::vector<std::vector<Node>> getGridNodes()const{
    return this->gridnodes;
  }
  private:
   std::vector<std::vector<Node>>gridnodes;
   int gridSizeX;
   int gridSizeY;
};
#endif // !GRID
