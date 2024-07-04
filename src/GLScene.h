#pragma once

#include <kazmath/kazmath.h>
#include "GLTypedefs.h"

extern VbHandle vb;
extern IbHandle ib;
extern ShaderLocation wvp_loc;

extern kmVec3 eye_pos;
extern kmVec3 target;
extern kmVec3 up;

void render(void);
