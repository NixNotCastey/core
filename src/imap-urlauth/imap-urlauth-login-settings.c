/* Copyright (c) 2013-2018 Dovecot authors, see the included COPYING file */

#include "lib.h"
#include "buffer.h"
#include "settings-parser.h"
#include "service-settings.h"
#include "login-settings.h"
#include "imap-urlauth-login-settings.h"

#include <stddef.h>

/* <settings checks> */
static struct file_listener_settings
imap_urlauth_login_unix_listeners_array[] = {
	{
		.path = "imap-urlauth",
		.mode = 0666,
		.user = "",
		.group = "",
	},
};
static struct file_listener_settings *imap_urlauth_login_unix_listeners[] = {
	&imap_urlauth_login_unix_listeners_array[0]
};
static buffer_t imap_urlauth_login_unix_listeners_buf = {
	{ { imap_urlauth_login_unix_listeners,
	    sizeof(imap_urlauth_login_unix_listeners) } }
};
/* </settings checks> */

struct service_settings imap_urlauth_login_service_settings = {
	.name = "imap-urlauth-login",
	.protocol = "imap",
	.type = "login",
	.executable = "imap-urlauth-login",
	.user = "$default_login_user",
	.group = "",
	.privileged_group = "",
	.extra_groups = "",
	.chroot = "token-login",

	.drop_priv_before_exec = FALSE,

	.process_min_avail = 0,
	.process_limit = 0,
	.client_limit = 0,
	.service_count = 1,
	.idle_kill = 0,
	.vsz_limit = UOFF_T_MAX,

	.unix_listeners = { { &imap_urlauth_login_unix_listeners_buf,
			      sizeof(imap_urlauth_login_unix_listeners[0]) } },
	.fifo_listeners = ARRAY_INIT,
	.inet_listeners = ARRAY_INIT
};

static const struct setting_define imap_urlauth_login_setting_defines[] = {
	SETTING_DEFINE_LIST_END
};

static const struct setting_parser_info *imap_urlauth_login_setting_dependencies[] = {
	&login_setting_parser_info,
	NULL
};

const struct setting_parser_info imap_urlauth_login_setting_parser_info = {
	.module_name = "imap-urlauth-login",
	.defines = imap_urlauth_login_setting_defines,

	.type_offset = SIZE_MAX,
	.parent_offset = SIZE_MAX,

	.dependencies = imap_urlauth_login_setting_dependencies
};

const struct setting_parser_info *imap_urlauth_login_setting_roots[] = {
	&login_setting_parser_info,
	&imap_urlauth_login_setting_parser_info,
	NULL
};
