#pragma once

#include <string>

struct Person {
  std::string name;
  std::string firstname;
  int year_of_birth;
  int sex; // 1 = garçon, 2 = fille
  bool married;
  Person* partner;
};