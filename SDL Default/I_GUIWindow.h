#pragma once
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "imgui_sdl.h"
#include "imgui_internal.h"


class I_GUIWindow
{
	virtual void GuiDraw() = 0;
};
