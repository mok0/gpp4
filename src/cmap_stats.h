/*
     cmap_stats.h: header file for cmap_stats.c
     Copyright (C) 2001  CCLRC, Charles Ballard

     This library is free software: you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation, either
     version 3 of the License, or (at your option) any later version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with This library.  If not, see
     <http://www.gnu.org/licenses/>.

*/

/*! @file cmap_stats.h
    @brief Declaration of the stats_update function.
    @author Charles Ballard.
*/

#ifndef __GUARD_MAPLIB_STATS
#define __GUARD_MAPLIB_STATS

#ifdef __cplusplus
extern "C" {
#endif

int stats_update(CMMFile_Stats *stats, void *section_begin,
                         void *section_end);

#ifdef __cplusplus
}
#endif

#endif   /* __GUARD_MAPLIB_STATS */

/*
  Local variables:
  mode: font-lock
  End:
*/
