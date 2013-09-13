CC=gcc
CFLAGS=-O -std=c99
INSTALL_DIR = /usr/local/lib/lv2
ifndef ARCHNAME
OEXT=.o
SOEXT=.so
ARCCFLAG=
ARCLFLAG=
DLLNAME=cheap_distortion
else
DLLNAME=so
OEXT=_$(ARCHNAME).o
SOEXT=.$(ARCHNAME)
ifeq ($(ARCHNAME),x86_64)
ARCCFLAG=-m64
else
ARCCFLAG=-m32
endif
ARCLFLAG=-melf_$(ARCHNAME)
endif
ifdef LV2CREATE
UNAME := $(shell uname -m)
COPYNAME=so
else
UNAME=so
COPYNAME=cheap_distortion
endif
BUNDLE=cheap_distortion.lv2
OBJECTS=cheap_distortion$(OEXT)
all: $(DLLNAME)$(SOEXT)

cheap_distortion$(OEXT): cheap_distortion.c cheap_distortion.h plugin.h
	$(CC) $(ARCCFLAG) -Wall -fPIC $(CFLAGS) -o cheap_distortion$(OEXT) -c cheap_distortion.c

plugin$(OEXT): plugin.c cheap_distortion.h plugin.h
	$(CC) $(ARCCFLAG) -Wall -fPIC $(CFLAGS) -o plugin$(OEXT) -c plugin.c

$(DLLNAME)$(SOEXT): $(OBJECTS) plugin$(OEXT)
	$(LD) $(ARCLFLAG) -o $(DLLNAME)$(SOEXT) plugin$(OEXT) $(OBJECTS) -shared

install:
	mkdir -p $(INSTALL_DIR)/$(BUNDLE)
	cp -f manifest.ttl $(INSTALL_DIR)/$(BUNDLE)/manifest.ttl
	cp -f plugin.ttl $(INSTALL_DIR)/$(BUNDLE)/cheap_distortion.ttl
	cp -f $(COPYNAME).$(UNAME) $(INSTALL_DIR)/$(BUNDLE)/cheap_distortion.so
	chmod 775 $(INSTALL_DIR)/$(BUNDLE)/*.ttl

uninstall:
	rm -rf $(INSTALL_DIR)/$(BUNDLE)

clean:
	rm -f *.o
