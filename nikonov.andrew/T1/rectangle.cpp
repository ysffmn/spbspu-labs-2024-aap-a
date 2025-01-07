#include "rectangle.hpp"
#include <algorithm>
#include "additional-utilities.hpp"
namespace
{
  double findExtremeCoord(nikonov::Triangle tgls[], size_t size, bool findX, bool findMin)
  {
    double extremeX = tgls[0].getFrameRect().pos.x - tgls[0].getFrameRect().width / 2;
    for (size_t i = 1; i < size; ++i)
    {
      double currX = tgls[i].getFrameRect().pos.x - tgls[i].getFrameRect().width / 2;
      if (findMin)
      {
        extremeX = std::min(extremeX, currX);
      }
      else
      {
        extremeX = std::max(extremeX, currX);
      }
    }
    return extremeX;
  }
  double findMinX(nikonov::Triangle tgls[], size_t size)
  {
    return findExtremeCoord(tgls, size, true, true);
  }
  double findMaxX(nikonov::Triangle tgls[], size_t size)
  {
    return findExtremeCoord(tgls, size, true, false);
  }
  double findMinY(nikonov::Triangle tgls[], size_t size)
  {
    return findExtremeCoord(tgls, size, false, true);
  }
  double findMaxY(nikonov::Triangle tgls[], size_t size)
  {
    return findExtremeCoord(tgls, size, false, false);
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
  double minY = findMinY(tgls, triangleNum);
  double minX = findMinX(tgls, triangleNum);
  double maxY = findMaxY(tgls, triangleNum);
  double maxX = findMaxX(tgls, triangleNum);
  double rectWidth = maxX - minX;
  double rectHeight = maxY - minY;
  double rectArea = rectWidth * rectHeight;
  double trianglesSumArea = tgl_1.getArea() + tgl_2.getArea() + tgl_3.getArea() + tgl_4.getArea();
  if (rectArea != trianglesSumArea)
  {
    throw std::logic_error("non-correct rectangle parameters");
  }
}
double nikonov::Rectangle::getArea() const noexcept
{
  return tgl_1_.getArea() + tgl_2_.getArea() + tgl_3_.getArea() + tgl_4_.getArea();
}
nikonov::rectangle_t nikonov::Rectangle::getFrameRect() const noexcept
{
  constexpr size_t triangleNum = 4;
  Triangle tgls[] = { tgl_1_, tgl_2_, tgl_3_, tgl_4_ };
  double minY = findMinY(tgls, triangleNum);
  double minX = findMinX(tgls, triangleNum);
  double maxY = findMaxY(tgls, triangleNum);
  double maxX = findMaxX(tgls, triangleNum);
  double rectWidth = maxX - minX;
  double rectHeight = maxY - minY;
  point_t pos = point_t({ minX + (rectWidth / 2), minY + (rectHeight / 2) });
  return rectangle_t({ rectWidth, rectHeight, pos });
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
  tgl_1_.move(x, y);
  tgl_2_.move(x, y);
  tgl_3_.move(x, y);
  tgl_4_.move(x, y);
}
void nikonov::Rectangle::scale(double k) noexcept
{
  rectangle_t crntRect = getFrameRect();
  ispScale(&tgl_1_, crntRect.pos.x, crntRect.pos.y, k);
  ispScale(&tgl_2_, crntRect.pos.x, crntRect.pos.y, k);
  ispScale(&tgl_3_, crntRect.pos.x, crntRect.pos.y, k);
  ispScale(&tgl_4_, crntRect.pos.x, crntRect.pos.y, k);
}
