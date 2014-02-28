NAME = hip2b

TARGET = $${NAME}_lv2
TEMPLATE = lib
CONFIG += shared plugin
CONFIG -= qt

QMAKE_CFLAGS += -std=c99 \
    -g


SOURCES += square.c

OTHER_FILES += \
    hip2b.lv2/manifest.ttl \
    hip2b.lv2/hip2b.ttl


unix {

        OBJECTS_DIR = .obj_lv2
        MOC_DIR     = .moc_lv2
        UI_DIR      = .ui_lv2

        isEmpty(PREFIX) {
                PREFIX = /usr
        }

        contains(PREFIX, $$system(echo $HOME)) {
                LV2DIR = $${PREFIX}/.lv2
        } else { 
                LV2DIR = $${PREFIX}/lib/lv2
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
                $${NAME}.lv2/manifest.ttl

        QMAKE_CLEAN += $${TARGET_LV2}
}
