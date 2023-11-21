#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
int main() {
	//constants window params
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 800;
	//initializing glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	
	//Clear the color of the buffer (RGBA)
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//Swapping the buffers to actually see the colors (front to back)
	//back buffer is the write-buffer, and front buffer is a read-buffer
	glfwSwapBuffers(window);

	//maintaning window to show on screen (main while loop)
	while (!glfwWindowShouldClose(window))
	{
		//adjusting resizing, minimizing
		glfwPollEvents();
	}
	//destroying a window
	glfwDestroyWindow(window);
	//closing application
	glfwTerminate();
	return 0;
}