BUILD_DIR = build
BUILD_LIB_DIR = $(BUILD_DIR)/lib
SRC_DIR = src
LIB_DIR = lib
IS_PI = true

# ------
all:
	make build

# ------
install:
	make install_libs
uninstall:
	make uninstall_libs

# ------
build:
	@echo hi FINI

# ------
# LIBS
install_libs:
ifeq ($(IS_PI),true) 
	rm -rf $(BUILD_LIB_DIR) && \
	make install_lib_PIGPIO
endif

uninstall_libs:
ifeq ($(IS_PI),true) 
	make uninstall_lib_PIGPIO && \
	rm -rf $(BUILD_LIB_DIR) 
endif

# - pigpio
install_lib_PIGPIO:
	mkdir -p $(BUILD_LIB_DIR)/pigpio_lib && \
	cp -R $(LIB_DIR)/pigpio_lib/PIGPIO/. $(BUILD_LIB_DIR)/pigpio_lib/ && \
	make -C $(BUILD_LIB_DIR)/pigpio_lib/ -j4 && \
	sudo make install -C $(BUILD_LIB_DIR)/pigpio_lib/ 

uninstall_lib_PIGPIO:
	sudo make uninstall -C $(BUILD_LIB_DIR)/pigpio_lib/ && \
	make -C $(BUILD_LIB_DIR)/pigpio_lib/ -j4 

# ------
clean: 
	rm -rf $(BUILD_DIR)