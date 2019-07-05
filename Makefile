CC = g++

# Folders
SRCDIR := src
BUILDDIR := build
TARGETDIR := bin
TESTBUILDDIR := build_tests

# Targets
EXECUTABLE := ffmpeg-in-a-nutshell
TARGET := $(TARGETDIR)/$(EXECUTABLE)

# Final Paths
INSTALLBINDIR := /usr/local/bin

# Code Lists
SRCEXT := cpp
HEADEREXT := h
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Folder Lists
INCDIRS := $(shell find $(SRCDIR)/**/* -name '*.$(SRCEXT)' -exec dirname {} \; | sort | uniq)
INCLIST := $(patsubst $(SRCDIR)/%,-I $(SRCDIR)/%,$(INCDIRS))
BUILDLIST := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(INCDIRS))

FFMPEG_PATH=$(HOME)/ffmpeg

FFMPEG_CONFIG_OPTS += --enable-gpl
FFMPEG_CONFIG_OPTS += --enable-shared --disable-static
# Documentation
FFMPEG_CONFIG_OPTS += --disable-doc
FFMPEG_CONFIG_OPTS += --enable-libx264
FFMPEG_CONFIG_OPTS += --enable-libx265
FFMPEG_CONFIG_OPTS += --enable-libvpx
FFMPEG_CONFIG_OPTS += --enable-ffplay
FFMPEG_CONFIG_OPTS += --enable-pthreads

PACKAGES += libvpx-dev libasound2-dev libx264-dev libx265-dev libsdl2-dev yasm

# Shared Compiler Flags
CFLAGS := -std=c++17 -O3 -Wall -Wextra
INC := -I include $(INCLIST) -I /usr/local/include
LIB := -pthread `pkg-config --libs libavformat` `pkg-config --libs libavdevice` `pkg-config --libs libavcodec` `pkg-config --libs libavutil` `pkg-config --libs libswscale` `pkg-config --libs libswresample`  -lm -lrt

ifeq ($(debug), 1)
CFLAGS += -g -ggdb3 -D DEBUG
else
CFLAGS += -DNDEBUG
endif

ifeq ($(debug), 2)
CFLAGS += -g -ggdb3 -D DEBUG -D DEBUG_EXTRA
else
CFLAGS += -DNDEBUG
endif

# ALL SHOULD BE REMOVED
all:
    @echo "Placeholder"

$(TARGET): $(OBJECTS)
	@mkdir -p $(TARGETDIR)
	@echo  "Linking all targets..."
	@$(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDLIST)
	@echo "CC    $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<
	
memtest: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --log-file=valgrind-out.txt $(TARGET)

clean:
	@echo "Cleaning $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGETDIR)

install-ffmpeg: install-dependencies
	@ cd ${FFMPEG_PATH} && ./configure ${FFMPEG_CONFIG_OPTS} && make -j${MAKE_J} && sudo make install

install-dependencies:
	dpkg-query -W ${PACKAGES} || sudo apt-get install ${PACKAGES}

install:
	@echo "Installing $(EXECUTABLE)"; cp $(TARGET) $(INSTALLBINDIR)

clone:
	git clone --branch 'release/4.1' https://github.com/FFmpeg/FFmpeg ${FFMPEG_PATH}

run:
	${TARGET}

.PHONY: clean
