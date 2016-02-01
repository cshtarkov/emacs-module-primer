/* Emacs Module Primer

As of Emacs 25, you are now able to load shared libraries
for that interact with existing Lisp functions, or introduce
new ones.

This is a primer on how this functionality may be used using C,
although other languages should work as well.
*/

// You need to include the Emacs module API, this is part of
// the source distribution.
#include "emacs-module.h"

// You need to state that your plugin is GPL compatible
// by having this symbol in the symbol table, otherwise
// Emacs will refuse to load it.
int plugin_is_GPL_compatible;

// This is a simple C function that will always return the
// Lisp value "t".
//
// *env is a pointer to the Emacs environment as described in the API.
// nargs is the number of arguments the function accepts.
// args[] is an array of length nargs.
// data is optionally passed data.
static emacs_value return_t(emacs_env *env, ptrdiff_t nargs,
                            emacs_value args[], void *data) {
    // env->intern(env, name) will return the emacs_value
    // of an internal symbol (i.e. defined in Emacs' C core, not
    // in the Lisp files.
    return env->intern(env, "t");
}

// This function is required as it is called when Emacs
// loads your module. You have a pointer to a runtime structure,
// but pretty much the only field you're interested in is the environment.
int emacs_module_init(struct emacs_runtime *ert) {
    // Get the Emacs environment.
    emacs_env *env = ert->get_environment(ert);

    // Create a function definiton of the function declared above.
    // 1, 1 are the minimum and maximum number of arguments.
    // The first NULL is the docstring.
    // The second NULL is optionally passed data.
    emacs_value f_return_t = env->make_function(env, 0, 0, return_t,
                                                NULL, NULL);

    // Get a 'pointer' to the Emacs function "fset", which
    // accepts a symbol and a definition, and sets the symbol
    // to that definition.
    emacs_value i_fset = env->intern(env, "fset");

    // Create a symbol "return-t" for the function we created.
    emacs_value i_sym = env->intern(env, "return-t");

    // Prepare the arguments for calling "fset" - symbol and definition.
    emacs_value args[] = { i_sym, f_return_t };

    // Call "fset" with the two arguments.
    env->funcall(env, i_fset, 2, args);

    // Not sure about possible return values here.
    return 0;
}
