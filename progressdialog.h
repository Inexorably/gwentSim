#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>

#include <vector>

#include "gwentcard.h"
#include "gwentcardcombo.h"
#include "simthread.h"
#include "gwentscenario.h"

//Note: This class will run simulations based on gwentcalc.set and passed decks / combos upon initalization in a worker thread.

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(const std::vector<GwentCard> &deckTemp, const std::vector<GwentCardCombo> &combosTemp, QWidget *parent = nullptr);
    ~ProgressDialog();

    std::vector<GwentCard> deck;
    std::vector<GwentCardCombo> combos;

private:
    Ui::ProgressDialog *ui;

};

#endif // PROGRESSDIALOG_H
