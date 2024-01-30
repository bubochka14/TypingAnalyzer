#include "localconfigloader.h"
LocalConfigLoader::LocalConfigLoader(QObject* parent, const QString& rootPath, const QString& configName)
	:AConfigLoader(parent)
	,_rootPath(rootPath)
	,_configName(configName)
{

}
bool LocalConfigLoader::loadConfigs()
{
	QJsonArray newArray;
	QDirIterator it(rootPath(), QStringList() << "config.json", QDir::Files, QDirIterator::Subdirectories);
	while (it.hasNext())
	{
		QJsonDocument doc;
		QFile jsonFile(it.filePath());
		jsonFile.open(QIODevice::ReadOnly);

		QByteArray data = jsonFile.readAll();
		QJsonDocument doc = QJsonDocument::fromJson(data);
		if (!doc.isNull() && doc.isObject())
			newArray.append(doc.object());
	}
	setJsonConfigs(newArray);
}
QString LocalConfigLoader::rootPath() const
{
	return _rootPath;
}
void LocalConfigLoader::setRootPath(const QString& other) 
{
	_rootPath = other;
}
void LocalConfigLoader::setConfigName(const QString& other)
{
	_configName = other;
}
QString LocalConfigLoader::configName() const
{
	return _configName;
}
