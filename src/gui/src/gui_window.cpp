#include "gui_window.h"

ImWindow::ImWindow(std::string name) {
    this->name = name;
    this->open = true;
}

ImWindow::~ImWindow() {
}

std::string ImWindow::GetName() {
    return name;
}

bool ImWindow::IsOpen() {
    return open;
}

void ImWindow::SetOpen(bool open) {
    this->open = open;
}

void ImWindow::SetName(std::string name) {
    this->name = name;
}
