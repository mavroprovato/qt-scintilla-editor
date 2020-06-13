Overview
========

An editor based on the Scintilla editor component, using the Qt framework.

Building
========

In order to build the project, Scintilla and the QT component need to be built first. Clone the Scintilla repository in
a directory that is at the same level with the project directory by running the following:

```shell script
hg clone http://hg.code.sf.net/p/scintilla/code scintilla-code
```

Then build it with:

```shell script
cd scintilla-code/qt/ScintillaEdit
python WidgetGen.py
qmake # use qmake CONFIG+=debug to build the debug version
make
```

Now you are ready to build the project. Change to the project directory and create a build directory with

```shell script
mkdir build-release
cd build-release
qmake ../qt-scintilla-editor.pro # use qmake CONFIG+=debug to build the debug version
make
```

Now you can run the editor like this:

```shell script
LD_LIBRARY_PATH=../../scintilla-code/bin/ ./qt-scintilla-editor
```