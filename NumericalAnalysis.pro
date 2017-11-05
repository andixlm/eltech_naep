QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NumericalAnalysis
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += \
            include/ \
            include/muParser

SOURCES += \
        src/main.cpp \
        src/mainwindow.cpp \
        src/methods.cpp \
        src/tools.cpp \
        src/muParser/muParser.cpp \
        src/muParser/muParserBase.cpp \
        src/muParser/muParserBytecode.cpp \
        src/muParser/muParserCallback.cpp \
        src/muParser/muParserDLL.cpp \
        src/muParser/muParserError.cpp \
        src/muParser/muParserInt.cpp \
        src/muParser/muParserTest.cpp \
        src/muParser/muParserTokenReader.cpp

HEADERS += \
        include/mainwindow.hpp \
        include/methods.hpp \
        include/tools.hpp \
        include/muParser/muParser.h \
        include/muParser/muParserBase.h \
        include/muParser/muParserBytecode.h \
        include/muParser/muParserCallback.h \
        include/muParser/muParserDef.h \
        include/muParser/muParserDLL.h \
        include/muParser/muParserError.h \
        include/muParser/muParserFixes.h \
        include/muParser/muParserInt.h \
        include/muParser/muParserStack.h \
        include/muParser/muParserTemplateMagic.h \
        include/muParser/muParserTest.h \
        include/muParser/muParserToken.h \
        include/muParser/muParserTokenReader.h
