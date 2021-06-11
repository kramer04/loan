#ifndef FONCTIONS_H
#define FONCTION_H

#include <string>

class Fonctions
{
  public:
    Fonctions();
    std::string calcul_capital(double mensualite, double taux, double duree);
    std::string calcul_mensualite(double capital, double taux, double duree);
    std::string cout_total(double capital, double mensualite, double duree);
    std::string calcul_taux(double capital, double mensualite, double duree);
    std::string calcul_duree(double capital, double mensualite, double taux);

  private:
    void affiche_resultat(double capital, double mensualite, double taux, double duree);
    void test();
};

#endif