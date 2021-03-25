APP_CFLAGS     := -Wall -Wextra -Wshadow -Werror
APP_CFLAGS     += -fvisibility=hidden -fvisibility-inlines-hidden -fno-stack-protector
APP_CFLAGS     += -fvisibility-global-new-delete-hidden -D_LIBCPP_DISABLE_VISIBILITY_ANNOTATIONS
APP_CFLAGS     += -D_LIBCPP_DISABLE_EXTERN_TEMPLATE -D_LIBCPP_HAS_NO_LIBRARY_ALIGNED_ALLOCATION
APP_CFLAGS     += -Wno-builtin-macro-redefined -D__FILE__=__FILE_NAME__
APP_CPPFLAGS   := -std=c++2a
APP_CONLYFLAGS := -std=c18
APP_LDFLAGS    := -Wl,--gc-sections -nostdlib
APP_STL        := system
