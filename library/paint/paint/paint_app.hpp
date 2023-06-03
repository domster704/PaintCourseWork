#ifndef PAINTTEST_PAINT_APP_HPP
#define PAINTTEST_PAINT_APP_HPP

#include <QMainWindow>
#include <QHBoxLayout>
#include "paint.hpp"

class PaintApp : public QMainWindow {
Q_OBJECT

public:
    explicit PaintApp(QWidget *parent = nullptr);

    ~PaintApp() override;

    void AddPaletteButtons(QHBoxLayout *layout);

    void AddFunctionButton(QHBoxLayout *layout);

    void SetSize();


public slots:

    void SetColor();

    void CreateRectangle();

    void CreateRoundedRectangle();

    void CreateEllipse() {}

    void SetPen();

    void SetSpray();

    void SetWidth();

    void CreateLine();

    void CreatePoint();

    void CreateText();

    void CreatePie();

    void CreateArc();

    void CreateChord();

    void CreatePolygon();

    void CreateImage();

    void Clear();

    void Save();

public:
    Canvas *canvas_ = new Canvas();

    int width_ = 1200;
    int height_ = 800;
};

#endif //PAINTTEST_PAINT_APP_HPP
