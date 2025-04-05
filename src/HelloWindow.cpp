#include<iostream>
#include <glad/glad.h>
#include<GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <stb_truetype/stb_truetype.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include"Texture.h"
#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include"Camera.h"
#include<string>
#include "Menu.h"

const unsigned int width = 1820;
const unsigned int height = 1080;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void Logs(std::string message, short int error);
std::string texturepath = RESOURCES_PATH"/Textures/";

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};

GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

int main()
{




	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Tell GLFW what version of GLSL we are using 
	// In this case we are using GLSL 3.3
	const char* glsl_version = "#version 330";

	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of width by height pixels, naming it "SailorPunishersThirdProgram"
	GLFWwindow* window = glfwCreateWindow(width, height, "SailorPunishersThirdProgram", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		Logs("Failed to create GLFW window", 1);
		glfwTerminate();
		return -1;
	}
	else 
	{
		Logs("Created GLFW Window", 2);
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	Logs("Made GLFW current context to window", 2);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	Logs("Loaded Glad", 2);

	// Icon For Main Window
	GLFWimage images[1];
	images[0].pixels = stbi_load(RESOURCES_PATH"/Icon/LunaIcon.png", &images[0].width, &images[0].height, 0, 4);
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);


	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	Logs("Set ImGui Color Style to Dark", 2);
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram(RESOURCES_PATH"/Shaders/default.vert", RESOURCES_PATH"/Shaders/default.frag");
	const int specularLighting = glGetUniformLocation(shaderProgram.ID, "specularLight");
	const int diffuseLighting = glGetUniformLocation(shaderProgram.ID, "diffuseLight");
	const int ambientLighting = glGetUniformLocation(shaderProgram.ID, "ambientLight");
	// Generates Vertex Array Object and binds it
	VAO VAO1;
	VAO1.Bind();
	Logs("Bound VAO1", 2);
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	Logs("Generated Vertex Buffer Object and linked it to vertices", 2);
	// Generates Element Buffer Object and links it to indices
	EBO EBO1(indices, sizeof(indices));
	Logs("Generated Element Buffer Object and linked it to vertices", 2);
	// Links VBO attributes such as coordinates and colors to VAO
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	Logs("Linked VBO attributes such as coordinates and colors to VAO", 2);
	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	Logs("Unbound VAO1", 2);
	VBO1.Unbind();
	Logs("Unbound VBO1", 2);
	EBO1.Unbind();
	Logs("Unbound EBO1", 2);
	// Shader for light cube
	Shader lightShader(RESOURCES_PATH"/Shaders/light.vert", RESOURCES_PATH"/Shaders/light.frag");
	// Generates Vertex Array Object and binds it
	VAO lightVAO;
	lightVAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO lightVBO(lightVertices, sizeof(lightVertices));
	// Generates Element Buffer Object and links it to indices
	EBO lightEBO(lightIndices, sizeof(lightIndices));
	// Links VBO attributes such as coordinates and colors to VAO
	lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	// Unbind all to prevent accidentally modifying them
	lightVAO.Unbind();
	lightVBO.Unbind();
	lightEBO.Unbind();

	// Texture
	Texture lunaTex((RESOURCES_PATH"/Textures/luna.png"), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	lunaTex.texUnit(shaderProgram, "tex0", 0);
	
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapInterval(vsync);
		// Creates camera object
		glm::vec4 lightColor = glm::vec4(SC_RED, SC_GREEN, SC_BLUE, SC_ALPHA);
		glm::vec3 lightPos = glm::vec3(lightpos1, lightpos2, lightpos3);
		glm::mat4 lightModel = glm::mat4(lightscale);
		lightModel = glm::rotate(lightModel, glm::radians(lightrotation), glm::vec3(lightpos1, lightpos2, lightpos3));
		lightModel = glm::translate(lightModel, lightPos);

		glm::vec3 pyramidPos = glm::vec3(pyramidpos1, pyramidpos2, pyramidpos3);
		glm::mat4 pyramidModel = glm::mat4(pyramidscale);
		pyramidModel = glm::rotate(pyramidModel, (float)glfwGetTime(), glm::vec3(pyramidpos1, pyramidpos2, pyramidpos3));
		pyramidModel = glm::translate(pyramidModel, pyramidPos);

		lightShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
		glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

		shaderProgram.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(pyramidModel));
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

		if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
		{
			continue;
		}

		// Rendering Stuff
		MenuIMGUI();
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		// Specify the color of the background
		glClearColor(BG_RED,BG_GREEN,BG_BLUE,BG_ALPHA);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Camera Stuff
		// Handles camera inputs
		camera.Inputs(window, Cameraspeed);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(Camerafov, Cameranearplane, Camerafarplane);
		camera.speed = Cameraspeed;
		camera.sensitivity = Camerasensitivity;


		// Tells OpenGL which Shader Program we want to use
		shaderProgram.Activate();
		// Exports the camera Position to the Fragment Shader for specular lighting
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
		// Export the camMatrix to the Vertex Shader of the pyramid
		camera.Matrix(shaderProgram, "camMatrix");
		// Binds texture so that is appears in rendering
		lunaTex.Bind();
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

		// Tells OpenGL which Shader Program we want to use
		lightShader.Activate();
		// Export the camMatrix to the Vertex Shader of the light cube
		camera.Matrix(lightShader, "camMatrix");
		// Bind the VAO so OpenGL knows to use it
		lightVAO.Bind();
		// Draw primitives, number of indices, datatype of indices, index of indices
		glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	// Delete all the objects we've created
	VAO1.Delete();
	Logs("Deleted VAO1", 2);
	VBO1.Delete();
	Logs("Deleted VBO1", 2);
	EBO1.Delete();
	Logs("Deleted EBO1", 2);
	lunaTex.Delete();
	Logs("Deleted luna Texture", 2);
	shaderProgram.Delete();
	Logs("Deleted shaderProgram", 2);
	lightVAO.Delete();
	Logs("Deleted lightVAO", 2);
	lightVBO.Delete();
	Logs("Deleted lightVBO", 2);
	lightEBO.Delete();
	Logs("Deleted lightEBO", 2);
	lightShader.Delete();
	Logs("Deleted lightShader", 2);
	// Delete window before ending the program
	glfwDestroyWindow(window);
	Logs("Destroyed GLFW Window", 2);
	// Terminate GLFW before ending the program
	glfwTerminate();
	Logs("Terminated GLFW", 2);
	return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
	Logs("viewport set to 0,0 " + std::to_string(width) + "x" + std::to_string(height), 2);

}
void Logs(std::string message, short int error)
{
	switch (error) {
	case 0:
		std::cout << "Sailor Success: " << "{" << message << "}" << '\n';
		break;
	case 1:
		std::cout << "Sailor Failure: " << "{" << message << "}" << '\n';
		break;
	case 2:
		std::cout << "Sailor Info: " << "{" << message << "}" << '\n';
		break;
	}

}