#include <sb7.h>
#include <vector>
#include <string>

class singlepoint_app : public sb7::application
{
	void runtime_error_check()
	{
		GLenum err = glGetError();

		if (err) {
			char buf[20];
			sprintf(buf, "Error = %x", err);
			MessageBoxA(NULL, buf, "Error in shader", MB_OK);
			exit(-1);
		}
	}

	void compiler_error_check(GLuint shader)
	{
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.
			MessageBoxA(NULL, &errorLog[0], "Error in shader", MB_OK);

			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
		}
	}

    void init()
    {
        static const char title[] = "OpenGL SuperBible - HW3";

        sb7::application::init();

        memcpy(info.title, title, sizeof(title));
    }

    virtual void startup()
    {
		static const char * vs_source[] =
		{
			"#version 420 core                                                 \n"
			"                                                                  \n"
			"layout (location = 0) in vec4 offset;                             \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
			"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
			"                                   vec4( 0.1, 0.15, 0.5, 1.0),  \n"
			"                                   vec4( 0.00, -0.05, 0.5, 1.0),  \n"
			"                                   vec4( 0.15,  0.25, 0.5, 1.0)); \n"
            "    gl_Position = vertices[gl_VertexID] + offset;                 \n"
            "}                                                                 \n"
        };

        static const char * fs_source[] =
        {
            "#version 420 core                                                 \n"
            "                                                                  \n"
            "out vec4 color;                                                   \n"
            "                                                                  \n"
            "void main(void)                                                   \n"
            "{                                                                 \n"
            "    color = vec4(0.0, 0.0, 1.0, 1.0);                             \n"
            "}                                                                 \n"
        };

        program = glCreateProgram();
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, fs_source, NULL);
        glCompileShader(fs);
		compiler_error_check(fs);

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, vs_source, NULL);
        glCompileShader(vs);
		compiler_error_check(vs);

        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
    }

    virtual void render(double currentTime)
    {
		currentTime = currentTime * 1; // Change the speed of the figure 8
        static const GLfloat red[] = { 0.5f, 0.0f, 0.0f, 1.0f };
        glClearBufferfv(GL_COLOR, 0, red);

        glUseProgram(program);

		GLfloat attrib[]{
			(GLfloat) sin(currentTime) * 0.8f,
			(GLfloat) cos(currentTime) * 0.9,
			0.0f,
			1.0
		};

		GLfloat attrib1[]{
			(GLfloat)cos(currentTime) * 0.7f,
			0.0f,
			0.0f,
			1.0
		};

		glVertexAttrib2fv(0, attrib1);
		glDrawArrays(GL_LINES, 0, 2);
		glVertexAttrib2fv(0, attrib);
		glDrawArrays(GL_LINES, 2, 4);
		runtime_error_check();
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
