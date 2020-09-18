APP_CFLAGS      := -Wall -Wextra -Wshadow -Werror -fvisibility=hidden
APP_CFLAGS      += -Wno-builtin-macro-redefined -D__FILE__=__FILE_NAME__
APP_CONLYFLAGS  := -std=c18
APP_STL         := c++_static
