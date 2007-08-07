/*
     ccp4_vars.h: Standard strings for certain quantites
     Copyright (C) 2002  CCLRC, Martyn Winn

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

/*! @file ccp4_vars.h
    @brief Standard strings for certain quantites - for future use 
*/

#ifndef __CCP4_VARS__
#define __CCP4_VARS__

#define MTZFILENAME "data::mtzfile::filename"
#define MTZTITLE "data::mtzfile::title"
#define MTZSPACEGROUP "data::mtzfile::spacegroup_num"        
#define MTZNUMREFLS "data::mtzfile::num_reflections"
#define MTZMNF "data::mtzfile::missing_number_flag"
#define MTZSORTORDER "data::mtzfile::sort_order"          

#define CRYSTALXTALNAME "data::crystal::crystal_name"
#define CRYSTALPNAME "data::crystal::project_name"
#define CRYSTALCELL "data::crystal::cell"

#define DATASETDNAME "data::crystal::dataset::dataset_name"
#define DATASETWAVELENGTH "data::crystal::dataset::wavelength"

#define COLUMNLABEL "data::crystal_i::dataset_i::column_i::label"
#define COLUMNTYPE "data::crystal_i::dataset_i::column_i::type"

#endif  /*!__CCP4_VARS__ */
