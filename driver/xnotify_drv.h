#ifndef __XNOTIFY_DRV_H__
#define __XNOTIFY_DRV_H__

#include <linux/module.h>

#include "xnotify_event.h"

int xnotify_init(void);
void xnotify_exit(void);

int xnotify_send_msg(XNOTIFY_EVENT event, int msg);

#endif //__KNOTIFY_DRV_H__
