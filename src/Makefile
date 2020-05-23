# Kitasuna Renga
#
# Makefile
#
# Copyright(C) 2020 Ashibananon(Yuan).
#
#
# This file is part of Kitasuna Renga.
#
# Kitasuna Renga is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Kitasuna Renga is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Kitasuna Renga.  If not, see <https://www.gnu.org/licenses/>.


CC=gcc
CFLAGS += -g -Wall -fPIC
LDFLAGS += -fPIC -shared

PWD=`pwd`
installdir?=${PWD}/out
installincdir=${installdir}/include
installlibdir=${installdir}/lib

KITASUNALIB=libkitasuna.so
test=test


.PHONY: target
target: ${KITASUNALIB} ${test}

test_objs := main.o
objs := ylinkedlist.o yarraylist.o ycommon.o ystack.o yavltree.o \
	ymap.o

${test}: ${test_objs} ${objs}
	${CC} -o $@ ${CFLAGS} $^

${KITASUNALIB}: ${objs}
	${CC} -o $@ ${LDFLAGS} $^

install: ${KITASUNALIB} ${test}
	install -d -m 0755 "${installdir}"
	install -d -m 0755 "${installincdir}"
	install -d -m 0755 "${installlibdir}"
	install -m 755 ${KITASUNALIB} "${installlibdir}"
	install -m 755 ${PWD}/*.h "${installincdir}"

.SUFFIXES: .c
.c.o:
	${CC} -c ${CFLAGS} $<

.PHONY: clean
clean:
	rm -rf $(objs) ${test_objs}
