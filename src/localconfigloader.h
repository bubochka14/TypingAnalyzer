#pragma once
#include "aconfigloader.h"
#include <QDIr>
#include <qdiriterator.h>
class LocalConfigLoader : public AConfigLoader
{
	Q_OBJECT;
public:
	explicit LocalConfigLoader(QObject* parent = nullptr, 
		const QString& rootPath = QDir::currentPath() + "/packs",
		const QString& configName = "config.json");
	bool loadConfigs() override;
	QString rootPath() const;
	QString configName() const;
	void setRootPath(const QString& other);
	void setConfigName(const QString& other);
private:
	QString _rootPath;
	QString _configName
};