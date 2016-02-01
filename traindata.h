#ifndef TRAINDATA__H
#define TRAINDATA__H
#include <string>
#include <map>
#include "parseXML.h"

class TrainData {
public:
  static TrainData& getInstance();
  void displayData() const;

  bool getXmlBool(const std::string&) const;
  const std::string& getXmlStr(const std::string&) const;
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;

  float getRandInRange(int min, int max) const;
private:
  static TrainData* instance;
  ParseXML parser;
  const map<std::string, std::string> trainData;

  TrainData(const std::string& fn = "SampleData/trainingData.xml");
  TrainData(const TrainData&);
  TrainData& operator=(const TrainData&);
};
#endif
