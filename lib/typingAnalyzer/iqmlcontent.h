#pragma once
#include <qqmlengine.h>
#include <QObject>
#include <qquickitem.h>
#include "typinganalyzer_include.h"

class TP_EXPORT IQmlContent
{
public:

	virtual ~IQmlContent() = default;
	virtual QQuickItem* getContent() = 0;
};
