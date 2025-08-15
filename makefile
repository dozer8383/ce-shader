# ----------------------------
# Makefile Options
# ----------------------------

NAME = SHADER
DESCRIPTION = "look ma, no GPU"
COMPRESSED = NO
ARCHIVED = YES

CFLAGS = -Wall -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
