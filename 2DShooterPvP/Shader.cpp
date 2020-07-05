#include "Shader.h"

Shader::Shader()
{
	m_Program = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteShader(m_Program);
}

void Shader::compileShader(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	// for logging
	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//compile vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "Vertex Shader Compilation Failed!\n" << infoLog << std::endl;
	}

	//compile fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "Fragment Shader Compilation Failed!\n" << infoLog << std::endl;
	}

	//link into program
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::compileShader(string filePath)
{
	//parse file
	string vsrc, fsrc;
	ShaderFileParser::getShaderSrc(filePath, vsrc, fsrc);

	const char* vertexShaderSource = vsrc.c_str();
	const char* fragmentShaderSource = fsrc.c_str();

	// for logging
	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//compile vertex shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		printf("Vertex Shader Compilation Failed! :-( : %s\n", infoLog);
	}
	else {
		printf("Vertex Shader Compliled!\n");
	}

	//compile fragment shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		printf("Fragment Shader Compilation Failed! :-( : %s\n", infoLog);
	}
	else {
		printf("Fragment Shader Compliled!\n");
	}

	//link into program
	glAttachShader(m_Program, vertexShader);
	glAttachShader(m_Program, fragmentShader);
	glLinkProgram(m_Program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

