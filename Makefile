# ---
CC = g++
CFLAGS = -O3 -Wall 
LDFLAGS = $(CFLAGS) -lpigpio -lrt

 # ---
BUILD_DIR = build
LIB_DIR = lib
SRC_DIR = src

# ---
SOURCES = $(shell find ./$(SRC_DIR) -type f  -name "*.cpp")
OBJECTS= $(SOURCES: .cpp = .o)
EXECUTABLE = start

PIGPIO_DIR = $(LIB_DIR)/pigpio_lib/PIGPIO

# ------
all:
	make build_cpp

# ------
install:
	make install_libs
uninstall:
	make uninstall_libs

# ------
build_cpp: $(SOURCES) $(EXECUTABLE)

# ------
# LIBS
install_libs:
	make install_lib_PIGPIO

uninstall_libs:
	make uninstall_lib_PIGPIO

# - pigpio
install_lib_PIGPIO:
	unzip $(LIB_DIR)/pigpio_lib/pigpio.zip -d $(LIB_DIR)/pigpio_lib && \
	make -C $(PIGPIO_DIR) -j4 && \
	sudo make install -C $(PIGPIO_DIR) 

uninstall_lib_PIGPIO:
	sudo make uninstall -C $(PIGPIO_DIR) && \
	make clean -C $(PIGPIO_DIR) -j4 && \
	sudo rm -rf $(PIGPIO_DIR)

# ------
clean: 
	rm -rf $(BUILD_DIR)

# ------
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

#.cpp.o:
#	$(CC) $(CFLAGS) $< -o $@
