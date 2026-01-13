#include "utilitaires.h"

Person* creerPersonne(std::string name,
					  std::string firstname,
					  int year_of_birth,
					  int sex,
					  bool married,
					  Person* partner,
					  Person* father,
					  Person* mother)
{
	Person* p = new Person;

	p->name = name;
	p->firstname = firstname;
	p->year_of_birth = year_of_birth;
	p->sex = sex;
	p->married = married;
	p->partner = partner;
	p->father = father;
	p->mother = mother;

	return p;
}

void detruirePersonne(Person* p)
{
    delete p;
}

void mariage(Person *p1, Person *p2){
	if (p1->partner != nullptr || p2->partner != nullptr) {
		if (ancetre(p1, p2) == false || ancetre(p2, p1) == false || frereSoeur(p1, p2)){
			return;
		}
	}
	else {
		p1->partner = p2;
		p1->married = true;
		p2->partner = p1;
		p2->married = true;
	}
}

void showPerson(Person *p){
	if(p == nullptr)
		return;
  std::cout << (p->sex == 2 ? "Madame " : "Monsieur ") << p->firstname << " " << p->name;
  if (p->married && p->partner != nullptr) {
      std::cout << (p->sex == 2 ? " epouse " : " epoux ") << "de " << (p->partner->sex == 2 ? "Mme. " : "M. ") << p->partner->name << " " << std::endl;
  }else{
		std::cout << " " << std::endl;
	}
  if (p->father != nullptr) {
      std::cout << "De pere " << p->father->firstname << " " << p->father->name << std::endl;
  } else {
      std::cout << "De pere INCONNU" << std::endl;
  }
  if (p->mother != nullptr) {
      std::cout << "De mere " << p->mother->firstname << " " << p->mother->name << std::endl;
  } else {
      std::cout << "De mere INCONNUE" << std::endl;
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
  if (a == nullptr || b == nullptr)
    return false;

  if (a->father == b || a->mother == b)
    return true;
  // } else {
  //   if(ancetre(a->father, b) || ancetre(a->mother, b)){
  //     return true;
  //   }
  // }
  return (ancetre(a->father, b) || ancetre(a->mother, b));
}

int generations(Person *p) {
    if (p == nullptr)
        return 0;
// 	int father = 1 + generations(p->father);
// 	int mother = 1 + generations(p->mother);
// 	return std::max(father, mother);
    return 1 + std::max(generations(p->father), generations(p->mother));
}

int treeSize(Person *p) {
    if (p == nullptr)
        return 0;

    Person* father = p->father;
    Person* mother = p->mother;

    // cas : père est un ancêtre de la mère
    if (ancetre(mother, father)) {
        // le père sera déjà compté dans l'arbre de la mère
        return 1 + treeSize(mother);
    }

    // cas : mère est un ancêtre du père
    if (ancetre(father, mother)) {
        // la mère sera déjà comptée dans l'arbre du père
        return 1 + treeSize(father);
    }

    // cas : les parents sont frère et sœur
    if (father != nullptr && mother != nullptr && frereSoeur(father, mother)) {
        // grands-parents identiques des deux côtés → on les compte une seule fois
        // soit p (1) + père (1) + mère (1) + arbre des grands-parents
        return 1 + 1 + 1 + treeSize(father->father) + treeSize(father->mother);
    }

    // cas normal : pas de consanguinité
    return 1 + treeSize(father) + treeSize(mother);
}

void showTree(Person *p){
	if(p == nullptr)
		return;

	showPerson(p);

	Person* father = p->father;
	Person* mother = p->mother;

	// cas : père est un ancêtre de la mère
	if (ancetre(mother, father)) {
			// le père sera déjà compté dans l'arbre de la mère
			showTree(mother);
			return;
	}

	// cas : mère est un ancêtre du père
	if (ancetre(father, mother)) {
			// la mère sera déjà comptée dans l'arbre du père
			showTree(father);
			return;
	}

	// cas : les parents sont frère et sœur
	if (father != nullptr && mother != nullptr && frereSoeur(father, mother)) {
			// grands-parents identiques des deux côtés → on les compte une seule fois
			// soit p (1) + père (1) + mère (1) + arbre des grands-parents
			showTree(father->father);
			showTree(father->mother);
			return;
	}

	showTree(father);
	showTree(mother);
	// return;
}
