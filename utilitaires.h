#pragma once

#include "type_def.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::max

Person* creerPersonne(std::string name,
                      std::string firstname,
                      int year_of_birth,
                      int sex,
                      bool married = false,
                      Person* partner = nullptr,
                      Person* father = nullptr,
                      Person* mother = nullptr);
void detruirePersonne(Person* p);
void mariage(Person *p1, Person *p2);
void showPerson(Person *p);
bool frereSoeur(Person *p1, Person *p2);
bool memePerson(Person *p1, Person *p2);
bool ancetre(Person *ancetre, Person *psonne);
int generations(Person *p);
int treeSize(Person *p);
void showTree(Person *p);