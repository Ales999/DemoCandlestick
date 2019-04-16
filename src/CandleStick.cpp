//
// Created by chenghaowang on 16/04/19.
//

#include "../include/CandleStick.h"

CandleStick::CandleStick(QIODevice *device) : QTextStream(device)
{
}

CandleStick::~CandleStick() = default;

void CandleStick::readFile(QIODevice *device)
{
    QTextStream::setDevice(device);
}

QCandlestickSet *CandleStick::readCandlestickSet()
{
    QString line = readLine();
    if (line.startsWith("#") || line.isEmpty())
        return nullptr;

    QStringList strList = line.split(" ", QString::SkipEmptyParts);
    if (strList.count() != 5)
        return nullptr;

    const qreal timestamp = strList.at(0).toDouble();
    const qreal open = strList.at(1).toDouble();
    const qreal high = strList.at(2).toDouble();
    const qreal low = strList.at(3).toDouble();
    const qreal close = strList.at(4).toDouble();

    auto *candlestickSet = new QCandlestickSet(timestamp);
    candlestickSet->setOpen(open);
    candlestickSet->setHigh(high);
    candlestickSet->setLow(low);
    candlestickSet->setClose(close);

    return candlestickSet;
}