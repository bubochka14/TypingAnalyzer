#include "applicationsettings.h"
ApplicationSettings::ApplicationSettings(const QString& appName, const QString& orgName)
{

}
QString ApplicationSettings::language() const
{
	return value("language", defaultLanguage()).toString();

}
QString ApplicationSettings::defaultLanguage() const
{
	return QString("en");

}
void ApplicationSettings::setLanguage(const QString& other)
{
	if (language() != other)
	{
		setValue("language", other);
		emit languageChanged();
	}
}