#include <tools_c/Logging.h>
#include "GLApi.h"
#include "GLInit.h"
#include "GLShaders.h"

ENABLE_LOGGING

int main(int argc, char* argv[])
{
    Args args = createArgs(argc, argv);
    initGL(&args);

    buildGeometry();
    buildShaders();

    initScene();

    glutMainLoop();
}
