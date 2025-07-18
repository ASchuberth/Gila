#pragma once
#include "observer/subject.hpp"

class Edge {};

class Model : public gila::Subject {

public:
  Model();
  Model(int id);
  ~Model();

  void addPoint(glm::vec3 p);
  void notify() override;

  void clearRender();

private:
  int mId;
  gila::RenderData mRenderables;
};