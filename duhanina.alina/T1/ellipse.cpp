#include "ellipse.hpp"
#include <stdexcept>

duhanina::Ellipse::Ellipse(point_t center, double horizRadius, double vertRadius):
  center_(center),
  horizRadius_(horizRadius),
  vertRadius_(vertRadius)
{
  if (vertRadius <= 0 || horizRadius <= 0)
  {
    throw std::invalid_argument("Error in parameters");
  }
}

double duhanina::Ellipse::getArea() const
{
  constexpr double pi = 3.1415;
  return pi * horizRadius_ * vertRadius_;
}

duhanina::rectangle_t duhanina::Ellipse::getFrameRect() const
{
  return { center_, 2 * horizRadius_, 2 * vertRadius_ };
}

void duhanina::Ellipse::move(const point_t& newPos)
{
  center_ = newPos;
}

void duhanina::Ellipse::move(double dx, double dy)
{
  center_.x += dx;
  center_.y += dy;
}

void duhanina::Ellipse::scale(double k)
{
  horizRadius_ *= k;
  vertRadius_ *= k;
}
