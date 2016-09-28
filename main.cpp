//the method to calculate hamming codes have been used from wikipedia and the following link: http://users.cis.fiu.edu/~downeyt/cop3402/hamming.html
//the codewords provided in the coursework sheet , seem to be INCORRECT as per wikipedia and the link attached above

//-----native C++ headers--------
#include<iostream>
#include<string>
#include<cstring>
#include<iomanip>

//-------Custom built headers------
#include "Coder.h"
#include "Decoder.h"
#include "Encoder.h"
using namespace std;

void menu() //menu for displaying the menu for every start and stop of program
{
	cout << "\nWelcome to the Encoding/Decoding program!" << endl;
	cout << "1.Encode\n2.Decode\n3.Quit\n";
	cout << "\nRULES:" << endl;
	cout << "\nyou MUST enter a binary number that is divisible by 4(ENCODING)" << endl;
	cout << "For DECODING you are allowed to enter any number of bits!\n" << endl;
}


int main()
{
	Coder c;
	string opt, code;
	menu(); //calls the menu
	cout << "press any option: ";
	cin >> opt; //take in option
	while (opt != "3")
	{
		while (opt != "1" && opt != "2" && opt != "3") //check for ANY sort of invalid option this is the reason 'opt' is of type string
		{
			menu(); //calls the menu function to make it easier to see options
			cout << "invalid, please enter again: ";
			cin >> opt;
		}
		if (opt == "1")
		{
			cout << "enter a binary number(make sure it is divisible by 4): ";
			cin >> code;
			Encoder enc; // object is instantiated here deriberately so that when the program repeats , the constructor runs and all values are set to NULL!!
			Coder *encptr = (Coder*)&enc;
			encptr->setcode(&code);
			encptr->check();
			enc.encode(); //not a virtual function hence calling it using dot operator 
			encptr->detect();
			encptr->display_code();
			cout << "press small 'y' to continue the coder , 'n' to quit: ";
			cin >> opt;
			while (opt != "y" && opt != "n")
			{
				cout << "invalid option , enter again: ";
				cin >> opt;
			}
			if (opt == "y")
			{
				menu();
				cout << "press any option: ";
				cin >> opt; //take in option
			}
			else if (opt == "n")
			{
				return 0; //stop the program
			}
		}
		else if (opt == "2")
		{
			cout << "enter an undecoded word: ";
			cin >> code; //takes in the chart type undecoded binary number
			Decoder dec;
			Coder *decptr = (Coder*)&dec;
			decptr->setcode(&code);
			decptr->check();
			decptr->detect();
			dec.decode(); //not a virtual function hence calling it using dot operator 
			cout << "press small 'y' to continue the hamming encoding/decoding , 'n' to quit: ";
			cin >> opt;
			while (opt != "y" && opt != "n")
			{
				cout << "invalid option , enter again: ";
				cin >> opt;
			}
			if (opt == "y")
			{
				menu();
				cout << "press any option: ";
				cin >> opt; //take in option
			}
			else if (opt == "n")
			{
				return 0;
			}
		}
		else if (opt == "3")
		{
			return 0;
		}
	}
	system("PAUSE");
}
