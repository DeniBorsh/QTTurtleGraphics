#pragma once
#include <QtWidgets>
#include <QJSEngine>
#include "turtle.h"

class TurtleWorkArea : public QWidget {
Q_OBJECT
public:
    explicit TurtleWorkArea(QWidget *parent = nullptr);

private slots:
    void slotEvaluate();
    void slotApplyCode(int);

private:
    QTextEdit* m_text;
    QJSEngine m_scriptEngine;
    Turtle* m_turtle;

};

