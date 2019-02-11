#include "utilities.h"

void importCsvToTable(QTableWidget &table, const QString &filename){
    //QString fileName = QFileDialog::getOpenFileName(this, ("Open File"), "/home", ("csv File(*.csv)"));
    QString data;
    QFile importedCSV(filename);
    QStringList rowOfData;
    QStringList rowData;
    data.clear();
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly)){
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    //Allocate memory for table (rows).  Columns are allocated when we split the first row.
    table.setRowCount(rowOfData.size()-1);

    for (int x = 0; x < rowOfData.size(); x++){
        rowData = rowOfData.at(x).split(CARDLISTSEPARATOR);
        //Allocate width axis memory now that we know how many columns there are.
        if (x == 0){
            table.setColumnCount(rowData.size()-1);
        }
        for (int y = 0; y < rowData.size(); y++){
            table.setItem(x, y, new QTableWidgetItem(rowData[y]));
        }
    }
}

void exportTableToCsv(const QTableWidget &table, const QString &filename){
    //Loop through rows / columns and create a csv style string.
    QString textData;
    for (int i = 0; i < table.rowCount(); i++) {
        for (int j = 0; j < table.columnCount(); j++) {
            //Account for the possibility of an empty cell, in which case checking item->text() will cause a crash.
            if (table.item(i, j)){
                textData += table.item(i, j)->text();
            }
            textData += CARDLISTSEPARATOR;
        }
        textData += "\n";
    }

    //Write to csv file.
    QFile csvFile(filename);
    if(csvFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&csvFile);
        out << textData;

        csvFile.close();
    }
}
