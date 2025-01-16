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

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;

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
            SetConsoleMode(hStdin, newM);
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
        else if (key == 32) // Space key
            return ' ';
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

        if (key == '\n' || key == ' ') { // Enter key
            return key;
        } else if (key == '\033') { // Escape sequence for arrow keys
            getchar(); // Skip the '['
            key = getchar();
            if (key != 'A' && key != 'B')
                key = '\0';
        } else {
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

    vector<pair<string, bool>> food {{"Pizza", false} , {"Burger", false}, {"Pasta",false}, {"Chicken", false}, {"Meat", false}};
	
    string styleStart = "\033[31m";
    string styleEnd = "\033[0m";
	string styleSelection = "\033[32m";
    int selectedIndex = 0;

    setRawMode(true);
    std::cout << "\0337"; // save position of the cursor
    
    do {
        cout << "Which food do you like?" << endl;
        for (size_t i = 0; i < food.size(); i++){
			if (selectedIndex == i){
				cout << styleSelection << ((food[i].second) ? " -[x] " : " -[ ] ") << food[i].first << styleEnd << endl;
			}
            else if (food[i].second){
                cout << styleStart << "-[x] " << food[i].first << styleEnd << endl;
            }
            else {
                cout << "-[ ] " << food[i].first << endl;
            }
        }
        cout << "Press on " << styleStart << "<space>" << styleEnd << " to toggle the item, ";
        cout << styleStart << "<enter>" << styleEnd << " to finish" << endl;
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
        else if (key == ' '){
			food[selectedIndex].second = !food[selectedIndex].second;
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

        std::cout << "\0338";
        cout << "\033[J"; // clear everything from the current position till the end of the screen
    } while (true);
    
    
    vector<string> foodSelected;
	for (size_t i = 0; i < food.size(); i++)
		if (food[i].second)
			foodSelected.push_back(food[i].first);
    if (foodSelected.size() != 0){
        cout << "\033[33m \n \n You choose ";
        for (size_t i = 0; i < foodSelected.size(); i++){
            cout << foodSelected[i];
            if ( i != foodSelected.size() - 1)
                cout << ", ";
        }
        cout << styleEnd << endl << endl;
    }
    else
        cout << "\033[33m \n \n You didnot choose anything";
		
    return 0;
}
