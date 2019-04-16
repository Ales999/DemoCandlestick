#include <iostream>
#include <QtWidgets/QApplication>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QCandlestickSeries>
#include <QtCore/QFile>
#include <include/CandleStick.h>
#include <QtCore/QDateTime>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFileDialog>
/**
 * @brief Copyright code copied from https://doc.qt.io/qt-5/qtcharts-candlestickchart-example.html
 */
QT_CHARTS_USE_NAMESPACE
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto *acmeSeries = new QCandlestickSeries();
    acmeSeries->setName("Acme Ltd");
    acmeSeries->setIncreasingColor(QColor(Qt::green));
    acmeSeries->setDecreasingColor(QColor(Qt::red));

    QFile acmeData("../../data/acme_data.txt");
    if (!acmeData.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QStringList categories;

    CandleStick dataReader(&acmeData);
    while (!dataReader.atEnd()) {
        QCandlestickSet *set = dataReader.readCandlestickSet();
        if (set) {
            acmeSeries->append(set);
            categories << QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(set->timestamp())).toString("dd");
        }
    }

    QChart *chart = new QChart();
    chart->addSeries(acmeSeries);
    chart->setTitle("Acme Ltd Historical Data (July 2015)");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chart->createDefaultAxes();

    QBarCategoryAxis *axisX = reinterpret_cast<QBarCategoryAxis *>(qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0)));
    axisX->setCategories(categories);

    QValueAxis *axisY = reinterpret_cast<QValueAxis *>(qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0)));
    axisY->setMax(axisY->max() * 1.01);
    axisY->setMin(axisY->min() * 0.99);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(800, 600);
    window.show();

    return a.exec();
}