#ifndef COMBOEDITORWINDOW_H
#define COMBOEDITORWINDOW_H

#include "globals.h"
#include "utilities.h"
#include "settingswindow.h"
#include "gwentcard.h"
#include "gwentcardcombo.h"
#include "dialog.h"
#include "simthread.h"
#include "progressdialog.h"

#include <QDialog>
#include <QMainWindow>
#include <QToolBar>
#include <QCompleter>
#include <QtMath>



//#include "deckeditorwindow.h"
//This is included in the source cpp file to prevent cross reference problems with the include guards.

namespace Ui {
class ComboEditorWindow;
}

class ComboEditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ComboEditorWindow(QWidget *parent = nullptr);
    ComboEditorWindow(std::vector<QString> deck, QString filename, std::vector<GwentCard> passedCards, QWidget *parent = nullptr);
    ~ComboEditorWindow();

public slots:


private slots:
    void on_addComboButton_clicked();

    void on_removeComboButton_clicked();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSettings_triggered();

    void on_cardSelectionLineEdit_editingFinished();

    void on_cardSelectionLineEdit_textChanged(const QString &arg1);

    void on_actionRun_triggered();

signals:

    void textChanged(const QString &arg1);

private:
    Ui::ComboEditorWindow *ui;

    QString filename;
    std::vector<QString> cardsInDeck;

    std::vector<GwentCard> allCards;    //All cards in game, including ones not present in deck.

};

#endif // COMBOEDITORWINDOW_H
