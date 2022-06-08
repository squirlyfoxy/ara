#include "gui/gui.h"

// Will include OS related stuff
ARA_INCLUDE_OS

namespace ara {

    namespace gui {

        std::string getCmdOutput(std::string cmd)
        {
            // string to store the final results in
            std::string outputString;

            // stream to capture the command output
            FILE *outpStream;

            // maximum line length when capturing
            //    command output
            const int MaxLineLen = 128;

            // storage for one line of captured output
            char  outpLine[MaxLineLen];

            // redirect the standard output from the command
            cmd += " 2>&1";

            // run the command, piping the output to our stream
            outpStream = popen(cmd.c_str(), "r");
            if (outpStream) {
                // capture the output, one line at a time,
                //    appending it to our output string
                while (!feof(outpStream)) {
                    if (fgets(outpLine, MaxLineLen, outpStream) != NULL) {
                        outputString += outpLine;
                    }
                }
                pclose(outpStream);
            }
            return outputString;
        
        }

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

        bool SimpleYesNoBox(const std::string& title, const std::string& message) {
            #ifdef _WIN32
                return MessageBoxA(NULL, message.c_str(), title.c_str(), MB_YESNO) == IDYES;
            #else
                // Need zenity to be installed

                // zenity --question  --text title
                //    if [[ $? = 0 ]]; then
                //    echo "y"
                //    else
                //    echo "n";
                //    fi

                std::string cmd = "zenity --question --text=\"" + message + "\"\n   if [[ $? = 0 ]]; then\n    echo \"y\"\n    else\n    echo \"n\"\n    fi";
                std::string output = getCmdOutput(cmd);
                return output.starts_with("y");
                
            #endif
        }

    } // gui

} // ara
