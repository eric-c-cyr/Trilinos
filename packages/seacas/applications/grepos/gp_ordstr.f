C Copyright(C) 2011 Sandia Corporation.  Under the terms of Contract
C DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
C certain rights in this software
C 
C Redistribution and use in source and binary forms, with or without
C modification, are permitted provided that the following conditions are
C met:
C 
C * Redistributions of source code must retain the above copyright
C    notice, this list of conditions and the following disclaimer.
C           
C * Redistributions in binary form must reproduce the above
C   copyright notice, this list of conditions and the following
C   disclaimer in the documentation and/or other materials provided
C   with the distribution.
C                         
C * Neither the name of Sandia Corporation nor the names of its
C   contributors may be used to endorse or promote products derived
C   from this software without specific prior written permission.
C                                                 
C THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
C "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
C LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
C A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
C OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
C SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
C LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
C DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
C THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
C (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
C OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
C 

C=======================================================================
      SUBROUTINE ORDSTR (NORD, IXORD, LOLD, NAME, ISCR)
C=======================================================================
C   --*** ORDSTR *** (GJOIN) Order a list of strings according to indices
C   --   Written by Greg Sjaardema - revised 07/11/90
C   --   Modified from ORDIX Written by Amy Gilkey 
C   --
C   --ORDSTR orders a list of strings according to a list of indices.
C   --
C   --Parameters:
C   --   NORD - IN - the number of indices
C   --   IXORD - IN - the indices of the ordered items
C   --   LOLD - IN - the length of NAME
C   --   NAME - IN - the unordered string list
C   --   ISCR - SCRATCH - size = LOLD
C   --   INEW - OUT - the ordered string list

      INTEGER IXORD(*)
      CHARACTER*(*) NAME(*)
      CHARACTER*(*) ISCR(*)

      DO 100 I = 1, LOLD
         ISCR(I) = NAME(I)
  100 CONTINUE
      DO 110 I = 1, NORD
         NAME(I) = ISCR(IXORD(I))
  110 CONTINUE

      RETURN
      END
