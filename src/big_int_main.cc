// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero main en el que 
// se recoge la informacion del fichero de entrada
// y se le pasa a la clase rpn_base para que instancie
// elementos de tipo BigInt y opere con ellos
//
// COMPILACIÓN: make

#include "rpn_number.h"

int main (int argc, char* argv[]) {

  std::ifstream input;
  std::vector<std::string> lines;
  input.open(argv[1], std::ios_base::in);
  if (input.is_open()) {
    std::string line;
    while (getline(input, line)) {
      if (line.empty() == false) {
        lines.push_back(line);
      }
    }
  } else {
    std::cerr << "An error was produced opening the file" << std::endl;
    exit(EXIT_SUCCESS);
  }
  rpn_number calculator(lines);
  //BigInt<10> a("14");
  // std::string op1 = {"10"}, op2 = {"6"};
  // Number* num1 = BigInt<10>::create(2, op1);
  // Number* num2 = BigInt<10>::create(10, op2);
  // Number* result = num1->add(num2);
  // result->write(std::cout);

  return 0;
} 
