#pragma once

#include <filesystem>
#include <string_view>

#include <glad/glad.h>

namespace Heavenly::Graphics
{
class Renderer;
}

namespace Heavenly::Resources
{

class Shader
{
public:
	/*Shader(
		const std::filesystem::path& vertexShader,
		const std::filesystem::path& fragmentShader
	);*/
	Shader(const std::string_view& vertexShader, const std::string_view& fragmentShader);
	inline ~Shader() { if (compiled) { glDeleteProgram(programID); } }

	inline unsigned int GetProgramID() const { return programID; }
	inline bool IsCompiled() const { return compiled; }

private:
	unsigned int programID = 0;
	bool compiled = false;
};

}