#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main()
{
	glfwInit();
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//if the window does not exist print an error
	if (window == NULL)
	{

		std::cout << "Sailor Error: Failed to create GLFW window" << '\n';
		return -1;
	}
	else
	{
		std::cout << "Sailor Success: created GLFW window" << '\n';
	}
	// Make window the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it can configure openGL
	gladLoadGL();

	//specify the viewport of openGL in the window
	// x = 0, y = 0, to x = 800 y = 800
	glViewport(0, 0, 800, 800);

	//specify colour of the backgrund
	glClearColor(0.07f, 0.13f, 0.17f, 5.5f);
	//clean the buffer back and assign it a new color 
	glClear(GL_COLOR_BUFFER_BIT);
	//swap back buffer with front buffer
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		//take care of GLFW events
		glfwPollEvents();
	}
	//delete the window beforendign program
	glfwDestroyWindow(window);
	//terminate glfw before ending program
	glfwTerminate();
	return 0;



	glfwTerminate();
}