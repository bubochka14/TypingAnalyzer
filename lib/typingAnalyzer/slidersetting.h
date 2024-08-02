#pragma once
#include <qobject.h>
#include "displayedsetting.h"
#include "contentbuilder.h"
#include "typinganalyzer_include.h"

class TP_EXPORT SliderSetting : public DisplayedSetting
{
	Q_OBJECT;
	Q_PROPERTY(int max READ max WRITE setMax NOTIFY maxChanged);
	Q_PROPERTY(int min READ min WRITE setMin NOTIFY minChanged);
public:
	explicit SliderSetting(const QString& name, QObject* parent = nullptr);
	bool setValue(const QVariant& other) override;
	QVariant value() const override;
	QQuickItem* getContent() override;
	int min() const;
	int max() const;
	void setMin(int other);
	void setMax(int other);
protected slots:
	void handleValueChange();
signals:
	void maxChanged();
	void minChanged();
private:
	QQuickItem* _content;
	QQmlEngine* _engine;
	double _value;
	int _min, _max;
};