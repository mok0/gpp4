C
C     pack_f.f: (de)compress diffraction image files
C     Copyright (C) 1995  Jan P Abrahams
C
C   This program is free software: you can redistribute it and/or modify it
C   under the terms of the Lesser GNU General Public License as published by
C   the Free Software Foundation, either version 3 of the License, or (at
C   your option) any later version.
C
C   This program is distributed in the hope that it will be useful, but
C   WITHOUT ANY WARRANTY; without even the implied warranty of
C   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the Lesser
C   GNU General Public License for more details.
C
C   You should have received a copy of the Lesser GNU General Public
C   License along with this program. If not, see
C   <http://www.gnu.org/licenses/>.
c
c
      subroutine pack_wordimage (data, x, y, filn)
c     =================================
c
c   Pack data stored in the array DATA with dimensions x * y in file FILN.
c
      implicit none
c
      character*(*) filn
      integer*4 x, y, j
      integer*2 data(x, y)
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external pack_wordimage_f

      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call pack_wordimage_f(data, x, y, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine v2pack_wordimage (data, x, y, filn)
c     =================================
c
c   Pack data stored in the array DATA with dimensions x * y in file FILN.
c
      implicit none
c
      character*(*) filn
      integer*4 x, y, j
      integer*2 data(x, y)
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external v2pack_wordimage_f

      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call v2pack_wordimage_f(data, x, y, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine pack_longimage (data, x, y, filn)
c     =================================
c
c   Pack data stored in the array DATA with dimensions x * y in file FILN.
c
      implicit none
c
      character*(*) filn
      integer*4 x, y, j
      integer*4 data(x, y)
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external pack_wordimage_f
c
      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call pack_wordimage_f(data, x, y, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine v2pack_longimage (data, x, y, filn)
c     =================================
c
c   Pack data stored in the array DATA with dimensions x * y in file FILN.
c
      implicit none
c
      character*(*) filn
      integer*4 x, y, j
      integer*4 data(x, y)
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external v2pack_wordimage_f
c
      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call v2pack_wordimage_f(data, x, y, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine readpack_word (data, filn)
c     =================================
c
c     Read a packed image from file 'filn' into array 'data'. If you want 
c     to generate the mirror-image, (interchange first and last stripes, etc.)
c     call "mirror_wordimg(data, nfast, nslow)", where nfast and nslow contain
c     the number of fast and slow indices, after reading the packed image.
c
      implicit none
c
      character*(*) filn
      integer*2 data, j
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external readpack_word_f
c
      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call readpack_word_f(data, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine readpack_long (data, filn)
c     =================================
c
c     Read a packed image from file 'filn' into array 'data'. If you want 
c     to generate the mirror-image, (interchange first and last stripes, etc.)
c     call "mirror_wordimg(data, nfast, nslow)", where nfast and nslow contain
c     the number of fast and slow indices, after reading the packed image.
c
      implicit none
c
      character*(*) filn
      integer*4 data, j
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external readpack_long_f
c
      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call readpack_long_f(data, filnarray)
      return
      end

c*******************************************************************************
c
c
c
      subroutine imsiz (filn, x, y)
c     =================================
c
c     Determines the size of the the packed image "filename" after 
c     unpacking.The dimensions are returned in x and y. 
c     Read a packed image from file 'filn' into array 'data'.
c
      implicit none
c
      character*(*) filn
      integer*4 x, y, j
      integer*4 filnarray(1025)
c
c     ..
c     .. External C-routine
      external imsiz_f
c
      do 10, j = 1, len(filn)
         if (filn(j:j) .ne. ' ') then
            filnarray(j) = ichar(filn(j:j))
         else
            filnarray(j) = 0
         endif
 10   continue
      filnarray(len(filn) + 1) = 0
      call imsiz_f(filnarray, x, y)
      return
      end

c*******************************************************************************
