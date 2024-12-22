#ifndef SIMPLECALCULATOR_H
#define SIMPLECALCULATOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class SimpleCalculator; }
QT_END_NAMESPACE

class SimpleCalculator : public QMainWindow {
    Q_OBJECT

public:
    SimpleCalculator(QWidget *parent = nullptr);
    ~SimpleCalculator();

private slots:
    void on_button_clicked();
private:
    Ui::SimpleCalculator *ui;
    double evaluateExpression(const QString &expression);
};

#endif // SIMPLECALCULATOR_H
