#include "text.hpp"

void Shirag::Drawing::drawTextCenterTopRect(Rectangle& Rect, std::string& Text, int FontSize, Color TextColor, int TopOffset, Font Font) {
    float spacing = FontSize / 10.0f; // same way as raylib calcs it (Ehmm you need a calc for that, I know you have a calc, chat calc stands for calculator btw)
    Vector2 textSize = MeasureTextEx(Font, Text.c_str(), FontSize, spacing);

    DrawTextEx(Font,
               Text.c_str(),
               { (Rect.x + Rect.width / 2) - textSize.x / 2, Rect.y + TopOffset },
               FontSize,
               spacing,
               TextColor);
}