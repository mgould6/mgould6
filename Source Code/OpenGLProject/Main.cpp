#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	// initialize GLFW
	glfwInit();


	// tell GLFW what version of OpenGL we are using
	// in this case we are using 3.3.8
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// tell glfw we are using the CORE profile
	// meaning we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a GLFWindow object of 800 by 800 pixels naming it "OpenGL Project"
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Project", NULL, NULL);

	// error check if the window failes to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	// introduce the window to the current context
	glfwMakeContextCurrent(window);

	// load GlAD so it configures OpenGL
	gladLoadGL();

	// specify the viewport of OpenGL in the window
	// in this case the viewport goes from x = 0, y = 0, to x = 800, to y = 800
	glViewport(0,0, 800, 800);

	

	// create vertex shader object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	// compile the vertex shader into machine code
	glCompileShader(vertexShader);
	
	//create fragment shader object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	
	//compile the vertex shader into machine code
	glCompileShader(fragmentShader);

	// create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();

	// attach vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// wrap up / link all the shaders together into the shader program
	glLinkProgram(shaderProgram);

	// delete the now useless vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertices coordinates
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	// create reference containers for the vertex array object and the vertex buffer object
	// make sure to generate vao before vbo the order is very important
	GLuint VAO, VBO;

	// generate the VAO and VBO with only 1 object each
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	// bind the VBO specifying it's a GL_ARRAY_BUFFER 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// configure the vertex attribute so that openGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// enable the vertex attribute so that openGL know to use it
	glEnableVertexAttribArray(0);

	// bind both the vbo and vao to 0 so that we don't accidentally modify the vao and vbo we created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// main while loop
	while (!glfwWindowShouldClose(window))
	{

		// specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		// clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		
		//tell openGL which shader program we want to use
		glUseProgram(shaderProgram);
		
		// bind the vao so openGL knows to use it
		glBindVertexArray(VAO);
		
		//draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// swap the back buffer with the front buffer
		glfwSwapBuffers(window);

		// take care of all GLFW events
		glfwPollEvents();
	}

	// delete all the objects we have created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// delete window before ending the program
	glfwDestroyWindow(window);
	
	// terminate GLFW before ending the program
	glfwTerminate();

	return 0;
}