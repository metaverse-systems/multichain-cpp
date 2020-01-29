AC_PREREQ([2.69])
AC_INIT([multichain-cpp], [0.0.1], [tim@metaverse.systems], [multichain-cpp], [https://metaverse.systems])
LT_INIT
AC_CONFIG_SRCDIR([src/MultiChain.cpp])
AC_CONFIG_HEADERS([config.h])

PKG_PROG_PKG_CONFIG
PKG_INSTALLDIR

AC_CONFIG_MACRO_DIR([m4])

AC_PROG_CXX
AM_INIT_AUTOMAKE([subdir-objects])

PKG_CHECK_MODULES([JSONCPP], jsoncpp)
PKG_CHECK_MODULES([CURL], libcurl)

AC_CONFIG_FILES([Doxyfile])
AC_CONFIG_FILES([multichain-cpp.pc])
AC_OUTPUT(Makefile src/Makefile)

