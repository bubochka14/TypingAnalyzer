#include "freemodepage.h"
FreeModePage::FreeModePage(Application* a, QQmlEngine* e, QObject* parent)
    :ExecutableAppPage("Free Mode", parent)
    ,_app(a)
    ,_freeModeExecutable(new ComplexExecutable(this))
    ,_content(nullptr)
    ,_engine(e)
{
    AKeyBoardInterceptor* kInter = new KeyboardInterceptor(this);
    _eKbProd = new ExecutableKBProducer(a->kbProd(),kInter,this);
    _typingMeter = new TypingMeter(kInter,this);
    _freeModeExecutable->addComponent(_eKbProd);
    _freeModeExecutable->addComponent(_typingMeter);
    connect(_typingMeter, &TypingMeter::ratesChanged,this, &FreeModePage::ratesChanged);
    connect(_app, &Application::kbProdChanged, this, [=]() {_eKbProd->setKBSoundProducer(_app->kbProd()); });
}
QList<typingRate> FreeModePage::rates() const {return _typingMeter->rates(); }
Executable* FreeModePage::executable() const { return _freeModeExecutable; }
QQuickItem* FreeModePage::getContent()
{
    if(_content==nullptr)
    {
        ContentBuilder builder(_engine);
        builder.addContextPointer("freeModePage", this);
        _content = builder.build(LIB_NAME, "FreeModePage");
    }
	return _content;
}
