#include <gtkmm/application.h>
#include <glibmm/refptr.h>
#include "App.h"
#include "Window.h"

int RunApp(int argc, char * argv[], std::string AppId, const Fetcher& Fetcher)
{
    Glib::RefPtr<Gtk::Application> App = Gtk::Application::create(argc, argv, AppId);

    CurrencyConverterWindow Window = CurrencyConverterWindow(Fetcher);

    return App->run(Window);
}