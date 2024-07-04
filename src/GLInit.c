#include "GLInit.h"
#include <tools_c/CheckResult.h>
#include <tools_c/Logging.h>
#include <kazmath/kazmath.h>
#include "GLApi.h"
#include "GLIo.h"
#include "GLScene.h"

static void initGlutCallbacks(void)
{
    glutIdleFunc((void (*)(void))(glutPostRedisplay));
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
}

static void initGlut(Args* args)
{
    glutInit(&args->argc, args->argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ogl_c");
    initGlutCallbacks();
}

static void initGlew(void)
{
    const GLenum res = glewInit();
    check(res == GLEW_OK, glewGetErrorString(res));
}

void initGL(Args* args)
{
    initGlut(args);
    initGlew();
    DEBUG_LOG("GL version: %s", glGetString(GL_VERSION));
}

static void buildVb(void)
{
    kmVec3 vs[4];
    kmVec3Fill(&vs[0], -1.0f, -1.0f, 0.5773f);
    kmVec3Fill(&vs[1], 0.0f, -1.0f, -1.15475f);
    kmVec3Fill(&vs[2], 1.0f, -1.0f, 0.5773f);
    kmVec3Fill(&vs[3], 0.0f, 1.0f, 0.0f);

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vs), vs, GL_STATIC_DRAW);
}

static void buildIb(void)
{
    unsigned is[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

    glGenBuffers(1, &ib);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(is), is, GL_STATIC_DRAW);
}

void buildGeometry()
{
    buildVb();
    buildIb();
}

void initScene()
{
    kmVec3Fill(&eye_pos, 0, 0, 3);
    kmVec3Fill(&target, 0, 0, -1);
    kmVec3Fill(&up, 0, 1, 0);
}
