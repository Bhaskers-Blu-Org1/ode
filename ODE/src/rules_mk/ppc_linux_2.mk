#
# This is the Makeconf platform specific part for CONTEXT=ppc_linux_2
#
OBJECT_FORMAT=ELF

# boolean vars
LINUX=
LINUX_PPC=

CCFAMILY ?= gnu

CDEFS += -DLINUX_PPC -DLINUX -DUNIX -D_POSIX_SOURCE \
         -D_POSIX_C_SOURCE=199309L -D_BSD_SOURCE

#########################################
#########################################
#
# COMPILER-SPECIFIC SECTIONS BEGIN HERE
#
#########################################
#########################################

.if ${CCFAMILY}=="gnu"

# -x c++ : treat .c files as C++ code
CPP_CFLAGS += -x c++

.endif # CCFAMILY
