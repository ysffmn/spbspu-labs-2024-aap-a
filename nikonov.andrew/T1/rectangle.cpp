#include "rectangle.hpp"
#include <cmath>
#include <limits>
#include "additional-utilities.hpp"
namespace
{
  nikonov::point_t findLbp(double tgls[])
  {
    constexpr size_t triangleNum = 4;
    constexpr size_t rectangleEdgesNum = 4;
    double minY = std::numeric_limits<double>::min();
    double minX = std::numeric_limits<double>::min();
    double edgesCnt = 0.0;
    for (size_t i = 0; i < triangleNum; ++i)
    {
      for (size_t j = 1; j < triangleNum - i; ++j)
      {
        if (tgls[i].getFrameRect().height == tgls[j].getFrameRect().height ||
          tgls[i].getFrameRect().width == tgls[j].getFrameRect().width)
        {
          ++edgesCnt;
        }
      }
    }
    if (edgesCnt != rectangleEdgesNum)
    {
      throw std::logic_error("non-correct rectangle parameters");
    }
    double trianglesArea = tgl_1.getArea() + tgl_2.getArea() + tgl_3.getArea() + tgl_4.getArea();
    //если площадь тругольников будет сопадать с площадью ограничевающего прямоугольника, и количество граней будет равно четырем, то такие треугольники 
    //подходят для построения прямоугольника.
  }
}
nikonov::Rectangle::Rectangle(const Triangle &tgl_1, const Triangle &tgl_2, const Triangle &tgl_3, const Triangle &tgl_4):
  tgl_1_(tgl_1),
  tgl_2_(tgl_2),
  tgl_3_(tgl_3),
  tgl_4_(tgl_4)
{
  constexpr size_t triangleNum = 4;
    constexpr size_t rectangleEdgesNum = 4;
    nikonov::Triangle tgls[] = { tgl_1, tgl_2, tgl_3, tgl_4 };
    double minY = std::numeric_limits<double>::min();
    double minX = std::numeric_limits<double>::min();
    double edgesCnt = 0.0;
    for (size_t i = 0; i < triangleNum; ++i)
    {
      for (size_t j = 1; j < triangleNum - i; ++j)
      {
        if (tgls[i].getFrameRect().height == tgls[j].getFrameRect().height ||
          tgls[i].getFrameRect().width == tgls[j].getFrameRect().width)
        {
          ++edgesCnt;
        }
      }
    }
    if (edgesCnt != rectangleEdgesNum)
    {
      throw std::logic_error("non-correct rectangle parameters");
    }
    double trianglesArea = tgl_1.getArea() + tgl_2.getArea() + tgl_3.getArea() + tgl_4.getArea();
    //если площадь тругольников будет сопадать с площадью ограничевающего прямоугольника, и количество граней будет равно четырем, то такие треугольники 
    //подходят для построения прямоугольника.
}
double nikonov::Rectangle::getArea() const noexcept
{
  return tgl_1_.getArea() + tgl_2_.getArea() + tgl_3_.getArea() + tgl_4_.getArea();
}
nikonov::rectangle_t nikonov::Rectangle::getFrameRect() const noexcept
{
  double width = rtp_.x - lbp_.x;
  double height = rtp_.y - lbp_.y;
  point_t pos = point_t({ lbp_.x + (width / 2), lbp_.y + (height / 2) });
  return rectangle_t({ width, height, pos });
}
void nikonov::Rectangle::move(const point_t &newPos) noexcept
{
  rectangle_t crntRect = getFrameRect();
  double diffX = newPos.x - crntRect.pos.x;
  double diffY = newPos.y - crntRect.pos.y;
  move(diffX, diffY);
}
void nikonov::Rectangle::move(double x, double y) noexcept
{
  movePoint(lbp_, x, y);
  movePoint(rtp_, x, y);
}
void nikonov::Rectangle::scale(double k) noexcept
{
  rectangle_t crntRect = getFrameRect();
  scalePoint(lbp_, crntRect.pos, k);
  scalePoint(rtp_, crntRect.pos, k);
}
