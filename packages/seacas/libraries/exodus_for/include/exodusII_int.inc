!*****************************************************************************
! Copyright 1994 Sandia Corporation. Under the terms of Contract
! DE-AC04-94AL85000 with Sandia Corporation, the U.S. Governement
! retains certain rights in this software.
!
! See the COPYRIGHT file for copying and redistribution conditions.
!
!*****************************************************************************
!
! EXODUSII_INT - exodus II internals include file
!
!*****************************************************************************
!  --
!  --  This file contains define constants that are used to refer to
!  --  netCDF variables, attributes, or dimensions in which the EXODUS
!  --  II data are stored.  Using the defined constants will allow the
!  --  names of the netCDF entities to be changed easily in the future
!  --  if needed.
!  --
!  --Constants:
!  --
!  --ATTRIBUTES
!  --
!  --   A_TYPE     The EXODUS II file type:
!                    "r" = regular
!                    "h" = history
!  --   A_TITLE    The database title
!  --   A_VERSION  The EXODUS II version number
!  --   A_NAMELB   The element type name for a given element block
!  --
!  --DIMENSIONS
!  --
!  --   D_NUMNOD   The number of nodes
!  --   D_NDIM     The number of coordinates per node
!  --   D_NUMEL    The number of elements
!  --   D_NELBLK   the number of element blocks
!  --   D_NUMELB   The number of elements in a given element block
!  --   D_NELNOD   The number of nodes per element in a given element
!  --              block
!  --   D_NATRIB   The number of attributes in a given element block
!  --   D_NUMESS   The number of side sets
!  --   D_NEESS    The number of elements in a given side set
!  --   D_NNESS    The number of nodes in a given side set
!  --   D_NUMNPS   The number of node sets
!  --   D_NNNPS    The number of nodes in a given node set
!  --   D_NQAREC   The number of QA records
!  --   D_NINFO    The number of information records
!  --   D_NVARGL   The number of global variables
!  --   D_NVARNP   The number of nodal variables
!  --   D_NVAREL   The number of element variables
!  --   D_NVARHI   The number of history variables
!  --   D_N4       General dimension of length 4
!  --   D_STRLEN   General dimension of length MXSTLN used for lengths
!  --              of names
!  --   D_LINLEN   General dimension of length MXLNLN used for lengths
!  --              of long strings
!  --   D_TIMSTP   The number of whole time steps
!  --   D_HTMSTP   The number of history time steps
!  --
!  --VARIABLES
!  --
!  --   V_COORD    The nodal coordinates
!  --   V_NAMECO   The names of coordinates
!  --   V_IDEBLK   The element block IDs
!  --   V_ICONK    The element connectivity for a given element block
!  --   V_ATRIBK   The list of attributes for a given element block
!  --   V_MAP      The element order map
!  --   V_IDESS    The side set Ids
!  --   V_FACESS   The distribution factor for each node in a given
!  --              side set
!  --   V_ELSSET   The list of elements in a given side set
!  --   V_NDSSET   The list of nodes in a given side set
!  --   V_IDNPS    The node set IDs
!  --   V_NODSET   The list of nodes in a given node set
!  --   V_FNPS     The list of distribution factors in a given node set
!  --   V_INFO     The information records
!  --   V_TIMEHS   The simulation times for history time steps
!  --   V_TIME     The simulation times for whole time steps
!  --   V_QATITL   The QA records
!  --   V_ISEVOK   The element variable truth table
!  --   V_NAMEGV   The names of global variables
!  --   V_VARGL    The values of global variables
!  --   V_NAMENV   The names of nodal variables
!  --   V_VARNP    The values of nodal variables
!  --   V_NAMEEV   The names of element variables
!  --   V_VAREL    The values of element variables for a given element
!  --              block and given element within that block
!  --   V_NAMEHV   The names of the history variables
!  --   V_VARHI    The values of the history variables
!  --

      character A_TYPE*4,    A_TITLE*5,   A_VERSION*7, A_NAMELB*9
      character D_NUMNOD*9,  D_NDIM*7,    D_NUMEL*8,   D_NELBLK*10
      character D_NUMELB*13
      character D_NELNOD*14, D_NATRIB*14, D_NUMESS*13, D_NEESS*9   
      character D_NNESS*10
      character D_NUMNPS*13, D_NNNPS*10,  D_NQAREC*10, D_NINFO*8  
      character D_NVARGL*11  D_NVARNP*11, D_NVAREL*12, D_NVARHI*11
      character D_N4*4,      D_STRLEN*10
      character D_LINLEN*8,  V_COORD*5,   V_NAMECO*10, V_IDEBLK*9
      character V_ICONK*7,   V_ELSSET*7,  V_INFO*12
      character V_ATRIBK*6,  V_MAP*8,     V_IDESS*12,  V_FACESS*12
      character V_NDSSET*7,  V_IDNPS*12,  V_NODSET*7,  V_FNPS*12
      character V_TIMEHS*9,  V_TIME*10,   V_QATITL*10, V_ISEVOK*12
      character V_NAMEGV*12, V_VARGL*12,  V_NAMENV*12, V_VARNP*12
      character V_NAMEEV*13, V_VAREL*13
      character V_NAMEHV*12, V_VARHI*12,  D_TIMSTP*9,  D_HTMSTP*14

!
!         Define attributes
!
      parameter (A_TYPE = 'type', A_TITLE = 'title')
      parameter (A_VERSION = 'version')
!
!         Define dimensions
!
      parameter (D_NUMNOD = 'num_nodes', D_NDIM = 'num_dim')
      parameter (D_NUMEL ='num_elem')
      parameter (D_NELBLK = 'num_el_blk', D_NUMELB ='num_el_in_blk')
      parameter (D_NELNOD = 'num_nod_per_el')
      parameter (D_NATRIB = 'num_att_in_blk')
      parameter (D_NUMESS = 'num_side_sets', D_NEESS = 'num_el_ss')
      parameter (D_NNESS = 'num_nod_ss', D_NUMNPS = 'num_node_sets')
      parameter (D_NNNPS = 'num_nod_ns', D_NQAREC = 'num_qa_rec')
      parameter (D_NINFO = 'num_info', D_NVARGL ='num_glo_var')
      parameter (D_NVARNP = 'num_nod_var', D_NVAREL ='num_elem_var')
      parameter (D_NVARHI = 'num_his_var', D_N4 = 'four')
      parameter (D_STRLEN = 'len_string', D_LINLEN = 'len_line')
      parameter (D_TIMSTP = 'time_step', D_HTMSTP ='hist_time_step')
!
!         Define variables
!
      parameter (V_COORD = 'coord', V_NAMECO = 'coor_names')
      parameter (V_IDEBLK = 'el_blk_id', V_ICONK = 'connect')
      parameter (V_ATRIBK = 'attrib', A_NAMELB = 'elem_type')
      parameter (V_MAP ='elem_map', V_IDESS = 'side_set_ids')
      parameter (V_FACESS = 'dist_fact_ss')
      parameter (V_ELSSET = 'elem_ss', V_NDSSET = 'node_ss')
      parameter (V_IDNPS = 'node_set_ids', V_NODSET ='node_ns')
      parameter (V_FNPS = 'dist_fact_ns', V_INFO = 'info_records')
      parameter (V_TIMEHS = 'time_hist')
      parameter (V_TIME = 'time_whole', V_QATITL = 'qa_records')
      parameter (V_ISEVOK = 'elem_var_tab', V_NAMEGV ='name_glo_var')
      parameter (V_VARGL ='vals_glo_var', V_NAMENV = 'name_nod_var')
      parameter (V_VARNP = 'vals_nod_var')
      parameter (V_NAMEEV = 'name_elem_var', V_VAREL = 'vals_elem_var')
      parameter (V_NAMEHV = 'name_his_var', V_VARHI = 'vals_his_var')
!
!        dummy character variables used through out EXODUS
!
      character name*32

!
!        dummy integer variables used throughout EXODUS
!
       integer istart(3), icount(3), id
!
!        declaration for various functions
!
       integer chkfil

