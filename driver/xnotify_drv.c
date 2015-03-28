/*
 *
 * Copyright (c) 2015, Stylon Wang
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Stylon Wang nor the
 *       names of his contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY STYLON WANG AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL STYLON WANG AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>

#include "xnotify_drv.h"

#define DBG_INFO(fmt, args...) do { \
        printk("[%s:%d] "fmt, __FUNCTION__, __LINE__, ##args); \
        } while(0)
//#define DBG_INFO(fmt, args..) do {} while(0)

#define DBG_ERR(fmt, args...) do { \
        printk(KERN_ALERT"[%s:%d][Error] "fmt, __FUNCTION__, __LINE__, ##args); } \
        while(0)


struct sock *g_nl_sk = NULL;

static void xnotify_nl_recv_msg(struct sk_buff *skb)
{

    struct nlmsghdr *nlh;
    int pid;
    struct sk_buff *skb_out;
    int msg_size;
    char *msg = "Hello from kernel";
    int res;

    DBG_INFO("Entering\n");

    msg_size = strlen(msg);

    nlh = (struct nlmsghdr *)skb->data;
    pid = nlh->nlmsg_pid; /*pid of sending process */
    printk(KERN_INFO "Netlink received msg payload from pid %d: %s\n", pid, (char *)nlmsg_data(nlh));

    skb_out = nlmsg_new(msg_size, 0);

    if (!skb_out)
    {
        DBG_ERR("Failed to allocate new skb\n");
        return;

    }
    nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    NETLINK_CB(skb_out).dst_group = 0; /* not in mcast group */
    strncpy(nlmsg_data(nlh), msg, msg_size);

    res = nlmsg_unicast(g_nl_sk, skb_out, pid);

    if (res < 0)
        DBG_ERR("Error while sending bak to user\n");
}

int xnotify_init(void)
{
    struct netlink_kernel_cfg cfg = {
        .groups = 0xFF,
        .input = xnotify_nl_recv_msg,
    };

    DBG_INFO("\n");

    g_nl_sk = netlink_kernel_create(&init_net, NETLINK_USERSOCK, &cfg);
    if (!g_nl_sk)
    {
        DBG_ERR("Error creating socket.\n");
        return -10;

    }
    return 0;
}

void xnotify_exit(void)
{
    DBG_INFO("\n");
    netlink_kernel_release(g_nl_sk);
}

int xnotify_send_msg(XNOTIFY_EVENT event, int msg)
{

    return 0;
}

EXPORT_SYMBOL(xnotify_init);
EXPORT_SYMBOL(xnotify_exit);
EXPORT_SYMBOL(xnotify_send_msg);

