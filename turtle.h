#pragma once
#include <QtWidgets>

class Turtle : public QWidget {
Q_OBJECT
public:
    Turtle(QWidget *parent = nullptr)
        : QWidget{parent}
        , m_pix{400, 400}
        , m_painter{&m_pix}
    {
        setFixedSize(m_pix.size());
        init();
    }

public slots:
    void forward(int n) {
        m_painter.drawLine(0, 0, n, 0);
        m_painter.translate(n, 0);
        repaint();
    }

    void back(int n) {
        m_painter.drawLine(0, 0, -n, 0);
        m_painter.translate(-n, 0);
        repaint();
    }

    void left(int angle) { m_painter.rotate(-angle); }
    void right(int angle) { m_painter.rotate(angle); }

    void reset() {
        m_painter.resetTransform();
        init();
        repaint();
    }

protected:
    void init() {
        m_pix.fill(Qt::yellow);
        m_painter.translate(rect().center());
        m_painter.rotate(-90);
    }

    virtual void paintEvent(QPaintEvent*) {
        QPainter painter(this);
        painter.drawPixmap(rect(), m_pix);
    }

private:
    QPixmap m_pix;
    QPainter m_painter;

};

