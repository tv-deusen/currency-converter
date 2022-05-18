#ifndef CC_UI_WINDOW_H
#define CC_UI_WINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/textview.h>
#include <gtkmm/window.h>
#include "Fetcher.h"

class CurrencyConverterWindow : public Gtk::Window
{
public:
    CurrencyConverterWindow(const Fetcher& Fetcher);
    virtual ~CurrencyConverterWindow();

protected:
    // Signal handlers
    void OnCalculateClicked();
    void OnClearClicked();
    void OnBaseCurrencyChanged();
    void OnTargetCurrencyChanged();
    void OnCellDataExtra(const Gtk::TreeModel::const_iterator& Iter);

    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
        public:
            ModelColumns()
            { add(MCurrencyCode); add(MCurrencyName); }

            Gtk::TreeModelColumn<Glib::ustring> MCurrencyCode;
            Gtk::TreeModelColumn<Glib::ustring> MCurrencyName;
    };

private:

    void PopulateComboBoxes();

    ModelColumns MColumns;
    
    // Member widgets
    Gtk::ComboBox MBaseCombo;
    Gtk::ComboBox MTargetCombo;
    Gtk::CellRendererText MCell;
    Glib::RefPtr<Gtk::ListStore> MRefListModel;
    Gtk::Grid MGrid;
    Gtk::Button MCalculate;
    Gtk::Button MClear;
    Gtk::TextView MBaseTextView;
    Gtk::TextView MTargetTextView;
    Fetcher MFetcher;
};

#endif