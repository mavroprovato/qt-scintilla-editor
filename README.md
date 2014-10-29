Overview
========

An editor based on the scintilla editor compotnent, using the Qt framework.

Installation
============

In order to build the project, Scintilla needs to be built first. Clone the scintilla repository with:

```
clone http://hg.code.sf.net/p/scintilla/code scintilla-code
cd scintilla-code
```

Then build the release version with:

```
cd qt/ScintillaEdit
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