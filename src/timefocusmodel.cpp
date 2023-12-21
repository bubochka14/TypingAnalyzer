#include "timefocusmodel.h"
Q_LOGGING_CATEGORY(LC_TimeFocusModel, "TimeFocusModel");

QHash<int, QByteArray> TimeFocusModel::_roles = { {Time,"time"},{TimeStr,"timeStr"},{FocusType,"type"}};
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
         _data[index.row()].timeStr = value.value<QTime>().toString("HH:mm:ss");
         
         return true;
    case TimeStr:
    {
        QString timeStr = value.value<QString>();

        auto list = timeStr.split(u':', Qt::SkipEmptyParts);
        if (list.size() != 3)
        {
            qCWarning(LC_TimeFocusModel) << "Incorrect time format received: " << timeStr;
            return false;
        }
        bool ok; QTime temp = QTime(list.at(0).toInt(&ok), list.at(1).toInt(&ok), list.at(2).toInt(&ok));
        if (!ok)
        {
            qCWarning(LC_TimeFocusModel) << "Incorrect time received: " << timeStr;
            return false;
        }
        _data[index.row()].timeStr = timeStr;
        _data[index.row()].time = temp;
        return true;

    }

    case FocusType:
        _data[index.row()].type = value.value<TimeFocusData::Type>();
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
        case TimeStr:
            return _data.at(index.row()).timeStr;
            break;
        case FocusType:
            return _data.at(index.row()).type;
            break;
        default:
            break;
        }
        if (role < Qt::UserRole)
        {

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