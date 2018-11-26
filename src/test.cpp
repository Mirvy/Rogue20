
//Compilation command:
//	g++ ./src/test.cpp -o tuto -Iinclude -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall


#include "core.h"

Engine engine(80,50);

int main(){
	while(!TCODConsole::isWindowClosed()){
		engine.update();
		engine.render();
		TCODConsole::flush();
	}
	return 0;
}
