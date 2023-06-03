#include "paint/paint.hpp"

Canvas::Canvas(QWidget *parent) : QLabel(parent), spray_(false), width_(3) {
    canvasImage_ = QImage(this->size(), QImage::Format_RGB32);
    canvasImage_.fill(Qt::white);
    penColor_ = QColor(0, 0, 0);
}

void Canvas::mouseMoveEvent(QMouseEvent *e) {
    if (lastPoint_.isNull()) {
        UpdateLastCoords(e);
        return;
    }

    QPainter painter(&canvasImage_);
    QPen p(penColor_, width_, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(p);

//    if (!spray_) {
        painter.drawLine(lastPoint_, e->pos());
        painter.end();
//    } else {
//        for (int i = 0; i < SPRAY_PARTICLES; i++) {
//            int x0 = GetGaussianRand(0, SPRAY_DIAMETER);
//            int y0 = GetGaussianRand(0, SPRAY_DIAMETER);
//            auto point = e->position();
//            painter.drawPoint(point.x() + x0, point.y() + y0);
//        }
//        painter.end();
//    }

    UpdateLastCoords(e);
    this->update();
}

void Canvas::resizeEvent(QResizeEvent *event) {
    canvasImage_ = QImage(this->size(), QImage::Format_RGB32);
    canvasImage_.fill(Qt::white);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint_ = event->pos();
    }
}

void Canvas::paintEvent(QPaintEvent *event) {
    QPainter canvasPainter(this);
    canvasPainter.drawImage(this->rect(), canvasImage_, canvasImage_.rect());
}

void Canvas::mouseReleaseEvent(QMouseEvent *e) {
    if (!isCreatingFigure_)
        return;
    // TODO: добавлять в массив точки нажатия для создания фигур
}

void Canvas::DrawFigures(const std::function<void(QPainter *)> f) {
    QPainter painter(&canvasImage_);
    QPen p(penColor_, width_);
    painter.setPen(p);

    f(&painter);
    painter.end();

    update();
}

void Canvas::ReImage() {
    canvasImage_ = QImage(this->size(), QImage::Format_RGB32);
    canvasImage_.fill(Qt::white);
    update();
}

void Canvas::UpdateLastCoords(QMouseEvent *e) {
    lastPoint_ = e->pos();
}

//int Canvas::GetGaussianRand(int lo, int hi) {
//    if (lo < hi) {
//        int range = hi - lo;
//        int val = (rand() % range + lo);
//        val += (rand() % range + lo);
//        val += (rand() % range + lo);
//        val += (rand() % range + lo);
//        float fVal = (float) val * 0.25f;
//        return (int) fVal;
//    } else {
//        return 0;
//    }
//}

void Canvas::SetPenColor(QColor c) {
    penColor_ = c;
}
