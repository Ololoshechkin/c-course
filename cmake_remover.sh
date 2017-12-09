#!/bin/bash
ls
find . -name "Makefile*"  | xargs git rm
find . -name "CMakeF*"    | xargs git rm
find . -name "CMakeC*"    | xargs git rm
find . -name "cmake*"     | xargs git rm