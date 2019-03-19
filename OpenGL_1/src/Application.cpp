#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//setting call profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//setting compatibility profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 
			 0.5f,  -0.5f, 1.0f, 0.0f,
			 0.5f, 0.5f, 1.0f, 1.0f,
			 -0.5f, 0.5f, 0.0f, 1.0f

		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};



		//Ruèno kreiran vertex buffer(3 linije iduæe) da to nismo napravili u call profilu bi pukli
		//unsigned int vao; //vertex array object
		//GLCall(glGenVertexArrays(1, &vao));
		//GLCall(glBindVertexArray(vao));

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		//GLCall(glEnableVertexAttribArray(0));
		//GLCall(glVertexAttribPointer(0,2,GL_FLOAT, GL_FALSE, sizeof(float)*2,0));

		//glEnableVertexAttribArray(0);
		////oVa linija binda vertex buffer s vertex arrayem jer kazemo da je index 0 array buffera ce biti povezan (bound) s trenutno aktivnim vertex buferom 
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

		IndexBuffer ib(indices, 6);

		Shader shader("res/shaders/Basic1.shader");
		shader.Bind();

		/*ShaderProgramSource source = ParseSahder("res/shaders/Basic.shader");
		std::cout << "VERTEX" << std::endl;
		std::cout << source.VertexSource << std::endl;
		std::cout << "FRAGMENT" << std::endl;
		std::cout << source.FragmentSource << std::endl;


		unsigned int shader = CreateShaders(source.VertexSource, source.FragmentSource);
		glUseProgram(shader);*/

		/*GLCall(int location = glGetUniformLocation(shader, "u_Color"));
		ASSERT(location != -1)

			GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));*/

		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		//Ovo nije potrebno radit samo kao pokazno sto trebamo sve bindat ako zelimo istu sliku (OVDJE SVE UNBIND-AMO)
		/*GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));*/
		/*GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));*/


		Texture texture("res/textures/rrback.png");
		texture.Bind();
		//0 for slot 0
		shader.SetUniform1i("u_Texture", 0);

		va.Unbind();
		shader.Unbind();
		vb.Unbind();
		ib.Unbind();
		

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.05f;
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			//

			//drawing
			//CRTANJE TROKUTA S LEGACY GL(iz 97. :-) )
			/*glBegin(GL_TRIANGLES);
			glVertex2f(-0.5f, -0.5f);
			glVertex2f(0.0f, 0.5f);
			glVertex2f(0.5f, -0.5f);
			glEnd();*/

			/*GLCall(glUseProgram(shader));*/
			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			/*GLCall(glUniform4f(location, r, 0.3f, 0.8f, 1.0f));*/


			//Ovo možemo zamijenit (3 iduæe linije) s bind vertex array
			//GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
			////next 2 line set layout of that vertex buffer
			//GLCall(glEnableVertexAttribArray(0));
			//GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
			
			//GLCall(glBindVertexArray(vao));
			/*va.Bind();

			ib.Bind();*/

			renderer.Draw(va, ib, shader);

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;

			r += increment;

			//If we don't have index buffer we use this function
			// Zato sto smo s GL_TRIANGLES rekli da imamo vertex2f
			//glDrawArrays(GL_TRIANGLES, 0, 6);

			//GLClearError();
			//With index buffer we use
			//JOŠ bolji Debuger
			//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
			//OLD  --> GLCheckError();
			//BETTER
			//		ASSERT(GLLOGCall());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		//glDeleteProgram(shader);
	}
	glfwTerminate();
	return 0;
}