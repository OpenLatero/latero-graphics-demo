# latero-graphics-demo

Program that showcases the Latero device's functionality. See [OpenLatero.org](http://OpenLatero.org) for more information.

## Installation

### MacOS

Tested on macOS Tahoe 26.3.1.

Install the latero and latero-graphics libraries.

#### Build and run the app

The app can be compiled with the following commands:

```
cmake --preset default
cmake --build build
```

and ran with this command:

```
build/src/latero-graphics-demo
```

or in a single command:

```
cmake --preset default && cmake --build build && build/src/latero-graphics-demo
```

## Authors

Vincent Levesque <vleves@cim.mcgill.ca>
