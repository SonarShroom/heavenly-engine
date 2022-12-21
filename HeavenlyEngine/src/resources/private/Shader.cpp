#include "Shader.h"

#include "logging/LogManager.h"
#include "graphics/Renderer.h"

namespace Heavenly::Resources
{

/*Shader::Shader(const std::filesystem::path& vertexShader, const std::filesystem::path& fragmentShader)
{
	
}*/

Shader::Shader(const UUIDType uuid, const std::string_view& vertexShader, const std::string_view& fragmentShader)
	: IResource(uuid)
{
	enum class _ShaderType
	{
		Vertex,
		Fragment,
		Size
	};

	static constexpr auto _compilationSucceeded = [](int shaderID) -> bool
	{
		int success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (success)
		{
			return true;
		}

		return false;
	};

	static constexpr auto _compileShader = [](const std::string_view& shaderSource, _ShaderType type) -> int
	{
		int _newShaderID = 0;
		switch (type)
		{
			case _ShaderType::Vertex:
			{
				_newShaderID = glCreateShader(GL_VERTEX_SHADER);
			} break;
			case _ShaderType::Fragment:
			{
				_newShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			} break;
			default: break;
		}

		const char* _shaderCStr = shaderSource.data();
		glShaderSource(_newShaderID, 1, &_shaderCStr, nullptr);
		glCompileShader(_newShaderID);
		return _newShaderID;
	};

	int _vertexShaderID = 0;
	bool _vertexCompiled = false;
	if (!vertexShader.empty())
	{
		_vertexShaderID = _compileShader(vertexShader, _ShaderType::Vertex);
		_vertexCompiled = _compilationSucceeded(_vertexShaderID);
		if (!_vertexCompiled)
		{
			char infoLog[512] {0};
			glGetShaderInfoLog(_vertexShaderID, 512, NULL, infoLog);
			HV_LOG_ERROR("Error on vertex shader compilation: {}", infoLog);
		}
	}

	int _fragmentShaderID = 0;
	bool _fragmentCompiled = false;
	if (!fragmentShader.empty())
	{
		_fragmentShaderID = _compileShader(fragmentShader, _ShaderType::Fragment);
		_fragmentCompiled = _compilationSucceeded(_fragmentShaderID);
		if (!_vertexCompiled)
		{
			char infoLog[512] {0};
			glGetShaderInfoLog(_fragmentShaderID, 512, NULL, infoLog);
			HV_LOG_ERROR("Error on vertex shader compilation: {}", infoLog);
		}
	}
	programID = glCreateProgram();
	if (_vertexCompiled)
	{
		glAttachShader(programID, _vertexShaderID);
	}
	if (_fragmentCompiled)
	{
		glAttachShader(programID, _fragmentShaderID);
	}
	glLinkProgram(programID);
	int _linkSuccess = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &_linkSuccess);
	if (!_linkSuccess)
	{
		char infoLog[512]{ 0 };
		glGetProgramInfoLog(programID, 512, nullptr, infoLog);
		HV_LOG_ERROR("Error on linking shader program: {}", infoLog);
	}

	compiled = (vertexShader.empty() || _vertexCompiled) && (fragmentShader.empty() || _fragmentCompiled) && _linkSuccess != 0;

	// NOTE: Should we really delete the shaders here?
	glDeleteShader(_vertexShaderID);
	glDeleteShader(_fragmentShaderID);
}

}