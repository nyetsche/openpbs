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
 * @file	ecl_verify_datatypes.c
 *
 * @brief	Attribute datatype verification functions
 *
 * @par Functionality:
 *	This module contains attribute datatype verification functions\n
 *	Each function in this module takes a common format as follows:\n
 *	int verify_datatype_xxxx(struct attropl * pattr, char **err_msg)\n
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

#include <pbs_config.h> /* the master config generated by configure */
#include <stdlib.h>
#include <string.h>

#include "pbs_ifl.h"
#include "pbs_ecl.h"
#include "pbs_error.h"

/**
 * @brief
 *	verifies boolean attribute
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_bool(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_b(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of short datatype
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_short(struct attropl *pattr, char **err_msg)
{
	short s;
	int ret;
	attribute atr;
	atr.at_flags = 0;
	if ((ret = decode_l(&atr, pattr->name, pattr->resource, pattr->value)))
		return ret;
	s = (short) atr.at_val.at_long;
	if (atr.at_val.at_long != (long) s)
		return (PBSE_BADATVAL);

	return PBSE_NONE;
}

/**
 * @brief
 *      verifies  attribute of long datatype
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_long(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_l(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of long long datatype
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return      int
 * @retval  0 - Attribute passed verification
 * @retval >0 - Attribute failed verification - pbs error code returned
 */

int
verify_datatype_long_long(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_ll(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of float datatype
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_float(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_f(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of size type
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_size(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_size(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of time type
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_time(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_time(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of node type
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_nodes(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	atr.at_flags = 0;
	return (decode_nodes(&atr, pattr->name, pattr->resource, pattr->value));
}

/**
 * @brief
 *      verifies  attribute of select type
 *
 * @param[in] pattr - struct attropl - Address of attribute to verify
 * @param[out] err_msg - char ** - Sets the error message if any
 *
 * @return int
 * @retval 0 - Attribute passed verification\n
 * @retval >0 - Attribute failed verification - pbs error code returned\n
 */

int
verify_datatype_select(struct attropl *pattr, char **err_msg)
{
	attribute atr;
	int ret = PBSE_BADATVAL;
	memset(&atr, 0, sizeof(struct attribute));
	ret = decode_select(&atr, pattr->name,
			    pattr->resource, pattr->value);
	(void) free(atr.at_val.at_str);
	return ret;
}
