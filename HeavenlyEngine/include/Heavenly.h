#pragma once

// TODO: Having the engine include this in this all purpose header seems wasteful.
#include <imgui.h>
#include <imgui_internal.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/AppRuntime.h"
#include "core/Engine.h"

#include "resources/Manager.h"
#include "resources/Shader.h"

#include "window_system/Window.h"

#include "world/Component.h"
#include "world/Entity.h"
#include "world/WorldAdmin.h"
#include "world/GUIComponents.h"
#include "world/RenderingComponents.h"
