#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "wrapper.h"

#include <QQmlContext> // for setContextProperty

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    Wrapper obj;
    engine.rootContext()->setContextProperty("wrapper", &obj);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("MyListVisual", "Main");

    return app.exec();
}
