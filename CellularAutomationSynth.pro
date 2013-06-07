TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    note.c \
    casynth.c

HEADERS += \
    constants.h \
    note.h \
    casynth.h

OTHER_FILES += \
    notes.txt

