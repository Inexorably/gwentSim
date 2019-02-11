#ifndef UTILITIES_H
#define UTILITIES_H

#include "globals.h"

#include <QTableWidget>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>

#include <QDebug>

void importCsvToTable(QTableWidget &table, const QString &filename);
void exportTableToCsv(const QTableWidget &table, const QString &filename);

#endif // UTILITIES_H
