/*
 *
 * (C) 2013-19 - ntop.org
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include "ntop_includes.h"

/* ******************************************* */

ThreadedActivityStats::ThreadedActivityStats(const ThreadedActivity *ta) {
  max_duration_ms = last_duration_ms = 0;
  threaded_activity = ta;
}

/* ******************************************* */

ThreadedActivityStats::~ThreadedActivityStats() {
}

/* ******************************************* */

void ThreadedActivityStats::updateStats(u_long duration_ms) {
  last_duration_ms = duration_ms;

  if(duration_ms > max_duration_ms)
    max_duration_ms = duration_ms;
}


/* ******************************************* */

void ThreadedActivityStats::lua(lua_State *vm) {
  lua_newtable(vm);

  lua_push_uint64_table_entry(vm, "max_duration_ms", (u_int64_t)max_duration_ms);
  lua_push_uint64_table_entry(vm, "last_duration_ms", (u_int64_t)last_duration_ms);

  lua_pushstring(vm, "duration");
  lua_insert(vm, -2);
  lua_settable(vm, -3);
}