#include "PeriodsModel.h"
Q_LOGGING_CATEGORY(LC_PERIODSMODEL, "PeriodsModel");

QHash<int, QByteArray> PeriodsModel::_roles = { 
    {Duration,"duration"},
    {Type,"type"}, 
    {RemainingTime, "remainingTime"},
    {PeriodState,"periodState"},
    {Rates,"rates"}
};
PeriodsModel::PeriodsModel(QObject *parent)
    : QAbstractListModel{parent}
{
}
bool PeriodsModel::setData(const QModelIndex& index, const QVariant& value, int role ) 
{
    if (index.isValid() && index.row() < rowCount() && index.row() >= 0)
    {
    switch (role)
    {
    case Duration:
        if (!value.canConvert<quint64>())
            return false;
         _data[index.row()].duration = value.value<quint64>();
         break;
    case RemainingTime:
        if (!value.canConvert<quint64>())
            return false;
        _data[index.row()].remainingTime = value.value<quint64>();
        break;
    case PeriodState:
        if (!value.canConvert<PeriodStates>())
            return false;
        _data[index.row()].periodState = value.value<PeriodStates>();
        break;
    case Type:
        if (!value.canConvert< PeriodInfo::PeriodType>())
            return false;
        _data[index.row()].type = value.value< PeriodInfo::PeriodType>();
        break;
    case Rates:
        if (!value.canConvert<RateList>())
            return false;
        _data[index.row()].rates = value.value<RateList>();
        break;
    }
    emit dataChanged(index, index);
    return true;
    }
    return false;
}
bool PeriodsModel::clear()
{
   return removeRows(0, rowCount());
}
QVariant PeriodsModel::data(const QModelIndex& index, int role) const 
{
    if (index.isValid() && index.row() < _data.size() && index.row() >= 0)
    {
        switch (role)
        {
        case Duration:
            return _data.at(index.row()).duration;
        case RemainingTime:
            return _data.at(index.row()).remainingTime;
        case PeriodState:
            return _data.at(index.row()).periodState;
        case Type:
            return _data.at(index.row()).type;
        case Rates:
            return QVariant::fromValue(_data.at(index.row()).rates);
        }
    }
    return QVariant();
}
QHash<int, QByteArray> PeriodsModel::roleNames() const
{
    return _roles;
}
int PeriodsModel::rowCount(const QModelIndex& parent) const 
{
    Q_UNUSED(parent);
    return _data.size();
}
bool PeriodsModel::insertRows(int row, int count, const QModelIndex& parent) 
{
    Q_UNUSED(parent);
    if (!count)
        return true;
    if (row < 0 || row >rowCount() || count < 0)
        return false;

    beginInsertRows(parent, row, row + count - 1);
        _data.insert(row,count, PeriodData());
    endInsertRows();
    return true;
}
bool PeriodsModel::removeRows(int row, int count, const QModelIndex& parent)
{
    Q_UNUSED(parent);
    if (!count)
        return true;
    if (row<0 || row + count > rowCount())
        return false;
    beginRemoveRows(parent, row, row + count - 1);
        _data.remove(row, count);
    endRemoveRows();
    return true;
}