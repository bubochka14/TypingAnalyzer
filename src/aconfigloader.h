#pragma once
#include <QObject>
#include <qjsondocument.h> 
#include <QJSonArray>
class AConfigLoader : public QObject
{
	Q_OBJECT;
	Q_PROPERTY(QJsonArray jsonConfigs READ jsonConfigs WRITE setJsonConfigs NOTIFY jsonConfigsChanged);

public:
	virtual bool loadConfigs() = 0;
	QJsonArray jsonConfigs() const;
signals:
	void jsonConfigsChanged();
protected:
	explicit AConfigLoader(QObject* parent = nullptr);
	void setJsonConfigs(const QJsonArray& other);
private:
	QJsonArray _jsonArray;
};