#include "windowSystem.hpp"

#include "drawing/line/line.hpp"
#include "drawing/rectangle/rectangle.hpp"
#include "drawing/text/text.hpp"
#include "raylib.h"
#include "text/fonts/fonts.hpp"
#include <raymath.h>
#include <vector>

bool Shirag::WindowSystem::IsMouseWithinWindow() {
    Vector2 mousePos = GetMousePosition();
    if (mousePos.x > GetScreenWidth())
        return false;
    if (mousePos.y > GetScreenHeight())
        return false;
    if (mousePos.x < 0)
        return false;
    if (mousePos.y < 0)
        return false;
    return true;
}

bool Shirag::WindowSystem::Window::update(bool SkipUpdate, std::vector<Shirag::Text::Font>* Fonts) {
    if (!shown)
        return false;
    mouseCursorChanged = false;

    if (SkipUpdate) // should be moved so it still shows u can drag even when window aint top KEEP IN MIND it might fuck with a lower window being behind and changing mouse cursor
        return false;

    if (resizable) {
        Rectangle dragableAreaRect = { window.x + window.width - 20, window.y + window.height - 20, 20.0f, 20.0f };
        Vector2 mousePos = GetMousePosition(); // [TASKIG] allow overload of mouse if user is using camera even tho nobody should be stupid enough to do use world space windows
        if (CheckCollisionPointRec(mousePos, dragableAreaRect)) {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_NWSE);
            mouseCursorChanged = true;
            if (IsMouseButtonPressed(0)) {
                resizing = true;
                offset = { window.width, window.height };
            }
        }

        if (IsMouseButtonUp(0)) {
            resizing = false;
        }

        if (resizing) {
            if (mousePos.x - window.x > minSize.x && mousePos.x - window.x < maxSize.x)
                window.width = mousePos.x - window.x;
            if (mousePos.y - window.y > minSize.y && mousePos.y - window.y < maxSize.y)
                window.height = mousePos.y - window.y;
        }
    }

    if (draggable) {
        Rectangle dragableAreaRect = { window.x, window.y, window.width, 55.0f };
        Vector2 mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, dragableAreaRect)) {
            SetMouseCursor(MOUSE_CURSOR_RESIZE_ALL);
            mouseCursorChanged = true;
            if (IsMouseButtonPressed(0)) {
                dragging = true;
                offset = Vector2Subtract({ window.x, window.y }, mousePos);
            }
        }

        if (IsMouseButtonUp(0)) {
            dragging = false;
        }

        if (dragging && IsMouseWithinWindow()) {
            window.x = mousePos.x + offset.x;
            window.y = mousePos.y + offset.y;
        }
    }

    closeBox = { window.x + window.width - 50, window.y, 50, 50 };

    if (CheckCollisionPointRec(GetMousePosition(), closeBox)) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        mouseCursorChanged = true;

        if (IsMouseButtonPressed(0)) {
            mouseCursorChanged = false; // it shows u can move whilst on close box, this is temp fix, should not show move on window close box // this is shizo ngl
            shown = false;
            dragging = false; // this would bug otherwise cus closing and draging is the same
        }
    }

    return false;
}

bool Shirag::WindowSystem::Window::draw(std::vector<Shirag::Text::Font>* Fonts) {
    if (!shown)
        return false;

    Shirag::Drawing::drawRectWithOutline(window, outline, GRAY, DARKGRAY);
    Shirag::Drawing::drawLineAligned({ window.x, window.y + 55.0f }, { window.x + window.width, window.y + 55.0f }, 5, DARKGRAY, Shirag::Drawing::UP);
    Shirag::Drawing::drawTextCenterTopRect(window, title, 50, DARKGRAY, 0, Shirag::Text::findClosestFont(Fonts, 50)->baseFont());

    DrawRectangleLinesEx(closeBox, 5, RED);
    DrawLineEx({ closeBox.x, closeBox.y }, { closeBox.x + closeBox.width, closeBox.y + closeBox.height }, 5, RED);
    DrawLineEx({ closeBox.x, closeBox.y + closeBox.height }, { closeBox.x + closeBox.width, closeBox.y }, 5, RED);
    return false;
}

bool Shirag::WindowSystem::Windows::update(std::vector<Shirag::Text::Font>* Fonts) { // I HATE THIS CODE, it took me atleast 2 hours to get the window z index to work correctly and its still bad // Som vanligt så satsade Shiralyn allting på dålig kod och inte fin eller bra kod, sen så gick skiten sönder, 10k KR skulle de ha för å fixa det. Då frågade jag sen när kod har blivit dyrare än kokain. Då sa de att det beror på vem som har skrivit koden, shiralyn uppenbarligen
    bool anyCursorChange = false;
    bool hoverOverAnyWindow = false;

    std::string clickedWindowKey;
    if (IsMouseButtonPressed(0)) {
        for (auto it = windows.begin(); it != windows.end(); ++it) {
            auto& [key, w] = *it;
            if (w->shown && CheckCollisionPointRec(GetMousePosition(), w->window)) {
                clickedWindowKey = key;
                break;
            }
        }
    }

    if (!clickedWindowKey.empty()) {
        auto node = windows.extract(clickedWindowKey);
        windows.insert(std::move(node));

        for (auto& [key, window] : windows)
            window->onTop = (key == clickedWindowKey);
    }

    std::string topWindowKey;
    for (auto& [key, window] : windows)
        if (window->onTop)
            topWindowKey = key;

    for (auto& [key, window] : windows) {
        bool allowUI = (key == topWindowKey);

        if (window->update(!allowUI, Fonts) == true)
            hoverOverAnyWindow = true;

        if (window->mouseCursorChanged)
            anyCursorChange = true;
    }

    if (!anyCursorChange)
        SetMouseCursor(1);

    return hoverOverAnyWindow;
}

void Shirag::WindowSystem::Windows::draw(std::vector<Shirag::Text::Font>* Fonts) {
    std::string onTopKey;

    for (auto& [key, value] : windows) {
        if (value->onTop) {
            onTopKey = key;
            continue;
        }
        value->draw(Fonts);
    }

    if (!onTopKey.empty())
        windows.at(onTopKey)->draw(Fonts);
}

void Shirag::WindowSystem::Windows::toggleWindow(std::string key) {
    windows.at(key)->shown = !windows.at(key)->shown;
}