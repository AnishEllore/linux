#include <linux/init.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/kernel.h>
SYSCALL_DEFINE2(s2_encrypt, char *, msg, unsigned int, key)
{
    int MAX_LEN = 256;
    char buf[MAX_LEN];
    long copied = strncpy_from_user(buf, msg, sizeof(buf));
    bool valid_key = key >= 0 && key <=5;
    if (!valid_key) return EINVAL;
    if (copied < 0 || copied == sizeof(buf))
    return -EFAULT;
    int i = 0;
    while(i < MAX_LEN && buf[i] != '\0') {
        buf[i] += key;
        i++;
    }
    printk(KERN_INFO "Encrypted Custom String: \"%s\"\n", buf);
    return 0;
}