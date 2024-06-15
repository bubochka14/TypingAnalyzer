#pragma once

#include <QAbstractListModel>
#include <QTime>
#include "soundinterfaces.h"
#include <qloggingcategory.h>
#include <KeyboardInterceptor.h>
#include <qqmlengine.h>
#include <qvariant.h>
#include "typingrate.h"
#include "typinganalyzer_include.h"

Q_DECLARE_LOGGING_CATEGORY(LC_PERIODSMODEL);
class PeriodsModel : public QAbstractListModel
{
    Q_OBJECT;
    QML_ELEMENT
    QML_SINGLETON
public:
    enum PeriodStates
    {
        Inactive,
        Active,
        Completed
    }; Q_ENUM(PeriodStates);
    enum Roles
    {
        Duration = Qt::UserRole,
        RemainingTime,
        PeriodState,
        Rates,
        Type
    }; Q_ENUM(Roles)
    explicit PeriodsModel(QObject* parent = nullptr);

    Q_INVOKABLE bool clear();
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;	
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
protected:  
    //Data field in model
    struct TP_EXPORT PeriodData
    {
        Q_GADGET
    public:
        qint64 duration;
        qint64 remainingTime;
        PeriodStates periodState;
        PeriodInfo::PeriodType type;
        RateList rates;

    };
private:
    QVector<PeriodData> _data;
    static QHash<int, QByteArray> _roles;
};
