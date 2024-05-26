#include "turtleworkarea.h"

TurtleWorkArea::TurtleWorkArea(QWidget *parent)
    : QWidget{parent}
{
    m_turtle = new Turtle;
    m_turtle->setFixedSize(400, 400);
    m_text = new QTextEdit;

    QComboBox* comboBox = new QComboBox;
    QStringList list;

    list << "Haus vom Nikolaus" << "Curly" << "Circle" << "Fantasy";
    comboBox->addItems(list);
    connect(comboBox, SIGNAL(activated(int)), SLOT(slotApplyCode(int)));
    slotApplyCode(0);

    QJSValue scriptTurtle = m_scriptEngine.newQObject(m_turtle);
    m_scriptEngine.globalObject().setProperty("turtle", scriptTurtle);

    QPushButton* evaluateBtn = new QPushButton("&Evaluate");
    connect(evaluateBtn, SIGNAL(clicked(bool)), SLOT(slotEvaluate()));

    QGridLayout* grid = new QGridLayout;

    grid->addWidget(comboBox, 0, 0);
    grid->addWidget(m_text, 1, 0);
    grid->addWidget(m_turtle, 0, 1, 2, 1);
    grid->addWidget(evaluateBtn, 2, 0, 1, 2);
    setLayout(grid);
}

void TurtleWorkArea::slotEvaluate() {
    QJSValue result = m_scriptEngine.evaluate(m_text->toPlainText());
    if (result.isError())
        QMessageBox::critical(0, "Evaluating error", result.toString(), QMessageBox::Yes);
}

void TurtleWorkArea::slotApplyCode(int n) {
    QString code;
    switch (n) {
    case 0:
        code = "var k = 100;\n"
               "turtle.reset();\n"
               "turtle.right(90);\n"
               "turtle.back(-k);\n"
               "turtle.left(90);\n"
               "turtle.forward(k);\n"
               "turtle.left(30);\n"
               "turtle.forward(k);\n"
               "turtle.left(120);\n"
               "turtle.forward(k);\n"
               "turtle.left(30);\n"
               "turtle.forward(k);\n"
               "turtle.left(135);\n"
               "turtle.forward(Math.sqrt(2)*k);\n"
               "turtle.left(135);\n"
               "turtle.forward(k);\n"
               "turtle.left(135);\n"
               "turtle.forward(Math.sqrt(2)*k);\n";
        break;
    case 1:
        code = "turtle.reset();\n"
               "for (var i = 0; i < 2; ++i) {\n"
               "  for (var j = 0; j < 100; ++j) {\n"
               "    turtle.forward(15);\n"
               "    turtle.left(100 - j);\n"
               "  }\n"
               "  turtle.right(180);\n"
               "}\n";
        break;
    case 2:
        code = "turtle.circle = function() {\n"
               "  for (var i = 0; i < 360; ++i) {\n"
               "    this.forward(1);\n"
               "    turtle.left(1);\n"
               "  }\n"
               "}\n"
               "turtle.reset();\n"
               "turtle.circle();\n";
        break;
    default:
        code = "turtle.reset();\n"
               "for (var i = 0; i < 200; ++i) {\n"
               "  turtle.forward(i*2);\n"
               "  turtle.left(91);\n"
               "}\n";
    }
    m_text->setPlainText(code);
}
