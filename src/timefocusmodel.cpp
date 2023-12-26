#include "timefocusmodel.h"
Q_LOGGING_CATEGORY(LC_TimeFocusModel, "TimeFocusModel");

QHash<int, QByteArray> TimeFocusModel::_roles = { {Time,"time"},{FocusType,"type"}};
TimeFocusModel::TimeFocusModel(QObject *parent)
    : QAbstractListModel{parent}
{

}
bool TimeFocusModel::setData(const QModelIndex& index, const QVariant& value, int role ) 
{
    if (index.isValid() || index.row() < rowCount() || index.row() >= 0)
    {
    switch (role)
    {
    case Time:
         _data[index.row()].time = value.value<QTime>();
         
         return true;
    case FocusType:
        _data[index.row()].type = value.value<TimeFocusData::PeriodType>();
        return true;

    default:
        return QAbstractListModel::setData(index,value, role);

    }
    }
    return false;
}
QVariant TimeFocusModel::data(const QModelIndex& index, int role) const 
{
    if (index.isValid() || index.row() < _data.size() || index.row() >= 0)
    {
        switch (role)
        {
        case Time:
            return _data.at(index.row()).time;
            break;
        case FocusType:
            return _data.at(index.row()).type;
            break;
        default:
            return QAbstractListModel::data(index, role);
        }
    }
    return QVariant();
}
QHash<int, QByteArray> TimeFocusModel::roleNames() const
{
    return _roles;
}
int TimeFocusModel::rowCount(const QModelIndex& parent) const 
{
    return _data.size();
}
bool TimeFocusModel::insertRows(int row, int count, const QModelIndex& parent) 
{
    Q_UNUSED(parent);
    if (!count)
        return true;
    if (row < 0 || row >rowCount())
        return false;

    beginInsertRows(parent, row, row + count - 1);
        _data.insert(row,count, TimeFocusData());
    endInsertRows();
    return true;
}
bool TimeFocusModel::removeRows(int row, int count, const QModelIndex& parent)
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