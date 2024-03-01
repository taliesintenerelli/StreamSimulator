// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

// To Do - Complete this function

std::string trim(const std::string& str) {
    if (str.empty()) {
        return str;
    }
    // Trim leading spaces
    size_t start = 0;
    while (start < str.length() && std::isspace(str[start])) {
        ++start;
    }
    // Trim trailing spaces
    size_t end = str.length();
    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }
    return str.substr(start, end - start);
}


void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    
          string firstLine;
      if (!getline(is, firstLine) || firstLine.empty()) {
          throw ParserError(error_msg_1); // If the line is empty or cannot be read
      }
      firstLine = trim(firstLine);

      // Check if the line consists of digits (integer)
      for (char c : firstLine) {
          if (!std::isdigit(c)) {
              throw ParserError(error_msg_1); // If the line contains non-digit characters
          }
      }
      int numContent = stoi(firstLine);
          
    // // Erase any old contents
    // content.clear();
    // users.clear();

    // // TO DO - Add your code below.

    // // get num of content
    // string firstLine;
    // getline(is, firstLine);
    // firstLine = trim(firstLine);

    // int numContent = stoi(firstLine);





    // get the content
    for (int i = 0; i < numContent; i++){
        int id = -1;
        int type = -1;
        string name = "";
        int numReviews = -1;
        int numStars = -1;
        int rating = -1;
        int numEpisodes;
        // ID and type
          if (!(is >> id)) {
            throw ParserError(error_msg_2); // Throw error if ID or id is missing or not an integer
          }
          is >> type;
        // get name
        getline(is, name);
        if (!(getline(is, name))) {
          throw ParserError(error_msg_2); // Throw error if ID or name is missing or not an integer
        }
        name = trim(name);
        // get reviews, stars, and rating
        int count = 0;
        while (count < 700){
          count++;
          if (!(is >> numReviews)) {
            throw ParserError(error_msg_2); // Throws error if numReviews is not a number
          }
          //is >> numReviews;
          if (numReviews != -1){
            break;
          }
        }
        while (count < 1400){
          count++;
          //is >> numStars;
          if (!(is >> numStars)) {
            throw ParserError(error_msg_2); // Throws error if numStars is not a number
          }
          if (numStars != -1){
            break;
          }
        }
        while (count < 2100){
          count++;
          if (!(is >> rating)) {
            throw ParserError(error_msg_2); // Throws error if rating read in or a number
          }
          //is >> rating;
          if (rating != -1){
            break;
          }
        }
        if (type == 1){
          while (count < 28000){
            count++;
            //is >> numEpisodes;
            if (!(is >> numEpisodes)) {
              throw ParserError(error_msg_2); // Throws error if numEpisodes not read in or not a number
            }
            if (numEpisodes != -1){
              break;
            }
          }
        }

      
        //create content variable, add all data members except usersWhoViewed
        Content* newc = NULL;
        if(type == 0){
          newc = new Movie(id, name, numReviews, numStars, rating);
        }
        else {
          newc = new Series(id, name, numReviews, numStars, rating, numEpisodes);
        }
        // get usersWhoViewed and add them to the current content variable
        string skipline;
        getline(is, skipline); 

        string linetwo;
        getline(is, linetwo); 
        istringstream lineStreamtwo(linetwo);

        string userName;
        while (lineStreamtwo >> userName){
          newc->addViewer(userName);
        }
        lineStreamtwo.clear();
        // add the current content variable to the content vector
        content.push_back(newc);
        //throw exception if neccesary
    }

    string uname;
    int limit;
    while (is >> uname){
        // Check if limit is a valid number
        if (!(is >> limit)) {
          throw ParserError(error_msg_3); // Throws error if limit is not a number
        }

        if (uname.empty()) {
          throw ParserError(error_msg_3); // Throw error if uname is empty or contains only whitespace characters
        }

        string line;
        getline(is, line);
        getline(is, line);
        istringstream lineStream(line);
        User* u = new User(uname, limit);
        int cid;
        while (lineStream >> cid){
          u->addToHistory(cid);
        }
        users.push_back(u);
    }

}

