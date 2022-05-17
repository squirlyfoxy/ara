#include "gui/gui.h"

ARA_INCLUDE_OS

namespace ara {

    namespace gui {

        void SimpleMessageBox(const std::string& title, const std::string& message) {
            #ifdef _WIN32
                MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK);
            #else
                // Need zenity to be installed
                system(("zenity --info --title=\"" + title + "\" --text=\"" + message + "\"").c_str());
            #endif
        }

    } // gui

} // ara
