//============================================================================
// Name        : Copy-Swap-Idiom.cpp
// Author      : Youssef
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <cstddef>
#include <new>
#include <cassert>
#include <sstream>
using namespace std;

template<typename T>
  class Array
  {

  public:

    Array () :
	size (0), arr (nullptr)
    {

    }
    explicit
    Array (size_t size, T initVal = 0) :
	size (size), arr (new T[size])
    {
      std::fill_n (arr, size, initVal);
    }

    Array (const Array &other) : Array(other.size)
    {
	    std::copy(other.arr , other.arr + size , arr);
    }

    Array (Array &&other) noexcept :
	Array () // delegate initialization to default constructor to leave other obj in valid state after swap
    {
      swap(*this,other);
    }
    /*
     * pass by value to delegate memory handling to compiler(copy constructor , Destructor)
     * and make it exception save so we will not enter this function if creation of memory failed
     * */
    Array&
    operator = (Array lhs) noexcept
    {
      swap (*this, lhs);

      return *this;
    }
    Array&
    operator = (Array &&lhs) noexcept
    {
      swap (*this, lhs);

      return *this;
    }
    ~Array ()
    {

      if (arr)
	delete[] arr;

      arr = nullptr;
    }

    /*
     * Friend to make it general swap and find it throw ADL
     *
     *
     * */
    friend void
    swap (Array<T> &first, Array<T> &second) noexcept
    {
      std::cout << "MySwap Call\n"; // for debugging purpose to make sure that our swap get called not std::swap
      using std::swap;
      // not required in our example
      swap (first.arr, second.arr);
      swap (first.size, second.size);

    }

    string
    ToStr ()
    {
      std::ostringstream oss;
      for (size_t i = 0; i < size; ++i)
	{
	  oss << arr[i];
	  if (i != size - 1)
	    oss << ",";
	}
      return oss.str ();
    }
  private:
    size_t size;
    T *arr;

  };

int
main ()
{
  Array<int> x (5, 3);
  Array<int> y (10, 10);
  using std::swap;
  // to make sure that our swap overload std::swap
  swap (x, y); // overload std::swap to our friend swap that swap pointers and exception safe
  cout << x.ToStr () << endl;
  cout << y.ToStr () << endl;
}

