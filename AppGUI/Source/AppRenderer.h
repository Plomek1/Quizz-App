#pragma once

#include <functional>

namespace AppGUI
{
	void Render(std::function<void()>& renderFunction);
}