#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream> 


// Recebe o codigo fonte e o tipo de shader. (tenta-se evitar o uso de types do OPENGL)
// Retorna-se o index deste. (identificador)
static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);                           // cria o shader especificado sobre o index id. 
	const char* src = source.c_str();                                 // converte o código fonte em um pointer para esta string, mas em type caracteristico de C 
	glShaderSource(id, 1, &src, nullptr);                             // especifica o arquivo fonte.
	glCompileShader(id);                                              // Compila o shader.

	//TODO : ERROR HANDLING checar se erramos algo no código.
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);               // adquire o tamanho da mensagem de erro
		char* message = (char*)alloca(length * sizeof(char));         // alloca :: permite allocar de forma dinâmica --> foi convertida em pointer.
		glGetShaderInfoLog(id , length , &length, message);           // coloca na mensagem o erro.
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << std::endl; // extrutura interessante condicional
		std::cout << message << std::endl;                                                                                // Printa o erro.
		glDeleteShader(id);                                                                                               // Deleta      
		return 0;
	}

	return id;                                                        // retorna o index do shader em questão.
}



// Dar ao OpenGL um código fonte para que compile os shaders, linke eles em um único shader e devolva um identificador único deste. 
// para que se possa se referenciar a ele no código dando binding e ativandoo.
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();                             // equivalente a generatebuffer, mas para shader. 
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);      // pede para compilar o shader em questão (VERTEX)
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);  // pede para compilar o shader em questão (fragment)

	glAttachShader(program, vs);                                          // aproxima ao programa criado anteriormente
	glAttachShader(program, fs);                                          // aproxima ao progrma criado anteriormente
	glLinkProgram(program);                                               // Linka tudo próximo a programa.
	glValidateProgram(program);                                           // Valida o código criado.

	glDeleteShader(vs);                                                   // Como temos um programa, vale excluir os resultados de compilação (.obj)
	glDeleteShader(fs);                                                   // Como temos um programa, vale excluir os resultados de compilação (.obj)

	return program;
}
  

// Programa principal, com o loop de impreção
int main(void)
{
	GLFWwindow* window;                                                     // Declara-se uma janela1
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);         // Cria-se uma janela sob condições específicas.
	if (!window)
	{
		glfwTerminate();
		return -1;                                                          // Se não foi possível criar a janela, retornar erro.
	}


	/* Make the window's context current */
	glfwMakeContextCurrent(window);                                         // Especifica-se a janela atual.



	if (glewInit() != GLEW_OK)                                              // Inicia-se GLEW em um contexto de janela. 
		std::cout << "ERRO!" << std::endl;                                  // Checa-se se foi possível iniciar GLEW 

	std::cout<<glGetString(GL_VERSION)<<std::endl;                          // Printa a versão do OPENGL.

	float position[6] = {                                                   // Declara dados de posição.
		-0.5f  , -0.5f,
		 0.0f  ,  0.5f,
		 0.5f  , -0.5f
	};



	unsigned int buffer;                                                          // declara-se um buffer 
	glGenBuffers(1, &buffer);                                                     // Gera-se esse buffer (quantidade 1)
	glBindBuffer(GL_ARRAY_BUFFER, buffer);                                        // seleciona-se ele para edição
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), position, GL_STATIC_DRAW);   // coloca-se dados dentro do buffer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);        // Se declara um atributo dos dados (com formatação.
	glEnableVertexAttribArray(0);                                                 // Se aciona essa atribuição



	std::string vertexShader =                                      // programa que será enviado para a placa de vídeo (vertex)
		"#version 330 core\n"                                       // Para compatibilidade, versções antigas são melhores
		"\n"
		"layout(location = 0) in vec4 position;\n"                  // Refere-se ao index 0, da atribuição preveamente criada.
		"\n"
		"void main()\n"
		"{\n"
		"	gl_Position = position ;\n"                             // necessita ser um vec4 , mesmo para códigos em 2 dimensões
		"}\n";

	std::string fragmentShader =                                    // programa que será enviado para a placa de vídeo (fragment)
		"#version 330 core\n"                                       // Para compatibilidade, versções antigas são melhores
		"\n"
		"out vec4 color;\n"                                         // declarou-se a cor.
		"\n"
		"void main()\n"
		"{\n"
		"	color = vec4(0.5 , 0.5 , 0.0, 1.0);\n"                  // especifica a cor, no caso, vermelho. (r ,g , b , a)
		"}\n";


	unsigned int shader = CreateShader(vertexShader, fragmentShader);     // Cria o programa na placa de vídeo.
	glUseProgram(shader);                                                 // Inicializa o programa. 




	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);


		glDrawArrays(GL_TRIANGLES, 0, 3);             // (comando de desenho) Modern OpenGl triangle. assiona-se o shader contextualizado.


		//glBegin(GL_TRIANGLES);
		//glVertex2f(-0.5f , -0.5f);                  // Legacy opengl triangle. Ainda sim usa nosso shader, mas não nossa atribuição
		//glVertex2f(0.0f  ,  0.5f);
		//glVertex2f(0.5f, -0.5f);
		//glEnd();
		


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}



	glDeleteProgram(shader);                           // Deleta-se o programa criado.

	glfwTerminate();                                   // finali-se glfw.

	return 0;
}