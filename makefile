# ----------------------------
# Makefile Options
# ----------------------------

NAME = SHADER
DESCRIPTION = "look ma, no GPU"
COMPRESSED = NO
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
