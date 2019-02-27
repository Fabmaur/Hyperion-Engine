#include "Shader.h"
#include <pch.h>

namespace graphics
{

	std::map<std::string, unsigned int> Shader::shaderMap;
	Shader::Shader(const std::string& filename)
	{
		auto shaderCache = shaderMap.find(filename);
		if (shaderCache == shaderMap.end())
		{
			HP_STATUS("Opening shader file: ", filename);
			ShaderContainer shader = ParseShader(filename);
			id = CreateShader(shader.vertex, shader.fragment);
			shaderMap.insert(std::pair(filename, id));
		}
		else
		{
			id = shaderCache->second;
		}
	}

	void Shader::Delete()
	{
		HP_STATUS("Destructing shader");
		GLCheck(glDeleteProgram(id));
	}

	ShaderContainer Shader::ParseShader(const std::string& filename)
	{
		std::ifstream in(filename);
		HP_ASSERT(in, "The file could not be found")

			enum class type {
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		type shader = type::NONE;
		std::stringstream ss[2];
		std::string line;

		while (std::getline(in, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					HP_STATUS("Found vertex shader");
					shader = type::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					HP_STATUS("Found fragment shader");
					shader = type::FRAGMENT;
				}
			}
			else
			{
				ss[(int)shader] << line << "\n";
				HP_ASSERT(((int)shader != -1), "Could not find #shader");
			}
		}
		return { ss[0].str(), ss[1].str() };
	}

	unsigned int Shader::CompileShader(const unsigned int type, const std::string& source)
	{
		GLCheck(unsigned int id = glCreateShader(type));
		const char* src = source.c_str();
		GLCheck(glShaderSource(id, 1, &src, NULL));
		GLCheck(glCompileShader(id));

		int  success;
		char infoLog[512];
		GLCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

		if (!success)
		{
			glGetShaderInfoLog(id, 512, NULL, infoLog);
			HP_ERROR("ERROR::SHADER::", (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), "::COMPILATION_FAILED\n", infoLog);
		}
		else
			HP_SUCCESS("Successful ", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), " shader");

		return id;
	}

	unsigned int Shader::CreateShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		GLCheck(unsigned int program = glCreateProgram());
		unsigned int vertexID = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		unsigned int fragmentID = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
		GLCheck(glAttachShader(program, vertexID));
		GLCheck(glAttachShader(program, fragmentID));
		GLCheck(glLinkProgram(program));
		GLCheck(glValidateProgram(program));
		GLCheck(glDeleteShader(vertexID));
		GLCheck(glDeleteShader(fragmentID));

		return program;
	}

	const int Shader::GetUniformLoc(const std::string& name)
	{
		GLCheck(int loc = glGetUniformLocation(id, name.c_str()));
		if (loc == -1)
		{
			HP_ERROR("Error uniform ", name, " not found!");
		}
		return loc;
	}

	void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		GLCheck(glUniform4f(GetUniformLoc(name), v0, v1, v2, v3));
	}

	void Shader::SetUniformiv(const std::string& name, int count, int* value)
	{
		GLCheck(glUniform1iv(GetUniformLoc(name), count, value));
	}

	void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		GLCheck(glUniform3f(GetUniformLoc(name), v0, v1, v2));
	}

	void Shader::SetUniform4v(const std::string & name, maths::vec4f& val)
	{
		GLCheck(glUniform4fv(GetUniformLoc(name), 1, &val.x));
	}

	void Shader::SetUniform3v(const std::string & name, maths::vec3f& val)
	{
		GLCheck(glUniform3fv(GetUniformLoc(name), 1, &val.x));
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		GLCheck(glUniform1i(GetUniformLoc(name), value));
	}

	void Shader::SetUniform1f(const std::string& name, float value)
	{
		GLCheck(glUniform1f(GetUniformLoc(name), value));
	}
	void graphics::Shader::SetUniform2f(const std::string& name, float v0, float v1)
	{
		GLCheck(glUniform2f(GetUniformLoc(name), v0, v1));
	}

	void Shader::SetUniformMat4f(const std::string& name, const maths::mat4f& matrix)
	{
		GLCheck(glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &matrix.elements[0]));
	}

	void Shader::Bind() const
	{
		GLCheck(glUseProgram(id));
	}

	void Shader::Unbind() const
	{
		GLCheck(glUseProgram(0));
	}
}