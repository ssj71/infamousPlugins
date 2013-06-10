TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CFLAGS += -std=c99

SOURCES += main.c \
    note.c \
    casynth.c

HEADERS += \
    constants.h \
    note.h \
    casynth.h

OTHER_FILES += \
    notes.txt \
    casynth.ttl \
    manifest.ttl


