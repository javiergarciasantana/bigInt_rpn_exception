// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la clase Rpn_base,
// la cual crea objetos de tipo big int para operar con ellos mediante
// una calculadora RPN
//
// COMPILACIÓN: make

#include "big_int.h"

#ifndef RPN_NUMBER_H
#define RPN_NUMBER_H

class rpn_number {
 public:
 rpn_number(std::vector<std::string>&);
 void Operate(std::string& line, int identifier);

 private:
  std::vector<Number*> integers_;//aqui almacenamos los integers que se definen en el fichero de texto
  std::vector<Number*> results_;
  std::stack<Number*> stack_;//aqui metemos los inte operandos para trabajar con ellos
};

rpn_number::rpn_number(std::vector<std::string>& input) {
  int counter = 0, last_pos;
  for (int i = 0; i < input.size(); ++i) {
    if (input[i][0] == 'N') {
      std::string base;
      input[i].erase(input[i].begin(), input[i].begin() + 5);
      for (int j = 0; input[i][j] != ','; ++j) {
        base += input[i][j];
        last_pos = j;
      }
      input[i].erase(input[i].begin(), input[i].begin() + (last_pos + 3));
      Number* aux = BigInt<10>::create(stoi(base), input[i]);
      integers_.push_back(aux);
    } else if (input[i][0] == 'E') {
      ++counter;
      input[i].erase(input[i].begin(), input[i].begin() + 5);
      std::cout << input[i] << std::endl;
      Operate(input[i], counter);
    }
  }
}

void rpn_number::Operate(std::string& line, int identifier) {
  const std::string kOperators = {"+-^*/%"};
  bool flag = false;
  for(int i = 0; i < line.size(); ++i) {
    for (int j = 0; j < kOperators.size(); ++j) {
      if (line[i] == kOperators[j]) {
        assert(!stack_.empty());                 
        Number* op2 = stack_.top();
        stack_.pop();
        Number* op1 = stack_.top();
        stack_.pop();    
        Number* result;
        switch(line[i]) {
          case '+':
            result = op1->add(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          case '-':
            result = op1->subtract(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          case '*':
            result = op1->multiply(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          case '^':
            result = op1->pow(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          case '/':
            result = op1->divide(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          case '%':
            result = op1->module(op2);
            stack_.push(result);
            results_.push_back(result);
            std::cout << "E" << identifier << " = ";
            result->write();
            break;
          default:
            break;
        }
        j = -1;
        ++i;
      } else if (line[i] == 'N' || line[i] == ' ' || line[i] == 'E') {
        j = -1;    
        ++i;
      } else if (int(line[i] - '0' > 0) && int(line[i] - '0' <= 10) && (line[i - 1] == 'N')){
        int aux = int(line[i] - '0');
        stack_.push(integers_.at(aux - 1));
        j = -1;
        ++i;
      } else if (int(line[i] - '0' > 0) && int(line[i] - '0' <= 10) && (line[i - 1] == 'E')){
        int aux = int(line[i] - '0');
        stack_.push(results_.at(aux - 1));
        j = -1;
        ++i;
      } 
    }
  }
}

#endif