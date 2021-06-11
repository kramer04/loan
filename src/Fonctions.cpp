#include "Fonctions.h"
#include <iostream>

#include <cmath>
#include <iomanip>

Fonctions::Fonctions()
{
  std::cout.imbue(std::locale("fr_FR.UTF-8"));
  std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(2);
}

std::string Fonctions::calcul_capital(double mensualite, double taux, double duree)
{
  double j{0.0}, capital{0.0};
  j = taux / 1200;
  capital = mensualite * (1 - pow(1 + j, -duree)) / j;
  affiche_resultat(capital, mensualite, taux, duree);
  return std::to_string(capital);
}
std::string Fonctions::calcul_mensualite(double capital, double taux, double duree)
{
  double mensualite{0.0}, j{0.0};
  j = taux / 1200;
  mensualite = (capital * j) / (1 - pow(1 + j, -duree));
  affiche_resultat(capital, mensualite, taux, duree);
  return std::to_string(mensualite);
}
std::string Fonctions::cout_total(double capital, double mensualite, double duree)
{
  double coutTotal{mensualite * duree - capital};
  return std::to_string(coutTotal);
}
std::string Fonctions::calcul_taux(double capital, double mensualite, double duree)
{
  double j{0.0}, min_rate{0.0}, max_rate{100.0}, mid_rate{0.0}, guess_pmt{0.0}; //pour calcul du taux
  while (min_rate < (max_rate - 0.000001))
  {
    mid_rate = (min_rate + max_rate) / 2;
    j = mid_rate / 1200;
    guess_pmt = capital * j / (1 - pow(1 + j, -duree));
    if (guess_pmt > mensualite)
    {
      max_rate = mid_rate;
    }
    else
    {
      min_rate = mid_rate;
    }
  }
  affiche_resultat(capital, mensualite, mid_rate, duree);
  return std::to_string(mid_rate);
}
std::string Fonctions::calcul_duree(double capital, double mensualite, double taux)
{
  double duree{0.0}, j{0.0};
  j = taux / 1200;
  duree = log(-mensualite / (j * capital - mensualite)) / log(1 + j);
  affiche_resultat(capital, mensualite, taux, duree);
  return std::to_string(duree);
}
void Fonctions::affiche_resultat(double capital, double mensualite, double taux, double duree)
{
  std::cout << "----------------------"
            << "\n"
            << std::flush;
  std::cout << "Capital = " << capital << "\n"
            << std::flush;
  std::cout << "Mensualité = " << mensualite << "\n"
            << std::flush;
  std::cout << "Taux = " << taux << "\n"
            << std::flush;
  std::cout << "Durée = " << duree << "\n"
            << std::flush;
  std::cout << "Coût total = " << mensualite * duree - capital << "\n"
            << std::flush;
  std::cout << "----------------------" << std::endl;
}