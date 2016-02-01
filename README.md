# Emacs Module Primer

As of Emacs 25, you are now able to load shared libraries
for that interact with existing Lisp functions, or introduce
new ones.

This is a primer on how this functionality may be used using C,
although other languages should work as well.

The module exposes a single function `return-t` callable from Lisp, that always
returns `t`. It demonstrates how to declare and expose your own functions, as well
as call existing Emacs ones.

## Notes

Emacs won't reload files that have already been loaded - it'll just return `t` and carry
on with the old version of the module. I don't know of any way around this except for
restarting your Emacs session, or better yet keeping a separate Emacs session just for
testing.
