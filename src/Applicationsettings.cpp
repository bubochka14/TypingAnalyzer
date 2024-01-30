#include "applicationsettings.h"
ApplicationSettings::ApplicationSettings(const QString& appName, const QString& orgName)
	:QSettings(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation)+"\config.ini", QSettings::IniFormat)
{
	qDebug() << QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "\config.ini";
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
QString ApplicationSettings::KBSoundProducerName() const
{
	return value("KBSoundProducerName", defaultKBSoundProducerName()).toString();
}
QString ApplicationSettings::defaultKBSoundProducerName() const
{
	return "empty";
}
void ApplicationSettings::setKBSoundProducerName(const QString& other)
{
	if (KBSoundProducerName() != other)
	{
		setValue("KBSoundProducerName", other);
		emit KBSoundProducerNameChanged();
	}
}
QString ApplicationSettings::periodSoundProducerName() const
{
	return value("periodSoundProducerName", defaultPeriodSoundProducerName()).toString();
}
QString ApplicationSettings::defaultPeriodSoundProducerName() const
{
	return "empty";
}
void ApplicationSettings::setPeriodSoundProducerName(const QString& other)
{
	if (periodSoundProducerName() != other)
	{
		setValue("periodSoundProducerName", other);
		emit periodSoundProducerNameChanged();
	}
}