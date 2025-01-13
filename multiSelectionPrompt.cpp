#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::pair;

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
}

int main (){

    cout << "\033[2J\033[3J\033[H";

    vector<pair<string, bool>> food {{"Pizza", false} , {"Burger", false}, {"Pasta",false}, {"Chicken", false}, {"Meat", false}};
	
    string styleStart = "\033[31m";
    string styleEnd = "\033[0m";
	string styleSelection = "\033[32m";
    int selectedIndex = 0;

    setRawMode(true);
    std::cout << "\0337"; // save position of the cursor
    
    do {
        cout << "Which food do to have in your meal?" << endl;
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
    cout << "\033[33m \n \n You choose ";
    for (size_t i = 0; i < foodSelected.size(); i++){
		cout << foodSelected[i];
		if ( i != foodSelected.size() - 1)
			cout << ", ";
			
	}
	cout << styleEnd << endl << endl;
		
    return 0;
}
