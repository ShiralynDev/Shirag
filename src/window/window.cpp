#include "window.hpp"

void Shirag::Window::updateWindow() {
    SetWindowTitle(title.c_str());
    SetWindowSize(width, height);
}