#pragma once
#include <qobject.h>
#include <qqmlapplicationengine.h>
#include "pressingmodel.h"
#include "typinganalyzer_include.h"

class TP_EXPORT KeyboardAnalyzer :public QObject
{
	Q_OBJECT;

public:
	explicit KeyboardAnalyzer(QObject *parent= nullptr);

//public slots:
//	void addKeyPress();
};