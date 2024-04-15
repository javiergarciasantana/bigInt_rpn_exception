// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la
// clase BigIntBadDigit 
//
// COMPILACIÓN: make

#include "big_int_exception.h"

#ifndef BIG_INT_BAD_DIGIT_H
#define BIG_INT_BAD_DIGIT_H

class BigIntBadDigit : public BigIntException {
 public:
  BigIntBadDigit() : BigIntException(),
                      msg_("msg"),
                      file_("file"),
                      function_("function"),
                      line_(9) {}
  BigIntBadDigit(const char* msg, const char* file, int line, const char* function) : BigIntException(),
                                                                                   msg_(msg),
                                                                                   file_(file),
                                                                                   function_(function),
                                                                                   line_(line) {}
 
  const char* file() const {
    return file_;
  }
  int line() const {
    return line_;
  }
  const char* function() const {
    return function_;
  }
  const char* msg() const {
    return msg_;
  }

 private:
  const char* file_;
  int line_;
  const char* function_;
  const char* msg_;
};

void BadDigit(const std::string& input, int base, int line) {
  try {
    for (int i = 0; i < input.size(); ++i) {
      if ((input[i] - '0') >= base && base < 16) {
        //std::cout << char(input[i]) << std::endl;
        throw BigIntBadDigit("Exception thrown by BigIntBadDigit: Cannot represent number in specified base", "big_int_bad_digit.h", line, "BigIntBadDigit");
      } 
      if (base == 16) {
        if (input[i] < 'A' && (input[i] - '0') >= base) {
          throw BigIntBadDigit("Exception thrown by BigIntBadDigit: Cannot represent number in specified base", "big_int_bad_digit.h", line, "BigIntBadDigit");
        }
        if (input[i] >= 'A' && ((input[i] - 'A') + 10) >= base) {
          throw BigIntBadDigit("Exception thrown by BigIntBadDigit: Cannot represent number in specified base", "big_int_bad_digit.h", line, "BigIntBadDigit");
        }
      }
    }
  }
  catch (BigIntBadDigit& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "File: " << e.file() << std::endl;
    std::cerr << "Function: " << e.function() << std::endl;
    std::cerr << "Line: " << e.line() << std::endl;
    std::cerr << "Message: " << e.msg() << std::endl;
    
    exit(EXIT_FAILURE);
  }
} 


#endif