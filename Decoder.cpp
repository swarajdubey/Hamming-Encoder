#include "Coder.h"
#include "Decoder.h"
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
using namespace std;
void Decoder::setcode(string *code) //setting the code 
{
	binary_number = *code;
	length = binary_number.size();
}
void Decoder::check()
{
	while (i < length)
	{
		if ((binary_number[i] != '0' && binary_number[i] != '1'))
		{
			error_count++;
			if (error_count >= 1)
			{
				cout << "cannot decode this binary number , enter again: ";
				cin >> binary_number; //new codeword 
				length = binary_number.size(); //change the length for the new codeword (so that it can loop accordingly)
				i = -1; //this is -1 so that when the loop runs again , it starts from 0 (this is done by i++ at the bottom)
				error_count = 0; //set it to 0 again for a new code
			}
		}
		i++;
	}
}
void Decoder::detect()
{
	for (int i = 0; i < length; i++)
	{
		float x = log(i) / log(2);
		if (floor(x) == x && i >= 1)
		{
			start_pos = i-1;
			skip_times = i;
			for (int j = start_pos; j < length; j++)
			{
				for (k = j; k < skip_times + j; k++)
				{
					if (k < length)
					{
						if (binary_number[k] == '1')
						{
							sum++;
						}
					}
				}
				j = (k - 1) + skip_times;
			}
			if (binary_number[start_pos] == '1')
			{
				sum = sum - 1;
			}
			if ((sum % 2) == 0)
			{
				if (binary_number[i-1] != '0')
				{
					sum_error_bits += (i + 1-1);
					confirm_error++;
				}
			}
			else if ((sum % 2) != 0)
			{
				if (binary_number[i-1] != '1')
				{
					sum_error_bits += i;
					confirm_error++;
				}
			}
			sum = 0;
		}
	}
	if (confirm_error >= 1) //this means there is atleast one error
	{
		if (sum_error_bits <= length)
		{
			cout << "error is at bit: " << sum_error_bits << endl << "after fixing the code... : " << endl;
			if (binary_number[sum_error_bits - 1] == '0')
			{
				binary_number.replace(sum_error_bits - 1, 1, "1"); // insert at error position if the bit is 0 then put 1
			}
			else if (binary_number[sum_error_bits - 1] == '1')
			{
				binary_number.replace(sum_error_bits - 1, 1, "0"); // insert at error position if the bit is 1 then put 0
			}
			cout << "code word is: " << binary_number << endl;
		}
		else
		{
			cout << "error bit: " << sum_error_bits << " is out of range, so cannot decode" << endl; //displayes if error bit position is out of range 
		}
	}
	else
	{
		cout << "\No errors found\n" << endl;
		cout << "code word is: " << binary_number << endl;
	}
}
void Decoder::decode()
{
	if (sum_error_bits <= length) // this prevents any OUT OR RANGE error bit , hence cannot output the decoded word
	{
		length = binary_number.size();
		cout << "decoded word is: ";
		for (int i = 0; i <= length; i++)
		{
			float x = log(i) / log(2);
			if (floor(x) == x && i>=1) {}
			else //we do not want powers of 2 
			{
				if (i-1 != -1) {
					cout << binary_number[i-1]; //displays the decoded word
				}
			}
		}
		cout << endl;
	}

}