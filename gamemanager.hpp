#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP
#include <vector>
#include <string>
#include <unordered_map>
#include "component.hpp"

class GameObject;

class GameManager {
public:
  static void addObj(GameObject* obj);
  static GameObject* getObj(std::string code); // Returns ref to first gameobject with matching string
  static std::vector<GameObject*> getObjs(std::string code); // Returns pointer to all gameobjects with matching string
  static std::vector<GameObject*>& getObjs();
  static std::unordered_map<std::string, std::vector<Component*>>& getCompGroups();
  static void delObj(GameObject* obj);
  static void update();
private:
  static std::vector<GameObject*> gameObjects;  //Contains every gameobject instance
  static std::unordered_map<std::string, std::vector<Component*>> componentGroups;
};
#endif
