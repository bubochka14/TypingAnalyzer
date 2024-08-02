#pragma once
#include "displayedsetting.h"
#include <qqmlengine.h>
#include "contentbuilder.h"
#include "typinganalyzer_include.h"

class TP_EXPORT ListSetting : public DisplayedSetting
{
	Q_OBJECT;
	QML_ELEMENT;
public:
	explicit ListSetting(const QString& name="", QObject* parent = nullptr);
	void addOption(const QString& optionName, const QVariant& var);
	void addOption(NamedObject* obj);
	bool setValue(const QVariant& other) override;
	QVariant value() const override;
	QQuickItem* getContent() override;
private slots:
	void handleTextChange();
private:
	QHash<QString,QVariant> _varHash;
	QString _currentObjectName;
	QQuickItem* _content;
	QQmlEngine* _engine;
};
