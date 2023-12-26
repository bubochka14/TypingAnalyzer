#ifndef RATESMODEL_H
#define RATESMODEL_H

#include <QAbstractListModel>
#include <QQmlEngine>

class RatesModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    explicit RatesModel(QObject *parent = nullptr);
};

#endif // RATESMODEL_H
