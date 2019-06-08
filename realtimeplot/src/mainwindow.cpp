#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect qcustomplot to widget
    connect(ui->plot, SIGNAL(mousePress(QMouseEvent *)), SLOT(clickedGraph(QMouseEvent *)));
    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

MainWindow::~MainWindow() { delete ui; }

// generate a rand int
int MainWindow::randInt(int low, int high)
{
    QTime time = QTime::currentTime();
    qsrand(uint(time.msec()));

    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void MainWindow::addPoint(double x, double y, int c)
{
    qvX.append(x);
    qvY.append(y);
    qvClass.append(c);
}

void MainWindow::clearData()
{
    qvX.clear();
    qvY.clear();
}

// TODO -> Correct function to plot different colors classes
void MainWindow::plot(int layer = 0)
{
    ui->plot->addGraph();
    ui->plot->graph(layer)->setPen(QPen(QColor(randInt(0, 255), randInt(0, 255), randInt(0, 255))));
    // ui->plot->graph(layer)->setPen(QPen(Qt::green));
    ui->plot->graph(layer)->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->plot->graph(layer)->setLineStyle(QCPGraph::lsNone);
    // ui->plot->setCurrentLayer(QVariant(ui->classNumber->value()).toString());
    ui->plot->graph(layer)->setData(qvX, qvY);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::saveFile()
{
    QString filename = "Dados.txt";
    QFile file(filename);
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream stream(&file);
        stream << "x, y, class" << endl;
        for (int i = 0; i < qvX.size(); ++i)  // v1 and v2 better be same size!
            stream << qvX[i] << "," << qvY[i] << "," << qvClass[i] << endl;
    }
    file.close();
}

void MainWindow::on_pushButtonAdd_clicked()
{
    addPoint(ui->bx->value(), ui->by->value(), ui->classNumber->value());
    plot();
}

void MainWindow::on_pushButtonClear_clicked()
{
    clearData();
    plot();
}

void MainWindow::clickedGraph(QMouseEvent *event)
{
    QPoint point = event->pos();
    // qDebug() << ui->plot->xAxis->pixelToCoord(point.x()) <<
    // ui->plot->yAxis->pixelToCoord(point.y());
    addPoint(ui->plot->xAxis->pixelToCoord(point.x()), ui->plot->yAxis->pixelToCoord(point.y()),
             ui->classNumber->value());
    plot(ui->classNumber->value());
}

void MainWindow::on_pushButtonSave_clicked() { saveFile(); }
