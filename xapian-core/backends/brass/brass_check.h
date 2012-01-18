/** @file brass_check.h
 * @brief Btree checking
 */
/* Copyright 1999,2000,2001 BrightStation PLC
 * Copyright 2002 Ananova Ltd
 * Copyright 2002,2004,2005,2006,2008,2009,2011,2012 Olly Betts
 * Copyright 2008 Lemur Consulting Ltd
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

#ifndef OM_HGUARD_BRASS_CHECK_H
#define OM_HGUARD_BRASS_CHECK_H

#include "brass_table.h"
#include "noreturn.h"

#include <iosfwd>
#include <string>

class BrassTableCheck : public BrassTable {
    public:
	static void check(const char * tablename, const std::string & path,
			  int opts, std::ostream &out);
    private:
	BrassTableCheck(const char * tablename_, const std::string &path_,
		        bool readonly, std::ostream &out_)
	    : BrassTable(tablename_, path_, readonly), out(out_) { }

	void block_check(Brass::Cursor * C_, int j, int opts);
	int block_usage(const byte * p) const;
	void report_block(int m, int n, const byte * p) const;
	void report_block_full(int m, int n, const byte * p) const;
	void report_cursor(int N, const Brass::Cursor *C_) const;

	XAPIAN_NORETURN(void failure(const char * msg) const);
	void print_key(const byte * p, int c, int j) const;
	void print_tag(const byte * p, int c, int j) const;
	void print_spaces(int n) const;
	void print_bytes(int n, const byte * p) const;

	std::ostream &out;
};

#endif /* OM_HGUARD_BRASS_CHECK_H */
