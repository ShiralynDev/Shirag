#include "rectangle.hpp"

void Shirag::Drawing::drawRectWithOutline(Rectangle& Rect, float LineThickness, Color RectColor, Color OutlineColor) {
    DrawRectangle(Rect.x, Rect.y, Rect.width, Rect.height, RectColor);
    DrawRectangleLinesEx(Rect, LineThickness, OutlineColor);
}