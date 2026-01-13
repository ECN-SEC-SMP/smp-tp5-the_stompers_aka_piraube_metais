#include "utilitaires.h"

Person* creerPersonne(std::string name,
                      std::string firstname,
                      int year_of_birth,
                      int sex,
                      bool married = false,
                      Person* partner = nullptr,
                      Person* father = nullptr,
                      Person* mother = nullptr)
{
    return new Person(name, firstname, year_of_birth, sex, married, partner, father, mother);
}

void detruirePersonne(Person* p)
{
    delete p;
}

void mariage( *Person p1, *Person p2){
	p1->partner = p2;
	p1->married = true;
	p2->partner = p1;
	p2->married = true;
}

void showPerson(Person *p){
  std::cout << p->sex == 2 ? "Madame " : "Monsieur " << p->firstname << " " << p->name << " ";
  if (p->married && p->partner != nullptr) {
      std::cout << p->sex == 2 ? "épouse " : "époux " << "de " << p->partner->sex == 2 ? "Mme. " : "M. " << p->partner->name << endl;
  }
  if (p->father != nullptr) {
      std::cout << "De père " << p->father->firstname << " " << p->father->name << endl;
  } else {
      std::cout << "De père INCONNU" << endl;
  }
  If (p->mother != nullptr) {
      std::cout << "De mère " << p->mother->firstname << " " << p->mother->name << endl;
  } else {
      std::cout << "De mère INCONNUE" << endl;
  }
}

bool frereSoeur(Person *p1, Person *p2){
	return ((p1->father == p2->father) && (p1->mother == p2->mother));
	// if(p1->father == p2->father && p1->mother == p2->mother){
	//  return true;
	// }
	// else{
	// 	return false;
	// }
}

bool memePerson(Person *p1, Person *p2){
  return (p1->name == p2->name && p1->firstname == p2->firstname && p1->year_of_birth == p2->year_of_birth && p1->sex == p2->sex);
	// if(p1->name == p2->name && p1->firstname == p2->firstname && p1->year_of_birth == p2->year_of_birth && p1->sex == p2->sex){
	// 	return true;
	// }
	// else{
	// 	return false;
	// }
}

bool ancetre(Person *a, Person *b){
}

int generations(Person *p){
}