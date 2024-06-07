#include "contentbuilder.h"
Q_LOGGING_CATEGORY(LC_CONTENT_BUILDER,"Content Builder")
ContentBuilder::ContentBuilder(QQmlEngine* e)
	:_context(new QQmlContext(e,e))
	,_engine(e)
{
}
void ContentBuilder::setInitialProperties(const QVariantMap& pr)
{
	_init = pr;
}
void ContentBuilder::setEngine(QQmlEngine* engine)
{
	_engine = engine;
}
void ContentBuilder::setInitialProperties(const QString& name, QObject* p)
{
	_init = { {name, QVariant::fromValue(p)} };
}

QQuickItem* ContentBuilder::build(const QUrl& source)
{
	QQmlComponent comp(_engine, source,
		QQmlComponent::PreferSynchronous);
	QObject* obj = comp.createWithInitialProperties(_init);
	if (comp.isError())
	{
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << comp.errors();
		return nullptr;
	}
	else
		return (QQuickItem*)obj;
}

QQuickItem* ContentBuilder::build(const QString& module, const QString& item)
{
	QQmlComponent comp(_engine,module,item,
		QQmlComponent::PreferSynchronous);
	QObject* obj = comp.createWithInitialProperties(_init);
	if (comp.isError())
	{
		qCritical(LC_CONTENT_BUILDER) << "Error while creating content" << ": " << comp.errors();
		return nullptr;
	}
	else
		return (QQuickItem*)obj;
}
