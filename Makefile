BUILD_DIR = build
BUILD_LIB_DIR = $(BUILD_DIR)/lib
SRC_DIR = src
LIB_DIR = lib
IS_PI = true

# ------
all:
	make clean && \
	make install_libs && \
	make build

# ------
build:
	@echo hi FINI

# ------
# LIBS
install_libs:
ifeq ($(IS_PI),true) 
	rm -rf $(BUILD_LIB_DIR) && \
	make build_lib_PIGPIO
endif

build_lib_PIGPIO:
	mkdir -p $(BUILD_LIB_DIR)/pigpio_lib && \
	cp -R $(LIB_DIR)/pigpio_lib/PIGPIO/. $(BUILD_LIB_DIR)/pigpio_lib/ && \
	make -C $(BUILD_LIB_DIR)/pigpio_lib/ -j4 && \
	make install -C $(BUILD_LIB_DIR)/pigpio_lib/ 
# ------
clean: 
	rm -rf $(BUILD_DIR)