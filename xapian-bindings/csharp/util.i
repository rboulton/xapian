%{
/* csharp/util.i: custom C# typemaps for xapian-bindings
 *
 * Copyright (c) 2005 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */
%}

namespace Xapian {

%typemap(cscode) class MSetIterator %{
    public static MSetIterator operator++(MSetIterator it) {
	return it.next();
    }
    public static MSetIterator operator--(MSetIterator it) {
	return it.prev();
    }
%}

%typemap(cscode) ESetIterator %{
    public static ESetIterator operator++(ESetIterator it) {
	return it.next();
    }
    public static ESetIterator operator--(ESetIterator it) {
	return it.prev();
    }
%}

%typemap(cscode) TermIterator %{
    public static TermIterator operator++(TermIterator it) {
	return it.next();
    }
%}

%typemap(cscode) ValueIterator %{
    public static ValueIterator operator++(ValueIterator it) {
	return it.next();
    }
%}

%typemap(cscode) PostingIterator %{
    public static PostingIterator operator++(PostingIterator it) {
	return it.next();
    }
%}

%typemap(cscode) PositionIterator %{
    public static PositionIterator operator++(PositionIterator it) {
	return it.next();
    }
%}

}
