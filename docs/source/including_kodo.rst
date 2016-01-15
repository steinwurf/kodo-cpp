.. including_kodo:

Including kodo-cpp in Your Application
======================================

This guide shows how to include the kodo-cpp library in your application.

First of all, you need to build kodo-cpp following the :ref:`getting_started`
guide. If you want to cross-compile for your target platform (e.g. Android,
iOS, Raspberry Pi), please follow the :ref:`cross_compile` section.

In principle, you can use the library with any build system. Basically,
you can choose between the shared library and the static library.

Shared Library
--------------

In many cases, it is easier to include the *shared* library in
your application. With the following command, you can copy the compiled
shared library to the target folder specified by the ``install_path`` option.
In this example, we will create the ``shared_test`` folder for this purpose::

    python waf install --install_shared_libs --install_path="./shared_test"

Actually, kodo-cpp uses the kodo-c shared library that is called ``libkodoc.so``
on Linux, ``kodoc.dll`` on Windows and ``libkodoc.dylib`` on Mac OSX. You can
link with this shared library using your own build system. You also need to
include the ``kodocpp.hpp`` header in your code. This header file depends on
other headers from kodo-cpp and on ``kodoc.h`` from kodo-c. All the necessary
header files are installed to the ``include`` folder within the specified
``install_path``.

Now we copy an existing kodo-cpp example (sparse_seed) to the
``shared_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/sparse_seed/sparse_seed.cpp shared_test/myapp.cpp
    cd shared_test

The following command demonstrates the necessary flags for the g++ compiler
(other compilers require similar settings)::

    g++ myapp.cpp -o myapp -std=c++11 -I./include -L. -Wl,-Bdynamic -lkodoc \
    -Wl,-rpath .

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the shared library.

Now you should be able to run the new binary::

    ./myapp

If you dynamically link your application with the shared library, then you
have to copy the shared library to a folder where your system can find it
when you execute your application. On Windows, you typically place the DLL
in the same folder as your executable. On Unix systems, you can set the
``rpath`` of your executable or you can adjust ``LD_LIBRARY_PATH`` to include
the path where you installed the shared library.

Static Library
--------------

After building kodo-cpp, you can install the static libraries to your target
folder with the following command (the ``install_path`` option specifies
the target folder which will be ``static_test`` in this example)::

    python waf install --install_static_libs --install_path="./static_test"

Actually, kodo-cpp is a header-only wrapper for the kodo-c static library that
is called ``libkodoc_static.a`` on Linux and Mac and ``kodoc_static.lib`` on
Windows. The install command also installs the static libraries from the
kodo-cpp dependencies (you will need the ``fifi``and ``cpuid`` libraries as well
to link your application).

You can link with these static libraries using your own build system. Of course,
you will need to include ``kodocpp.hpp`` in your code that depends on other
header files. All the necessary header files are installed to the ``include``
folder within the specified ``install_path``.

Now we copy an existing kodo-cpp example (sparse_seed) to the
``static_test`` folder and we compile it to a binary called ``myapp``::

    cp examples/sparse_seed/sparse_seed.cpp static_test/myapp.cpp
    cd static_test

The following command demonstrates the necessary flags for the gcc/g++ compiler
(other compilers require similar settings)::

    g++ myapp.cpp -o myapp -std=c++11 -I./include -Wl,-Bstatic -L. \
    -lkodoc_static -lfifi -lcpuid -Wl,-Bdynamic

In practice, you should set the ``-I`` and ``-L`` flags to the path where you
installed the static libraries.

Now you should be able to run the new binary (note that this binary will
be quite large, since it includes all the static libraries)::

    ./myapp

To reduce the size of the resulting binary, you can add the ``-s`` flag to the
g++ command above to strip all debugging symbols.
