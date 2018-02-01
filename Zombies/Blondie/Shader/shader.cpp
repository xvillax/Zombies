#include "shader.h"
#include "..\Utils\Printerror.h"
#include <fstream>
#include <vector>

BLONDIE::Shader::Shader()
	:m_programID(0),
	 m_vertID(0),
	 m_fragID(0),
	 m_numatribs(0)
{
}


BLONDIE::Shader::~Shader()
{
}

void BLONDIE::Shader::CreateShaders(const std::string& vertfilepath, const std::string& fragfilepath)
{
	m_programID = glCreateProgram();

	m_vertID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertID == 0)
		PrintError("Failed To Create Vertex Shader ID");

	m_fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if(m_fragID == 0)
		PrintError("Failed To Create Fragment Shader ID");

	CompileShaders(vertfilepath, m_vertID);
	CompileShaders(fragfilepath, m_fragID);
}


void BLONDIE::Shader::CompileShaders(const std::string& filepath, const GLuint& shaderid)
{
	////Read in the Vertex Shader File///////

	std::ifstream shaderfile(filepath);
	if (shaderfile.fail())
	{
		perror(filepath.c_str());
		PrintError("Failed to open shader file...  " + filepath);
	}

	std::string shaderfilestr = "";
	std::string line = "";

	while (std::getline(shaderfile, line))
	{
		shaderfilestr += line + "\n";
	}
	shaderfile.close();
	const char* contentsptr = shaderfilestr.c_str();
	
	glShaderSource(shaderid, 1, &contentsptr, nullptr);
	glCompileShader(shaderid);
	GLint isCompiled = 0;
	glGetShaderiv(shaderid, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shaderid, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(shaderid, maxLength, &maxLength, &errorLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(shaderid); // Don't leak the shader.

		std::printf("%s\n", &errorLog[0]);
		PrintError("Shader " + filepath + " Failed To Compile...");
	}
}

void BLONDIE::Shader::LinkShaders()
{
	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	

	// Attach our shaders to our program
	glAttachShader(m_programID, m_vertID);
	glAttachShader(m_programID, m_fragID);

	// Link our program
	glLinkProgram(m_programID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_programID);
		// Don't leak shaders either.
		glDeleteShader(m_vertID);
		glDeleteShader(m_fragID);

		std::printf("%s\n", &errorLog[0]);
		PrintError("Shader Failed To Link...");

	}

	// Always detach and delete shaders after a successful link.
	glDetachShader(m_programID, m_vertID);
	glDetachShader(m_programID, m_fragID);
	glDeleteShader(m_vertID);
	glDeleteShader(m_fragID);

}

void BLONDIE::Shader::AddAttrib(const std::string& attribname)
{

	glBindAttribLocation(m_programID, m_numatribs++, attribname.c_str());
	
}

void BLONDIE::Shader::Use()
{
	glUseProgram(m_programID);
	for (GLuint i = 0; i < m_numatribs; i++)
		glEnableVertexAttribArray(i);
}

void BLONDIE::Shader::Unuse()
{
	glUseProgram(0);
	for (GLuint i = 0; i < m_numatribs; i++)
		glDisableVertexAttribArray(i);
}

GLint BLONDIE::Shader::GetUniformLocation(const std::string & uniformname)
{
	GLint location = glGetUniformLocation(m_programID, uniformname.c_str());
	
	if (location == GL_INVALID_INDEX)
		PrintError("Uniform " + uniformname + "not found in shader");

	return location;
}
