#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include "component.hpp"

class GameObject;

class GameManager {
public:
  ~GameManager();
  void addObj(GameObject* obj);
  void drawObjects();
  GameObject* getObj(std::string code); // Returns ref to first gameobject with matching string
  std::vector<GameObject*> getObjs(std::string code); // Returns pointer to all gameobjects with matching string
  std::vector<GameObject*>& getObjs();
  std::unordered_map<std::string, std::vector<Component*>>& getCompGroups();
  void delObj(GameObject* obj);
  void updateObjects();
  void start();
private:
  std::vector<GameObject*> gameObjects;  //Contains every gameobject instance
  std::unordered_map<std::string, std::vector<Component*>> componentGroups;
};
#endif
