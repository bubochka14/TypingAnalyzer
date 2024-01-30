#pragma once
#include <QHash>
class ConfigPrototype
{
public:
	virtual ConfigPrototype* clone() = 0;
	virtual QHash<QString, QVariant> data() {}
	virtual ~ConfigPrototype() {}
protected:
	ConfigPrototype() {}
};