#include "paint/paint_app.hpp"
#include "paint/palette_button.hpp"

#include <QFileDialog>
#include <iostream>

std::vector<std::string> COLOR{
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

const int WIDTH = 1200;
const int HEIGHT = 600;

PaintApp::PaintApp(QWidget *parent) : QMainWindow(parent) {
    this->setWindowTitle("Paint");
    SetSize();

    auto *widget = new QWidget();
    auto *vLayout = new QVBoxLayout(widget);
    auto *topLayout = new QHBoxLayout();
    auto *colorLayout = new QHBoxLayout();
    auto *functionButtonLayout = new QHBoxLayout();

    topLayout->addWidget(canvas_);
    AddPaletteButtons(colorLayout);
    AddFunctionButton(functionButtonLayout);

    vLayout->addLayout(topLayout);
    vLayout->addLayout(colorLayout);
    vLayout->addLayout(functionButtonLayout);

    setCentralWidget(widget);
    setFixedSize(width_, height_);

    /*delete mainForm;
    delete widget;
    delete palette;*/
}

PaintApp::~PaintApp() {
    delete canvas_;
}

void PaintApp::AddPaletteButtons(QHBoxLayout *layout) {
    layout->addStretch();
    for (std::string c: COLOR) {
        auto *button = new PaletteButton(this, c);
        QObject::connect(button, SIGNAL (clicked()), this, SLOT(SetColor()));

        layout->addWidget(button);
        layout->addStretch();
    }
}

void PaintApp::AddFunctionButton(QHBoxLayout *layout) {
    std::vector<std::pair<std::string, void (PaintApp::*)()>> functionButtonName{
            {"Rectangle", &PaintApp::CreateRectangle},
            {"Rounded R", &PaintApp::CreateRoundedRectangle},
            {"Ellipse",   &PaintApp::CreateEllipse},
            {"Pen",       &PaintApp::SetPen},
//            {"Spray",     &PaintApp::SetSpray},
            {"Width",     &PaintApp::SetWidth},
            {"Line",      &PaintApp::CreateLine},
            {"Point",     &PaintApp::CreatePoint},
            {"Text",      &PaintApp::CreateText},
            {"Pie",       &PaintApp::CreatePie},
            {"Arc",       &PaintApp::CreateArc},
            {"Chord",     &PaintApp::CreateChord},
//            {"Polygon",   &PaintApp::CreatePolygon},
            {"Image",     &PaintApp::CreateImage},
            {"Clear",     &PaintApp::Clear},
            {"Save",      &PaintApp::Save},
    };

    layout->addStretch();
    for (std::pair buttonData: functionButtonName) {
        auto *funcButton = new QPushButton(this);
        funcButton->setText(QString::fromStdString(buttonData.first));
        QObject::connect(funcButton, &QPushButton::clicked, this, buttonData.second);

        layout->addWidget(funcButton);
        layout->addStretch();
    }
}

void PaintApp::Clear() {
    canvas_->ReImage();
}

void PaintApp::SetColor() {
    canvas_->SetPenColor(QColor(QString::fromStdString(((PaletteButton *) sender())->color)));
}

void PaintApp::CreateRectangle() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры прямоугольника"),
                                         tr("Координаты левого верхнего угла, ширина, высота"), QLineEdit::Normal,
                                         "10 10 100 100", &ok);
    if (ok && !text.isEmpty()) {
        QList<int> res{};
        for (QString i: text.split(" ")) {
            res.append(i.toInt());
        }
        if (res.size() == 4) {
            canvas_->DrawFigures([&res](QPainter *painter) {
                painter->drawRect(res[0],
                                  res[1],
                                  res[2],
                                  res[3]);
            });
        }
    }
}

void PaintApp::CreateRoundedRectangle() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры прямоугольника"),
                                         tr("Координаты левого верхнего угла, ширина, высота, радиус"),
                                         QLineEdit::Normal,
                                         "10 10 100 100 20", &ok);
    if (ok && !text.isEmpty()) {
        QList<int> res{};
        for (QString i: text.split(" ")) {
            res.append(i.toInt());
        }
        if (res.size() == 5) {
            canvas_->DrawFigures([&res](QPainter *painter) {
                painter->drawRoundedRect(res[0],
                                         res[1],
                                         res[2],
                                         res[3],
                                         res[4],
                                         res[4]);
            });
        }
    }
}

void PaintApp::SetPen() {
    canvas_->spray_ = false;
}

void PaintApp::SetSpray() {
    canvas_->spray_ = true;
}

void PaintApp::SetWidth() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Ширина кисти"),
                                         tr("Введите ширину кисти"),
                                         QLineEdit::Normal,
                                         "3", &ok);
    if (!ok || text.isEmpty())
        return;
    canvas_->width_ = text.toInt();
}

void PaintApp::CreateLine() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры линии"),
                                         tr("Координаты первой и второй"),
                                         QLineEdit::Normal,
                                         "10 10 100 100", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() == 4) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawLine(res[0],
                              res[1],
                              res[2],
                              res[3]);
        });
    }
}

void PaintApp::CreatePoint() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры точки"),
                                         tr("Координаты точки"),
                                         QLineEdit::Normal,
                                         "50 50", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() == 4) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawPoint(res[0],
                               res[1]);
        });
    }
}

void PaintApp::CreateText() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры текста"),
                                         tr("Координаты начала строки и текст"),
                                         QLineEdit::Normal,
                                         "100 100 Hello World", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<QString> list = text.split(" ");
    QList<QString> res{};
    res.append(list[0]);
    res.append(list[1]);
    res.append(text.remove(0, list[0].size() + 1 + list[1].size()));
    if (res.size() == 3) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawText(res[0].toInt(),
                              res[1].toInt(),
                              res[2]);
        });
    }

}

void PaintApp::CreatePie() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры сектора"),
                                         tr("Координаты левого верхнего угла, ширина, высота,"
                                            "стартовый угол, конечный угол"),
                                         QLineEdit::Normal,
                                         "100 100 200 300 20 90", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() == 6) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawPie(res[0],
                             res[1],
                             res[2],
                             res[3],
                             res[4],
                             res[5]);
        });
    }
}

void PaintApp::CreateArc() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры дуги"),
                                         tr("Координаты левого верхнего угла,"
                                            " ширина, высота, стартовый угол,"
                                            " конечный угол"),
                                         QLineEdit::Normal,
                                         "100 100 200 300 0 360", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() == 6) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawArc(res[0],
                             res[1],
                             res[2],
                             res[3],
                             res[4],
                             res[5]);
        });
    }
}

void PaintApp::CreateChord() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры кругового сегмента"),
                                         tr("Координаты левого верхнего"
                                            " угла, ширина, высота, стартовый угол,"
                                            " конечный угол"),
                                         QLineEdit::Normal,
                                         "100 100 200 300 0 360", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() == 6) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawChord(res[0],
                               res[1],
                               res[2],
                               res[3],
                               res[4],
                               res[5]);
        });
    }
}

void PaintApp::CreatePolygon() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Параметры многоугольника"),
                                         tr("Координаты каждой вершины многоугольника"
                                            "(координаты - через запятые,"
                                            " точки - через пробел)"),
                                         QLineEdit::Normal,
                                         "100 100 200 300 0 360", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<int> res{};
    for (QString i: text.split(" ")) {
        res.append(i.toInt());
    }
    if (res.size() >= 3) {
        canvas_->DrawFigures([&res](QPainter *painter) {
            painter->drawChord(res[0],
                               res[1],
                               res[2],
                               res[3],
                               res[4],
                               res[5]);
        });
    }
}

void PaintApp::CreateImage() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Выбрать фото"));
    if (fileName.isEmpty())
        return;

    auto image = QImage();
    image.load(fileName);
    canvas_->canvasImage_ = image;
    update();
}

void PaintApp::Save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить как"),
                                                    tr("img.png"),
                                                    tr("Image Files (*.png *.jpg)"));
    if (fileName.isEmpty())
        return;

    canvas_->canvasImage_.save(fileName);
}

void PaintApp::SetSize() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Размеры"),
                                         tr("Ширина, высота"),
                                         QLineEdit::Normal,
                                         "1200 800", &ok);
    if (!ok || text.isEmpty())
        return;

    QList<QString> res = text.split(" ");
    width_ = res[0].toInt();
    height_ = res[1].toInt();
}
