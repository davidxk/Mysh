#ifndef _EXECUTOR_C_
#define _EXECUTOR_C_

#include "global.h"

void execute(Job aJob);
bool findRunCmd();
void decoratePath();
void prepareIO();
void resetIO();
void forkThread();
#endif
