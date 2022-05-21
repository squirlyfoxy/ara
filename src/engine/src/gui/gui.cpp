#include "gui/gui.h"

// Will include OS related stuff
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

        void ErrorMessageBox(const std::string& title, const std::string& message) {
            #ifdef _WIN32
                MessageBoxA(NULL, message.c_str(), title.c_str(), MB_OK | MB_ICONERROR);
            #else
                // Need zenity to be installed
                system(("zenity --error --title=\"" + title + "\" --text=\"" + message + "\"").c_str());
            #endif
        }

        int SimpleYesNoBox(const std::string& title, const std::string& message) {
            #ifdef _WIN32
                return MessageBoxA(NULL, message.c_str(), title.c_str(), MB_YESNO) == IDYES;
            #else
                // Need zenity to be installed
                return system(("zenity --question --title=\"" + title + "\" --text=\"" + message + "\"").c_str()) == 0;
            #endif
        }

    } // gui

} // ara
