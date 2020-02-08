ACLOCAL_AMFLAGS = -I m4
lib_LTLIBRARIES = libmultichain-cpp.la
pkginclude_HEADERS = \
    ../include/multichain-cpp/multichain-cpp.hpp \
    ../include/multichain-cpp/MultiChain.hpp \
    ../include/multichain-cpp/Stream.hpp \
    ../include/multichain-cpp/Item.hpp
    

libmultichain_cpp_la_CXXFLAGS = -std=c++17 -Werror -Wall -I../include $(JSONCPP_CFLAGS) $(CURL_FLAGS)
libmultichain_cpp_la_LIBADD = $(JSONCPP_LIBS) $(CURL_LIBS)
libmultichain_cpp_la_SOURCES = MultiChain.cpp Stream.cpp Item.cpp
libmultichain_cpp_la_LDFLAGS = -no-undefined

bin_PROGRAMS = example
example_SOURCES = example.cpp
example_CXXFLAGS = -std=c++17 -I../include -Werror -Wall $(JSONCPP_CFLAGS)
example_LDADD = libmultichain-cpp.la $(JSONCPP_LIBS)
