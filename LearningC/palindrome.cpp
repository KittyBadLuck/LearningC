#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

template<typename Bidirectional>
bool isPalindrome(Bidirectional first, Bidirectional last) //check if something is a palindrome
{
	while (true) //infinite loop
	{
		last--; //advance last
		if (first == last) //assume >= undefined
			break; //break if both itr are on the same element
		if (*first != *last) //check if they are different
			return false;
		first++; //advance first
		if (first == last)
			break; //break if both itr are on the same element
	}

	return true;
}