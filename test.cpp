#include "bigint.hxx"

int main(int argv, char** argc){
      Bigint s(123123123123);
      Debug((s + Bigint(11)).toString(Bigint::HEX));
      Debug((s + Bigint(0)).toString(Bigint::HEX));
      return 0;
}