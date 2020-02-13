/*
 Code by Drake Johnson
*/
#include "output/clear_screen.hpp"
#include "output/print.hpp"
#ifdef _WIN32
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif // !WIN32_LEAN_AND_MEAN
#   include <windows.h>
namespace cons
{
    void clear_screen()
    {
        constexpr int FAIL = 0;
        HANDLE std_out_h = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO cons_data;
        DWORD bytes_written;
        DWORD cons_area;
        COORD home_pos{ 0, 0 };

        try
        {
            if (std_out_h == INVALID_HANDLE_VALUE)
            { // Output handle invalid
                throw ClearScreenException();
            }

            if (GetConsoleScreenBufferInfo(std_out_h, &cons_data) == FAIL)
            { // Could not get current console buffer info
                throw ClearScreenException();
            }

            // Store area of screen
            cons_area = cons_data.dwSize.X * cons_data.dwSize.Y;

            if (FillConsoleOutputCharacter(std_out_h, static_cast<TCHAR>(' '), cons_area, home_pos, &bytes_written) == FAIL)
            { // Could not fill console buffer with spaces
                throw ClearScreenException();
            }

            if (FillConsoleOutputAttribute(std_out_h, cons_data.wAttributes, cons_area, home_pos, &bytes_written) == FAIL)
            { // Could not set current console buffer with previous attributes
                throw ClearScreenException();
            }
        }
        catch (const ClearScreenException & e)
        {
            print(e.what());
            return;
        }

        // Set cursor position to home coords
        SetConsoleCursorPosition(std_out_h, home_pos);
    }
#else // Assuming Unix
    inline void clear_screen() { system("tput clear"); }
#endif // _WIN32
} // namespace cons