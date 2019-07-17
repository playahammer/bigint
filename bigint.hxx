#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <vector>
#include <algorithm>

#define Debug(s) std::cout<<s<<std::endl;

class Bigint{

public:
      Bigint();
      Bigint(long long);
      Bigint(int*, size_t);
      Bigint(std::vector<int>);

      std::string toString();
      std::string toString(int radix);

      std::vector<unsigned int> getNumbers();

      //ops
      //Add
      Bigint operator+(Bigint const &) const;
      Bigint& operator+=(Bigint const &);

      //Sub
      Bigint operator-(Bigint const &)const;
      Bigint& operator-=(Bigint const &);
      const static int BIN = 2;
      const static int OCT = 8;
      const static int DEC = 10;
      const static int HEX = 16;
protected:


private:
      std::vector<unsigned int> numbers;
      int sign; // -1 is nagetive, 1 is positive, 0 is zero.
      const static unsigned long long base = 0x100000000; 

      bool fromSub = false;
      bool fromAdd = false;

      int compare(Bigint const &, Bigint const &) const;
};
#endif