//
// Created by root on 3/5/23.
//

#include "shader.h"


namespace dge::frontend {

	void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if ((key == GLFW_KEY_ESCAPE || key == GLFW_KEY_A) && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

}








int main()
{
	struct {
		int width{0};
		int height{0};
	} viewport;

	//Start GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	
	
	//WARNING, ACHTUNG:
	//GLFW: Theres a macro called GLWF_VERSION_MAJOR, using that one (as well for MINOR) will lead into crashes,
	//https://github.com/glfw/glfw/issues/1849
	

	//Create a 800x600 window, use nullptr
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//IN APPLE THIS SHOULD BE TURNED UNCOMMENTED: glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	//Bringin the pointers.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	
	//Start the Scene
	//Set the key callback
	glfwSetKeyCallback(window, dge::frontend::glfw_key_callback);
	
	//Set the viewport
	glfwGetFramebufferSize(window, &viewport.width, &viewport.height);
	glViewport(0, 0, viewport.width, viewport.height);
	

	//Simple Shader String use opengl 3.30
	
	std::string vertexShaderSource = R"(
		#version 330 core
		layout (location = 0) in vec3 aPos;
		layout (location = 1) in vec3 aColor;
		layout (location = 2) in vec2 aTexCoord;

		out vec3 ourColor;
		out vec2 TexCoord;
		void main()
		{
			gl_Position = vec4(aPos, 1.0);
		}
	)";
	std::string fragmentShaderSource = R"(
		#version 330 core
		in vec3 ourColor;
		in vec2 TexCoord;
		out vec4 FragColor;
		void main()
		{
			FragColor = vec4(1.0, 0.0, 0.0, 1.0);
		}
	)";
	
	//Create a shader program
	auto vrtxShader = glCreateShader(GL_VERTEX_SHADER);
	auto fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	//Attach the shader source to the shader
	const char* vrtxShaderSource = vertexShaderSource.c_str();
	const char** vrtxShaderSourcePtr = &vrtxShaderSource;
	const char* fragShaderSource = fragmentShaderSource.c_str();
	const char** fragShaderSourcePtr = &fragShaderSource;
	glShaderSource(vrtxShader, 1, vrtxShaderSourcePtr, nullptr);
	glShaderSource(fragShader, 1, fragShaderSourcePtr, nullptr);

	//Compile the shader
	glCompileShader(vrtxShader);
	glCompileShader(fragShader);

	//Check for errors
	int success;
	char infoLog[512];
	glGetShaderiv(vrtxShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vrtxShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl << infoLog << std::endl;
	}

	//Create a shader program
	auto shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vrtxShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);

	//Check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl << infoLog << std::endl;
	}
	else
	{
		std::cout << "Shader Program Linked Successfully" << std::endl;
	}

	//Splash the window with a blue slate color and clear the buffer. Implement a while (true) loop, that breaks when esc key is pressed.
	


	//Create a Triangle, at plane  z = -1.0f

	//Create a Rectangl at plane z = -1.0f
	float vertices[] = {
		-0.5f, -0.5f, -1.0f,
		0.5f, -0.5f, -1.0f,
		0.5f,  0.5f, -1.0f,
		-0.5f,  0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		0.5f,  0.5f, -1.0f
	};

	//Create a Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	
	//Bind the VAO: All subsequent VBO/Element Buffer Object calls will be stored in this VAO.
	glBindVertexArray(VAO);
	
	
	//Bind data to buffer. 
	
	//GL_ARRAY_BUFFER: The buffer is used to store vertex attributes, such as vertex coordinates, texture coordinates, or vertex color information.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Copy the vertices array in a buffer for OpenGL to use (GL_STATIC_DRAW: the data will most likely not change at all or very rarely)
	std::cout << "Vertices size: " << sizeof(vertices) << std::endl;
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	//Now the attributes:
	//the first parameter is the location of the attribute in the shader (layout = 0), 
	//the second is the size of the attribute (3 for a vec3),
	//the third is the type of the attribute, 
	//the fourth is if the data should be normalized (0-1), we don't want this, so false.
	//the fifth is the stride (the space between this and the next attributes), 
	//the last is the offset of the attribute since the beginning of the buffer.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	//Create a Blue Window that escapes with escape
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		
		//Render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Draw the triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	
		
		//Draw
		glfwSwapBuffers(window);

	}



	//Destroy the Window.
	glfwDestroyWindow(window);

	//Terminate GLFW
	glfwTerminate();

	//bye bye
	return 0;


}



