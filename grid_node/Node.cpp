#include "Node.h"
#include <raylib.h>
#include <sys/types.h>


Node::Node(bool _walkable, Vector3 _worldpos, uint _gridY, uint _gridX, Color _c){
  this->walkable = _walkable;
  this->worldposition = _worldpos;
  this->gridY = _gridY;
  this->gridX = _gridX;
  this->c = _c;
}

float Node::getFcost() const{
  return  gcost+hcost;
}

