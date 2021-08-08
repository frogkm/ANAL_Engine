#include "../include/managers.hpp"
#include "../include/gamemanager.hpp"
#include "../include/displaymanager.hpp"
#include "../include/timemanager.hpp"
#include "../include/physicsmanager.hpp"

GameManager* Managers::gameManager = NULL;        //GameObject handling
DisplayManager* Managers::displayManager = NULL;  //Rendering functions
TimeManager* Managers::timeManager = NULL;
PhysicsManager* Managers::physicsManager = NULL;
//PhysicsManager* physicsManager;  //Physics system
//TimeManager* timeManager;       //Keep time

void Managers::setupManagers(int sW, int sH) {
  Managers::gameManager = new GameManager();
  Managers::displayManager = new DisplayManager(sW, sH);
  Managers::timeManager = new TimeManager();
  Managers::physicsManager = new PhysicsManager();
}


void Managers::cleanup() {
  delete Managers::gameManager;
  delete Managers::displayManager;
  delete Managers::timeManager;
  delete Managers::physicsManager;
  Managers::gameManager = NULL;
  Managers::displayManager = NULL;
  Managers::timeManager = NULL;
  Managers::physicsManager = NULL;
}
