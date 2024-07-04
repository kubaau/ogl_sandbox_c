#include "GLScene.h"
#include <tools_c/Logging.h>
#include <tools_c/SimpleTimer.h>
#include "GLInit.h"

VbHandle vb;
IbHandle ib;
ShaderLocation wvp_loc;

kmVec3 eye_pos;
kmVec3 target;
kmVec3 up;

void render()
{
    SimpleTimer render_timer = createSimpleTimer();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    static float i = 0.0f;
    i += 0.1f;
    DEBUG_LOG("%f", i);
    DEBUG_LOG("eye_pos: {%f, %f, %f}", eye_pos.x, eye_pos.y, eye_pos.z);
    DEBUG_LOG("target: {%f, %f, %f}", target.x, target.y, target.z);

    kmMat4 scale_mat;
    kmMat4Scaling(&scale_mat, 1, 1, 1);

    kmMat4 translation_mat;
    kmMat4Translation(&translation_mat, 0, 0, -3);

    kmMat4 rotation_mat;
    const float rotation_factor = i;
    kmMat4RotationYawPitchRoll(&rotation_mat, 0, rotation_factor, 0);

    kmMat4 view_mat;
    kmMat4LookAt(&view_mat, &eye_pos, &target, &up);

    kmMat4 projection_mat;
    kmMat4PerspectiveProjection(&projection_mat, 60, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 1, 100);

    kmMat4 world;
    kmMat4Multiply(&world, &projection_mat, &view_mat);
    kmMat4Multiply(&world, &world, &translation_mat);
    kmMat4Multiply(&world, &world, &scale_mat);
    kmMat4Multiply(&world, &world, &rotation_mat);

    glUniformMatrix4fv(wvp_loc, 1, GL_FALSE, &world.mat[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);

    SimpleTimer draw_timer = createSimpleTimer();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    DEBUG_LOG("draw\t%f", elapsed(&draw_timer));

    glDisableVertexAttribArray(0);

    glutSwapBuffers();
    DEBUG_LOG("render\t%f", elapsed(&render_timer));
}
