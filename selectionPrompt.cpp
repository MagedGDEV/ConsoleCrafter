#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <vector>
using namespace std;



void setRawMode(bool enable) {
    static struct termios oldt, newt;

    if (enable) {
        tcgetattr(STDIN_FILENO, &oldt); // Get current terminal attributes
        newt = oldt;                    // Copy them to modify
        newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply changes immediately
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore original attributes
    }
    
}


char getCommand(){

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
}

int main (){

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
