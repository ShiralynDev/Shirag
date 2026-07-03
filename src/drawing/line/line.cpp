#include "line.hpp"

void Shirag::Drawing::drawLineAligned(Vector2 StartPos, Vector2 EndPos, float LineThick, Color LineColor, ALIGN Alignment) {
    switch (Alignment) {
        case 0:
            StartPos.x = StartPos.x - LineThick / 2;
            EndPos.x = EndPos.x - LineThick / 2;
            break;

        case 1:
            StartPos.x = StartPos.x + LineThick / 2;
            EndPos.x = EndPos.x + LineThick / 2;
            break;

        case 2:
            StartPos.y = StartPos.y - LineThick / 2;
            EndPos.y = EndPos.y - LineThick / 2;
            break;

        case 3:
            StartPos.y = StartPos.y + LineThick / 2;
            EndPos.y = EndPos.y + LineThick / 2;
            break;

        default:
            break;
    }

    DrawLineEx(StartPos, EndPos, LineThick, LineColor);
}