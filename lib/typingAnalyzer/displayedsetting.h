#pragma once
 #include <QObject>
 #include "namedobject.h"
 #include <qqmlengine.h>
 #include "iqmlcontent.h"
#include "typinganalyzer_include.h"
class TP_EXPORT DisplayedSetting  :public NamedObject
{
	Q_OBJECT;
	QML_ELEMENT;
	QML_UNCREATABLE("");
	Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged);
public:
	virtual bool setValue(const QVariant& other) = 0;
	virtual QVariant value() const = 0;
	virtual Q_INVOKABLE QQuickItem* getContent()=0;

signals:
	void valueChanged();
protected:
	explicit DisplayedSetting(const QString& name,  QObject* parent = nullptr);
};
