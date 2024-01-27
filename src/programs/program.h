#include "../glad/glad.h"
#include <GLFW/glfw3.h>

#include "../rendering/shader.h"


#ifndef PROGRAM_H
#define PROGRAM_H

class Program {
public:
	Shader shader;

	virtual void load() = 0;
	virtual void render(double dt) = 0;
	virtual void cleanup() = 0;
};

#endif