#include "Coder.h"
#include<iostream>
using namespace std;
Coder::Coder()
{
	// all variables are set to null in the base constructor so no need to redefine it in 2 constructors i.e coder and decoder constructor
	error_count = 0; //variable to check if ANY error has been detected
	i = 0; //counter which loops through all the elements in the codeword
	finish = 0;
	sum = 0; //sums up the error bits positions
	confirm_error = 0; //variable to check if ANY error has been detected
	sum_error_bits = 0; //these will be summed to produce a single digit which will tell where the error is
	k = 0;
}
Coder::~Coder() {}