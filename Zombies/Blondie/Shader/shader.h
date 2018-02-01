#pragma once
#include <gl\glew.h>
#include <string>

namespace BLONDIE {
	class Shader
	{
	public:
		Shader();
		~Shader();
		void CreateShaders(const std::string& vertfilepath, const std::string& fragfilepath);
		void LinkShaders();
		void AddAttrib(const std::string& attribname);
		void Use();
		void Unuse();
		GLint GetUniformLocation(const std::string& uniformname);

	private:
		void CompileShaders(const std::string& fielpath, const GLuint& shaderid);

		GLuint m_numatribs;
		GLuint m_programID;
		GLuint m_vertID;
		GLuint m_fragID;
	};
}

