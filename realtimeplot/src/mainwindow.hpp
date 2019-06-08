#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QDebug>
#include <QFile>
#include <QMainWindow>
#include <QTextStream>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int randInt(int, int);
    void addPoint(double, double, int);

    void clearData();
    void plot(int);
    void saveFile();

  private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonClear_clicked();
    void clickedGraph(QMouseEvent *event);

    void on_pushButtonSave_clicked();

  private:
    Ui::MainWindow *ui;

    QVector<double> qvX;
    QVector<double> qvY;
    QVector<int> qvClass;
};

#endif  // MAINWINDOW_HPP
