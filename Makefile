BUILD_DIR = build
LIB_DIR = lib
SRC_DIR = src

PIGPIO_DIR = $(LIB_DIR)/pigpio_lib/PIGPIO

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
	make install_lib_PIGPIO

uninstall_libs:
	make uninstall_lib_PIGPIO && \

# - pigpio
install_lib_PIGPIO:
	unzip $(LIB_DIR)/pigpio_lib/pigpio.zip -d $(PIGPIO_DIR) && \
	make -C $(PIGPIO_DIR) -j4 && \
	sudo make install -C $(PIGPIO_DIR) 

uninstall_lib_PIGPIO:
	sudo make uninstall -C $(PIGPIO_DIR) && \
	make clean -C $(PIGPIO_DIR) -j4 && \
	sudo rm -rf $(PIGPIO_DIR) && \

# ------
clean: 
	rm -rf $(BUILD_DIR)