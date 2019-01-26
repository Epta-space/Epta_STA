#include<GLFW/glfw3.h>
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
	//Initialize GLFW and create a GLFW window object (640 , 480)
	GLFWwindow * window;
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 480, "Chapter 1: Simple GLFW Example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//Loop that is terminated when the window is closed
	while (!glfwWindowShouldClose(window))
	{
		//Setup the viewport (using the screen dimensions) and clear the screen color buffer
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = (float)width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//Set up the camera matrix (more details in the 3D implementation)
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Draw an rotation triangle, with the first line managing the rotation.
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);
		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		//Spawn front and back buffers (GLFW works with two buffers) to updade the screen and process all pending events.
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Release the memory and terminate the glfw library and exit the aplication
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
