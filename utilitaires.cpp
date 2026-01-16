#include "utilitaires.h"

std::unordered_set<int> usedIds;

Person* creerPersonne(
						const std::string name,
					  const std::string firstname,
					  const int year_of_birth,
					  const int sex,
					  const bool married,
					  Person* partner,
					  Person* father,
					  Person* mother,
						const int id)
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

	if(id != -1){
		p->id = id;
		usedIds.insert(id);
	} else {
		do{
			p->id = rand();
		}while(usedIds.count(p->id));
		usedIds.insert(p->id);
	}

	return p;
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
        // grands-parents identiques des deux côtés => on les compte une seule fois
        // soit p (1) + père (1) + mère (1) + arbre des grands-parents
        return 1 + 1 + 1 + treeSize(father->father) + treeSize(father->mother);
    }

    // cas normal : pas de consanguinité
    return 1 + treeSize(father) + treeSize(mother);
}

void showTree(Person *p){ // pareil que treeSize() mais avec showPerson()
	if(p == nullptr)
		return;

	showPerson(p);

	Person* father = p->father;
	Person* mother = p->mother;

	// cas : père est un ancêtre de la mère
	if (ancetre(mother, father)) {
			showTree(mother);
			return;
	}

	// cas : mère est un ancêtre du père
	if (ancetre(father, mother)) {
			showTree(father);
			return;
	}

	// cas : les parents sont frère et sœur
	if (father != nullptr && mother != nullptr && frereSoeur(father, mother)) {
			showTree(father->father);
			showTree(father->mother);
			return;
	}

	showTree(father);
	showTree(mother);
}

// Fonction pour sauvegarder une personne dans un fichier texte
int save(Person *p) {
	// Création ou modification du fichier sauvegarde.txt
	std::ofstream fichierPersonne("sauvegarde.txt", std::ios::app);

	// Si il y a un problème dans la création ou l'ouverture du fichier
	if (!fichierPersonne) {
		std::cerr << "Can't open the file" << std::endl;
		return 0;
	}
	// Ecriture des attributs dans le fichier texte
	fichierPersonne << p->id << " "
	 << p->name << " "
	 << p->firstname << " "
	 << p->year_of_birth << " "
	 << p->sex << " "
	 << p->married << " "
	 << (p->partner ? p->partner->id : -1) << " "
	 << (p->father  ? p->father->id  : -1) << " "
	 << (p->mother  ? p->mother->id  : -1)
	 << "\n";
	return 1;
}

// Fonction qui renvoie l'adresse d'une personne en fonction de son id
Person* findPersonById(std::vector<Person>& persons, int id) {
	for (auto& p : persons) {
		if (p.id == id) {
			return &p;
		}
	}
	return nullptr;
}

// Fonction pour charger les liens entre les personnes
std::vector<Person> setLink(std::vector<Person> personnes, std::unordered_map<int, std::array<int, 3>> links) {
	for (const auto& relation : links) {
		// On récupère l'ID d'une personne
		int key = relation.first;

		// On récupère les id du conjoint, père et mère
		const std::array<int, 3>& values = relation.second;

		// On récupère l'objet de la personne en fonction de son id
		Person *currentPerson = findPersonById(personnes, key);

		// On récupère la personne conjoint, père et mère
		Person *conjoinPerson = findPersonById(personnes, links[key][0]);
		Person *fatherPerson = findPersonById(personnes, links[key][1]);
		Person *motherPerson = findPersonById(personnes, links[key][2]);

		// On attribue les adresses sur l'attribut
		currentPerson->partner = conjoinPerson;
		currentPerson->father = fatherPerson;
		currentPerson->mother = motherPerson;
	}
	return personnes;
}

std::vector<Person> loadPerson() {
	// Vecteur de personnes
	std::vector<Person> personnes;
	// Hashmap des relations
	std::unordered_map<int, std::array<int, 3>> persons_relations;
	std::ifstream fichierPersonne("sauvegarde.txt");
	if (!fichierPersonne) {
		std::cerr << "Can't open the file" << std::endl;
		return personnes;
	}

	// Ligne du fichier en lecture
	std::string line;
	while (std::getline(fichierPersonne, line)) {
		int id, year, sex, married;
		std::string name, firstname;
		int partner_id, father_id, mother_id;
		// Pour ségmenter les différents attributs
		std::istringstream iss(line);

		// Récupération des attributs de la ligne aux variables
		iss >> id >> name >> firstname >> year >> sex >> married >> partner_id >> father_id >> mother_id;

		// On créé la personne et on la met dans le vecteur avec nullptr pour les liens (partenaire, père, mère)
		Person *personActu = creerPersonne(name, firstname, year, sex, married, nullptr, nullptr, nullptr, id);

		// On stocke en fonction de l'id de la personnes, l'id des relations
		persons_relations[id] = {partner_id, father_id, mother_id};
		personnes.push_back(*personActu);
	}

	// Attribution des liens conjoint, père et mère
	personnes = setLink(personnes, persons_relations);
	return personnes;
}