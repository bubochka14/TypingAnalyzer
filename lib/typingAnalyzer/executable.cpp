#include "executable.h"
Executable::Executable(QObject* parent) :QObject(parent),_state(NotStarted) {}
Executable::State Executable::state() const { return _state; }
void Executable::start() 
{
    if (_state != Started)
    {
        _state = Started;
        emit started();
    }
}
void Executable::stop() 
{ 
    if (_state != Stopped)
    {
        _state = Stopped;
        emit stopped();
    }

}
void Executable::finish() 
{ 
    if(_state != Finished)
    {
        _state = Finished;
        emit finished();
    }
}

ComplexExecutable::ComplexExecutable(QObject* parent)
    :Executable(parent)
{
}
QString Executable::stateToString() const
{
   return QMetaEnum::fromType<Executable::State>().valueToKey(_state);
}
void ComplexExecutable::addComponent(Executable* other)
{
    _components.append(other);
    emit componentsChanged();
}
QList<Executable*> ComplexExecutable::components() const
{
    return _components;
}
void ComplexExecutable::start()
{
    for(auto i: _components)
    {
        i->start();
    }
    Executable::start();
}
void ComplexExecutable::stop()
{
    for(auto i: _components)
    {
        i->stop();
    }
    Executable::stop();
}
void ComplexExecutable::finish()
{
    for(auto i: _components)
    {
        i->finish();
    }
    Executable::finish();

}
