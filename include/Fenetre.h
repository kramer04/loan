#ifndef FENETRE_H
#define FENETRE_H

#include <iostream>
#include <string>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/box.h>
#include <gtkmm-3.0/gtkmm/button.h>
#include <gtkmm-3.0/gtkmm/buttonbox.h>
#include <gtkmm-3.0/gtkmm/comboboxtext.h>
#include <gtkmm-3.0/gtkmm/entry.h>
#include <gtkmm-3.0/gtkmm/grid.h>
#include <sigc++/connection.h>
#include <locale>
#include <sstream>
#include <sigc++/connection.h>
#include "Fonctions.h"

class Fenetre : public Gtk::Window
{
private:
  Gtk::VBox boiteV;
  Gtk::Button m_boutonC, m_boutonM, m_boutonT, m_boutonD, m_boutonCT, resultat, clear, quitter;
  Gtk::HButtonBox boutonH;
  Gtk::Grid m_layout;
  Gtk::Entry m_capital, m_mensualite, m_taux, m_duree, m_coutTotal, m_test;
  Gtk::ComboBoxText listeDeroulante;

  void on_clicked_calcul();
  void on_clicked_clear();
  void on_clicked_quitter();
  void listeD();
  void sensitive();
  std::string stream(std::string const &entry);
  double sup_espace(std::string entry);
  std::stringstream loc;

  sigc::connection c, c1, m, m1, t, t1, d, d1, d2;

  Fonctions pret;

public:
  Fenetre();
};

#endif