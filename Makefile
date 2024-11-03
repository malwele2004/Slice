LIB_INSTALL_PATH := /usr/local/lib
HEADER_INSTALL_PATH := /usr/local/include/josiah/slice

INCLUDEDIR := include
DEFDIR := def

SRCDIR := src
BINDIR := bin
BUILDDIR := build

OUT := libslice.so
SONAME := $(OUT).0
TARGET := $(OUT).0.0.0

CLIST := $(wildcard src/*.c)
LIST := $(patsubst src/%.c,%,$(CLIST))

FLAGS := -fPIC -c 
RELEASE_FLAGS := -Wl,--soname=$(SONAME) -shared

install: prepare release
	sudo cp $(BUILDDIR)/$(TARGET) $(LIB_INSTALL_PATH)/
	sudo sh -c 'ln -s $(LIB_INSTALL_PATH)/$(TARGET) $(LIB_INSTALL_PATH)/$(OUT) || true'
	sudo cp -r $(INCLUDEDIR) $(DEFDIR) $(HEADER_INSTALL_PATH)/
	sudo ldconfig

prepare:
	-mkdir $(BINDIR) $(BUILDDIR) || true
	-mkdir $(HEADER_INSTALL_PATH) || true

release: clean all
	gcc $(RELEASE_FLAGS) -o $(BUILDDIR)/$(TARGET) $(BINDIR)/*

all:
	for item in $(LIST); do \
		gcc $(FLAGS) -o $(BINDIR)/$${item}.o $(SRCDIR)/$${item}.c; \
	done

clean:
	-rm $(BINDIR)/* $(BUILDDIR)/* || true