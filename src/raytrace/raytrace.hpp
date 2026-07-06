#pragma once

#include <raylib.h>
#include <vector>

namespace Shirag::Raytrace {

    std::vector<Vector2> raytrace(Vector2 StartPosition, int Segments, std::vector<Rectangle>& Obstacles, int Range);

}