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
 * @file	pbs_statnode.c - contains pbs_statnode() and pbs_statvnode()
 * @brief
 * Return the status of host(s) or vnodes.
 */

#include <pbs_config.h> /* the master config generated by configure */

#include "libpbs.h"
#include "pbs_ecl.h"

/**
 * @brief
 * 	-pbs_statnode() - calls pbs_stathost(), returns status of host
 *	maintained for backward compatibility
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return      structure handle
 * @retval      pointer to batch_status struct          Success
 * @retval      NULL					error
 *
 */
struct batch_status *
__pbs_statnode(int c, const char *id, struct attrl *attrib, const char *extend)
{
	return pbs_stathost(c, id, attrib, extend);
}

/**
 * @brief
 * 	-__pbs_statvnode() - returns information about virtual nodes (vnodes)
 *
 * @param[in] c - communication handle
 * @param[in] id - object id
 * @param[in] attrib - pointer to attribute list
 * @param[in] extend - extend string for encoding req
 *
 * @return	structure handle
 * @retval	pointer to batch_status struct		Success
 * @retval	NULL					error
 *
 */
struct batch_status *
__pbs_statvnode(int c, const char *id, struct attrl *attrib, const char *extend)
{
	int rc;
	struct batch_status *ret = NULL;

	/* initialize the thread context data, if not already initialized */
	if (pbs_client_thread_init_thread_context() != 0)
		return NULL;

	/* first verify the attributes, if verification is enabled */
	rc = pbs_verify_attributes(c, PBS_BATCH_StatusNode, MGR_OBJ_NODE,
				   MGR_CMD_NONE, (struct attropl *) attrib);
	if (rc)
		return NULL;

	if (pbs_client_thread_lock_connection(c) != 0)
		return NULL;

	ret = PBSD_status(c, PBS_BATCH_StatusNode, id, attrib, extend);

	/* unlock the thread lock and update the thread context data */
	if (pbs_client_thread_unlock_connection(c) != 0)
		return NULL;

	return ret;
}
