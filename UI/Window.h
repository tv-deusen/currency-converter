#include<gtkmm/window.h>
#include<gtkmm/button.h>

class CurrencyConverterWindow : public Gtk::Window
{
public:
    CurrencyConverterWindow();
    virtual ~CurrencyConverterWindow();

protected:
    // Signal handlers
    void OnCalculateClicked();
    void OnClearClicked();
    
    // Member widgets
    Gtk::Button MCalculate;
    Gtk::Button MClear;
};