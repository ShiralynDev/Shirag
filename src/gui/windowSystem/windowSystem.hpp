#pragma once

#include "../../text/fonts/fonts.hpp"

#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace Shirag::WindowSystem {

    class Window {
    private:
        Rectangle closeBox{};
        bool dragging = false;
        bool resizing = false;
        Vector2 offset = { 0, 0 };

    protected:
        float outline = 0.0;

    public:
        virtual ~Window() = default;
        Rectangle window = {};
        std::string title = "";
        bool draggable = false;
        bool resizable = false;
        bool shown = false;
        Vector2 minSize = { 200, 200 };
        Vector2 maxSize = { 99999, 99999 };
        bool mouseCursorChanged = false;
        bool onTop = false;

        Window(Rectangle WindowRect, std::string Title, bool Draggable, bool Resizeable, bool Shown, int Outline, Vector2 MaxSize)
          : window{ WindowRect }
          , title{ Title }
          , draggable{ Draggable }
          , resizable{ Resizeable }
          , shown(Shown)
          , outline(Outline)
          , maxSize(MaxSize) {
            closeBox = { window.x + window.width - 50, window.y, 50, 50 };
        }

        virtual bool draw(std::vector<Shirag::Text::Font>* Fonts); // returns true on close requested
        virtual bool update(bool SkipUpdate, std::vector<Shirag::Text::Font>* Fonts);
    };

    class Windows { // linux user having to write windows :pensive:
    public:
        std::unordered_map<std::string, std::unique_ptr<Window>> windows;
        void draw(std::vector<Shirag::Text::Font>* Fonts);
        bool update(std::vector<Shirag::Text::Font>* Fonts);
        void toggleWindow(std::string key);
    };

    bool IsMouseWithinWindow();

}