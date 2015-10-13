Examples of kodo-cpp
--------------------

This directory contains a set of examples which aim to use some of the
functionality available in kodo-cpp.

Their wscript_build file all points to the shared library version of the kodo-c
library. This means that the shared library version of kodo-c needs to be
available for them to be executable.
If not you will get the following error::

    ./use_trace_layers: error while loading shared libraries: libkodoc.so: cannot open shared object file: No such file or directory

To resolve this issue you need to make the shared library available. This is
can be done by copying the library to one of you systems default search paths
for shared libs, e.g., ``/usr/lib/``. Alternatively you can also copy the
library so that it's is located next to the executable.

The last approach can be automated using the waf build system. You simply need
to execute the install command with the following parameters::

    ./waf install --options=install_shared_libs,install_path="path/of/your/choosing"
