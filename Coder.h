#pragma once
#include<string>
using namespace std;
class Coder {
public:
	Coder(); // constructor 
	~Coder(); //destructor 
	virtual void setcode(string *code) {} //all of these funtions are common in both encoder and decoder class 
	virtual void check() {}
	virtual void detect() {}
	virtual void display_code() {}
protected: //these set of variables are used by both the classes hence no need to declare it in the derived classes 
	string binary_number; //stores the binary number 
	int error_count, i, length, finish, sum, confirm_error, sum_error_bits, k, start_pos, skip_times; //essential variables for encoding,decoding,error detection,checking
};