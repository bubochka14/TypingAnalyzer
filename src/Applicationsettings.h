#pragma once
#include <QObject>
#include <QSettings>
#include <QStandardPaths>


class ApplicationSettings : public QSettings
{
	Q_OBJECT;
	Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged);
	Q_PROPERTY(QString KBSoundProducerName READ KBSoundProducerName WRITE setKBSoundProducerName NOTIFY KBSoundProducerNameChanged);
	Q_PROPERTY(QString periodSoundProducerName READ periodSoundProducerName WRITE setPeriodSoundProducerName NOTIFY periodSoundProducerNameChanged);
public:
	// APP_NAME, ORG_NAME - CMake definitions
	explicit ApplicationSettings(const QString& appName = APP_NAME, const QString& orgName = ORG_NAME);
	QString language() const;
	QString defaultLanguage() const;
	void setLanguage( const QString& other);

	QString KBSoundProducerName() const;
	QString defaultKBSoundProducerName() const;
	void setKBSoundProducerName(const QString& other);

	QString periodSoundProducerName() const;
	QString defaultPeriodSoundProducerName() const;
	void setPeriodSoundProducerName(const QString& other);

signals:
	void languageChanged();
	void KBSoundProducerNameChanged();
	void periodSoundProducerNameChanged();
};