// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la
// clase BigIntBaseNotImplemented 
//
// COMPILACIÓN: make

#include <bits/stdc++.h>

#ifndef BIG_INT_BASE_NOT_IMPLEMENTED_H
#define BIG_INT_BASE_NOT_IMPLEMENTED_H

class BigIntBaseNotImplemented : public BigIntException {
 public:
  BigIntBaseNotImplemented() : BigIntException(),
                      msg_("msg"),
                      file_("file"),
                      function_("function"),
                      line_(9) {}
  BigIntBaseNotImplemented(const char* msg, const char* file, int line, const char* function) : BigIntException(),
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

void BaseNotImplemented(size_t& base, int line) {
  try {
    if (base != 2 && base != 8 && base != 10 && base != 16) {
      throw BigIntBaseNotImplemented("Exception thrown by BigIntBaseNotImplemented: Base not allowed as it is not implemented", "big_int_base_not_implemented.h", line, "BigIntBaseNotImplemented");
    }
  }
  catch (BigIntBaseNotImplemented& e) {
     std::cerr << e.what() << std::endl;
    std::cerr << "File: " << e.file() << std::endl;
    std::cerr << "Function: " << e.function() << std::endl;
    std::cerr << "Line: " << e.line() << std::endl;
    std::cerr << "Message: " << e.msg() << std::endl;
    
    exit(EXIT_FAILURE);
  }
}
#endif