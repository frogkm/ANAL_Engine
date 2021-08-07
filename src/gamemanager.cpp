#include <string>
#include <vector>
#include "../include/gamemanager.hpp"
#include "../include/gameobject.hpp"

std::vector<GameObject*> GameManager::gameObjects;
std::unordered_map<std::string, std::vector<Component*>> GameManager::componentGroups;

void GameManager::addObj(GameObject* obj) {
  gameObjects.push_back(obj);
  for (Component* comp : obj->getComponents()) {
    componentGroups[comp->getTag()].push_back(comp);
  }
}

GameObject* GameManager::getObj(std::string code) {
  return gameObjects[0];
}

std::vector<GameObject*> GameManager::getObjs(std::string code) {
  std::vector<GameObject*> temp;
  temp.push_back(gameObjects[0]);
  return temp;
}

std::vector<GameObject*>& GameManager::getObjs() {
  return gameObjects;
}

void GameManager::delObj(GameObject* obj) {
  //Get rid of component pointers from comp map
  for (Component* comp : obj->getComponents()) {
    for (int i = 0; i < componentGroups[comp->getTag()].size(); i++) {
      if (comp == componentGroups[comp->getTag()][i]) {
        componentGroups[comp->getTag()].erase(componentGroups[comp->getTag()].begin() + i);
      }
    }
  }
  //Now get rid of gameObject pointers -- Then free mem for each gameObject (Which also frees it for it's components)
  for (int i = 0; i < gameObjects.size(); i++) {
    if (obj == gameObjects[i]) {
      gameObjects.erase(gameObjects.begin() + i);
      delete obj;
      break;
    }
  }
}

std::unordered_map<std::string, std::vector<Component*>>& GameManager::getCompGroups() {
  return componentGroups;
}

void GameManager::update() {
  for (auto it = componentGroups.begin(); it != componentGroups.end(); it++) {
		for (Component* comp : it->second) {
			comp->update();
		}
	}
}
