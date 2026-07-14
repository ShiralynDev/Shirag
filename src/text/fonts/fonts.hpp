#pragma once

#include <raylib.h>
#include <string>
#include <vector>

namespace Shirag::Text {

    /// Struct for advanced versions of the Raylib Font struct
    struct Font { // [TASKIG] add overload for codepoints
    private:
        ::Font font;

    public:
        /// Gets the fontsize
        constexpr int size() const {
            return font.baseSize;
        }
        ::Font baseFont() const {
            return font;
        }
        /// Load basic font with normal size
        Font(std::string FilePath) {
            font = LoadFont(FilePath.c_str());
        }
        /// Load font size with specified size
        Font(std::string FilePath, int FontSize) {
            font = LoadFontEx(FilePath.c_str(), FontSize, NULL, 0);
        }

        ~Font() {
            UnloadFont(font);
        }
    };

    /// Finds the font closest to the target size
    Font* findClosestFont(std::vector<Font>* Fonts, int TargetFontSize);

}