

#include <iostream>
#include "irrKlang.h"

#include <irrKlang/irrKlang.h>

using namespace irrklang;
static ISoundEngine* engine;
static void init() {
	 engine = createIrrKlangDevice();
}
void play()
{
	if (engine == NULL) {
		init();
	}else if (!engine) return ; // error starting up the engine
	ISound* music = engine->play2D("./songs/tetris.wav", true);
	return ;
}
void stop() {
	engine->drop(); // delete engine
}