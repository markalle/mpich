/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#include "mpiimpl.h"

#include "tsp_gentran.h"

/* instantiate ibcast tree algorithms for the gentran transport */
#include "ineighbor_allgather_tsp_linear_algos_prototypes.h"
#include "ineighbor_allgather_tsp_linear_algos.h"
#include "ineighbor_allgather_tsp_linear_algos_undef.h"

#include "tsp_undef.h"
