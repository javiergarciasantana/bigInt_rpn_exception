// AUTOR: Javier Garcia Santana
// FECHA: 7/3/2023
// EMAIL: alu0101391663@ull.edu.es
// VERSION: 3.0
// ASIGNATURA: Algoritmos y Estructuras de Datos Avanzadas
// PRÁCTICA Nº: 3
// COMENTARIOS: Fichero .h en el que se instancia la
// clase Number y todos sus metodos para que posteriormente 
// definirlos en la case BigInt, ya que Number es una clase
// abstracta y hemos de habilitar el polimorfismo dinamico
// entre la clase base(Number) y las derivadas

#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <cassert>
#include <cmath>
#include <stack>

#ifndef NUMBER_H
#define NUMBER_H

template<const size_t Base>
class BigInt;

class Number {
 public:
  //Constructor?
  static Number* create(size_t base, const std::string& s);
  //virtual Number& operator=(const Number&) = 0;
  //Operadores aritmeticos
  virtual Number* add(const Number*) const = 0; 
  virtual Number* subtract(const Number*) const = 0; 
  virtual Number* multiply(const Number*) const = 0; 
  virtual Number* divide(const Number*) const = 0; 
  virtual Number* module(const Number*) const = 0; 
  virtual Number* pow(const Number*) const = 0;
  //Cambio de tipo
  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0; 
  virtual operator BigInt<10>() const = 0; 
  virtual operator BigInt<16>() const = 0;
  //Operadores de flujo
  virtual std::ostream& write(std::ostream& = std::cout) const = 0;
  virtual std::istream& read(std::istream& = std::cin) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&); 
  friend std::istream& operator>>(std::istream&, Number&);

};

#endif