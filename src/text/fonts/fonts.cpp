#include "fonts.hpp"
#include <cstdlib>
#include <iostream>

Shirag::Text::Font* Shirag::Text::findClosestFont(std::vector<Font>* Fonts, int TargetFontSize) {
    Shirag::Text::Font* closestFontPtr = nullptr;
    int closestFontDiffrenceInSize = 0;

    for (auto& font : *Fonts) {
        int diffrenceInSize = TargetFontSize - font.size();
        if (diffrenceInSize == 0) {
            return &font;
        }

        diffrenceInSize = abs(diffrenceInSize);
        if (closestFontPtr == nullptr || diffrenceInSize - closestFontDiffrenceInSize < 0) {
            closestFontPtr = &font;
            closestFontDiffrenceInSize = diffrenceInSize;
        }
    }

    return closestFontPtr;
}