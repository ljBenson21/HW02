#define _DEBUG
#include <sb7.h>
#include <shader.h>

class singlepoint_app : public sb7::application
{



    void init()
    {
        static const char title[] = "OpenGL SuperBible - Single Triangle";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {

        GLuint shaders[2];

        shaders[0] = sb7::shader::load("vs.glsl", GL_VERTEX_SHADER);
        shaders[1] = sb7::shader::load("fs.glsl", GL_FRAGMENT_SHADER);

        program = sb7::program::link_from_shaders(shaders, 2, true);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    virtual void render(double currentTime)
    {
        static const GLfloat blue[] = { 0.23f, 0.0f, 0.75f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, blue);

		glUseProgram(program);

		currentTime = currentTime * 5;
		GLfloat attrib[]{
			(GLfloat)sin(currentTime) * 0.75f,
			(GLfloat)cos(currentTime) * sin(currentTime) * 0.2f,
			0.0f,
			1.0
		};

		glVertexAttrib4fv(0, attrib);
        glDrawArrays(GL_LINE_LOOP, 0, 1000);

    }

    virtual void shutdown()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteProgram(program);
    }

private:
    GLuint          program;
    GLuint          vao;
};

DECLARE_MAIN(singlepoint_app)
