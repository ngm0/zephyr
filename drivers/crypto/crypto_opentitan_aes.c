/*
 * Copyright (c) 2024 Meta Technologies, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/kernel.h>
#include <zephyr/crypto/crypto.h>
#include "crypto_opentitan_aes.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(opentitan);

#if DT_HAS_COMPAT_STATUS_OKAY(lowrisc_opentitan_aes)
#define DT_DRV_COMPAT lowrisc_opentitan_aes
#else
#error No OpenTitan AES Accelerator in device tree
#endif

static int ot_aes_session_setup(const struct device *dev,
				struct cipher_ctx *ctx, enum cipher_algo algo,
				enum cipher_mode mode, enum cipher_op op_type)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(ctx);
	ARG_UNUSED(algo);
	ARG_UNUSED(mode);
	ARG_UNUSED(op_type);

	return 0;
}

static int ot_aes_session_free(const struct device *dev,
			       struct cipher_ctx *session)
{
	ARG_UNUSED(dev);
	ARG_UNUSED(session);

	return 0;
}

static int ot_aes_query_caps(const struct device *dev)
{
	ARG_UNUSED(dev);

	return (CAP_OPAQUE_KEY_HNDL | CAP_SEPARATE_IO_BUFS | CAP_SYNC_OPS |
		CAP_AUTONONCE);
}

static int ot_aes_init(const struct device *dev)
{
	ARG_UNUSED(dev);

	return 0;
}

static struct crypto_driver_api crypto_funcs = {
	.cipher_begin_session = ot_aes_session_setup,
	.cipher_free_session = ot_aes_session_free,
	.cipher_async_callback_set = NULL,
	.query_hw_caps = ot_aes_query_caps,
};

DEVICE_DT_INST_DEFINE(0, ot_aes_init, NULL, NULL, NULL, POST_KERNEL,
		      CONFIG_CRYPTO_INIT_PRIORITY, &crypto_funcs);
