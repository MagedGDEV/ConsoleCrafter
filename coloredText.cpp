#include <iostream>
using std::cout;
using std::endl;

int main (){
	
	
	// Fixed colors
	// Black, red, green, yellow, blue, magenta, cyan, white, default, reset
	// (30 - 39) -> foreground colors, (40 - 49) -> background colors
	cout << endl << "Fixed Colors" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\033[31m Hello world \033[0m" << endl;
	cout << "\033[41m Hello world \033[0m" << endl;
	
	// Bright Fixed colors
	// Black, red, green, yellow, blue, magenta, cyan, white, default, reset
	// (90 - 97) -> foreground colors, (100 - 107) -> background colors
	cout << endl << "Bright Fixed Colors" << endl;
	cout << "--------------------------------------------------" << endl;
	cout << "\033[91m Hello world \033[0m" << endl;
	cout << "\033[101m Hello world \033[0m" << endl << endl;
	
	// 256 colors
	// 38 -> foreground colors, 48 background colors
	cout << endl << "256 COLORS" << endl;
	cout << "--------------------------------------------------" << endl;
	int color = 130;
	cout << "\033[38;5;" << color << "m" << " Hello world \033[0m" << endl;
	cout << "\033[48;5;" << color << "m" << " Hello world \033[0m" << endl << endl;
	
	// RGB colors
	// 38 -> foreground colors, 48 background colors
	cout << endl << "RGB COLORS" << endl;
	cout << "--------------------------------------------------" << endl;
	int r = 0, g = 255, b = 255;
	cout << "\033[38;2;" << r << ";" << g << ";" << b << "m" << " Hello World \033[0m" << endl;
	cout << "\033[48;2;" << r << ";" << g << ";" << b << "m" << "\033[38;2;255;255;255m" << " Hello World \033[0m" << endl;
	
	return 0;
}
