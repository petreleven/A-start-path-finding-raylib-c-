#include <iostream>
#include "raylib.h"
#include "./grid_node/Grid.h"
#include "./imgui/imgui.h"
#include "./imgui/rlImGui.h"
#include "Pathfinder.h"
const int SCREENWIDTH = 1280 ;
const int SCREENHEIGHT = 800;

static Vector3 startPos{0,0,0};
static Vector3 startEndpos{0,0,0};
static Grid gamegrid = Grid(40, 700, 500);
static bool leftClick = false;
static bool rightClick = false; 

void checkInputs(){
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    leftClick=true;
  }
}

int main()
{
  Vector2 mousePos {0,0};
  Node startNode = gamegrid.getGridNodes()[2][0];
  Node endNode = gamegrid.getGridNodes()[2][0];
  Vector3 startPos = startNode.worldposition;
  Vector3 endPos = endNode.worldposition;
  Pathfinder pathfinder = Pathfinder(gamegrid);
  pathfinder.FindPath({startPos.x, startPos.y}, {endPos.x,endPos.y});

  //---------UI-------------//
  SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  float worldsizex = 10.f;
  float worldsizey = 10.f;
  for(auto n: gamegrid.path){
    std::cout<<"path ("<<n->gridY<<", "<<n->gridX<<")"<<"\n";
  }
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "A star simulation");

  rlImGuiSetup(true);
  SetTargetFPS(60);

  //---------game loop-------------//
  while (!WindowShouldClose())
  {
    checkInputs();
    //---BEGINS--//
    BeginDrawing();
    ClearBackground(BLACK);
    rlImGuiBegin(); 
    //----RENDER GAME-----//
    ImGui::SliderFloat("worldsize x", &worldsizex, 20, SCREENWIDTH, "%.2f");    
    ImGui::SliderFloat("worldsize y", &worldsizey, 20, SCREENHEIGHT, "%.2f");
    if(leftClick )  {
      mousePos = GetMousePosition();
      pathfinder.FindPath({startPos.x, startPos.y},  mousePos);
    }
    gamegrid.DrawGizmos(leftClick, rightClick, mousePos);



    leftClick=false;
    //-----END RENDER ------//
    rlImGuiEnd();
    EndDrawing();
  }

  CloseWindow();
  rlImGuiShutdown();
  return 0; 
}
