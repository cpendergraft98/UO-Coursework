/*
  Implementation of methods for classes Response, AngryResponse, HappyResponse
*/
#include <iostream>
#include <string>
#include <algorithm>

#include "response.h"

using namespace std;

/*
  Implementation of Word class
  Don't worry too hard about these implementations.
  If you'd like to learn more about STL see:
    https://www.geeksforgeeks.org/the-c-standard-template-library-stl/
*/
string Word::upper()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::toupper);
  return result;
}

string Word::lower()
{
  string result(theWord);
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

/*
  Implementation of Response methods
*/
bool Response::checkAndRespond(const string& inWord, ostream& toWhere)
{
    // Initialize a return boolian value, default is false unless overwritten
    bool ret = false;

    // Check to make sure that the keyword appears somewhere in inWord
    if (inWord.find(keyword.upper()) != std::string::npos)
    {
      // If yes, we want to call our response function
      respond(toWhere);
      // And set our return value to true
      ret = true;
    }

    // Return the appropriate boolian value
    return ret;
}

// Implementation of the generic Response method
void Response::respond(ostream& toWhere)
{
    // Write the "I am neither angry nor happy" response and response word to
    // the output file
    toWhere << "I am neither angry nor happy: " << response << "\n";
}

// Implementation of the AngryResponse method
void AngryResponse::respond(ostream& toWhere)
{
  // Write the "I am angry" response and response word to the output file
  toWhere << "I am angry: " << response << "\n";
}


// Implementation of the HappyResponse method
void HappyResponse::respond(ostream& toWhere)
{
  // Write the "I am happy" response and response word to the output file
  toWhere << "I am happy: " << response << "\n";
}
