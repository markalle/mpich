/*
 * Copyright (C) by Argonne National Laboratory
 *     See COPYRIGHT in top-level directory
 */

#include "mpiimpl.h"

/* -- Begin Profiling Symbol Block for routine MPI_Comm_set_errhandler */
#if defined(HAVE_PRAGMA_WEAK)
#pragma weak MPI_Comm_set_errhandler = PMPI_Comm_set_errhandler
#elif defined(HAVE_PRAGMA_HP_SEC_DEF)
#pragma _HP_SECONDARY_DEF PMPI_Comm_set_errhandler  MPI_Comm_set_errhandler
#elif defined(HAVE_PRAGMA_CRI_DUP)
#pragma _CRI duplicate MPI_Comm_set_errhandler as PMPI_Comm_set_errhandler
#elif defined(HAVE_WEAK_ATTRIBUTE)
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
    __attribute__ ((weak, alias("PMPI_Comm_set_errhandler")));
#endif
/* -- End Profiling Symbol Block */

/* Define MPICH_MPI_FROM_PMPI if weak symbols are not supported to build
   the MPI routines */
#ifndef MPICH_MPI_FROM_PMPI
#undef MPI_Comm_set_errhandler
#define MPI_Comm_set_errhandler PMPI_Comm_set_errhandler
#endif


/*@
   MPI_Comm_set_errhandler - Set the error handler for a communicator

Input Parameters:
+ comm - communicator (handle)
- errhandler - new error handler for communicator (handle)

.N ThreadSafeNoUpdate

.N Fortran

.N Errors
.N MPI_SUCCESS
.N MPI_ERR_COMM
.N MPI_ERR_OTHER

.seealso MPI_Comm_get_errhandler, MPI_Comm_call_errhandler
@*/
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler)
{
    int mpi_errno = MPI_SUCCESS;
    MPIR_Comm *comm_ptr = NULL;
    MPIR_Errhandler *errhan_ptr = NULL;
    MPIR_FUNC_TERSE_STATE_DECL(MPID_STATE_MPI_COMM_SET_ERRHANDLER);

    MPIR_ERRTEST_INITIALIZED_ORDIE();

    MPID_THREAD_CS_ENTER(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    MPIR_FUNC_TERSE_ENTER(MPID_STATE_MPI_COMM_SET_ERRHANDLER);

    /* Validate parameters, especially handles needing to be converted */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            MPIR_ERRTEST_COMM(comm, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif

    /* Convert MPI object handles to object pointers */
    MPIR_Comm_get_ptr(comm, comm_ptr);
    MPIR_Errhandler_get_ptr(errhandler, errhan_ptr);

    /* Validate parameters and objects (post conversion) */
#ifdef HAVE_ERROR_CHECKING
    {
        MPID_BEGIN_ERROR_CHECKS;
        {
            /* Validate comm_ptr; if comm_ptr is not valid, it will be reset to null */
            MPIR_Comm_valid_ptr(comm_ptr, mpi_errno, TRUE);

            if (!HANDLE_IS_BUILTIN(errhandler)) {
                MPIR_Errhandler_valid_ptr(errhan_ptr, mpi_errno);
            }
            MPIR_ERRTEST_ERRHANDLER(errhandler, mpi_errno);
        }
        MPID_END_ERROR_CHECKS;
    }
#endif /* HAVE_ERROR_CHECKING */

    /* ... body of routine ...  */

    MPIR_Comm_set_errhandler_impl(comm_ptr, errhan_ptr);

    /* ... end of body of routine ... */

#ifdef HAVE_ERROR_CHECKING
  fn_exit:
#endif
    MPIR_FUNC_TERSE_EXIT(MPID_STATE_MPI_COMM_SET_ERRHANDLER);
    MPID_THREAD_CS_EXIT(GLOBAL, MPIR_THREAD_GLOBAL_ALLFUNC_MUTEX);
    return mpi_errno;

    /* --BEGIN ERROR HANDLING-- */
#ifdef HAVE_ERROR_CHECKING
  fn_fail:
    {
        mpi_errno =
            MPIR_Err_create_code(mpi_errno, MPIR_ERR_RECOVERABLE, __func__, __LINE__, MPI_ERR_OTHER,
                                 "**mpi_comm_set_errhandler", "**mpi_comm_set_errhandler %C %E",
                                 comm, errhandler);
    }
    mpi_errno = MPIR_Err_return_comm(comm_ptr, __func__, mpi_errno);
    goto fn_exit;
#endif
    /* --END ERROR HANDLING-- */
}
