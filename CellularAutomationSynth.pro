TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.c \
    note.c \
    notelist.c \
    casynth.c \
    cell_automation.c

HEADERS += \
    constants.h \
    note.h \
    notelist.h \
    casynth.h \
    cell_automation.h

OTHER_FILES += \
    notes.txt

