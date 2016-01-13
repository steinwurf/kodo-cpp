.. _cross_compile:

Cross-compilation and tool options
==================================

This section describes the waf configuration options that are used to
cross-compile Kodo for different platforms and to change some properties
of your builds.

.. contents:: Table of Contents
   :local:

Generic tool options
--------------------

cxx_debug
    By default, our build system will remove all debugging info from the
    generated binaries. You can enable the debugging symbols with the
    ``cxx_debug`` option::

        python waf configure --cxx_debug

    .. note:: Using this option will add a ``_debug`` postfix to the waf build
              output path. For example, your binaries will be built in
              ``build\linux_debug`` or ``build\win32_debug``.

run_tests
    You can use this option to run the unit tests after your build is
    completed::

        python waf build --run_tests

run_benchmark
    You can use this option to run a specific benchmark after your build is
    completed::

        python waf build --run_benchmark=my_benchmark

enable_codecs
    You can configure kodo-c to only enable some desired codecs and disable
    all others. For example::

        python waf configure --enable_codecs=full_vector

    Run ``python waf --help`` to list the available codecs. You can even
    select multiple codecs with a comma-separated list::

        python waf configure --enable_codecs=full_vector,seed,sparse_seed


Cross-compilation options
-------------------------

We use "mkspecs" (short for "make specifications") to instruct ``waf`` to select
a specific compiler based on its version number (e.g. ``4.8``) and binary name
(e.g. ``g++-4.8`` or ``arm-linux-androideabi-g++``). Some mkspecs also
include compiler and linker flags to select a CPU architecture or
change some other characteristics of the build process. You can select an
mkspec with the ``cxx_mkspec`` tool option, see various examples below.

By using an mkspec, we can easily select a toolchain that can compile binaries
for different platforms. First, you have to install the appropriate toolchain,
then you can configure Kodo with the corresponding mkspec.

Different mkspecs are available on different operating systems. You can
get the list of the currently supported mkspecs with the ``config.py`` helper
script located in the Kodo root folder::

    python config.py

This helper script automatically updates itself when you run it. You can use
this script to go through the common configuration options without typing
too much.

The full list of currently tested mkspecs can be seen at the bottom of the
Steinwurf Buildbot page (mkspecs in red are temporarily offline):
http://buildbot.steinwurf.dk

Android
.......
You need a standalone Android toolchain to compile for Android. You can follow
the instructions in our `Android guide`_ to quickly create a toolchain using
the latest Android NDK.

You can also download a toolchain for your platform from this page:
http://bongo.steinwurf.dk/files/toolchains

You also need the Android SDK, because we need to find the ``adb`` tool
during the configure step. If you do not have it already the `Android
guide`_ describes both where to download the Android SDK and how to get the
``adb`` tool. To ensure our build system will pick up the dependencies the
easiest solution is to add the path to ``adb`` and the ``bin`` folder of
the standalone toolchain to your PATH. For example, you can add the
following lines to your ``~/.profile`` (please adjust the paths to match
your folder names and locations)::

    PATH="$PATH:$HOME/toolchains/android-sdk-linux-r22.6/platform-tools"
    PATH="$PATH:$HOME/toolchains/arm-linux-androideabi-4.8-r10/bin"

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are really in your PATH with these
commands::

    adb version
    arm-linux-androideabi-g++ --version

Once you have everything in your PATH, use the following mkspec when you
configure Kodo (you may also select another Android mkspec if available
in the list provided by ``config.py``)::

    python waf configure --cxx_mkspec=cxx_android_gxx48_armv7

The configure command should find your toolchain and the necessary binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated Android binaries in the
``build/cxx_android_gxx48_arm`` folder. You can transfer these binaries to your
Android device with adb. Read our `Android guide`_ for more information on this.

If you don't want to add the Android toolchains to your PATH, then we also
provide explicit options to specify these folders during the configure step.
Here is an example for that::

    python waf configure --cxx_mkspec=cxx_android_gxx48_armv7 \
    --android_sdk_dir=~/toolchains/android-sdk-linux-r22.6 \
    --android_ndk_dir=~/toolchains/arm-linux-androideabi-4.8-r10

.. note:: If you want to use the generated static libraries with ``ndk-build``,
          then make sure that you process at least one C++ source file (.cpp)
          with ``ndk-build`` (this can be a dummy cpp file). Otherwise you
          will get a lot of linkage issues, because ``ndk-build`` does not link
          with the C++ standard library by default.

.. _Android guide: https://github.com/steinwurf/steinwurf-labs/blob/master/docs/android-c-application.rst


iOS
...
You need to install the latest XCode to compile for iOS. Please make sure
that you also have the Apple command-line tools in your PATH by executing
the following command on OSX Mavericks::

    xcode-select --install

Open a Terminal, and use this command to check if you have the Apple LLVM
compiler in your PATH::

    clang++ --version

XCode installs the iOS SDK to a standard location, so you only need to specify
the iOS mkspec when you configure (please note that the version numbers in
the name of the mkspec may change, so use ``config.py`` to list the currently
available versions)::

    python waf configure --cxx_mkspec=cxx_ios70_apple_llvm_armv7

Then you can build Kodo as usual::

    python waf build

You can find the generated iOS binaries in the
``build/cxx_ios70_apple_llvm_armv7`` folder. You can transfer these binaries
to your iOS device with any tool you like. Please note that these are
command-line binaries, so you will need a terminal application to run them.


Raspberry Pi
............
You can download our pre-built Raspberry Pi toolchain for 64-bit Linux here:
http://buildbot.steinwurf.dk/toolchains/linux/

Extract ``raspberry-gxx49-arm.zip`` to a folder of your liking. You also need
to add the `bin`` folder of the Raspberry toolchain to your PATH. For example,
you can add the following lines to your ``~/.profile`` (please adjust the
paths to match your folder names and locations)::

    PATH="$PATH:$HOME/toolchains/raspberry-gxx49-arm/bin"

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are in your PATH with this command::

    raspberry-gxx49-arm-g++ --version

Go to your Kodo folder, configure Kodo with the following mkspec::

    python waf configure --cxx_mkspec=cxx_raspberry_gxx49_arm

The configure command should find your toolchain binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated binaries in the
``build/cxx_raspberry_gxx49_arm`` folder. You can transfer these binaries
to your Raspberry Pi with any tool you like (e.g. SCP).


OpenWrt
.......
You should build a compatible OpenWrt toolchain for your target device.
Here we explain how to do that for a device with an ARM CPU.

First, you should install the required packages to build the toolchain (this
list works for Ubuntu and Debian)::

    sudo apt-get install gcc g++ subversion git-core build-essential gawk libncurses5-dev zlib1g-dev unzip

Then clone the standard OpenWrt toolchain (you change the target path if
you prefer)::

    cd ~/toolchains
    git clone git://git.openwrt.org/openwrt.git
    cd openwrt

This guide was written using revision 46117 of OpenWrt, and it is recommended
to check out the same revision (you can also try the master).
You can check your current revision::

    git show --summary

To find the corresponding git commit ID and check out revision 46117::

    git log --grep=46117
    git checkout be88f0504603a

This command will pop up a menuconfig window::

    make package/symlinks

Here you should select a Target System and a Target Profile that are
compatible with your OpenWrt device.

Save this initial menuconfig, and then open the full menuconfig::

    make menuconfig

Here we need to change the GCC version to 4.8.x::

    [*] Advanced configuration options (for developers)  --->
     Toolchain Options  --->
      GCC compiler Version (gcc 4.8.x with Linaro enhancements)  --->
       (X) gcc 4.8.x with Linaro enhancements

Save the configuration and build the OpenWrt toolchain (``-j4`` uses 4 cores to
speed up the process)::

    make -j4

After the toolchain is built, you need to add the ``bin`` folder of the
generated toolchain to your PATH (the toolchain is created in the
``staging_dir`` folder). You should also set the ``STAGING_DIR`` variable
to point to the ``staging_dir`` folder. For example, you can add the following
lines to your ``~/.profile`` (please adjust the paths to match your folder
names and locations if necessary)::

    PATH="$PATH:$HOME/toolchains/openwrt/staging_dir/toolchain-arm_v6k_gcc-4.8-linaro_uClibc-0.9.33.2_eabi/bin"
    STAGING_DIR="$HOME/toolchains/openwrt/trunk/staging_dir/"
    export STAGING_DIR

You need to log in again or open a new terminal to get the updated PATH.
You can check that the required binaries are in your PATH with this command::

    arm-openwrt-linux-g++ --version

Go to your Kodo folder, and configure Kodo with the following mkspec::

    python waf configure --cxx_mkspec=cxx_openwrt_gxx48_arm

The configure command should find your toolchain binaries,
and you can build the codebase as usual after this::

    python waf build

You can find the generated binaries in the
``build/cxx_openwrt_gxx48_arm`` folder. You can transfer these binaries
to your OpenWrt device with any tool you like (e.g. SCP). The binaries
can be a bit large, because the mkspec embeds the C++ standard library (with
the ``-static-libstdc++`` linker flag). The ``libstdcpp`` package is usually
not installed on OpenWrt devices, or it might be incompatible with the
GCC 4.8.x compiler.

Note that the following packages are required on your OpenWrt device to
run the generated binaries, you can run these commands on your device if it
has Internet connectivity::

    opkg install libpthread
    opkg install librt

Alternatively, you can activate these packages in ``menuconfig`` and deploy
the generated ``*.ipk`` files manually on the device (with SCP and opkg)::

    Base system  ->
        <*> libpthread
        <*> librt


Other toolchains
................
Other toolchains might also work if you specify your custom compiler with
the CXX variable when you configure Kodo::

    CXX=/path/to/custom/compiler/g++ python waf configure

This compiler must have a recognizable name (e.g. it contains the ``g++``
string) and waf must be able to determine its version to accept it.
