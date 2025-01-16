#include <iostream>
#include <string>
#include <vector>


#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else 
    #include <termios.h>
    #include <unistd.h>
#endif

using std::cout;
using std::endl;
using std::vector;
using std::string;

#ifdef _WIN32
    // Define ENABLE_VIRTUAL_TERMINAL_PROCESSING if not already defined
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif

    void enableANSI() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode)) return;
    }

#endif

void setRawMode(bool enable) {
    #ifdef _WIN32
        static DWORD oldM, newM;
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        if (enable){
            GetConsoleMode(hStdin, &oldM);
            newM = oldM & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT);
            if(!SetConsoleMode(hStdin, newM)){
                std::cerr << "Unable to set console mode" << std::endl;
            }
        } else {
            SetConsoleMode(hStdin, oldM);
        }   

    #else
        static struct termios oldt, newt;

        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt); // Get current terminal attributes
            newt = oldt;                    // Copy them to modify
            newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply changes immediately
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original attributes
        }
    #endif
}


char getCommand(){
    #ifdef _WIN32
        int key = _getch();
        if (key == 3) // Ctrl+C - Exit program
            exit(0);
        else if (key == 13) // Enter key
            return '\n'; 
        else if (key == 0 || key == 224) { // Arrow keys are a two-part code
            key = _getch(); // Get the second part
            switch (key) {
                case 72: return 'A';
                case 80: return 'B';
                default: return '\0';
            }
        }
        return '\0';
    #else
        char key = getchar(); // Read a single character

        if (key == '\n') { // Enter key
            return key;
        } else if (key == '\033') { // Escape sequence for arrow keys
            getchar(); // Skip the '['
            key = getchar();
            if (key != 'A' && key != 'B')
                key = '\0';
        }
        else{
            key = '\0';
        }
        return key;
    #endif
}

int main (){

    #ifdef _WIN32
        enableANSI();
    #endif
    cout << "\033[2J\033[3J\033[H";
    vector<string> food {"Pizza", "Burger", "Pasta", "Chicken", "Meat"};

    string styleStart = "\033[31m";
    string styleEnd = "\033[0m";

    int selectedIndex = 0;

    setRawMode(true);

    std::cout << "\0337"; 
    
    do {
        cout << "Which food do you prefer the most?" << endl;
        for (size_t i = 0; i < food.size(); i++){
            if (selectedIndex == i){
                cout << styleStart << " > " << food[i] << styleEnd << endl;
            }
            else {
                cout << "  " << food[i] << endl;
            }
        }
        cout << "\033[?25l\033[0m"; // hide cursor
        char key = getCommand();
        while (key == '\0')
            key = getCommand();

        if (key == '\n'){
            // delete the selections and the question
            // return the selected item/index in the vector
            std::cout << "\0338";
            cout << "\033[J";
            setRawMode(false);
            cout << "\033[?25h\033[0m"; // view cursor again
            break;
        }
        else if (key == 'A'){
            if (selectedIndex == 0)
                selectedIndex = food.size() - 1;
            else 
                selectedIndex--;
        }
        else if (key == 'B'){
            if (selectedIndex == food.size() - 1)
                selectedIndex = 0;
            else 
                selectedIndex++;
        }
        //cout << "\033[" << food.size() << "A"; // move the cursor up according to the size of the vector
        std::cout << "\0338";
        cout << "\033[J"; // clear everything from the current position till the end of the screen
    } while (true);
    
    cout << "\033[32m \n \n You choose " << food[selectedIndex] << styleEnd << endl << endl;
    return 0;
}
