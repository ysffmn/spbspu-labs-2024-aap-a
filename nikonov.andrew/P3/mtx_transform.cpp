#include "mtx_transform.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
bool inputCheck(int argc, char** argv)
{
  if (argc < 4)
  {
    std::cerr << "Not enough arguments\n";
    return 0;
  }
  else if (argc > 4)
  {
    std::cerr << "Too many arguments\n";
    return 0;
  }
  if (strlen(argv[1]) != 1)
  {
    std::cerr << "First parameter is not a number\n";
    return 0;
  }
  else if (!atoi(argv[1]))
  {
    std::cerr << "First pararmetr is not a number\n";
  }
  return 1;
}
std::istream& readMatrix(std::istream& input, int* mtx, size_t m, size_t n, size_t& read)
{
  for (size_t i = 0; i < m * n; ++i)
  {
    if (!(input >> mtx[i]))
    {
      return input;
    }
    else
    {
      ++read;
    }
  }
  return input;
}
void printMatrix(std::ostream& output, int* mtx, size_t m, size_t n)
{
  if (m > 0 && n > 0)
  {
    output << m << " " << n << " " << mtx[0];
  }
  else
  {
    output << m << " " << n;
  }
  for (size_t i = 1; i < m * n; ++i)
  {
    output << " " << mtx[i];
  }
}
void transformMatrix(int* mtx, size_t m, size_t n, size_t decreaser, size_t vertMove)
{
  size_t currentIndex = m * n - n;
  while (m > 0 && n > 0)
  {
    for (size_t moveUp = 0; moveUp < m - 1; ++moveUp)
    {
      mtx[currentIndex] -= decreaser;
      ++decreaser;
      currentIndex -= vertMove;
    }
    for (size_t moveRight = 0; moveRight < n - 1; ++moveRight)
    {
      mtx[currentIndex] -= decreaser;
      ++decreaser;
      currentIndex += 1;
    }
    for (size_t moveDown = 0; moveDown < m - 1; ++moveDown)
    {
      mtx[currentIndex] -= decreaser;
      ++decreaser;
      currentIndex += vertMove;
    }
    for (size_t moveLeft = 0; moveLeft < n - 1; ++moveLeft)
    {
      mtx[currentIndex] -= decreaser;
      ++decreaser;
      currentIndex -= 1;
    }
    currentIndex -= (vertMove - 1);
    --m;
    --n;
  }
}