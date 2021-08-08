#include "../include/engine.hpp"

int main(int argc, char* args[]) {
	Engine engine(1000, 1000, 60);
	engine.start();
	engine.stop();
	return 0;
}
