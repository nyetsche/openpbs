/*
 * Copyright (C) 1994-2021 Altair Engineering, Inc.
 * For more information, contact Altair at www.altair.com.
 *
 * This file is part of both the OpenPBS software ("OpenPBS")
 * and the PBS Professional ("PBS Pro") software.
 *
 * Open Source License Information:
 *
 * OpenPBS is free software. You can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * OpenPBS is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Affero General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Commercial License Information:
 *
 * PBS Pro is commercially licensed software that shares a common core with
 * the OpenPBS software.  For a copy of the commercial license terms and
 * conditions, go to: (http://www.pbspro.com/agreement.html) or contact the
 * Altair Legal Department.
 *
 * Altair's dual-license business model allows companies, individuals, and
 * organizations to create proprietary derivative works of OpenPBS and
 * distribute them - whether embedded or bundled with other software -
 * under a commercial license agreement.
 *
 * Use of Altair's trademarks, including but not limited to "PBS™",
 * "OpenPBS®", "PBS Professional®", and "PBS Pro™" and Altair's logos is
 * subject to Altair's trademark licensing policies.
 */

/**
 * @file	int_msg2.c
 * @brief
 *	send the MessageJob request
 */

#include <pbs_config.h> /* the master config generated by configure */

#include <string.h>
#include <stdio.h>
#include "libpbs.h"
#include "dis.h"
#include "net_connect.h"
#include "tpp.h"

/**
 * @brief
 *	-PBS_msg_put Send the MessageJob request, does not read the reply.
 *
 * @param[in] c - socket descriptor
 * @param[in] jobid - job identifier
 * @param[in] fileopt - file type
 * @param[in] msg - msg to be sent
 * @param[in] extend - extention string for req encode
 * @param[in] prot - PROT_TCP or PROT_TPP
 * @param[in] msgid - message id
 *
 * @return      int
 * @retval      0               Success
 * @retval      pbs_error(!0)   error
 */
int
PBSD_msg_put(int c, const char *jobid, int fileopt, const char *msg, const char *extend, int prot, char **msgid)
{
	int rc = 0;

	if (prot == PROT_TCP) {
		DIS_tcp_funcs();
	} else {
		if ((rc = is_compose_cmd(c, IS_CMD, msgid)) != DIS_SUCCESS)
			return rc;
	}

	if ((rc = encode_DIS_ReqHdr(c, PBS_BATCH_MessJob, pbs_current_user)) ||
	    (rc = encode_DIS_MessageJob(c, jobid, fileopt, msg)) ||
	    (rc = encode_DIS_ReqExtend(c, extend))) {
		return (pbs_errno = PBSE_PROTOCOL);
	}

	if (dis_flush(c)) {
		pbs_errno = PBSE_PROTOCOL;
		rc = pbs_errno;
	}

	return rc;
}

/**
 * @brief
 *	-Send the PySpawn request, does not read the reply.
 *
 * @param[in] c - socket descriptor
 * @param[in] jobid - job identifier
 * @param[in] argv - pointer to arguments
 * @param[in] envp - pointer to environment vars
 * @param[in] prot - PROT_TCP or PROT_TPP
 * @param[in] msgid - message id
 *
 * @return	int
 * @retval	0		Success
 * @retval	pbs_error(!0)	error
 */
int
PBSD_py_spawn_put(int c, char *jobid, char **argv, char **envp, int prot, char **msgid)
{
	int rc = 0;

	if (prot == PROT_TCP) {
		DIS_tcp_funcs();
	} else {
		if ((rc = is_compose_cmd(c, IS_CMD, msgid)) != DIS_SUCCESS)
			return rc;
	}

	if ((rc = encode_DIS_ReqHdr(c, PBS_BATCH_PySpawn, pbs_current_user)) ||
	    (rc = encode_DIS_PySpawn(c, jobid, argv, envp)) ||
	    (rc = encode_DIS_ReqExtend(c, NULL))) {
		return (pbs_errno = PBSE_PROTOCOL);
	}

	if (dis_flush(c)) {
		pbs_errno = PBSE_PROTOCOL;
		rc = pbs_errno;
	}

	return rc;
}

/*
 *	PBS_relnodes_put.c
 *
 *	Send the RelnodesJob request, does not read the reply.
 */
int
PBSD_relnodes_put(int c, const char *jobid, const char *node_list, const char *extend, int prot, char **msgid)
{
	int rc = 0;

	if (prot == PROT_TCP) {
		DIS_tcp_funcs();
	} else {
		if ((rc = is_compose_cmd(c, IS_CMD, msgid)) != DIS_SUCCESS)
			return rc;
	}

	if ((rc = encode_DIS_ReqHdr(c, PBS_BATCH_RelnodesJob, pbs_current_user)) ||
	    (rc = encode_DIS_RelnodesJob(c, jobid, node_list)) ||
	    (rc = encode_DIS_ReqExtend(c, extend))) {
		return (pbs_errno = PBSE_PROTOCOL);
	}

	if (dis_flush(c)) {
		pbs_errno = PBSE_PROTOCOL;
		rc = pbs_errno;
	}

	return rc;
}
