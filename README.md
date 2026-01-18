# Compte rendu TP5 SMP

## Q1 : Construction d'un type de personne

### Définir le stockage d'une personne

Voici comment on a défini la structure pour la construction d'une personne :

```cpp
struct Person {
  int id;
  std::string name;
  std::string firstname;
  int year_of_birth;
  int sex;
  bool married;
  Person* partner;
  Person* father;
  Person* mother;
};
```

On remarque bien l'utilisation de pointeur pour "pointer" vers d'autres personnes comme le conjoint, le père et la mère.

### Fonction pour créer une personne

#### Déclaration/prototype

```cpp
Person* creerPersonne(std::string name,
                      std::string firstname,
                      int year_of_birth,
                      int sex,
                      bool married = false,
                      Person* partner = nullptr,
                      Person* father = nullptr,
                      Person* mother = nullptr,
                      int id = -1);
```

On définit bien des valeurs par défaut pour les champs optionnels à la création d'une personne.

#### Définition/implémentation

```cpp
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
```

Fonction assez simple qui vient créer une case mémoire pour une personne puis l'on vient ajouter chaque paramètre d'entrée dans la structure. Particularité pour l'id où l'on vient générer un id et s'il existe déjà, car chaque id est stocké dans un `unordered_set` qui est un type qui répond vraiment à cette problématique c'est-à-dire que c'est fait pour stocker des objets qui sont uniques (comme un id) et qui propose des méthodes pour facilement manipuler ces objets.

---

## Q2 : Mariage

### Algorithme

```
FONCTION mariage(p1: Personne*, p2: Personne*)
    SI p1->conjoint != NULL OU p2->conjoint != NULL ALORS
        SI NON ancetre(p1, p2) OU NON ancetre(p2, p1) OU frereSoeur(p1, p2) ALORS
            RETOURNER (mariage impossible)
        FIN SI
    SINON
        p1->conjoint ← p2
        p1->marié ← VRAI
        p2->conjoint ← p1
        p2->marié ← VRAI
    FIN SI
FIN FONCTION
```

### Implémentation

```cpp
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
```

Cette fonction marie deux personnes en modifiant mutuellement leurs champs `partner` et en mettant à jour le booléen `married`. Elle vérifie également que les deux personnes ne sont pas déjà mariées avant de procéder.

---

## Q3 : Affichage simple

### Algorithme

```
FONCTION showPerson(p: Personne*)
    SI p == NULL ALORS RETOURNER
    
    AFFICHER (p->sexe == 2 ? "Madame " : "Monsieur ") + p->prénom + " " + p->nom
    
    SI p->marié ET p->conjoint != NULL ALORS
        AFFICHER (p->sexe == 2 ? " épouse " : " époux ") + "de " + 
                 (conjoint->sexe == 2 ? "Mme. " : "M. ") + conjoint->nom
    FIN SI
    
    SI p->père != NULL ALORS
        AFFICHER "De père " + père->prénom + " " + père->nom
    SINON
        AFFICHER "De père INCONNU"
    FIN SI
    
    SI p->mère != NULL ALORS
        AFFICHER "De mère " + mère->prénom + " " + mère->nom
    SINON
        AFFICHER "De mère INCONNUE"
    FIN SI
FIN FONCTION
```

### Implémentation

```cpp
void showPerson(Person *p){
    if(p == nullptr)
        return;
    std::cout << (p->sex == 2 ? "Madame " : "Monsieur ") << p->firstname << " " << p->name;
    if (p->married && p->partner != nullptr) {
        std::cout << (p->sex == 2 ? " epouse " : " epoux ") << "de " 
                  << (p->partner->sex == 2 ? "Mme. " : "M. ") << p->partner->name << " " << std::endl;
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
```

Cette fonction affiche les informations d'une personne de manière formatée, en utilisant l'opérateur ternaire pour adapter l'affichage selon le sexe et en gérant les cas où les parents sont inconnus.

---

## Q4 : Relations de parenté

La question 4 demande d'ajouter les champs `father` et `mother` au type `Person` et de modifier la fonction d'affichage. Ces modifications ont été intégrées directement dans la structure `Person` (voir Q1) et dans la fonction `showPerson` (voir Q3).

Les champs ajoutés sont :

```cpp
Person* father;
Person* mother;
```

Ces pointeurs permettent de relier chaque personne à ses parents biologiques, formant ainsi la structure d'arbre généalogique.

---

## Q5 : Frère et sœur

### Algorithme

```
FONCTION frereSoeur(p1: Personne*, p2: Personne*) : BOOLÉEN
    RETOURNER (p1->père == p2->père) ET (p1->mère == p2->mère)
FIN FONCTION
```

### Fonction auxiliaire memePersonne

```
FONCTION memePersonne(p1: Personne*, p2: Personne*) : BOOLÉEN
    RETOURNER (p1->nom == p2->nom) ET (p1->prénom == p2->prénom) 
              ET (p1->annéeNaissance == p2->annéeNaissance) ET (p1->sexe == p2->sexe)
FIN FONCTION
```

### Implémentation

```cpp
bool frereSoeur(Person *p1, Person *p2){
    return ((p1->father == p2->father) && (p1->mother == p2->mother));
}

bool memePerson(Person *p1, Person *p2){
    return (p1->name == p2->name && p1->firstname == p2->firstname 
            && p1->year_of_birth == p2->year_of_birth && p1->sex == p2->sex);
}
```

La fonction `frereSoeur` vérifie si deux personnes partagent les mêmes parents (même père ET même mère). La comparaison se fait sur les pointeurs, ce qui suppose que les mêmes objets `Person` sont utilisés comme références pour les parents.

---

## Q6 : Ancêtres

### Algorithme

```
FONCTION ancetre(a: Personne*, b: Personne*) : BOOLÉEN
    SI a == NULL OU b == NULL ALORS
        RETOURNER FAUX
    FIN SI
    
    SI a->père == b OU a->mère == b ALORS
        RETOURNER VRAI
    FIN SI
    
    RETOURNER ancetre(a->père, b) OU ancetre(a->mère, b)
FIN FONCTION
```

### Implémentation

```cpp
bool ancetre(Person *a, Person *b){
    if (a == nullptr || b == nullptr)
        return false;

    if (a->father == b || a->mother == b)
        return true;

    return (ancetre(a->father, b) || ancetre(a->mother, b));
}
```

Cette fonction récursive parcourt l'arbre généalogique de `a` pour vérifier si `b` est un ancêtre. Elle vérifie d'abord si `b` est un parent direct, sinon elle remonte récursivement dans l'arbre en cherchant du côté du père puis de la mère.

---

## Q7 : Générations

### Algorithme

```
FONCTION generations(p: Personne*) : ENTIER
    SI p == NULL ALORS
        RETOURNER 0
    FIN SI
    
    RETOURNER 1 + MAX(generations(p->père), generations(p->mère))
FIN FONCTION
```

### Implémentation

```cpp
int generations(Person *p) {
    if (p == nullptr)
        return 0;
    return 1 + std::max(generations(p->father), generations(p->mother));
}
```

Cette fonction calcule la profondeur maximale de l'arbre généalogique. Elle utilise la récursion pour explorer les deux branches (paternelle et maternelle) et retourne la profondeur maximale trouvée, en ajoutant 1 pour compter la génération actuelle.

---

## Q8 : Taille de l'arbre

### Algorithme

```
FONCTION treeSize(p: Personne*) : ENTIER
    SI p == NULL ALORS
        RETOURNER 0
    FIN SI
    
    père ← p->père
    mère ← p->mère
    
    // Cas : père est un ancêtre de la mère
    SI ancetre(mère, père) ALORS
        RETOURNER 1 + treeSize(mère)
    FIN SI
    
    // Cas : mère est un ancêtre du père
    SI ancetre(père, mère) ALORS
        RETOURNER 1 + treeSize(père)
    FIN SI
    
    // Cas : les parents sont frère et sœur
    SI père != NULL ET mère != NULL ET frereSoeur(père, mère) ALORS
        RETOURNER 1 + 1 + 1 + treeSize(père->père) + treeSize(père->mère)
    FIN SI
    
    // Cas normal : pas de consanguinité
    RETOURNER 1 + treeSize(père) + treeSize(mère)
FIN FONCTION
```

### Implémentation

```cpp
int treeSize(Person *p) {
    if (p == nullptr)
        return 0;

    Person* father = p->father;
    Person* mother = p->mother;

    // cas : père est un ancêtre de la mère
    if (ancetre(mother, father)) {
        return 1 + treeSize(mother);
    }

    // cas : mère est un ancêtre du père
    if (ancetre(father, mother)) {
        return 1 + treeSize(father);
    }

    // cas : les parents sont frère et sœur
    if (father != nullptr && mother != nullptr && frereSoeur(father, mother)) {
        return 1 + 1 + 1 + treeSize(father->father) + treeSize(father->mother);
    }

    // cas normal : pas de consanguinité
    return 1 + treeSize(father) + treeSize(mother);
}
```

Cette fonction compte le nombre de membres uniques dans l'arbre généalogique. Elle gère les cas de consanguinité (où un ancêtre apparaît plusieurs fois) pour éviter de compter plusieurs fois la même personne.

---

## Q9 : Mariage possible

La vérification du mariage possible a été intégrée directement dans la fonction `mariage` (voir Q2). Les conditions vérifiées sont :

- `a` ne doit pas être un ancêtre de `b`
- `b` ne doit pas être un ancêtre de `a`  
- `a` et `b` ne doivent pas être frère et/ou sœur

```cpp
if (ancetre(p1, p2) == false || ancetre(p2, p1) == false || frereSoeur(p1, p2)){
    return; // Mariage impossible
}
```

---

## Q10 : Affichage de l'arbre généalogique

### Algorithme

```
FONCTION showTree(p: Personne*)
    SI p == NULL ALORS RETOURNER
    
    showPerson(p)
    
    père ← p->père
    mère ← p->mère
    
    // Cas : père est un ancêtre de la mère
    SI ancetre(mère, père) ALORS
        showTree(mère)
        RETOURNER
    FIN SI
    
    // Cas : mère est un ancêtre du père
    SI ancetre(père, mère) ALORS
        showTree(père)
        RETOURNER
    FIN SI
    
    // Cas : les parents sont frère et sœur
    SI père != NULL ET mère != NULL ET frereSoeur(père, mère) ALORS
        showTree(père->père)
        showTree(père->mère)
        RETOURNER
    FIN SI
    
    showTree(père)
    showTree(mère)
FIN FONCTION
```

### Implémentation

```cpp
void showTree(Person *p){
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
```

Cette fonction affiche l'arbre généalogique complet en utilisant la même logique que `treeSize` pour gérer les cas de consanguinité et éviter d'afficher plusieurs fois les mêmes personnes.

---

## Q11 : Gestion des fichiers

### Sauvegarde

#### Algorithme

```
FONCTION save(p: Personne*) : ENTIER
    Ouvrir fichier "sauvegarde.txt" en mode ajout
    
    SI erreur d'ouverture ALORS
        AFFICHER erreur
        RETOURNER 0
    FIN SI
    
    ÉCRIRE dans fichier : id, nom, prénom, année, sexe, marié, 
                          id_conjoint (ou -1), id_père (ou -1), id_mère (ou -1)
    
    RETOURNER 1
FIN FONCTION
```

#### Implémentation

```cpp
int save(Person *p) {
    std::ofstream fichierPersonne("sauvegarde.txt", std::ios::app);

    if (!fichierPersonne) {
        std::cerr << "Can't open the file" << std::endl;
        return 0;
    }
    
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
```

La fonction `save` écrit les attributs d'une personne dans un fichier texte. Les pointeurs vers d'autres personnes sont remplacés par leurs identifiants uniques (ou -1 si null).

### Chargement

#### Fonctions auxiliaires

```cpp
Person* findPersonById(std::vector<Person>& persons, int id) {
    for (auto& p : persons) {
        if (p.id == id) {
            return &p;
        }
    }
    return nullptr;
}

std::vector<Person> setLink(std::vector<Person> personnes, 
                            std::unordered_map<int, std::array<int, 3>> links) {
    for (const auto& relation : links) {
        int key = relation.first;
        const std::array<int, 3>& values = relation.second;

        Person *currentPerson = findPersonById(personnes, key);
        Person *conjoinPerson = findPersonById(personnes, links[key][0]);
        Person *fatherPerson = findPersonById(personnes, links[key][1]);
        Person *motherPerson = findPersonById(personnes, links[key][2]);

        currentPerson->partner = conjoinPerson;
        currentPerson->father = fatherPerson;
        currentPerson->mother = motherPerson;
    }
    return personnes;
}
```

#### Fonction principale de chargement

```cpp
std::vector<Person> loadPerson() {
    std::vector<Person> personnes;
    std::unordered_map<int, std::array<int, 3>> persons_relations;
    std::ifstream fichierPersonne("sauvegarde.txt");
    
    if (!fichierPersonne) {
        std::cerr << "Can't open the file" << std::endl;
        return personnes;
    }

    std::string line;
    while (std::getline(fichierPersonne, line)) {
        int id, year, sex, married;
        std::string name, firstname;
        int partner_id, father_id, mother_id;
        std::istringstream iss(line);

        iss >> id >> name >> firstname >> year >> sex >> married 
            >> partner_id >> father_id >> mother_id;

        Person *personActu = creerPersonne(name, firstname, year, sex, married, 
                                           nullptr, nullptr, nullptr, id);

        persons_relations[id] = {partner_id, father_id, mother_id};
        personnes.push_back(*personActu);
    }

    personnes = setLink(personnes, persons_relations);
    return personnes;
}
```

Le processus de chargement se fait en deux étapes :

1. **Lecture des données** : On lit chaque ligne du fichier et on crée les objets `Person` avec des pointeurs `nullptr` pour les relations. On stocke les IDs des relations dans une hashmap.

2. **Reconstruction des liens** : Une fois toutes les personnes créées, on parcourt la hashmap pour reconstituer les pointeurs vers le conjoint, le père et la mère en utilisant la fonction `findPersonById`.

---

## Fichiers du projet

### type_def.h

```cpp
#pragma once
#include <string>

struct Person {
  int id;
  std::string name;
  std::string firstname;
  int year_of_birth;
  int sex;
  bool married;
  Person* partner;
  Person* father;
  Person* mother;
};
```

### utilitaires.h

```cpp
#pragma once

#include "type_def.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <unordered_set>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <array>
#include <sstream>

Person* creerPersonne(std::string name,
                      std::string firstname,
                      int year_of_birth,
                      int sex,
                      bool married = false,
                      Person* partner = nullptr,
                      Person* father = nullptr,
                      Person* mother = nullptr,
                      int id = -1);
void detruirePersonne(Person* p);
void mariage(Person *p1, Person *p2);
void showPerson(Person *p);
bool frereSoeur(Person *p1, Person *p2);
bool memePerson(Person *p1, Person *p2);
bool ancetre(Person *ancetre, Person *psonne);
int generations(Person *p);
int treeSize(Person *p);
void showTree(Person *p);
int save(Person *p);
Person* findPersonById(std::vector<Person>& persons, int id);
std::vector<Person> setLink(std::vector<Person> personnes, 
                            std::unordered_map<int, std::array<int, 3>> links);
std::vector<Person> loadPerson();
```

### main.cpp (exemple de test)

```cpp
#include "utilitaires.h"

int main(int argc, char **argv)
{
    srand(time(0));
    Person *p1 = creerPersonne("Metai", "Thoma", 2005, 1, 0);
    Person *p2 = creerPersonne("Balais", "Jardin", 2000, 2, 0);
    mariage(p1, p2);
    Person *p3 = creerPersonne("Golf", "Corentin", 2001, 1, 0, nullptr, p1, p2);
    Person *p4 = creerPersonne("Alpha", "Sophie", 2002, 2, 0, nullptr, p1, p2);
    Person *p5 = creerPersonne("Beta", "Homer", 2003, 1, 0, nullptr, p3, p4);
    Person *p6 = creerPersonne("Ceta", "Voltaire", 2004, 2, 0, nullptr, p5, p4);

    std::cout << generations(p6) << std::endl;
    std::cout << treeSize(p6) << std::endl;
    showTree(p6);
    save(p1);
    save(p2);
    save(p3);
    save(p4);
    save(p5);
    save(p6);
    std::vector<Person> personnes = loadPerson();

    return 0;
}
```

---

## Conclusion

Ce TP nous a permis de manipuler des arbres binaires dans le contexte des arbres généalogiques. Les principales notions abordées sont :

- **Structures de données** : Définition d'un type `Person` avec des pointeurs auto-référencés pour créer une structure arborescente
- **Récursivité** : Utilisation intensive de fonctions récursives pour parcourir l'arbre (ancêtres, générations, taille, affichage)
- **Gestion de la mémoire** : Allocation dynamique avec `new` et utilisation de pointeurs
- **Gestion des fichiers** : Sérialisation et désérialisation de structures de données avec gestion des références croisées via des identifiants uniques
- **Cas particuliers** : Gestion de la consanguinité pour éviter de compter plusieurs fois les mêmes ancêtres