#pragma once
#include <qobject.h>
#include <qquickitem.h>
#include <qqmlengine.h>
#include <qqmlcontext.h>
#include <qloggingcategory.h>
#include "typinganalyzer_include.h"

Q_DECLARE_LOGGING_CATEGORY(LC_CONTENT_BUILDER)
class TP_EXPORT ContentBuilder
{
public:
	explicit ContentBuilder(QQmlEngine* e);
	void setInitialProperties(const QVariantMap& pr);
	void setInitialProperties(const QString&name, QObject* p);
	void addContextPointer(const QString& name, QObject* p);
	void setEngine(QQmlEngine* engine);
	QQuickItem* build(const QString& module, const QString& item);
	QQuickItem* build(const QUrl& source);
private:
	QQmlContext* _context;
	QQmlEngine* _engine;
	QVariantMap _init;
};