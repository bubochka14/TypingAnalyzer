#include "settingspage.h"
SettingsPage::SettingsPage(QQmlEngine* e, QObject* parent)
	:AppPage("Settings",parent)
	,_engine(e)
	,_content(nullptr)
{}
QStringList SettingsPage::headers() const
{
	return _headers;
}

QQuickItem* SettingsPage::getContent()
{
	if (!_content)
	{
		ContentBuilder builder(_engine);
		builder.addContextPointer("settingsPage", this);
		_content = builder.build(LIB_NAME, "SettingsPage");
	}
	return _content;
}
void SettingsPage::addSetting(DisplayedSetting* s, const QString& header)
{
	if(!_addedSettings.contains(header))
	{
		_addedSettings[header].append(s);
		_headers.append(header);
		emit headersChanged();
	}else 
		_addedSettings[header].append(s);
}
QList<DisplayedSetting*> SettingsPage::addedSettings(const QString& header) const
{
	return _addedSettings[header];
}