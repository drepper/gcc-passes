Discover GCC Optimization Passes
================================

This project is a script which, in conjunction with the included GCC plugin,
allows to discover which optimization passes GCC executes for which optimization
level.  All the levels of `-O` are supported (`0`, `g`, `1`, `s`, `2`, `3`, `fast`).

When the script is called with one of the levels as the command line argument it
shows all the passes by name, nested according to the part of the compiler they
belong too.

When the script is given two parameters the passes used in the invocations
according to the two optimization levels are compared and differences highlighted.

As an example see the beginning of the output of the following command:

     $ ./gcc-passes.sh 0
     GIMPLE pass:
         pass *warn_unused_result
         pass omplower
         pass lower
         pass ehopt
         pass eh
         pass cfg
         pass *warn_function_return
         pass ompexp
         pass *build_cgraph_edges
     simple IPA pass:
         pass *free_lang_data
         pass visibility
         pass build_ssa_passes
     GIMPLE pass:
         pass    fixup_cfg
         pass    ssa
         pass    *rebuild_cgraph_edges
     simple IPA pass:
         pass opt_local_passes
     GIMPLE pass:
         pass    fixup_cfg
         pass    *rebuild_cgraph_edges
         pass    local-fnsummary
         pass    einline

This output shows the different types of passes (GIMPLE, IPA, …).  This might vary
from compiler version to version.  What this also shows that even with `-O0` some
optimization passes are executed.


Author: Ulrich Drepper <drepper@gmail.com>

