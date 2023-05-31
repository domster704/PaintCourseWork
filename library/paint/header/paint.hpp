//
// Created by isupo on 31.05.2023.
//

#ifndef PAINT_PAINT_H
#define PAINT_PAINT_H

#include <random>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPolygon>
#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QList>
#include <QMouseEvent>
#include <QtCore/QSize>
#include <QMessageBox>

#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>

const int SPRAY_PARTICLES = 10;
const int SPRAY_DIAMETER = 10;

class PaletteButton : public QPushButton {

    Q_OBJECT

public:
    explicit PaletteButton(QWidget *parent = nullptr, const std::string& color="#000") : QPushButton(parent), color(color) {
        this->setFixedSize(QSize(SIDE_SIZE, SIDE_SIZE));
        this->setStyleSheet(QString::fromStdString("background-color: ") + QString::fromStdString(color));
    };

    std::string color;

private:
    const int SIDE_SIZE = 24;
};

class Canvas : public QLabel {

    Q_OBJECT

public slots:
    void setPenColor(QColor c) {
        penColor = c;
    }

public:
    explicit Canvas(QWidget *parent = nullptr) : QLabel(parent), spray(false), width(3) {
        canvasImage = QImage(this->size(), QImage::Format_RGB32);
        canvasImage.fill(Qt::white);
        penColor = QColor(0, 0, 0);
    }

    void mouseMoveEvent(QMouseEvent *e) override {
        if (lastX == -1) {
            updateLastCoords(e);
            return;
        }

        QPainter painter(&canvasImage);
        QPen p(penColor, width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);

        if (!spray) {
            painter.drawLine(lastPoint, e->pos());
            painter.end();
        }
        else {
            for (int i = 0; i < SPRAY_PARTICLES; i++) {
                int x0 = getGaussianRand(0, SPRAY_DIAMETER);
                int y0 = getGaussianRand(0, SPRAY_DIAMETER);
                painter.drawPoint(e->x() + x0, e->y() + y0);
            }
        }

        updateLastCoords(e);
        this->update();
    }

    void resizeEvent(QResizeEvent *event) override {
        canvasImage = QImage(this->size(), QImage::Format_RGB32);
        canvasImage.fill(Qt::white);
    }

    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            lastPoint = event->pos();
        }
    }

    void paintEvent(QPaintEvent *event) override {
        QPainter canvasPainter(this);
        canvasPainter.drawImage(this->rect(), canvasImage, canvasImage.rect());
    }


    void mouseReleaseEvent(QMouseEvent *e) override {
        lastX = -1;
        lastY = -1;
    }

    void Rectangle(std::array<int, 4> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawRect(points[0],
                         points[1],
                         points[2],
                         points[3]);
        painter.end();
    }

    void RoundRectangle(std::array<int, 6> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawRoundedRect(points[0],
                                points[1],
                                points[2],
                                points[3],
                                points[4],
                                points[5]);
        painter.end();
    }

    void Line(std::array<int, 4> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawLine(points[0],
                         points[1],
                         points[2],
                         points[3]);
        painter.end();
    }

    void Point(std::array<int, 2> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawPoint(points[0],
                          points[1]);
        painter.end();
    }

    void Text(std::array<int, 2> points, QString text) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawText(points[0],
                         points[1], text);
        painter.end();
    }

    void Pie(std::array<int, 6> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawPie(points[0],
                         points[1],
                         points[2],
                         points[3],
                         points[4],
                         points[5]);
        painter.end();
    }

    void Arc(std::array<int, 6> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawArc(points[0],
                        points[1],
                        points[2],
                        points[3],
                        points[4],
                        points[5]);
        painter.end();
    }

    void Chord(std::array<int, 6> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);
        painter.drawChord(points[0],
                        points[1],
                        points[2],
                        points[3],
                        points[4],
                        points[5]);
        painter.end();
    }

    void Polygon(std::array<std::array<int, 2>, 6> points) {
        QPainter painter(this);
        QPen p = painter.pen();
        p.setWidth(width);
        p.setColor(penColor);
        painter.setPen(p);

        QList<QPoint> qtPoints{};
        for (std::array<int, 2> i : points) {
            qtPoints.append(QPoint(i[0], i[1]));
        }

        painter.drawPolygon(QPolygon(qtPoints));
        painter.end();
    }

    // TODO: image

private:
    void updateLastCoords(QMouseEvent *e) {
        lastPoint = e->pos();
        lastX = e->x();
        lastY = e->y();
    }

    int getGaussianRand(int lo, int hi) {
        if ( lo < hi )	{
            int range = hi - lo;
            int val = (rand() % range + lo);
            val += (rand() % range + lo);
            val += (rand() % range + lo);
            val += (rand() % range + lo);
            float fVal = (float)val * 0.25f;
            return (int) fVal;
        } else {
            return 0;
        }
    }

private:
    QImage canvasImage;
    QPoint lastPoint;

    int lastX{-1}, lastY{-1};
    bool spray;
    int width;

    QColor penColor;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPaletteButtons(QGridLayout* layout);
    void addFunctionButton(QGridLayout* layout);


public slots:
    void setColor() {
        canvas->setPenColor(QColor(QString::fromStdString(((PaletteButton*)sender())->color)));
    }

    void rectangle() {}
    void roundedRectangle() {}
    void ellipse() {}
    void pen() {}
    void spray() {}
    void setWidth() {}
    void line() {}
    void point() {}
    void text() {}
    void pie() {}
    void arc() {}
    void chord() {}
    void polygon() {}
    void image() {}
    void clear() {}
    void save() {}

public:
    Canvas* canvas = new Canvas();
};

#endif //PAINT_PAINT_H
