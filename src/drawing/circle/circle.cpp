#include "circle.hpp"
#include "raylib.h"

void Shirag::Drawing::drawCircleWithOutline(Vector2 Center, float Radius, Color CircleColor, Color OutlineColor) {
    DrawCircleV(Center, Radius, CircleColor);
    DrawCircleLinesV(Center, Radius, OutlineColor);
}