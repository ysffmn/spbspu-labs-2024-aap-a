#include "tableMaker.hpp"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <iomanip>
#include "teilorFun.hpp"

void standartiseOut(double num)
{
  std::cout << std::fixed << std::setprecision(6) << std::setw(10) << num;
}

void tableOut(double num, size_t k, double error)
{
  try
  {
    double temp = 0;
    temp = maslovskiy::teilorCos(num, k, error);
    standartiseOut(num);
    std::cout << " ";
    standartiseOut(temp);
    std::cout << " ";
    standartiseOut(std::cos(num));
  }
  catch (const std::logic_error& e)
  {
    std::cerr << e.what() << '\n';
  }
}

void maslovskiy::tableMaker(double left, double right, double step, size_t k, double error)
{
  for (double i = left; i < right; i += step)
  {
    tableOut(i, k, error);
    std::cout << "\n";
  }
  tableOut(right, k, error);
}
