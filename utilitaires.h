#pragma once

#include "type_def.h"
#include <iostream>  // std::cout
#include <algorithm> // std::max
#include <cstdlib>   // rand()
#include <unordered_set>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <sstream>

Person *creerPersonne(std::string name,
                      std::string firstname,
                      int year_of_birth,
                      int sex,
                      bool married = false,
                      Person *partner = nullptr,
                      Person *father = nullptr,
                      Person *mother = nullptr,
                      int id = -1);
void mariage(Person *p1, Person *p2);
void showPerson(Person *p);
bool frereSoeur(Person *p1, Person *p2);
bool memePerson(Person *p1, Person *p2);
bool ancetre(Person *ancetre, Person *psonne);
int generations(Person *p);
int treeSize(Person *p);
void showTree(Person *p);
int save(Person *p);
Person *findPersonById(std::vector<Person> &persons, int id);
std::vector<Person> setLink(std::vector<Person> personnes, std::unordered_map<int, std::array<int, 3>> links);
std::vector<Person> loadPerson();
