#pragma once

#include <raylib.h>
#include <string>

namespace Shirag {
    class Window {
    public:
        std::string title = "";
        int width = 0;
        int height = 0;

        Window(std::string Title, int Width, int Height, int Monitor = 0)
          : title(Title)
          , width(Width)
          , height(Height) {
            InitWindow(width, height, title.c_str());
            SetWindowMonitor(Monitor);
        };

        Window(std::string Title, Vector2 Size, int Monitor = 0)
          : title(Title)
          , width(Size.x)
          , height(Size.y) {
            InitWindow(width, height, title.c_str());
            SetWindowMonitor(Monitor);
        };

        ~Window() {
            if (IsWindowReady())
                CloseWindow();
        }

        void updateWindow();
    };
}