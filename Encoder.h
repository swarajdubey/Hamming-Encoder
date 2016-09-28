#pragma once
#include "Coder.h"
class Encoder :protected Coder {
public:
	void setcode(string*); //sets the code
	void check(); //check for invalid input
	void encode(); //encodes the binary number using the hamming encoder
	void detect(); //detects errors
	void display_code(); //outputs the encoded word
};