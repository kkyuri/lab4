#include <QPushButton>
#include "simplecalculator.h"
#include "ui_simplecalculator.h"
#include <QJSEngine>

SimpleCalculator::SimpleCalculator(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::SimpleCalculator) {
    ui->setupUi(this);

    connect(ui->button0, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button1, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button2, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button3, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button4, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button5, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button6, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button7, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button8, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->button9, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);

    connect(ui->buttonAdd, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->buttonSubtract, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->buttonMultiply, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->buttonDivide, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);

    connect(ui->buttonClear, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
    connect(ui->buttonEquals, &QPushButton::clicked, this, &SimpleCalculator::on_button_clicked);
}

SimpleCalculator::~SimpleCalculator() {
    delete ui;
}

void SimpleCalculator::on_button_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString buttonText = button->text();

        if (buttonText == "=") {
            QString expression = ui->lineEditDisplay->text();
            double result = evaluateExpression(expression);
            ui->lineEditDisplay->setText(QString::number(result));
        } else if (buttonText == "C") {
            ui->lineEditDisplay->clear();
        } else {
            ui->lineEditDisplay->insert(buttonText);
        }
    }
}

double SimpleCalculator::evaluateExpression(const QString &expression) {
    QJSEngine engine;
    return engine.evaluate(expression).toNumber();
}
