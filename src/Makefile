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


CFLAGS += -g -Wall


.PHONY: target
target: kitasuna

objs := main.o ylinkedlist.o yarraylist.o ycommon.o ystack.o yavltree.o \
	ymap.o

kitasuna: ${objs}
	${CC} -o $@ ${CFLAGS} $^


.SUFFIXES: .c

.c.o:
	${CC} -c ${CFLAGS} $<

.PHONY: clean
clean:
	rm -rf $(objs)
