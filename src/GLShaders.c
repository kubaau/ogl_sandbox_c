#include "GLShaders.h"
#include <tools_c/ReadFile.h>
#include "GLScene.h"
#include "GLTypedefs.h"
#include "Nullptr.h"

static ShaderHandle buildShader(GLuint program, GLenum type, const char* code)
{
    const ShaderHandle shader = glCreateShader(type);
    if (not shader)
    {
        char wrong_shader[wrong_entity_buffer_size];
        sprintf(wrong_shader, "Error creating shader type %d", type);
        check(false, wrong_shader);
    }

    const size_t code_length = strlen(code);
    glShaderSource(shader, 1, &code, (GLint*)&code_length);

    glCompileShader(shader);
    GLResult result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if (not result)
    {
#define LOG_BUFFER_LENGTH 1024
        char log[LOG_BUFFER_LENGTH];
        glGetShaderInfoLog(
            shader, LOG_BUFFER_LENGTH, nullptr, log + sprintf(log, "Error compiling shader type %d: ", type));
        check(false, log);
    }

    glAttachShader(program, shader);
    return shader;
}

void buildShaders(void)
{
    const ShaderProgram program = glCreateProgram();
    check(program, "Error creating shader program");

#define SHADER_CODE_MAX_LENGTH 1024
    char vs_code[SHADER_CODE_MAX_LENGTH];
    char fs_code[SHADER_CODE_MAX_LENGTH];
#define SHADER_FOLDER "../../src/"
    readTextFile(vs_code, SHADER_FOLDER "vs.glsl");
    readTextFile(fs_code, SHADER_FOLDER "fs.glsl");

    const ShaderHandle vs = buildShader(program, GL_VERTEX_SHADER, vs_code);
    const ShaderHandle fs = buildShader(program, GL_FRAGMENT_SHADER, fs_code);

    glLinkProgram(program);
    GLResult result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (not result)
    {
        char log[LOG_BUFFER_LENGTH];
        glGetProgramInfoLog(program, LOG_BUFFER_LENGTH, nullptr, log + sprintf(log, "Error linking shader program: "));
        check(false, log);
    }

    glDetachShader(program, vs);
    glDeleteShader(vs);
    glDetachShader(program, fs);
    glDeleteShader(fs);

    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (not result)
    {
        char log[LOG_BUFFER_LENGTH];
        glGetProgramInfoLog(program, LOG_BUFFER_LENGTH, nullptr, log + sprintf(log, "Invalid shader program: "));
        check(false, log);
    }

    glUseProgram(program);

    const char* loc = "wvp";
    wvp_loc = glGetUniformLocation(program, loc);
    if (wvp_loc == (ShaderLocation)-1)
    {
        char wrong_loc[wrong_entity_buffer_size];
        sprintf(wrong_loc, "Wrong %s location", loc);
        check(false, wrong_loc);
    }
}
