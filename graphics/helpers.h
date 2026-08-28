#pragma once
#include <glad/glad.h>
#include <string>
#include "../src/log.h"

namespace eclipse::graphics{
void CheckGLError(const char* file = "", int line = 0);
}
#ifndef ECLIPSE_CONFIG_RELEASE
#define ECLIPSE_CHECK_GL_ERROR eclipse::graphics::CheckGLError(__FILE__, __LINE__);
#else
#define ECLIPSE_CHECK_GL_ERROR (void)0
#endif
