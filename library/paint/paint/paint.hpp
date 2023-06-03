#ifndef PAINT_PAINT_H
#define PAINT_PAINT_H

#include <random>
#include <QMainWindow>
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QDir>
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
#include <functional>

const int SPRAY_PARTICLES = 10;
const int SPRAY_DIAMETER = 10;

class Canvas : public QLabel {

Q_OBJECT

public slots:

    void SetPenColor(QColor c);

public:
    explicit Canvas(QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *e) override;

    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *e) override;

    void DrawFigures(std::function<void(QPainter *)> f);

//    void Polygon(std::array<std::array<int, 2>, 6> points) {
//        QPainter painter(this);
//        QPen p = painter.pen();
//        p.setWidth(width_);
//        p.setColor(penColor_);
//        painter.setPen(p);
//
//        QList<QPoint> qtPoints{};
//        for (std::array<int, 2> i: points) {
//            qtPoints.append(QPoint(i[0], i[1]));
//        }
//
//        painter.drawPolygon(QPolygon(qtPoints));
//        painter.end();
//    }

    void ReImage();

    // TODO: image

private:
    void UpdateLastCoords(QMouseEvent *e);

//    static int GetGaussianRand(int lo, int hi);

public:
    QImage canvasImage_;
    bool spray_;
    int width_;

    bool isCreatingFigure_ = false;
    int pointCountForCreatingFigure_ = 0;

private:
    QPoint lastPoint_;

    QColor penColor_;
};

#endif //PAINT_PAINT_H
