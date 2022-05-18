#include "Window.h"

CurrencyConverterWindow::CurrencyConverterWindow(const Fetcher& Fetcher)
    : MCalculate("Calculate"), MClear("Clear"), MFetcher{Fetcher}
{
    set_title("Currency Conversion");
    set_border_width(10);

    add(MGrid);

    MGrid.set_column_spacing(25);
    MGrid.set_row_spacing(25);
    MGrid.set_border_width(10);

    MRefListModel = Gtk::ListStore::create(MColumns);
    MBaseCombo.set_model(MRefListModel);
    MTargetCombo.set_model(MRefListModel);

    PopulateComboBoxes();

    MGrid.add(MBaseCombo);
    MBaseCombo.show();

    MGrid.add(MTargetCombo);
    MTargetCombo.show();
    MGrid.show();

    MCalculate.signal_clicked().connect(
            sigc::mem_fun(*this, &CurrencyConverterWindow::OnCalculateClicked)
        );
    MGrid.attach_next_to(MCalculate, MBaseCombo, Gtk::POS_BOTTOM);
    MCalculate.show();

    MClear.signal_clicked().connect(
        sigc::mem_fun(*this, &CurrencyConverterWindow::OnClearClicked)
    );
    MGrid.attach_next_to(MClear, MTargetCombo, Gtk::POS_BOTTOM);
    MClear.show();

    MBaseTextView.set_size_request(1, 50);
    MGrid.attach_next_to(MBaseTextView, MBaseCombo, Gtk::POS_TOP);
    MBaseTextView.show();

    MTargetTextView.set_size_request(1, 50);
    MGrid.attach_next_to(MTargetTextView, MTargetCombo, Gtk::POS_TOP);
    MTargetTextView.show();
}

CurrencyConverterWindow::~CurrencyConverterWindow()
{

}

void CurrencyConverterWindow::OnCalculateClicked()
{
    // Make a fetch to get rates
    // Update UI
    auto BaseAmount = MBaseTextView.get_buffer()->get_text();
    if (!BaseAmount.empty())
    {
        auto BaseCurrencyRow = *MBaseCombo.get_active();
        auto TargetCurrencyRow = *MTargetCombo.get_active();
        auto BaseCurrency = Glib::ustring{BaseCurrencyRow[MColumns.MCurrencyCode]};
        auto TargetCurrency = Glib::ustring{TargetCurrencyRow[MColumns.MCurrencyCode]};
        auto TargetAmount = MFetcher.GetExchangeRate(std::string{BaseCurrency},
                                                     std::string{TargetCurrency},
                                                     BaseAmount);
        MTargetTextView.get_buffer()->set_text(std::to_string(TargetAmount));
    }
}

void CurrencyConverterWindow::OnClearClicked()
{
    // Clear conversion selections
    MBaseTextView.get_buffer()->set_text("");
    MTargetTextView.get_buffer()->set_text("");
}

void CurrencyConverterWindow::PopulateComboBoxes()
{
    auto Symbols = MFetcher.GetCurrencySymbols();
    Gtk::TreeModel::Row row;
    for (auto& Symbol : Symbols)
    {
        row = *(MRefListModel->append());
        row[MColumns.MCurrencyCode] = Symbol.first;
        row[MColumns.MCurrencyName] = Symbol.second;
    }
    MBaseCombo.pack_start(MColumns.MCurrencyName);
    MBaseCombo.pack_start(MColumns.MCurrencyCode);
    MTargetCombo.pack_start(MColumns.MCurrencyName);
    MTargetCombo.pack_start(MColumns.MCurrencyCode);
    MBaseCombo.set_cell_data_func(MCell,
        sigc::mem_fun(*this, &CurrencyConverterWindow::OnCellDataExtra));
    MTargetCombo.set_cell_data_func(MCell,
        sigc::mem_fun(*this, &CurrencyConverterWindow::OnCellDataExtra));
}

void CurrencyConverterWindow::OnCellDataExtra(const Gtk::TreeModel::const_iterator& Iter)
{

}