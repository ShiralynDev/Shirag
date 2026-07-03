#pragma once

#include <raylib.h>

namespace Shirag::Drawing {

    enum ALIGN {
        LEFT = 0,
        RIGHT,
        UP,
        DOWN
    };

    void drawLineAligned(Vector2 StartPos, Vector2 EndPos, float LineThick, Color LineColor, ALIGN Alignment);

}