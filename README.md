# Qt Handlebars [![Build Status](https://travis-ci.org/mdhooge/qt-handlebars.svg?branch=master)](https://travis-ci.org/mdhooge/qt-handlebars)

This is a Qt-based implementation of Handlebars.
I used it to scaffold REST-like Qt applications;
it can produced hundreds of kB of source code in a couple of seconds.

It uses `flex` and `bison` to parse the templates.
And it uses Qt `QVariant` to keep the original, dynamic aspects of Handlebars.

A complete, detailed manual is available in the `doc` folder.
A demo program, with templates to show all the functionalities, is also
available in the folder.

Because generating the flex & bison output files isn't always straightforward,
working versions are provided in `src/bison-flex_ref`.

