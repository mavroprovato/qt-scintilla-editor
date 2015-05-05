Overview
========

An editor based on the Scintilla editor compotnent, using the Qt framework.

Installation
============

In order to build the project, Scintilla needs to be built first. Clone the
Scintilla repository in a directory that is at the same level with the project
directory, by running the following:

```
hg clone http://hg.code.sf.net/p/scintilla/code scintilla-code
```

Then build the release version with:

```
cd scintilla-code/qt/ScintillaEdit
python WidgetGen.py
qmake
make
```

And the debug version with:

```
qmake CONFIG+=debug
make clean
make
```
