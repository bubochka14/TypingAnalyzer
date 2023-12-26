#ifndef TIMEFOCUSMODEL_H
#define TIMEFOCUSMODEL_H

#include <QAbstractListModel>
#include <QTime>
#include <qloggingcategory.h>
#include <KeyboardInterceptor.h>
#include <qqmlengine.h>
#include <qvariant.h>
Q_DECLARE_LOGGING_CATEGORY(LC_TimeFocusModel);
struct TimeFocusData
{
    Q_GADGET
public:
    enum PeriodType
    {
        Break,
        Work
    }; Q_ENUM(PeriodType)
    QTime time;
    PeriodType type;
};
class TimeFocusModel : public QAbstractListModel
{
    Q_OBJECT;
    QML_ELEMENT
    QML_SINGLETON
public:
    explicit TimeFocusModel(QObject *parent = nullptr);
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;	
    bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
private:
    enum Roles
    {
        Time = Qt::UserRole,
        FocusType
    };
    QVector<TimeFocusData> _data;
    static QHash<int, QByteArray> _roles;
};

#endif // TIMEFOCUSMODEL_H
