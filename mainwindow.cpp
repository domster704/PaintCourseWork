#include "mainwindow.h"
#include <vector>

std::vector<std::string> COLOR {
   "#000000",
   "#141923",
   "#414168",
   "#3a7fa7",
   "#35e3e3",
   "#8fd970",
   "#5ebb49",
   "#458352",
   "#dcd37b",
   "#fffee5",
   "#ffd035",
   "#cc9245",
   "#a15c3e",
   "#a42f3b",
   "#f45b7a",
   "#c24998",
   "#81588d",
   "#bcb0c2",
   "#ffffff"
};
const int rowIndexForPalleteButtons = 0;
const int rowIndexForFunctionButtons = 1;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    this->setWindowTitle("Paint");
    QWidget* widget = new QWidget();
    QGridLayout* mainForm = new QGridLayout(widget);

    mainForm->addWidget(canvas, rowIndexForFunctionButtons + 1, 0, COLOR.size(), COLOR.size());
    addPaletteButtons(mainForm);
    addFunctionButton(mainForm);

    setCentralWidget(widget);
    setMinimumSize(640, 480);

    /*delete mainForm;
    delete widget;
    delete palette;*/
}

MainWindow::~MainWindow() {
    delete canvas;
}

void MainWindow::addPaletteButtons(QGridLayout* layout) {
    int i = 0;
    for (std::string c : COLOR) {
        PaletteButton* button = new PaletteButton(this, c);
        QObject::connect(button, SIGNAL (clicked()), this, SLOT(setColor()));
        layout->addWidget(button, rowIndexForPalleteButtons, i++, Qt::AlignTop | Qt::AlignLeft);
    }
}

void MainWindow::addFunctionButton(QGridLayout* layout) {
    std::vector<std::pair<std::string, void(MainWindow::*)()>> functionButtonName {
        {"Rectangle", &MainWindow::rectangle}
    };
    int index = 0;
    for (std::pair i : functionButtonName) {
        QPushButton* funcButton = new QPushButton(this);
        funcButton->setText(QString::fromStdString(i.first));
        QObject::connect(funcButton, SIGNAL(clicked()), this, SLOT(rectangle()));
        layout->addWidget(funcButton, rowIndexForPalleteButtons, COLOR.size() + index++, Qt::AlignTop | Qt::AlignLeft);
    }
}

