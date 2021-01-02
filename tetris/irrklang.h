#ifndef IRRKLANG_H
#define IRRKLANG_H
#include <windows.h>
#ifdef __cplusplus
extern "C" void play();
extern "C" void stop();
#else
void play();
void stop();
#endif

#endif // !irrKlang
