NAME = ewham 

TARGET = $${NAME}_lv2
TEMPLATE = lib
CONFIG += shared plugin
CONFIG -= qt
LIBS += -lfftw3

QMAKE_CFLAGS += -g \
    -msse2 \
    -mfpmath=sse \
    -ffast-math


SOURCES += ewham.c \
    retuner.c  
    
HEADERS += retuner.h \
    fftw3.h

OTHER_FILES += \
    ewham.lv2/manifest.ttl \
    ewham.lv2/ewham.ttl

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
