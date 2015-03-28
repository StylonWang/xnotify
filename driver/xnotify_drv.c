
#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#include "xnotify_drv.h"

int xnotify_init(void)
{

    return 0;
}

void xnotify_exit(void)
{

}

int xnotify_send_msg(XNOTIFY_EVENT event, int msg)
{

    return 0;
}

EXPORT_SYMBOL(xnotify_init);
EXPORT_SYMBOL(xnotify_exit);
EXPORT_SYMBOL(xnotify_send_msg);
