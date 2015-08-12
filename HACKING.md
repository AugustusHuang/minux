Minux Hacking Guide
===================

This guide is influenced by *SBCL Hacking Guide*.  

Table of Contents
-----------------

	1. Modules and functions
	2. Comments
	3. Debug messages

### Modules and functions
Every module, except for those really are 'kernels', should be made to be
configurable by users, i.e. users can enable/disable it, can resize the
resources of it, can change some property of it, etc.  
**Module names** should be exact and short, like `process` or `task`,
functions belong to this module should have names prefixed with `process_`,
and follow with their actions, e.g. `process_create` if the purpose of the
function is to create a brand new process, and `process_idle` if this is a
process whose name is **idle** (i.e. noun describes noun).  
Every kernel non-static non-API function should return error value, so its
return type should be `int`, if it has to return something, pass it through
`retval` slot in the `process` structure.

### Comments
Comments can be of two kinds: **long comment** and **short comment**. 

**Long comment** should begin with `/*` and end with `*/`, in between
there should be sentence(s), so they will be capitalized.  
**Short comment** should also begin with `/*` and end with `*/`, phrase(s)
lie in between so there's no need to capitalize them.  
**Long comment** which occupies more than one line should have a `*` before
each line.  
If it's necessary to draw pictures in the comment, make it looks well within
a 80x24 terminal, since it's the *de facto* size.  

Comments can appear within different scale of contexts, **file-wise**,
**statement-wise** and **item-wise**, **file-wise** comments should appear
in the top of a file and should only be **long comment**, and it should be

	/*
	 * blablabla 
	 */

**statement-wise** comments can be **long-comment** or **short-comment**,
so can **item-wise** comments, if **item-wise** comments don't lie on the same
line as the described item, it should appear above it.  
If **long-comments** are **statement-wise** or **item-wise**, they should be

	/* blablabla
	 * blablabla */

### Debug messages
Because I decide to use **ARM**'s semihost property, function `panic` will
be a great place to play kernel running error.  
If debug messages and information are necessary, change the macro `CONFIG_DEBUG`
to 1 and use `#ifdef CONFIG_DEBUG` and `#endif` wrapper around debug code.  
Of course `panic` is not enough, use `printf` then!
