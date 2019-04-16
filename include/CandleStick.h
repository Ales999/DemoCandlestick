//
// Created by chenghaowang on 16/04/19.
//

#ifndef DEMOCANDLESTICK_CANDLESTICK_H
#define DEMOCANDLESTICK_CANDLESTICK_H

#include <QtCharts/QCandlestickSet>
#include <QtCore/QTextStream>

/**
 * @brief Copyright code copied from https://doc.qt.io/qt-5/qtcharts-candlestickchart-example.html
 */

QT_CHARTS_USE_NAMESPACE
class CandleStick : public QTextStream
{
public:
    explicit CandleStick(QIODevice *device);
    ~CandleStick();

    void readFile(QIODevice *device);
    QCandlestickSet *readCandlestickSet();
};


#endif //DEMOCANDLESTICK_CANDLESTICK_H
