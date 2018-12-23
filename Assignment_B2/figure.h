#ifndef FIGURE_H
#define FIGURE_H
#include "shape.h"

class Figure
{
private:
  Shape **shapes = nullptr;
  int amountOfShapes = 0;

public:
  ~Figure();
  std::string GetBoundingBox() const;
  void AddShape(Shape *s);
  void RecursiveBubbleSort(Shape &loc, int iterations, int currentIndex);
  int GetAmountOfShapes() const;
  double DistanceToShape(const Shape &s1, const Shape &s2);
  Shape **GetClosest(Shape *location, int n);
};
#endif
