#include "fonts.hpp"
#include <cstdlib>
#include <iostream>

Shirag::Text::Fonts::Font* Shirag::Text::Fonts::findClosestFont(std::vector<Font> Fonts, int TargetFontSize) {
    Shirag::Text::Fonts::Font* closestFontPtr = nullptr;
    int closestFontDiffrenceInSize = 0;

    for (auto& font : Fonts) {
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