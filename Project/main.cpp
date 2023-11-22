#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <FragmentShader.h>
#include <cmath>
int main() {
	FragmentShader shaderProp = *new FragmentShader();
	//constants window params
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	//initializing glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] =
	{
		//left corner
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//right corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		//top corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,
	};

	//creating window (width, height, window title, if it's fullscreen or not, is not important)
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Learning OpenGL", NULL, NULL);
	if (window == NULL) 
	{
		std::cout << "ERROR CREATING A WINDOW! " << std::endl;
		glfwTerminate();
		return -1;
	}
	//use this window
	glfwMakeContextCurrent(window);

	//preparing glad
	gladLoadGL();
	
	//front and back buffers
	//in this case viewport goes from x = 0 and y = 0 to x = 800, y = 800
	glViewport(0, 0, 800, 800);
	//Creating a vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//binding to a shaderSource
	glShaderSource(vertexShader, 1, &shaderProp.vertexShaderSource, NULL);
	//compiles down to machine code in order to GPU can handles it
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentShader, 1, &shaderProp.fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	//Wrap it up using shader program
	GLuint shaderProgram = glCreateProgram();
	//attaching shader to a shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//wrap shader program
	glLinkProgram(shaderProgram);
	//deleting shaders created, because they're already in the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//Creating in memory Vertices Buffers Objects;
	GLuint VAO, VBO;
	//binding &VBO to be the current object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//binding VAO
	glBindVertexArray(VAO);
	//binding VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enabling vertexshaders
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Clear the color of the buffer (RGBA)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//Swapping the buffers to actually see the colors (front to back)
	//back buffer is the write-buffer, and front buffer is a read-buffer
	glfwSwapBuffers(window);

	//maintaning window to show on screen (main while loop)
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		//adjusting resizing, minimizing
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	//destroying a window
	glfwDestroyWindow(window);
	//closing application
	glfwTerminate();
	return 0;
}