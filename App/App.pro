################################################################################
# Config.
################################################################################
CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

################################################################################
# Dependencies.
################################################################################
include( $$PWD/../ImageControl/ImageControl.pri )

################################################################################
# Sources.
################################################################################
SOURCES += \
    $$PWD/main.cpp

################################################################################
# Headers.
################################################################################
HEADERS += \
