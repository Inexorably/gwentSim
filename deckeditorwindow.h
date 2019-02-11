#ifndef DECKEDITORWINDOW_H
#define DECKEDITORWINDOW_H

#include <QMainWindow>
#include <QString>

#include "comboeditorwindow.h"
#include "utilities.h"
#include "globals.h"
#include "gwentcard.h"

#include <vector>

namespace Ui {
class DeckEditorWindow;
}

class DeckEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit DeckEditorWindow(QWidget *parent = nullptr);
    ~DeckEditorWindow();

    //Get the contents of deck in QString.
    std::vector<QString> getDeck() const;

private slots:
    void on_spawnComboWindowButton_clicked();

    void on_cardSelectionLineEdit_editingFinished();

    void on_addPushButton_clicked();

    void on_removePushButton_clicked();

    void on_actionSave_deck_as_triggered();

    void on_actionOpen_deck_triggered();

    void on_actionSave_deck_triggered();

    void on_actionNew_deck_triggered();

    void on_actionSettings_triggered();

    void on_cardSelectionLineEdit_textChanged(const QString &arg1);

private:
    Ui::DeckEditorWindow *ui;

    //Load from the cards.crd file.
    void loadCards();

    //Card list does not currently need to be public -- combo editor does not need access to it.  In future if auto-optimisation implemented, can move to public.
    std::vector<GwentCard> cardList;
};

#endif // DECKEDITORWINDOW_H
