PROJECTNAME := slice

LDCONFFILE := /etc/ld.so.conf.d/$(PROJECTNAME).conf
LIB_INSTALL_PATH := /usr/local/lib/josiah/$(PROJECTNAME)
HEADER_INSTALL_PATH := /usr/local/include/josiah/$(PROJECTNAME)

INCLUDEDIR := include
DEFDIR := def

SRCDIR := src
BINDIR := bin
BUILDDIR := build

OUT := lib$(PROJECTNAME).so
SONAME := $(OUT).0
TARGET := $(OUT).0.0.0

CLIST := $(wildcard src/*.c)
LIST := $(patsubst src/%.c,%,$(CLIST))

FLAGS := -fPIC -c 
RELEASE_FLAGS := -Wl,--soname=$(SONAME) -shared

install: prepare release
	sudo cp $(BUILDDIR)/$(TARGET) $(LIB_INSTALL_PATH)/
	sudo sh -c 'ln -s $(LIB_INSTALL_PATH)/$(TARGET) $(LIB_INSTALL_PATH)/$(OUT) || true'
	sudo sh -c 'ln -s $(LIB_INSTALL_PATH)/$(TARGET) $(LIB_INSTALL_PATH)/$(SONAME) || true'
	sudo cp -r $(INCLUDEDIR) $(DEFDIR) $(HEADER_INSTALL_PATH)/
	sudo ldconfig

prepare:
	sudo sh -c 'mkdir $(BINDIR) $(BUILDDIR) || true'
	sudo sh -c 'echo $(LIB_INSTALL_PATH) > $(LDCONFFILE)'
	sudo sh -c 'mkdir -p $(HEADER_INSTALL_PATH) $(LIB_INSTALL_PATH) || true'

release: clean all
	gcc $(RELEASE_FLAGS) $(BINDIR)/* -o $(BUILDDIR)/$(TARGET)

all:
	for item in $(LIST); do \
		gcc $(FLAGS) -o $(BINDIR)/$${item}.o $(SRCDIR)/$${item}.c; \
	done

clean:
	-rm $(BINDIR)/* $(BUILDDIR)/* || true
