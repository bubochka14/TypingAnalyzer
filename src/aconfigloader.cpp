#include "aconfigloader.h"
AConfigLoader::AConfigLoader(QObject* parent)
	:QObject(parent)
{

}
QJsonArray AConfigLoader::jsonConfigs() const
{
	return _jsonArray;
}
void AConfigLoader::setJsonConfigs(const QJsonArray& other)
{
	if (other != _jsonArray)
	{
		_jsonArray = other;
		emit jsonConfigsChanged();
	}
}