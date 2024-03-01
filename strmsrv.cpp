#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

// To do - Complete this function
StreamService::StreamService() : cUser_(nullptr) 
{
    // Update as needed

}

// To do - Complete this function
StreamService::~StreamService() {
    // Clean up dynamically allocated memory
    for (auto& user : users_) {
    delete user;
    }
    for (auto& cont : content_) {
        delete cont;
    }
    
    // Delete the current user pointer if needed
    //delete cUser_;
}

// Complete - Do not alter
void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

// To do - Complete this function
void StreamService::userLogin(const std::string& uname)
{
  // throw runtime_error if another user is already logged in (i.e. 
  //                                      they should logout first)
  // throw invalid_argument if the username is not valid
  if (cUser_ != nullptr){
    // throw error because the other user hasnt logged out
    throw runtime_error("Current user has not logged out");
    return;
  } 
  for (auto it = users_.begin(); it != users_.end(); ++it){
    if ((*it)->uname == uname){
      cUser_ = *it;

      return;
    }
  }
  //  throw error because the username is not valid
  throw invalid_argument("Username is not valid");

}

// To do - Complete this function
void StreamService::userLogout()
{
  cUser_ = nullptr;
}

// To do - Complete this function
std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        // TO DO - modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        string mainString = content_[i] -> name();
        size_t found = mainString.find(partial);

        if(partial == "*" || found != std::string::npos){
            results.push_back(i);
        }        
    }      
    return results;
}

// Complete - Do not alter
std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

// To do - Complete this function
void StreamService::watch(CID_T contentID)
{
  // throw error if no current user
  throwIfNoCurrentUser();

  // throw error if content ID out of bounds
  if (isValidContentID(contentID) == 0){
    throw IdOutOfBoundsError("ID out of bounds");
  }

  // throw error if rating limit is above users rating limit
  if (cUser_->ratingLimit < content_[contentID]->rating()){
    throw RatingLimitError("Rating limit is above users rating limit");
  }  

  // update user
  cUser_->history.push_back(contentID);
  // update content
  //(content_[contentID]->getViewers()).push_back(cUser_->uname);
  content_[contentID]->addViewer(cUser_->uname);
}

// To do - Complete this function
void StreamService::reviewShow(CID_T contentID, int numStars)
{
  // throw UserNotLoggedInError if no User is currently logged in.
  throwIfNoCurrentUser();

  // throw ReviewRangeError if the contentID is not valid or the 
  //                     number of stars is out of the range 0-5
  if (isValidContentID(contentID) == 0 || numStars < 0 || numStars > 5){
    throw ReviewRangeError("Review range error");
  }

  //(content_[contentID]->numReviews_) += 1;
  //(content_[contentID]->totalStars_;) += numStars;
  content_[contentID]->review(numStars);
}

// To do - Complete this function
CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const {    
    vector<int> contentIds;  
    vector<string> userStrVec = content_[contentID]->getViewers();
    int match = 0;

    for (const auto& username : userStrVec) {
        User* userPtr = users_[getUserIndexByName(username)];
        for (auto watchedContentID : userPtr->history){
            if (watchedContentID != contentID && userPtr != cUser_){
                contentIds.push_back(watchedContentID);
                match = 1;
                //cout << "FOUND ONNNEEE " << id << contentID << cUser_-> << endl;
            }
        }
    }
    if (match == 0) {return -1;}

    std::vector<int> counts(content_.size(), 0);
    for (auto id : contentIds){
        counts[id]++;
    }

    int largestCount = 0;
    int mostFrequentContentID = -1; // Assuming -1 indicates no suggestion found
    for (size_t i = 0; i < counts.size(); ++i) { 
        if (counts[i] > largestCount) { 
            largestCount = counts[i];
            mostFrequentContentID = i; 
        }
    }

    for (size_t i = 0; i < (cUser_->history).size(); i++){
      if ((cUser_->history)[i] == mostFrequentContentID){return -1;}
    }


    return mostFrequentContentID;
}

// To do - Complete this function
void StreamService::displayContentInfo(CID_T contentID) const
{
    // Do not alter this
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object



}

// Complete - Do not alter
bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

// Complete - Do not alter
void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user is logged in");
    }
}

// Complete - Do not alter
int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    
    return -1;
}
