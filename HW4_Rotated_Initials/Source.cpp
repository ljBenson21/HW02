#define _DEBUG
#include <sb7.h>
#include <shader.h>

class singlepoint_app : public sb7::application
{
	GLfloat Theta[3] = { 0.0, 0.0, 0.0 };
	GLuint theta;

    void init()
    {
        static const char title[] = "OpenGL SuperBible - HW4";

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

		theta = glGetUniformLocation(program, "theta");
    }

    virtual void render(double currentTime)
    {
        static const GLfloat green[] = { 0.75f, 0.50f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, green);

		glUseProgram(program);

		Theta[0] = 0.785398;
		Theta[1] = 0.785398;
		Theta[2] = 0.785398;

		currentTime = currentTime * 5;
		GLfloat attrib[]{
			(GLfloat)sin(currentTime) * 0.5f,
			(GLfloat)cos(currentTime) * sin(currentTime) * 0.6f,
			0.0f,
			1.0
		};

		glVertexAttrib4fv(0, attrib);
       glUniform3fv(theta, 1, Theta);
		glDrawArrays(GL_TRIANGLES, 0, 18);
		

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
