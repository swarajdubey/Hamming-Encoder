#pragma once
#include "Coder.h"
class Decoder :protected Coder {
public:
	void setcode(string*); //for setting the code
	void check(); //for checking inva;id input
	void detect(); // error detection function
	void decode(); //for decoding an endecoded 
};