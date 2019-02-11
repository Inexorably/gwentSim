#include "progressdialog.h"
#include "ui_progressdialog.h"

ProgressDialog::ProgressDialog(const std::vector<GwentCard> &deckTemp, const std::vector<GwentCardCombo> &combosTemp, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    deck = deckTemp;
    combos = combosTemp;

    GwentScenario pkg(deck, combos);

    //Begin worker thread for simulations.  Initalize, and then call start which calls run().
    SimThread *sim = new SimThread(pkg);

    //Connect the signal for updating the progress bar to the signals emited by the thread.
    connect(sim, SIGNAL(percentChanged(int)), ui->progressBar, SLOT(setValue(int)));

    //Call start() which calls run().
    sim->start();
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}
