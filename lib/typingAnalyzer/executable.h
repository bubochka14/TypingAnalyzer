#pragma once
#include <qobject.h>
#include "typinganalyzer_include.h"
#include <qmetaenum>
#include <QQMlEngine>
class TP_EXPORT Executable : public QObject
{
	Q_OBJECT;
	QML_ELEMENT;
public:
	enum State
	{
		NotStarted,// initial state
		Stopped,
		Started,
		Finished
	}; Q_ENUM(State);
	explicit Executable(QObject* parent = nullptr);
	State state() const;
	Q_INVOKABLE QString stateToString() const;
public slots:
	virtual void start();
	virtual void stop();
	virtual void finish();
signals:
	void stateChanged();
protected:
	void setState(State other);
private:
	Q_PROPERTY(State state READ state NOTIFY stateChanged);
	State _state;
};
class TP_EXPORT ComplexExecutable : public Executable
{
    Q_OBJECT;
    Q_PROPERTY(QList<Executable*> components READ components NOTIFY componentsChanged);
public:
    explicit ComplexExecutable(QObject* parent = nullptr);
	QList<Executable*> components() const;
    void addComponent(Executable* other);
    void start() override;
    void stop() override;
    void finish() override;
signals:
	void componentsChanged();
private:
    QList<Executable*> _components;
};
