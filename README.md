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

License
=======

```
Copyright (c) 2013-2020, Kostas Kokkoros

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
```
