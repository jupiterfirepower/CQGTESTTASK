#ifndef NATURAL_COMPARE_H
#define NATURAL_COMPARE_H

#include <cmath>
#include <locale>

typedef unsigned int uint;

using namespace std;

bool IsStringANumber(string);
inline const char space = ' ';

int natural_compare(string first, string second)
{
	size_t firstLength = first.length();
	size_t secondLength = second.length();
	size_t count = 0;
	uint firstSpaces = 0, secondSpaces = 0;
	//////////////////////////////////////////////////////////////////////////////
	//  testing for testing null strings
	if (firstLength == 0 && secondLength != 0)
		return -1;
	if (secondLength == 0 && firstLength != 0)
		return 1;
	if (firstLength == 0 && secondLength == 0)
		return 0;
	/////////////////////////////////////////////////////////////////////////////////
	//  eating trialing whitespaces.  no data is modified just the size
	//  of the string to compare is changed.
	while(firstLength > 0 && first[firstLength - 1] == space)
	{
		firstSpaces++;
		firstLength--;
	}
	while(secondLength > 0 && second[secondLength - 1] == space)
	{
		secondSpaces++;
		secondLength--;
	}
	//////////////////////////////////////////////////////////////////////////////////
	//  testing of numbers.  all numbers come first so if one
	//  string is a number it will be less than the other string
	if (!IsStringANumber(first) && !IsStringANumber(second))
	{
		if (first[0] > second[0])
			return 1;
		if (first[0] < second[0])
			return -1;
	}
	if (IsStringANumber(first) && !IsStringANumber(second))
		return -1;
	if (!IsStringANumber(first) && IsStringANumber(second))
		return 1;
	////////////////////////////////////////////////////////////////////////////////////
	//  testing the length.  if the string is shorter and satisfies the other
	//  conditions than it is smaller
	if (firstLength > secondLength)
		return 1;
	if (firstLength < secondLength)
		return -1;
	/////////////////////////////////////////////////////////////////////////////////////
	//  this block checks equality over same length strings.
	while (count < firstLength)
	{
		if (first[count] == second[count])
		{
			count++;
			continue;
		}
		return first[count] > second[count] ? 1 : -1;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	//  is the strings are equal than the one with less trailing whitespace is smaller
	if (firstSpaces || secondSpaces)
	{
		return firstSpaces == secondSpaces ? 0 : firstSpaces > secondSpaces ? 1 : -1;
	}
	//////////////////////////////////////////////////////////////////////////////////////
	// if string are totaly equal return 0
	return 0;
}

bool IsStringANumber(string test)
{
	return !!atof(test.c_str());
}

#endif