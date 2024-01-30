#pragma once
#include <QObject>
#include <qqmlengine.h>
struct SoundConfig
{
	Q_GADGET;
	QML_ELEMENT;
public:
	enum Type
	{
		Unkonown,
		Period,
		Keyboard
	}; Q_ENUM(Type);
	//matches sound names with their paths
	QHash<QString, QString> soundPaths;
	interface
};
class SoundConfigBuilder : public QObject
{
	Q_OBJECT;
public:
	explicit SoundConfigBuilder(QObject* parent = nullptr);
	virtual SoundConfig buildConfigFromJson(const QJsonObject& obj);
};