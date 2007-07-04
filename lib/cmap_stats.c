/*
     cmap_stats.c: deal with map statistics.
     Copyright (C) 2001  CCLRC, Charles Ballard

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later
     version.

     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.

     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free
     Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
     Boston, MA 02110-1301 USA

*/
#include <math.h>
#include "cmaplib.h"
#include "cmap_stats.h"
#include "cmap_errno.h"

/*! Internal: use floats in range section_begin to section_end
  to update the map statistics.
  \param stats (CMMFile_Stats *)
  \param section_begin (void *) start of section
  \param section_end (void *) one past end-of-section
  \return total of map elements so far */
int stats_update(CMMFile_Stats *stats, void *section_begin,
                         void *section_end)
{        
  float *ufp = (float *) section_begin;
  double val;
      
  if (stats->total == 0 && *ufp < -1.0e10 ) {         
    stats->offset = *ufp;
  } 
  while (ufp < (float *) section_end) {
    val = (double) (*ufp - stats->offset);
    stats->mean += val;
    stats->rms += val * val;
    stats->min = MIN( stats->min, *ufp);
    stats->max = MAX( stats->max, *ufp);
    
    ufp++;
  }
  
  stats->total += (float *)section_end - (float *)section_begin;
                
  return (stats->total);
}

