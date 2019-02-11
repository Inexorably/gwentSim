#include "deckeditorwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Initialization functions occur here on program startup.
    //Main window.
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DisableWindowContextHelpButton);
    DeckEditorWindow deckEditor;


    deckEditor.show();

    return a.exec();
}
