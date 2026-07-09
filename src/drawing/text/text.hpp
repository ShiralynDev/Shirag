#pragma once

#include <raylib.h>
#include <string>

namespace Shirag::Drawing {

    void drawTextCenterTopRect(Rectangle& Rect, std::string& Text, int FontSize, Color TextColor, int TopOffset = 0, Font Font = GetFontDefault());

    void drawTextCenterPoint(Vector2 Center, std::string& Text, int FontSize, Color TextColor, bool CenterX = true, bool CenterY = true, Font Font = GetFontDefault());

    void drawTextCenterRect(Rectangle Rect, std::string& Text, int FontSize, Color TextColor, bool CenterX, bool CenterY, Font Font = GetFontDefault());
}