#pragma once

#include <string>

struct Person {
  std::string name;
  std::string firstname;
  int year_of_birth;
  int sex;
  bool married;
  Person* partner;
  Person* father;
  Person* mother;
};