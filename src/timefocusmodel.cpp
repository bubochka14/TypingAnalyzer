#include "timefocusmodel.h"
Q_LOGGING_CATEGORY(LC_TimeFocusModel, "TimeFocusModel");

QHash<int, QByteArray> TimeFocusModel::_roles = { {Duration,"duration"},{Type,"type"}, {RemainingTime, "remainingTime"},{Completed,"completed"} };
TimeFocusModel::TimeFocusModel(QObject *parent)
    : QAbstractListModel{parent}
{

}
TimeFocusModel* TimeFocusModel::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
    return instance();
}
TimeFocusModel* TimeFocusModel::instance()
{
    if (!_p_inst)
    {
        _p_inst = new TimeFocusModel;
        std::atexit([]() {delete _p_inst; });
    }
    return _p_inst;
}
bool TimeFocusModel::setData(const QModelIndex& index, const QVariant& value, int role ) 
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
    case Completed:
        if (!value.canConvert<bool>())
            return false;
        _data[index.row()].completed = value.value<bool>();
        break;
    case Type:
        if (!value.canConvert<QString>())
            return false;
        _data[index.row()].type = value.value<QString>();
        break;
    case Rates:
        if (!value.canConvert<RatesList>())
            return false;
        _data[index.row()].rates = value.value<RatesList>();
        break;
    }
    emit dataChanged(index, index);
    return true;
    }
    return false;
}
bool TimeFocusModel::clear()
{
   return removeRows(0, rowCount());
}
QVariant TimeFocusModel::data(const QModelIndex& index, int role) const 
{
    if (index.isValid() && index.row() < _data.size() && index.row() >= 0)
    {
        switch (role)
        {
        case Duration:
            return _data.at(index.row()).duration;
        case RemainingTime:
            return _data.at(index.row()).remainingTime;
        case Completed:
            return _data.at(index.row()).completed;
        case Type:
            return _data.at(index.row()).type;
        case Rates:
            return QVariant::fromValue(_data.at(index.row()).rates);
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