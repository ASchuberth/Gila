#pragma once

#include "observer.hpp"

namespace GILA_APP_NAMESPACE {


class Subject {

public:

  void addRender(Observer* observer);
  void removeRender(Observer* observer);
  virtual void notify();

protected:
  
std::vector<Observer*> observers;



private:

  


};
}