INC_PATH = -Icore/include -Icore -Iextra/include
PROG_LIB = libalphacool.so
LDFLAGS  = -shared -o $(PROG_LIB)
CXXFLAGS = -Wall -Werror -fstack-protector -fpic -g -O3 -std=c++11 -pthread $(INC_PATH)

CORE_HEADERS = $(wildcard core/include/*.hpp)
CORE_OBJECTS = $(patsubst %.cpp,%.o,$(wildcard core/src/*.cpp))

EXTRA_HEADERS = $(wildcard extra/include/*.hpp)
EXTRA_OBJECTS = $(patsubst %.cpp,%.o,$(wildcard extra/src/*.cpp))

all: $(PROG_LIB)

$(PROG_LIB): $(CORE_OBJECTS) $(EXTRA_OBJECTS)
	$(CC) $(LDFLAGS) $^

$(CORE_OBJECTS):  $(CORE_HEADERS)
$(EXTRA_OBJECTS): $(EXTRA_HEADERS) $(CORE_OBJECTS)


prefix          = 
prefix_local    = $(prefix)/usr
LIB_INSTDIR     = $(prefix_local)/lib
INSTMODE        = 755
INSTOWNER       = root
INSTGROUP       = root
PROG_LIB_PATH   = $(LIB_INSTDIR)/$(PROG_LIB)

ifeq ($(prefix),)
	LDCONFIG_COMMAND = ldconfig $(LIB_INSTDIR)
else
	LDCONFIG_COMMAND =
endif

install: $(PROG_LIB)
	install -d $(LIB_INSTDIR)
	install -m $(INSTMODE) -o $(INSTOWNER) -g $(INSTGROUP) $(PROG_LIB) $(LIB_INSTDIR)
	$(LDCONFIG_COMMAND)

uninstall: $(PROG_LIB_PATH) $(HEADERS_INSTDIR)
	rm -rf $^

clean:
	rm -f core/src/*.o
	rm -f extra/src/*.o
	rm -f $(PROG_LIB)
