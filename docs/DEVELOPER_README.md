# Development of the Nano Shell

<https://brennan.io/2015/01/16/write-a-shell-in-c/>

## Lifetime

A shell has three main phases in its lifecycle.

1.  **Initialize**: The shell reads configuration files that affects the shell's behavior.
1.  **Interpret**: The shell reads commands from stdin. This could be interactive
    (i.e. input by user) or from a file.
1.  **Terminate**: The shell executes shutdown commands, frees memory, and exits.
