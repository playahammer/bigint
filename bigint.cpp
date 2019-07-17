#include "bigint.hxx"


Bigint::Bigint(){
      this->numbers.push_back(0);
      this->sign = 0;
}

Bigint::Bigint(long long value){
      long long _value = value < 0 ? -value : value;
      this->sign = value > 0 ? 1 : (value == 0 ? 0 : -1);
      do{
            this->numbers.push_back(_value % Bigint::base);
            _value = _value / Bigint::base;
      }while(_value != 0);
}

Bigint::Bigint(int *values, size_t len){
      this->sign = *values > 0 ? 1 : (*values == 0 ? 0 : -1);
      for (size_t i = len - 1; i > 0; i++) this->numbers.push_back(static_cast<unsigned int>(values[i]));
}

Bigint::Bigint(std::vector<int> values){
      this->sign = *(values.begin()) > 0 ? 1 : (*(values.begin()) == 0 ? 0 : -1);
      std::vector<int>::reverse_iterator valuesIter;
      for (valuesIter = values.rbegin(); valuesIter != values.rend(); valuesIter++)
            this->numbers.push_back(static_cast<unsigned int>(*valuesIter));
}

Bigint Bigint::operator+(const Bigint & b)const{
      Bigint c = *this;
      c += b;
      return c;
}

Bigint& Bigint::operator+=(const Bigint & b){

      // 2 + (-3) or -2 + 3
      if (this->sign * b.sign == -1 && ! this->fromSub){
            fromSub = true;
            return *this -= b;
      }

      // -2 + (-3) = -(2 + 3)
      //if (this->sign == -1 && b.sign == -1) this->sign = -1;

      if (this->sign == 1 || b.sign == 1) this->sign = 1;
      std::vector<unsigned int>::iterator iIter = this->numbers.begin();
      std::vector<unsigned int>::const_iterator bIter= b.numbers.cbegin();

      unsigned long sum = 0;
      while (iIter != this->numbers.end() || bIter != b.numbers.cend()){
            if (iIter != this->numbers.end()){
                  sum += *iIter;
            }else{
                  this->numbers.push_back(0);
                  iIter = this->numbers.end() - 1;
            }

            if (bIter != b.numbers.cend()){
                  sum += *bIter;
                  bIter++;
            }

            *iIter = sum % Bigint::base;
            iIter++;
            sum /= Bigint::base;
            
      }
      if (sum){
            numbers.push_back(1);
      }

      fromSub = false;

      
      if (this->numbers.size() > 0){
            do {
                  iIter = this->numbers.end() - 1;
                  if (*iIter == 0) this->numbers.pop_back();
                  else break;
            }while(this->numbers.size() > 0);
      }
      
      // 0 + 0
      if (this->numbers.size() == 0){
            this->numbers.push_back(0); 
            this->sign = 0;
      }
      
      return *this;
}


Bigint Bigint::operator-(const Bigint & b) const{
      Bigint c = *this;
      c -= b;
      return c;
}

Bigint& Bigint::operator-=(const Bigint & b) {
      return *this;
}

std::vector<unsigned int> Bigint::getNumbers(){
      return this->numbers;
}

/**
 *  tostring as dec
 *  @return 
 */ 

std::string Bigint::toString(){
      return toString(Bigint::DEC);
}

/**
 *  output vectors as string
 * @params radix
 * @return std::string
 **/ 
std::string Bigint::toString(int radix){
      std::string str;
      if(this->sign < 0) str.append("-"); else if(this->sign > 0) str.append("+");
      std::vector<unsigned int>::reverse_iterator numbersIter = this->numbers.rbegin();
      const std::string hex[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
      std::string bits;
      int bitLen;
      switch (radix)
      {
      case Bigint::BIN:
            bitLen = 32;
            break;
      
      default:
            bitLen = 8;
            break;
      }

      for(; numbersIter != this->numbers.rend(); numbersIter++){
            unsigned int value = *numbersIter;
            std::string temp;
            for (int i = 0; i < bitLen; i++)
            {
                  int bit = value % radix;
                  value /= radix;
                  temp.append(hex[bit]);
            }
            std::reverse(temp.begin(), temp.end());
            bits.append(temp);
      }
      while (bits.at(0) == '0'){
            bits = bits.substr(1);
      }
      
      str.append(bits);
      return str;
}