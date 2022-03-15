#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Vertex Shader Source Cpde
const char* vertexShaderSource = "#version 330\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader Source Code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit();

	//Tell GLFW what version of OpenGL we are using
	//In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using the core profile
	//So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Vertices coordinates
	GLfloat vertices[] =
	{
		/*-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		//Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			//Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f		//Upper Corner*/
		-0.5f, 1.0f, 0.0f,		//Lower left corner
		0.5f, -1.0f, 0.0f,			//Lower right corner
		0.0f, 1.0f, 0.0f,		//Upper Corner
		0.5f, 0.75f, 0.0f
	};

	//Create a GLFWwindow object of size 800 by 800 named VVVVV
	GLFWwindow* window = glfwCreateWindow(800, 800, "Eat my anus bitch", NULL, NULL);
	//Checks if the window fails to be made
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW Window you idiot" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();

	//Eat my ass - specify the viewport of OpenGL in the window
	//In this case the viewport goes from x=0, y=0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);

	//Create vertex shader object and get reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Attach vertex shader source to the vertex shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compile the vertex shader into machine code
	glCompileShader(vertexShader);

	//Create fragment shader object and get reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Attach fragment shader source to the fragment shader object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compile the vertex shader into machine code
	glCompileShader(fragmentShader);

	//Create shader program object and get its reference
	GLuint shaderProgram = glCreateProgram();
	//Attach the vertex and fragment shaders to the shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//weap-up/link all the shaders together into the shader program
	glLinkProgram(shaderProgram);

	//Delete the now useless vertex and fragment shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//create reference contrainers for the vertex array object and the vertex buffer object
	GLuint VAO, VBO;

	//Generate the VAO
	glGenVertexArrays(1, &VAO);
	//Generate the VBO
	glGenBuffers(1, &VBO);

	//Make the VAO the current vertex array object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configure the vertex attribute so that OpenGL knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable the vertex attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	//Bind both the VBO and VAO to 0 so that we dont accidentally modify the VAO and VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);





	//Tells openGL to prepare to clear the back buffer and give it another color - RGB and alpha
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//Use the command on the color buffer
	glClear(GL_COLOR_BUFFER_BIT);				//glClear sets the bitplane area of the window to values previously selected by glClearColor, glClearDepth, and glClearStencil
	glfwSwapBuffers(window);

	while(!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OpenGL which shader program we want to use it
		glUseProgram(shaderProgram);
		//Bind the VAO so OpenGL knows how to use it
		glBindVertexArray(VAO);
		//Draw the triangle using the GL_TRIANGLES primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	//Delete all the objects we've created
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);


	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}