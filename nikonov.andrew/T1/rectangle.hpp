#ifndef RECTANGE_HPP
#define RECTANGE_HPP
#include "base-types.hpp"
#include "shape.hpp"
#include "triangle.hpp"
namespace nikonov
{
  class Rectangle final: public Shape
  {
  public:
    Rectangle(const Triangle &tgl_1, const Triangle &tgl_2, const Triangle &tgl_3, const Triangle &tgl_4);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &a) noexcept override;
    void move(double x, double y) noexcept override;
    void scale(double k) noexcept override;
  private:
    Triangle tgl_1_;
    Triangle tgl_2_;
    Triangle tgl_3_;
    Triangle tgl_4_;
  };
}
#endif
