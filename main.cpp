#include "Fenetre.h"
#include <gtkmm-3.0/gtkmm/application.h>

int main(int argc, char *argv [])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  Fenetre fenetre;

  return app->run(fenetre);
}