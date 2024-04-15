#include "settingspage.h"
SettingsPage::SettingsPage(QQmlEngine* e, QObject* parent)
	:AppPage("Settings",parent)
	,_engine(e)
	,_content(nullptr)
{
	setIconSource(QUrl("qrc:/components/icons/settings"));
}

QQuickItem* SettingsPage::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(QUrl("qrc:/components/SettingsPage.qml"), _engine);
		builder.addContextPointer("settingsPage", (QObject*)this);
		_content = builder.build();
	}
	return _content;
}
void SettingsPage::addSetting(AbstractAppSetting* s)
{
	_settings.append(s);
	emit settingsChanged();
}
QList<AbstractAppSetting*> SettingsPage::settings() const
{
	return _settings;
}