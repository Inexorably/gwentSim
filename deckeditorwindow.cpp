#include "deckeditorwindow.h"
#include "ui_deckeditorwindow.h"

#include <QDebug>

std::vector<QString> DeckEditorWindow::getDeck() const{
    std::vector<QString> deck;

    for (int i = 0; i < ui->deckTableWidget->rowCount(); ++i){
        deck.push_back(ui->deckTableWidget->item(i, 1)->text());
    }
    return deck;
}

DeckEditorWindow::DeckEditorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DeckEditorWindow)
{
    ui->setupUi(this);

    //*****************Settings creation on first time run**********
    QFile inSettings(SETTINGSFILENAME);

    if (inSettings.open(QFile::ReadOnly)){
        inSettings.close();
    }
    else{
        //Need to create the settings file as this is the first run and no settings file exists.
        //Write to csv file.
        //Forr some reason, if we don't specify the directory, this will save in the build folder, not in \debug.
        QFile outSettings(SETTINGSFILENAME);
        //Settings are seperated by newlines.
        /*bool multithread default 1
         *bool run n iterations default 0
         *int n iterations default 5000
         *bool run until error default 1
         *double error default 1
         * int r1 length
         * int r2 length
         * bool vary round
         * bool vary round length
        */
        QString settings = "1\n0\n5000\n1\n1\n6\n4\n1\n3";
        if(outSettings.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&outSettings);
            out << settings;
            outSettings.close();
        }
    }

    //*****************Load Card List*******************************
    loadCards();

    //*****************Base Widget Setup****************************

    //Set default text on QLineEdit object on search bar.
    ui->cardSelectionLineEdit->setPlaceholderText("Card Name");

    //Set up deck list table.
    ui->deckTableWidget->setColumnCount(2);
    ui->deckTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //We begin working with an untitled deck.
    currentDeckFilename = "untitled deck";
    this->setWindowTitle(DECKBUILDERWINDOWTITLE + currentDeckFilename);
}

DeckEditorWindow::~DeckEditorWindow()
{
    delete ui;
}

void DeckEditorWindow::on_spawnComboWindowButton_clicked(){
    //Save the deck if it's not empty.
    if (ui->deckTableWidget->rowCount() != 0){
        on_actionSave_deck_triggered();
    }

    QString passedFilename = currentDeckFilename;


    //If the deck list is empty in the table widget, force the user to open a .gwc.  Load the csv from the gwc into the deckEditorWindow, and the gwc into the comboEditorWindow.
    if (ui->deckTableWidget->rowCount() == 0){
        //We need to load the .gwc file, and then import the filenames from it to import the needed information.

        //Get the filename.
        QString openName = QFileDialog::getOpenFileName(this, tr("GWC file"), qApp->applicationDirPath (),tr("GWC File (*.gwc)"));

        if (openName.isEmpty()){
            return;
        }

        QString data;
        QFile infile(openName);
        QStringList fileList;

        if (infile.open(QFile::ReadOnly)){
            data = infile.readAll();
            fileList = data.split("\n");
            infile.close();
        }

        //Order (see save function) is combo, value, deck.
        importCsvToTable(*ui->deckTableWidget, fileList[2]);
        this->setWindowTitle(DECKBUILDERWINDOWTITLE + fileList[2]);
        currentDeckFilename = fileList[2];
        passedFilename = openName;
    }

    //this->hide();
    ComboEditorWindow *comboEditor = new ComboEditorWindow(this->getDeck(), passedFilename, cardList);
    comboEditor->show();

}

void DeckEditorWindow::on_cardSelectionLineEdit_editingFinished(){

}

void DeckEditorWindow::on_addPushButton_clicked(){
    //We first check if we can add anymore copies to the deck.
    QString name = ui->cardSelectionComboBox->currentText();
    bool alreadyInDeck = false;
    for (int i = 0; i < ui->deckTableWidget->rowCount(); ++i){
        if (ui->deckTableWidget->item(i, 1)->text() == name){
            alreadyInDeck = true;
            //There are either 1 or 2 copies of the card in the deck.
            if (ui->deckTableWidget->item(i, 0)->text().toInt() == 1){
                ui->deckTableWidget->setItem(i,0,new QTableWidgetItem("2"));
            }
            //Else do nothing as we can't have more than two copies in the deck.
        }
    }
    //If it wasn't in the deck already, we insert into the deck.
    if (!alreadyInDeck){
        ui->deckTableWidget->setRowCount(ui->deckTableWidget->rowCount()+1);
        ui->deckTableWidget->setItem(ui->deckTableWidget->rowCount()-1, 0, new QTableWidgetItem("1"));
        ui->deckTableWidget->setItem(ui->deckTableWidget->rowCount()-1, 1, new QTableWidgetItem(name));
    }
}

void DeckEditorWindow::on_removePushButton_clicked(){
    //Get row of selected item.
    QModelIndexList indexList = ui->deckTableWidget->selectionModel()->selectedIndexes();
    int row = 0;
    if (indexList.empty())
        return;
    foreach(QModelIndex index, indexList){
        row = index.row();
    }

    //If there are 2 we just change "2" to "1".
    if ("2" == ui->deckTableWidget->item(row, 0)->text()){
        ui->deckTableWidget->setItem(row, 0, new QTableWidgetItem("1"));
    }
    //If there is 1 we remove the row.
    else{
        ui->deckTableWidget->removeRow(row);
    }
}

void DeckEditorWindow::on_actionSave_deck_as_triggered(){
    //Get the filename.
    QString filename = QFileDialog::getSaveFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)"));
    if (filename.isEmpty())
        return;
    exportTableToCsv(*ui->deckTableWidget, filename);
    this->setWindowTitle(DECKBUILDERWINDOWTITLE + filename);
    currentDeckFilename = filename;
}

void DeckEditorWindow::on_actionOpen_deck_triggered(){
    //Get the filename.
    QString filename = QFileDialog::getOpenFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)"));
    if (filename.isEmpty())
        return;
    importCsvToTable(*ui->deckTableWidget, filename);
    this->setWindowTitle(DECKBUILDERWINDOWTITLE + filename);
    currentDeckFilename = filename;
}

void DeckEditorWindow::on_actionSave_deck_triggered(){
    if (currentDeckFilename == "untitled deck"){
        QString filename = QFileDialog::getSaveFileName(this, tr("CSV file"), qApp->applicationDirPath (),tr("CSV File (*.csv)"));
        exportTableToCsv(*ui->deckTableWidget, filename);
        this->setWindowTitle(DECKBUILDERWINDOWTITLE + filename);
        currentDeckFilename = filename;
    }
    else
        exportTableToCsv(*ui->deckTableWidget, currentDeckFilename);
}

void DeckEditorWindow::on_actionNew_deck_triggered(){
    currentDeckFilename = "untitled deck";
    this->setWindowTitle(DECKBUILDERWINDOWTITLE + currentDeckFilename);
    ui->deckTableWidget->clear();
    ui->deckTableWidget->setRowCount(0);
}

void DeckEditorWindow::on_actionSettings_triggered(){
    SettingsWindow *settings = new SettingsWindow();
    settings->setModal(true);
    settings->exec();
}

//Load the cards from cards.crd into the cardList member variable.
void DeckEditorWindow::loadCards(){
    QString data;
    QFile infile(CARDLISTFILENAME);
    QStringList tempCardList;
    QStringList rowData;

    if (infile.open(QFile::ReadOnly)){
        data = infile.readAll();
        tempCardList = data.split("\n");
        infile.close();
    }

    //Sort the cardList alphabetically (lmao).
    tempCardList.sort(Qt::CaseInsensitive);

    //Push the cards into the cardList vector, and update the comboBox with the list of cards.
    //columns in cards.crd should be: name, provisions, basePoints... adding more as implement simulation.
    //commas appear in some names, so a different char should be used to seperate values.  Using '|' tentatively.
    cardList.clear();
    ui->cardSelectionComboBox->clear();
    for (int i = 0; i < tempCardList.size(); ++i){
        //We are now in a row separated by | chars.
        rowData = tempCardList[i].split("|");
        ui->cardSelectionComboBox->addItem(rowData[0]);
        cardList.push_back(GwentCard(rowData[0], rowData[1].toInt(), rowData[2].toDouble()));
    }
}

void DeckEditorWindow::on_cardSelectionLineEdit_textChanged(const QString &arg1){
    ui->cardSelectionComboBox->clear();
    for (size_t i = 0; i < cardList.size(); ++i){
        if (cardList[i].name.contains(arg1, Qt::CaseInsensitive)){
            ui->cardSelectionComboBox->addItem(cardList[i].name);
        }
    }
}
