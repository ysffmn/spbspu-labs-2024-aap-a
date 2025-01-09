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
  struct RectangleData
  {
    double minX;
    double maxX;
    double minY;
    double maxY;
    double width;
    double height;
    nikonov::point_t midP;
    RectangleData(const nikonov::point_t &lbp, const nikonov::point_t &rtp):
      minX(std::min(lbp.x, rtp.x)),
      maxX(std::max(lbp.x, rtp.x)),
      minY(std::min(lbp.y, rtp.y)),
      maxY(std::max(lbp.y, rtp.y)),
      width(maxX - minX),
      height(maxY - minY),
      midP({ minX + width / 2, minY + height / 2 })
    {}
  };
  nikonov::Triangle findLeftTgl(const nikonov::point_t &lbp, const nikonov::point_t &rtp)
  {
    RectangleData data(lbp, rtp);
    nikonov::point_t topP({ data.minX, data.maxY });
    nikonov::point_t botP({ data.minX, data.minY });
    nikonov::point_t midP({ data.minX + data.width / 2, data.minY + data.height / 2 });
    return nikonov::Triangle({ topP, botP, midP });
  }
  nikonov::Triangle findRightTgl(const nikonov::point_t &lbp, const nikonov::point_t &rtp)
  {
    RectangleData data(lbp, rtp);
    nikonov::point_t topP({ data.maxX, data.maxY });
    nikonov::point_t botP({ data.maxX, data.minY });
    nikonov::point_t midP({ data.minX + data.width / 2, data.minY + data.height / 2 });
    return nikonov::Triangle({ topP, botP, midP });
  }
  nikonov::Triangle findTopTgl(const nikonov::point_t &lbp, const nikonov::point_t &rtp)
  {
    RectangleData data(lbp, rtp);
    nikonov::point_t topP1({ data.minX, data.maxY });
    nikonov::point_t topP2({ data.maxX, data.maxY });
    nikonov::point_t midP({ data.minX + data.width / 2, data.minY + data.height / 2 });
    return nikonov::Triangle({ topP1, topP2, midP });
  }
  nikonov::Triangle findBottomTgl(const nikonov::point_t &lbp, const nikonov::point_t &rtp)
  {
    RectangleData data(lbp, rtp);
    nikonov::point_t botP1({ data.minX, data.minY });
    nikonov::point_t botP2({ data.maxX, data.minY });
    nikonov::point_t midP({ data.minX + data.width / 2, data.minY + data.height / 2 });
    return nikonov::Triangle({ botP1, botP2, midP });
  }
}
nikonov::Rectangle::Rectangle(const point_t &lbp, const point_t &rtp):
  tgl_1_(findLeftTgl(lbp, rtp)),
  tgl_2_(findRightTgl(lbp, rtp)),
  tgl_3_(findTopTgl(lbp, rtp)),
  tgl_4_(findBottomTgl(lbp, rtp))
{
  if (lbp.x >= rtp.x || lbp.y >= rtp.y)
  {
    throw std::logic_error("ERROR:noncorrect rectangle parameters");
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
