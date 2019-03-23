AC_PREREQ([2.61])
AC_INIT([bossinit], [0.1], [mkschreder.uk@gmail.com])
AC_CONFIG_AUX_DIR(aux-dist)
AM_INIT_AUTOMAKE

AC_PROG_MAKE_SET
AC_PROG_CC
AM_PROG_AS
AC_LANG(C,ASM)

CXXFLAGS="-std=c++11 -fPIC"

AC_CONFIG_MACRO_DIR([m4])

AC_ARG_WITH([devicetree],
    [AC_HELP_STRING([--with-devicetree],
        [Specify device tree source])],
    [],
    [with_devicetree=linux])

AC_SUBST([WITH_DEVICETREE], ["$with_devicetree"])

AC_ARG_WITH([drivers],
    [AC_HELP_STRING([--with-drivers],
        [Specify drivers to include from libraries])],
    [],
    [with_drivers=none])

AC_SUBST([WITH_DRIVERS], ["$with_drivers"])

AC_ARG_WITH([libs],
    [AC_HELP_STRING([--with-libs],
        [Specify extra libraries to link])],
    [],
    [])

AC_SUBST([WITH_LIBS], ["$with_libs"])

AC_ARG_WITH([target],
    [AC_HELP_STRING([--with-target],
        [Specify which chip we are compiling for])],
    [],
    [with_target=linux])


AC_SUBST([WITH_TARGET], ["$with_target"])
AM_CONDITIONAL([WITH_TARGET_LINUX], [test "x$with_target" = xlinux])

AM_CONDITIONAL([WITH_TARGET_STM32F429ZET6], [test "x$with_target" = xstm32f429zet6])
AM_COND_IF([WITH_TARGET_STM32F429ZET6], (AC_DEFINE([WITH_TARGET_STM32F429ZET6], [1], [Build for stm32f429zet6 mcu])))

AM_CONDITIONAL([WITH_TARGET_STM32F40_41XXX], [test "x$with_target" = xstm32f40_41xxx])
AM_COND_IF([WITH_TARGET_STM32F40_41XXX], (AC_DEFINE([WITH_TARGET_STM32F40_41XXX], [1], [Build for stm32f40_41xxx mcu])))

AM_CONDITIONAL([WITH_TARGET_STM32F10X], [test "x$with_target" = xstm32f10x])
AM_COND_IF([WITH_TARGET_STM32F10X], (AC_DEFINE([WITH_TARGET_STM32F10X], [1], [Build for stm32f10x mcu])))

AC_CONFIG_FILES([Makefile include/Makefile src/Makefile])

AC_OUTPUT
