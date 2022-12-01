#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "control_unit.h"
#include "can_send.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    ControlUnit control_unit;
    engine.rootContext()->setContextProperty("control_unit", &control_unit);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FILE *sysfs_handle = NULL;

    if((sysfs_handle = fopen("/sys/class/gpio/export", "w")) != NULL){
        fwrite("3", sizeof(char), 2, sysfs_handle);
        fclose(sysfs_handle);
    }

    if((sysfs_handle = fopen("/sys/class/gpio/gpio3/direction", "w")) != NULL){
        fwrite("out", sizeof(char), 4, sysfs_handle);
        fclose(sysfs_handle);
    }
    
    sysfs_handle = fopen("/sys/class/gpio/gpio3/value", "w");
    if(sysfs_handle != NULL){
	fwrite("1", sizeof(char), 2, sysfs_handle);
	fclose(sysfs_handle);
    }
    can_send_s();
    return app.exec();
}
