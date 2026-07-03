#pragma once

#include "raylib.h"
#include "text/fonts/fonts.hpp"

namespace Shirag::Drawing {

    void drawTextCenterTopRect(Rectangle& Rect, std::string& Text, int FontSize, Color TextColor, int TopOffset = 0, Font Font = GetFontDefault());

}