
#include <linux/module.h>

#include "xnotify_drv.h"

static int __init drv_init(void)
{
    int ret;
    ret = xnotify_init();
    return ret;
}

static void __exit drv_exit(void)
{
    xnotify_exit();
}

module_init(drv_init);
module_exit(drv_exit);
MODULE_LICENSE("BSD");
