#include "Coder.h"
#include "Encoder.h"
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
using namespace std;
void Encoder::setcode(string *code) //set the code 
{
	binary_number = *code;
	length = binary_number.size();
}
void Encoder::check() //check for invalid input
{
	while (i<length)
	{
		if ((binary_number[i] != '0' && binary_number[i] != '1') || (binary_number.size() % 4 != 0))
		{
			error_count++; //this variable decides if there is ANY sort of error in the code!!!;
			if (error_count == 1) // error_count will be equal to 1 if any error has been detected hence we have to enter our codeword again
			{
				cout << "not a binary number , enter again: ";
				cin >> binary_number; //new codeword 
				length = binary_number.size(); //change the length for the new codeword (so that it can loop accordingly)
				i = -1; //this is -1 so that when the loop runs again , it starts from 0 (this is done by i++ at the bottom)
				error_count = 0; //set it to 0 again for a new code
			}
		}
		i++; //keep incrementing i
	}
	i = 0;
}
void Encoder::encode()
{
	while (finish<length)
	{
		//find out if 'i' is a power of 2
		float x = log(i) / log(2);
		if (floor(x) == x && i>=1) //for detecting even powers
		{
			binary_number.insert(i-1, "_"); //keep allocating space (this is necessary for calculating the parity bits while encoding)
		}
		else
		{
			finish++; //this variable ensure that only the right number of spaces are inserted into our string 
		}
		i++; //keep incrementing the i counter till all the spaces are not allocated 
	}
	length = binary_number.size(); //assign new length
	for (int i = 0; i < length; i++)
	{
		if (binary_number[i] == '_') //this basically means if a bit that is a power of 2 has been detected or not
		{
			start_pos = i; //all the powers of 2 bits will be checked hence this variable defines from which bit will the calculation begin 
			skip_times = i + 1; // for bit 1 , we need to check and skip once , for bit 2 , check 2 skip2 , for bit 3 ,check 3 skip 3 
			for (int j = start_pos; j < length; j++)
			{
				for (k = j; k < skip_times + j; k++)
				{
					if (k<length)
					{
						if (binary_number[k] == '1')
						{
							sum++; //sums all the elements for each parity bit calculation
						}
					}
				}
				j = (k - 1) + skip_times;
			}
			if ((sum % 2) == 0)
			{
				binary_number.replace(i, 1, "0"); //if each parity bit sum is even the we have to replace it by 0
			}
			else if ((sum % 2) != 0)
			{
				binary_number.replace(i, 1, "1"); //if each parity bit sum is even the we have to replace it by 0
			}
			sum = 0; //must reset the sum value!!!
		}
	}
}
void Encoder::detect()
{
	for (int i = 0; i < length; i++)
	{
		if (binary_number[i] == '_') //for detecting even powers
		{
			start_pos = i; //initializing stating postions (essential for deciding from where to start looping for which parity bit)
			skip_times = i + 1;
			for (int j = start_pos; j < length; j++)
			{
				for (k = j; k < skip_times + j; k++)
				{
					if (k < length) //to prevent out of range array subscript
					{
						if (binary_number[k] == '1')
						{
							sum++; //keep summing if 1 is found (this is essential for finding which bit has the error)
						}
					}
				}
				j = (k - 1) + skip_times;
			}
			if (binary_number[start_pos] == '1')
			{
				sum = sum - 1; //must subtract 1 if the staring value was 1 while looping!!!
			}
			if ((sum % 2) == 0) //if sum of error bits is even
			{
				cout << "sum is: " << sum;
				if (binary_number[i] != '0')
				{
					cout << " , parity check bit 0 = " << binary_number[i] << " (error at bit: " << i + 1 << ")" << endl; //indicates TEMPORARY error bit
					sum_error_bits += (i + 1); //this variable will show where EXACTLY the error is!!
					confirm_error++; //this variable tells us that for sure an error has been found 
				}
				else if (binary_number[i] == '0')
				{
					cout << " , parity check bit 0 = " << binary_number[i] << " (no error)" << endl; // this tells that there is no error for the current bit
				}
			}
			else if ((sum % 2) != 0) //if sum of error bits is odd
			{
				cout << "sum is: " << sum;
				if (binary_number[i] != '1')
				{
					cout << " , parity check bit 1 = " << binary_number[i] << " (error at bit: " << i + 1 << ")" << endl; //indicates TEMPORARY error bit
					sum_error_bits += (i + 1); //this variable will show where EXACTLY the error is!!
					confirm_error++; //this variable tells us that for sure an error has been found 
				}
				else if (binary_number[i] == '1')
				{
					cout << " , parity check bit 1 = " << binary_number[i] << " (no error)" << endl;
				}
			}
			sum = 0; // resetting sum value to zero 
		}
	}
}
void Encoder::display_code()
{
	cout << "the encoded word is: " << binary_number << endl << endl;
}