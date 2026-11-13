QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bola.cpp \
    Cuadrado.cpp \
    Entidad.cpp \
    RegistroDatos.cpp \
    ResolutorColisiones.cpp \
    Simulador.cpp \
    Vector2D.cpp \
    VentanaSimulacion.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Bola.h \
    Cuadrado.h \
    Entidad.h \
    RegistroDatos.h \
    ResolutorColisiones.h \
    Simulador.h \
    TipoColision.h \
    Vector2D.h \
    VentanaSimulacion.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
