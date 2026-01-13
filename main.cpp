#include "utilitaires.h"

int main(int argc, char** argv) {
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
    return 0;
}