#pragma once

#include "commons.h"

#include <string>

namespace ara {

    namespace gui {

        ARA_API void SimpleMessageBox(const std::string& title, const std::string& message);
        ARA_API void ErrorMessageBox(const std::string& title, const std::string& message);
        ARA_API int SimpleYesNoBox(const std::string& title, const std::string& message);

    } // gui

} // ara
