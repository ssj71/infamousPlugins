NAME = casynth

TARGET = $${NAME}_lv2
TEMPLATE = lib
CONFIG += shared plugin
CONFIG -= qt

QMAKE_CFLAGS += -std=c99 \
    -g


SOURCES += note.c \
    casynth.c \
    waves.c \
    sstring.c \
    bridge.c \
    sintar.c

HEADERS += \
    constants.h \
    note.h \
    casynth.h \
    sstring.h \
    bridge.h \
    sintar.h

OTHER_FILES += \
    notes.txt \
    manifest.ttl \
    README \
    casynth.lv2/casynth_presets.ttl


unix {

        OBJECTS_DIR = .obj_lv2
        MOC_DIR     = .moc_lv2
        UI_DIR      = .ui_lv2

        isEmpty(PREFIX) {
                PREFIX = /usr/local
        }

        contains(PREFIX, $$system(echo $HOME)) {
                LV2DIR = $${PREFIX}/.lv2
        } else {
                ARCH = $$system(uname -m)
                contains(ARCH, x86_64) {
                        LV2DIR = $${PREFIX}/lib64/lv2
                } else {
                        LV2DIR = $${PREFIX}/lib/lv2
                }
        }

        isEmpty(QMAKE_EXTENSION_SHLIB) {
                QMAKE_EXTENSION_SHLIB = so
        }

        TARGET_LV2 = $${NAME}.lv2/$${NAME}.$${QMAKE_EXTENSION_SHLIB}

        !exists($${TARGET_LV2}) {
                system(touch $${TARGET_LV2})
        }

        QMAKE_POST_LINK += $${QMAKE_COPY} -vp $(TARGET) $${TARGET_LV2}

        INSTALLS += target

        target.path  = $${LV2DIR}/$${NAME}.lv2
        target.files = $${TARGET_LV2} \
                $${NAME}.lv2/$${NAME}.ttl \
                $${NAME}.lv2/manifest.ttl \
                $${NAME}.lv2/$${NAME}_presets.ttl

        QMAKE_CLEAN += $${TARGET_LV2}
}
