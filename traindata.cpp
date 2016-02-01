#include <sstream>
#include <limits>
#include "traindata.h"

TrainData& TrainData::getInstance() {
  static  TrainData instance  ;
  return instance;
}

TrainData::TrainData(const string& fn ) :
  parser(fn),
  trainData(parser.getXmlData())
{ }

float TrainData::getRandInRange(int min, int max) const {
  return min + (rand()/(std::numeric_limits<int>::max()+1.0f))*(max-min);
}

bool TrainData::getXmlBool(const string& tag) const {
  std::map<string, string>::const_iterator ptr = trainData.find(tag);
  if ( ptr == trainData.end() )
    throw string("Didn't find boolean tag ")+tag+string(" in xml");
  else {
    if ( ptr->second == "true" ) return true;
    else return false;
  }
}

int TrainData::getXmlInt(const string& tag) const {
  std::map<string, string>::const_iterator ptr = trainData.find(tag);
  if ( ptr == trainData.end() )
    throw string("Didn't find integer tag ")+tag+string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float TrainData::getXmlFloat(const string& tag) const {
  std::map<string, string>::const_iterator ptr = trainData.find(tag);
  if ( ptr == trainData.end() )
    throw string(" Didn't find float tag ")+tag+string(" in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    float data;
    strm >> data;
    return data;
  }
}

const string& TrainData::getXmlStr(const string& tag) const {
  std::map<string, string>::const_iterator ptr = trainData.find(tag);
  if ( ptr == trainData.end() )
    throw string("Didn't find string tag ")+tag+string(" in xml");
  else return ptr->second;
}

void TrainData::displayData() const {
  std::map<string, string>::const_iterator ptr = trainData.begin();
  while ( ptr != trainData.end() ) {
    std::cout << ptr->first << ", " << ptr->second << std::endl;
    ++ptr;
  }
}


