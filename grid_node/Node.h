#ifndef NODE_OBJ
#define NODE_OBJ
#include "raylib.h"
#include <cmath>
#include <sys/types.h>
#include <tuple>

class Node{
  public: 
    Node(bool _walkable, Vector3 _worldpos, uint _gridY, uint _gridX, Color _c);
    float getFcost()const;
    float gcost=INFINITY;
    float hcost=INFINITY;
    uint gridX;
    uint gridY;
    Node *parent;
    bool operator<(const Node& other) const {
      if(this->gridX < other.gridX && this->gridY < other.gridY){
        return  true;
      }
      return  false;
    }
    bool operator==(const Node &other) const{
    if(this->gridX==other.gridX && this->gridY==other.gridY){return  true;}
    return  false;
  }
   bool walkable;
    Color c = GREEN;
    Vector3 worldposition;
    bool isPlayerpos = false;

  private:
   
        
};



#endif // !NODE_OBJ
