#include "grid_node/Grid.h"
#include <raylib.h>
#include <vector>
class Pathfinder{
  private:
    Grid &grid;
    void RetracePath(Node *startNode, Node *targetNode);
  public:
    Pathfinder(Grid &_grid);
    void FindPath(Vector2 startpos, Vector2 endpos);
};
