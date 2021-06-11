#include "Fenetre.h"
#include <algorithm>
#include <gtkmm-3.0/gtkmm/stock.h>
#include <iomanip>
#include <list>
#include <locale>

Fenetre::Fenetre() :
    boiteV(false, 25), m_boutonC("Capital"), m_boutonM("Mensualité"),
    m_boutonT("Taux"), m_boutonD("Durée en mois"), m_boutonCT("Coût total"),
    resultat("Résultat"), clear("Effacer"), quitter(Gtk::Stock::QUIT),
    boutonH(Gtk::BUTTONBOX_END, 10)
{
  std::cout << "User-preferred locale setting is " << std::locale("").name().c_str() << std::endl;
  //locale.imbue(std::locale("fr_FR.UTF-8"));

  set_title("Test avec Gtk::Grid");
  set_position(Gtk::WIN_POS_CENTER);
  set_border_width(10);
  set_default_size(420, 200);
  set_icon_from_file("sac.png");

  std::list<std::string> liste = {"Que calculer ?", "Capital", "Mensualité", "Taux", "Durée"};
  for (std::string i : liste)
  {
    listeDeroulante.append(i);
  }
  listeDeroulante.set_active(0);

  m_layout.set_row_spacing(15);
  m_layout.set_column_spacing(50);
  m_layout.attach(m_boutonC, 0, 0, 1, 1);
  m_layout.attach(m_capital, 1, 0, 1, 1);
  m_layout.attach(m_boutonM, 0, 1, 1, 1);
  m_layout.attach(m_mensualite, 1, 1, 1, 1);
  m_layout.attach(m_boutonT, 0, 2, 1, 1);
  m_layout.attach(m_taux, 1, 2, 1, 1);
  m_layout.attach(m_boutonD, 0, 3, 1, 1);
  m_layout.attach(m_duree, 1, 3, 1, 1);
  m_layout.attach(m_boutonCT, 0, 4, 1, 1);
  m_layout.attach(m_coutTotal, 1, 4, 1, 1);

  m_coutTotal.set_sensitive(false);
  m_capital.set_alignment(Gtk::ALIGN_END);
  m_mensualite.set_alignment(Gtk::ALIGN_END);
  m_taux.set_alignment(Gtk::ALIGN_END);
  m_duree.set_alignment(Gtk::ALIGN_END);
  m_coutTotal.set_alignment(Gtk::ALIGN_END);

  boutonH.set_homogeneous(true);

  boutonH.pack_start(resultat);
  boutonH.pack_start(clear);
  boutonH.pack_start(quitter);

  boutonH.set_child_secondary(resultat);

  boiteV.pack_start(listeDeroulante);
  boiteV.pack_start(m_layout);
  boiteV.pack_start(boutonH);
  add(boiteV);
  show_all();

  resultat.signal_clicked().connect([this]() { on_clicked_calcul(); });
  clear.signal_clicked().connect([this]() { on_clicked_clear(); });
  quitter.signal_clicked().connect([this]() { on_clicked_quitter(); });
  listeDeroulante.signal_changed().connect([this]() { listeD(); });
}
std::string Fenetre::stream(std::string const &entry)
{
  double valeur{std::stod(entry)};
  loc.str("");
  loc.clear();
  loc << std::setiosflags(std::ios::fixed) << std::setprecision(2);
  loc.imbue(std::locale(""));
  loc << valeur;

  std::string traduction{loc.str().c_str()};
  return traduction;
}
void Fenetre::listeD()
{
  int liste{listeDeroulante.get_active_row_number()};

  switch (liste)
  {
  case 1: // capital
    sensitive();
    t.disconnect();
    t1.disconnect();
    d.disconnect();
    d1.disconnect();
    d2.disconnect();
    m.disconnect();
    m1.disconnect();
    m_capital.set_sensitive(false);
    m_mensualite.grab_focus();
    if (c.connected() == false)
    {
      c = m_mensualite.signal_activate().connect([this]() {
        m_taux.grab_focus();
        m_mensualite.set_text(stream(m_mensualite.get_text()));
        m_mensualite.signal_activate().emission_stop();
      });
    }
    if (c1.connected() == false)
    {
      c1 = m_taux.signal_activate().connect([this]() {m_duree.grab_focus(); m_taux.signal_activate().emission_stop(); });
    }
    m_duree.signal_activate().connect([this]() {on_clicked_calcul(); m_duree.signal_activate().emission_stop(); });

    break;
  case 2: // mensualité
    sensitive();
    c.disconnect();
    c1.disconnect();
    t.disconnect();
    t1.disconnect();
    d.disconnect();
    d1.disconnect();
    d2.disconnect();
    m_mensualite.set_sensitive(false);
    m_capital.grab_focus();
    if (m.connected() == false)
    {
      m = m_capital.signal_activate().connect([this]() {m_taux.grab_focus(); m_capital.set_text(stream(m_capital.get_text())); });
    }
    if (m1.connected() == false)
    {
      m1 = m_taux.signal_activate().connect([this]() {m_duree.grab_focus(); m_taux.signal_activate().emission_stop(); });
    }
    m_duree.signal_activate().connect([this]() {on_clicked_calcul(); m_duree.signal_activate().emission_stop(); });
    break;
  case 3: // taux
    sensitive();
    c.disconnect();
    c1.disconnect();
    m.disconnect();
    m1.disconnect();
    d.disconnect();
    d1.disconnect();
    d2.disconnect();
    m_taux.set_sensitive(false);
    m_capital.grab_focus();
    if (t.connected() == false)
    {
      t = m_capital.signal_activate().connect([this]() {m_mensualite.grab_focus(); m_capital.set_text(stream(m_capital.get_text())); m_capital.signal_activate().emission_stop(); });
    }
    if (t1.connected() == false)
    {
      t1 = m_mensualite.signal_activate().connect([this]() {
        m_duree.grab_focus();
        m_mensualite.set_text(stream(m_mensualite.get_text()));
        m_mensualite.signal_activate().emission_stop();
      });
    }
    m_duree.signal_activate().connect([this]() {on_clicked_calcul(); m_duree.signal_activate().emission_stop(); });
    break;
  case 4: //duree
    sensitive();
    c.disconnect();
    c1.disconnect();
    m.disconnect();
    m1.disconnect();
    t.disconnect();
    t1.disconnect();
    m_duree.set_sensitive(false);
    m_capital.grab_focus();
    if (d.connected() == false)
    {
      d = m_capital.signal_activate().connect([this]() {
        m_mensualite.grab_focus();
        m_capital.set_text(stream(m_capital.get_text()));
        m_capital.signal_activate().emission_stop();
      });
    }
    if (d1.connected() == false)
    {
      d1 = m_mensualite.signal_activate().connect([this]() {
        m_taux.grab_focus();
        m_mensualite.set_text(stream(m_mensualite.get_text()));
        m_mensualite.signal_activate().emission_stop();
      });
    }
    if (d2.connected() == false)
    {
      d2 = m_taux.signal_activate().connect([this]() {on_clicked_calcul(); m_taux.signal_activate().emission_stop(); });
    }
    break;
  default:
    std::cout << "Erreur calcul" << std::endl;
    break;
  }
}
void Fenetre::sensitive()
{
  if (m_capital.get_sensitive() == false && listeDeroulante.get_active_row_number() != 1)
  {
    m_capital.set_sensitive(true);
  }
  else if (m_mensualite.get_sensitive() == false && listeDeroulante.get_active_row_number() != 2)
  {
    m_mensualite.set_sensitive(true);
  }
  else if (m_taux.get_sensitive() == false && listeDeroulante.get_active_row_number() != 3)
  {
    m_taux.set_sensitive(true);
  }
  else
  {
    m_duree.set_sensitive(true);
  }
}
void Fenetre::on_clicked_calcul()
{
  /*double capital{0.0}, mensualite{0.0};
  if (m_capital.get_text() != "")
  {
    capital = std::stod(m_capital.get_text());
  }
  if (m_mensualite.get_text() != "")
  {
    mensualite = std::stod(m_mensualite.get_text());
  }
  */
  std::string capital, mensualite, tx, temps, coutTotal;
  double taux{0.0}, duree{0.0};
  int choix{listeDeroulante.get_active_row_number()};
  if (m_taux.get_text() != "")
  {
    taux = std::stod(m_taux.get_text());
  }
  if (m_duree.get_text() != "")
  {
    duree = std::stod(m_duree.get_text());
  }

  switch (choix)
  {
  case 1: //capital
    capital = pret.calcul_capital(sup_espace(m_mensualite.get_text()), taux, duree);
    m_capital.set_text(stream(capital));
    coutTotal = pret.cout_total(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), duree);
    m_coutTotal.set_text(stream(coutTotal));
    break;
  case 2: //mensualité
    mensualite = pret.calcul_mensualite(sup_espace(m_capital.get_text()), taux, duree);
    m_mensualite.set_text(stream(mensualite));
    coutTotal = pret.cout_total(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), duree);
    m_coutTotal.set_text(stream(coutTotal));
    break;
  case 3: //taux
    tx = pret.calcul_taux(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), duree);
    m_taux.set_text(stream(tx));
    coutTotal = pret.cout_total(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), duree);
    m_coutTotal.set_text(stream(coutTotal));
    break;
  case 4: //durée
    temps = pret.calcul_duree(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), taux);
    m_duree.set_text(stream(temps));
    coutTotal = pret.cout_total(sup_espace(m_capital.get_text()), sup_espace(m_mensualite.get_text()), std::stod(m_duree.get_text()));
    m_coutTotal.set_text(stream(coutTotal));
    break;
  default:
    std::cout << "Erreur calcul" << std::endl;
    break;
  }
}
double Fenetre::sup_espace(std::string entry)
{
  auto it{std::remove(std::begin(entry), std::end(entry), ' ')};
  entry.erase(it, std::end(entry));
  return std::stod(entry);
}
void Fenetre::on_clicked_clear()
{
  m_capital.set_text("");
  m_mensualite.set_text("");
  m_taux.set_text("");
  m_duree.set_text("");
  m_coutTotal.set_text("");
  m_capital.reset_im_context();
  m_mensualite.reset_im_context();
  m_taux.reset_im_context();
  m_duree.reset_im_context();
  m_coutTotal.reset_im_context();

  int choix{listeDeroulante.get_active_row_number()};
  if (choix == 1)
  {
    m_mensualite.grab_focus();
  }
  else
  {
    m_capital.grab_focus();
  }
}
void Fenetre::on_clicked_quitter()
{
  hide();
}