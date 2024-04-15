// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la
// clase BigInt y todos sus metodos para que posteriormente sea
// posible operar con ellos
//
// COMPILACIÓN: make

#include "number.h"
#include "big_int_bad_digit.h"
#include "big_int_division_by_zero.h"
#include "big_int_base_not_implemented.h"

#ifndef BIG_INT_H
#define BIG_INT_H

template <const size_t Base>

class BigInt : public Number {

 public:
  BigInt() {}
  BigInt(const std::string&);
  BigInt(const char*);
  BigInt(const std::vector<char>, int);
  BigInt(const BigInt<Base>&); // Constructor de copia

  std::vector<char> getDigits() const { return digits_; }

  BigInt<Base>& operator=(const BigInt<Base>&);
  
  std::istream& read(std::istream& = std::cin);
  std::ostream& write(std::ostream& = std::cout) const;

  friend std::ostream& operator<<(std::ostream& out, const BigInt& big_int) {
    big_int.write(out);
    return out;
  }

  friend std::istream& operator>>(std::istream& in, BigInt& big_int) {
    big_int.read(in);
    return in;
  }
  
  int sign() const; // Signo: 1 o -1
  long DecimalValue() const;
  int SumOfVectorElements() const;
  std::vector<char> OriginalBaseValue(long) const;
  char operator[](int) const; // Acceso al i-ésimo dígito

  bool operator<=(const BigInt<Base>&) const;
  bool operator>=(const BigInt<Base> &) const;
  bool operator!=(const BigInt<Base>&) const;

  BigInt<Base> operator+(const BigInt<Base>&) const;
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator*(const BigInt<Base>&) const;
  BigInt<Base> pow(const BigInt<Base>&) const;
  BigInt<Base> operator/(const BigInt<Base>&) const;
  BigInt<Base> operator%(const BigInt<Base>&) const;

  Number* add(const Number* other_number) const override {
    return new BigInt<Base>(*this + (const BigInt<Base>) *other_number);
  }
  Number* subtract(const Number* other_number) const override {
    return new BigInt<Base>(*this - (const BigInt<Base>) *other_number);
  }
  Number* multiply(const Number* other_number) const override {
    return new BigInt<Base>(*this * (const BigInt<Base>) *other_number);
  }
  Number* divide(const Number* other_number) const override {
    return new BigInt<Base>(*this / (const BigInt<Base>) *other_number);
  }
  Number* module(const Number* other_number) const override {
    return new BigInt<Base>(*this % (const BigInt<Base>) *other_number);
  }
  Number* pow(const Number* other_number) const {
    return new BigInt<Base>(this->pow((const BigInt<Base>) *other_number));
  }

  static Number* create(size_t base, const std::string& s) {
    BaseNotImplemented(base, 86);
    switch(base) {
      case 2:
        return new BigInt<2> (s);
      case 8:
        return new BigInt<8> (s);
      case 10:
        return new BigInt<10> (s);
      case 16:
        return new BigInt<16> (s);
    }
    return new BigInt<10> (s);
  }

  friend bool operator==(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return !(big_int != other_big_int);
  }

  friend bool operator>(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return big_int.DecimalValue() > other_big_int.DecimalValue();
  }

  friend bool operator<(const BigInt<Base>& big_int, const BigInt<Base>& other_big_int) {
    return !(big_int > other_big_int);
  } 

  operator BigInt<2>() const override {
    long operand = DecimalValue();
    char aux;
    std::string result, c2_result;
    if (operand == 0) {
      result.push_back(0);
      return BigInt<2>(result);
    }
    while (operand > 0) {
      aux = (operand % 2) + '0';//char conversion
      result.push_back(aux);
      operand /= 2;
    }
    //result.push_back('0');
    reverse(result.begin(), result.end());
  
    // if (sign_ == -1) { //caso negativo
    //   for (auto digit : result) {
    //     if (digit == '0') {
    //       c2_result.push_back('1');
    //     } else if(digit == '1') {
    //       c2_result.push_back('0');
    //     }
    //   }
      //return BigInt<2>(c2_result) + BigInt<2>("01");
    //}
    return BigInt<2>(result);
  }

  operator BigInt<8>() const {
    long operand = DecimalValue();
    char aux;
    std::string result, c2_result;
    if (operand == 0) {
      result.push_back(0);
      return BigInt<8> (result);
    }
    while (operand > 0) {
      aux = (operand % 8) + '0';//char conversion
      result.push_back(aux);
      operand /= 8;
    }
    return BigInt<8>(std::to_string(operand));
  }

  operator BigInt<10>() const override {
    long operand = DecimalValue();
    return BigInt<10>(std::to_string(operand));
  }

  operator BigInt<16>() const override {
    long operand = DecimalValue();
    BigInt<10> decimal_int(std::to_string(operand));
    std::string result;
    std::vector<int> sum;
    long decimal_number = decimal_int.DecimalValue();
    while (decimal_number != 0) {
      int rem = 0;
      char each_character;
      rem = decimal_number % 16;
      if (rem < 10) {
        each_character = rem + 48;
      } else {
        each_character = rem + 55;
      } 
      result += each_character;
      decimal_number /= 16;
    }
    for (int i = 0, j = result.size() - 1; i <= j; ++i, --j) {
      std::swap(result[i], result[j]);
    }
    //std::cout << "result: " << result << std::endl;
    return BigInt<16>(result);
  }

 private:
  std::vector<char> digits_;
  int sign_;
};

template<size_t Base>
BigInt<Base>::BigInt(const std::string& input) {
  BadDigit(input, Base, 194);
  std::string big_integer = input;
  if (big_integer[0] == '-') {
    sign_ = -1;
    big_integer.erase(big_integer.begin());
  } else {
    sign_ = 1;
  }
  for (int i = 0; i < big_integer.size(); ++i) {
    if ((big_integer[i] - '0') < Base) {
      digits_.push_back(big_integer[i] - '0');
    } else if (big_integer[i] - 'A' + 10 < Base) {
      digits_.push_back(big_integer[i] - 'A' + 10);
    }
  } 
}

template<size_t Base>
BigInt<Base>::BigInt(const char* input) {
  std::string usable_input = input;
  BadDigit(usable_input, Base, 214);

  if (input[0] == '-') {
    sign_ = -1;
    usable_input.erase(usable_input.begin());
  } else {
    sign_ = 1;
  }
  for (int i = 0; i < usable_input.size(); ++i) {
    if ((usable_input[i] - '0') < Base) {
      digits_.push_back(usable_input[i] - '0');
    } else if (usable_input[i] - 'A' + 10 < Base) {
      digits_.push_back(usable_input[i] - 'A' + 10);
    } 
  } 
}

template<size_t Base>
BigInt<Base>::BigInt(const std::vector<char> input, int sign) {
  digits_ = input;
  sign_ = sign;
}

template<size_t Base>
BigInt<Base>::BigInt(const BigInt<Base>& other_big_int) {
  digits_ = other_big_int.digits_;
  sign_ = other_big_int.sign_;
}

template<size_t Base>
BigInt<Base> &BigInt<Base>::operator=(const BigInt<Base>& other_big_int) {
  digits_ = other_big_int.digits_;
  sign_ = other_big_int.sign_;
  return *this;
}

template<size_t Base>
std::ostream& BigInt<Base>::write(std::ostream& os) const {
  if (sign_ == -1) {
    os << "-";
  }
  for (int i = 0; i < digits_.size(); ++i) {
    if (digits_.at(i) < 10) {
      os << char(digits_.at(i) + '0');
    } else if (digits_.at(i) >= 10 && digits_.at(i) < 16) {
      os << char(digits_.at(i) + 'A' - 10);
    }
  }
  os << std::endl;
  return os;
}

template<size_t Base> 
std::istream& BigInt<Base>::read(std::istream& in) {
  std::string input;
  in >> input;
  int size = input.size();
  for (int i = size - 1; i >= 0; --i) {
    digits_.push_back(input[i] - '0');
  }
  return in;
}



template<size_t Base>
int BigInt<Base>::sign() const { // Signo: 1 o -1
  return sign_;
}  

template<size_t Base>
long BigInt<Base>::DecimalValue() const {

  long sum = 0;
  for (int i = 0; i < digits_.size(); ++i) {
    sum += (digits_.at(i) * std::pow(Base, (digits_.size() - 1) - i));
  }
  return sum;
}

template<size_t Base>
std::vector<char> BigInt<Base>::OriginalBaseValue(long input) const {

  std::vector<char> result;
  if (input < 0) {
    input *= -1;
  }
  if (input == 0) {
    result.push_back(0);
    return result;
  }
  while (input > 0) {
    result.push_back(input % Base);
    input /= Base;
  }
  reverse(result.begin(), result.end());
  return result;
}

template<size_t Base>
char BigInt<Base>::operator[](int i) const{ // Acceso al i-ésimo dígito
  return digits_.at(i);
}

template<size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base>& other_big_int) const {
  bool flag = false;
  if (digits_.size() == other_big_int.digits_.size() && sign_ == other_big_int.sign_) {
    for (int i = 0; i < digits_.size(); ++i) {
      if (digits_.at(i) != other_big_int.digits_.at(i)) {
        flag = true;
      }
    }
    return flag;
  } 
  return true;
}

template<size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> & other_big_int) const {

  if (*this > other_big_int || *this == other_big_int) {
    return true;
  }
  return false;
}

template<size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> & other_big_int) const {

  if (*this < other_big_int || *this == other_big_int) {
    return true;
  }
  return false;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator+(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if ((DecimalValue() * sign_) + (other_big_int.DecimalValue() * other_big_int.sign_) < 0) {
    result.sign_ = -1;
  } else {
    result.sign_ = 1;
  }
  result.digits_ = result.OriginalBaseValue(((DecimalValue() * sign_) + (other_big_int.DecimalValue() * other_big_int.sign_)));
  return result;
} 

template<size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if ((DecimalValue() * sign_) - (other_big_int.DecimalValue() * other_big_int.sign_) < 0) {
    result.sign_ = -1;
  } else {
    result.sign_ = 1;
  }
  result.digits_ = OriginalBaseValue(((DecimalValue() * sign_) - (other_big_int.DecimalValue() * other_big_int.sign_)));

  return result;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if (sign_ == -1 || other_big_int.sign_ == -1) {
    result.sign_ = -1;
  }
  result.digits_ = OriginalBaseValue(DecimalValue() * other_big_int.DecimalValue());
  return result;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::pow(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  int multiplicator = 1;
  if (sign_ == -1 ) {
    result.sign_ = -1;
  }
  for (int i = 0; i < other_big_int.DecimalValue(); ++i) {
    multiplicator *= DecimalValue();
  }
  result.digits_ = result.OriginalBaseValue(multiplicator);
  return result;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator/(const BigInt<Base>& other_big_int) const {
  DivisionByZero(other_big_int, 401);
  BigInt<Base> result;
  if (sign_ == -1 || other_big_int.sign_ == -1) {
    result.sign_ = -1;
  }
  result.digits_ = result.OriginalBaseValue(DecimalValue() / other_big_int.DecimalValue());
  return result;
}

template<size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base>& other_big_int) const {
  BigInt<Base> result;
  if (sign_ == -1 || other_big_int.sign_ == -1) {
    result.sign_ = -1;
  }
  result.digits_ = OriginalBaseValue(DecimalValue() % other_big_int.DecimalValue());
  return result;
}

#endif