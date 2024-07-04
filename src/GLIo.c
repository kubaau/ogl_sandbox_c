#include "GLIo.h"
#include "GLApi.h"
#include "GLScene.h"

static kmVec3 createStep(float step)
{
    kmVec3 ret;
    kmVec3Fill(&ret, step, step, step);
    return ret;
}

static const float step = 1.0f;

static void moveForward(void)
{
    const kmVec3 step_vec = createStep(step);
    kmVec3 eye_pos_delta;
    kmVec3Mul(&eye_pos_delta, &target, &step_vec);
    kmVec3Add(&eye_pos, &eye_pos, &eye_pos_delta);
}

static void moveBack(void)
{
    const kmVec3 step_vec = createStep(step);
    kmVec3 eye_pos_delta;
    kmVec3Mul(&eye_pos_delta, &target, &step_vec);
    kmVec3Subtract(&eye_pos, &eye_pos, &eye_pos_delta);
}

static void moveLeft(void)
{
    kmVec3Normalize(&target, &target);
    kmVec3 dir;
    kmVec3Cross(&dir, &up, &target);
    kmVec3Normalize(&dir, &dir);
    const kmVec3 step_vec = createStep(step);
    kmVec3 eye_pos_delta;
    kmVec3Mul(&eye_pos_delta, &dir, &step_vec);
    kmVec3Add(&eye_pos, &eye_pos, &eye_pos_delta);
    kmVec3Add(&target, &target, &eye_pos_delta);
}

static void moveRight(void)
{
    kmVec3Normalize(&target, &target);
    kmVec3 dir;
    kmVec3Cross(&dir, &target, &up);
    kmVec3Normalize(&dir, &dir);
    const kmVec3 step_vec = createStep(step);
    kmVec3 eye_pos_delta;
    kmVec3Mul(&eye_pos_delta, &dir, &step_vec);
    kmVec3Add(&eye_pos, &eye_pos, &eye_pos_delta);
    kmVec3Add(&target, &target, &eye_pos_delta);
}

static void moveUp(void)
{
    eye_pos.y += step;
}

static void moveDown(void)
{
    eye_pos.y -= step;
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'w': moveForward(); return;
        case 's': moveBack(); return;
        case 'a': moveLeft(); return;
        case 'd': moveRight(); return;
        case 'e': moveUp(); return;
        case 'q': moveDown(); return;
    }
    (void)x;
    (void)y;
}

void special(int code, int x, int y)
{
    switch (code)
    {
        case GLUT_KEY_UP: moveForward(); return;
        case GLUT_KEY_DOWN: moveBack(); return;
        case GLUT_KEY_LEFT: moveLeft(); return;
        case GLUT_KEY_RIGHT: moveRight(); return;
        case GLUT_KEY_PAGE_UP: moveUp(); return;
        case GLUT_KEY_PAGE_DOWN: moveDown(); return;
    }
    (void)x;
    (void)y;
}
