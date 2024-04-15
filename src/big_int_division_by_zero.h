// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la
// clase BigIntDivisionByZero 
//
// COMPILACIÓN: make

#ifndef BIG_INT_DIVISION_BY_ZERO_H
#define BIG_INT_DIVISION_BY_ZERO_H

class BigIntDivisionByZero : public BigIntException {
 public:
  BigIntDivisionByZero() : BigIntException(),
                      msg_("msg"),
                      file_("file"),
                      function_("function"),
                      line_(9) {}
  BigIntDivisionByZero(const char* msg, const char* file, int line, const char* function) : BigIntException(),
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

template<size_t Base>
void DivisionByZero(const BigInt<Base>& big_int, int line) {
  long sum = 0;
  try {
    for (auto digit : big_int.getDigits()) {
      sum += digit;
    }
    if (sum == 0) {
      throw BigIntDivisionByZero("Exception thrown by BigIntDivisionByZero: Division by zero not allowed", "big_int_division_by_zero.h", line, "BigIntDivisionByZero");
    }
  }
  catch (BigIntDivisionByZero& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "File: " << e.file() << std::endl;
    std::cerr << "Function: " << e.function() << std::endl;
    std::cerr << "Line: " << e.line() << std::endl;
    std::cerr << "Message: " << e.msg() << std::endl;
    
    exit(EXIT_FAILURE);
  }
}
#endif