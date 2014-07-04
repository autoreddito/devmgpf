#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/init.h>		/* Needed for the macros */
#include <linux/types.h>	/* Holds dev_t */
#include <linux/fs.h>		/* holds register_chrdev */
#include <asm/uaccess.h>	/* for put_user */
#include "figo.h"

extern char to_the_infinity_and_beyond[];
extern unsigned int to_the_infinity_and_beyond_len;

MODULE_AUTHOR("Autoreddi.to");
MODULE_DESCRIPTION("A mgpf generator char device");
MODULE_LICENSE("GPL");

#define DEVICE_NAME "mgpf"	  /* Dev name as it appears in /proc/devices   */

static int Major;		    /* Major number assigned to our device driver */

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "[mgpf] Sorry, this operation isn't supported.\n");
	return -EINVAL;
}

static int device_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);  /* marks this module as in use*/
	return 0;
}

static int i =0;
static ssize_t device_read(struct file * file, char * buf, size_t count, loff_t *ppos)
{


  /* Number of bytes actually written to the buffer */
  int bytes_read = 0;

  /* If we're at the end of the message, return 0 
   * (which signifies end of file) */
  if (*to_the_infinity_and_beyond == 0)
    return 0;

  /* Actually put the data into the buffer */
  while (count && (i<to_the_infinity_and_beyond_len))  {

    /* Because the buffer is in the user data segment, 
     * not the kernel data segment, assignment wouldn't 
     * work. Instead, we have to use put_user which 
     * copies data from the kernel data segment to the 
     * user data segment. */
    put_user(*(to_the_infinity_and_beyond+i), buf++);

    i++;
    count --;
    bytes_read ++;
    }
  return bytes_read;


}

static int device_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}

static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

static int __init startup(void)
{
    Major = register_chrdev(0, DEVICE_NAME, &fops);

	if (Major < 0) {
        printk(KERN_ALERT "[mgpf] Registering char device failed with %d\n", Major);
        return Major;
	}

	printk(KERN_INFO "[mgpf] I was assigned major number %d.\nto the infinity... and beyond!\nZZZZZZZZZ$$ZZZZO888OZZ$ZZZ$ZZ$ZZZZZZZZZZ\nZZZZZZZ$$$ODDI??++++++?$ZZ$ZZZZZZZZZZZZZ\nZZZZZ$Z$8N8?+++===+++=++?$Z$ZZZZZZZZZZZZ\nZZ$Z$OMMDZ????+==+=+==+==+ZZZZZZZZZZZZZZ\nZZZ$ZMNNO7???++========?7IIZZZZZZZZZZZZZ\nZ$ZONNDN8$???+?Z7II??=+II??$ZZZZZZZZZZZZ\nZ$Z8NNDD8$I??I$=I7II?++7ZDDDDN8ZZZZZZZZZ\n$Z$NNNNNOZ??IDZ7IZ$778?8I~ZO$O8ZZZZZZZZZ\n$ZZNNNNN8$IMO$O7II7$ZI?==$$$ZMZZZZZZZZZZ\n$Z$NNMMDD8N7$$Z7I??+II???7??I$ZZZZZZZZZZ\nZZZZNNNNMN7???+?++==+IOI77=+?IZZZZZZZZZZ\nZZ$$D?7NNN7??+++====+?I7IO++?IZZZZZZZZZZ\n$Z$$7ZI7$Z7II?+?+++++$$I?I7$IIZZZZZZZZZZ\n$$$$$I+$7I777I?????$77$$7$O$Z7ZZZZZZZZZZ\nZ$Z$Z7??IZ$77IIII?$7II7I?I77Z7ZZZZZZZZZZ\n$$$$$$II??$$$I7I??I$??IZ887IZ7ZZZZZZZZZZ\n$$$$$ZZ$MNZZZ$$7II7ZZ77$78ZOO$ZZZZZZZZZZ\n$$$$$$$$Z8DZZOZ$$77$8DDDDNDNOZZZZZZZZZZZ\n$ZZ$$$$$$$MZ$OOZZZZZ8NNNNND8Z7ZZZZZZZZZZ\nZ$$$$$$$$$$O$$ZOOOOOOOOOOZO$O7$ZZZZZZZZZ\nZ$$$$$$$$$$$Z$$ZZZOOOOOZZZZ$$~~8ZZZZZZZZ\nZZ$$Z$ZZ$$$Z7$$$ZZZZZZZZZZ77~:=NNOZZZZZZ\nZZ$$$$$ZZ$ZIIOZ$$ZZ$ZZZZZ7?~~:8NNNN8OZZZ\nZZZ$$$$$ZZD+7$Z$7$Z$$$777~~~~+NNNNNDNNNN\nZ$Z$$ZZOMNN=IZO$77$$777?~:~~=DNNNNNDNNNN\n", Major);
/*    printk(KERN_INFO "ZZZZZZZZZ$$ZZZZO888OZZ$ZZZ$ZZ$ZZZZZZZZZZ\nZZZZZZZ$$$ODDI??++++++?$ZZ$ZZZZZZZZZZZZZ\nZZZZZ$Z$8N8?+++===+++=++?$Z$ZZZZZZZZZZZZ\nZZ$Z$OMMDZ????+==+=+==+==+ZZZZZZZZZZZZZZ\nZZZ$ZMNNO7???++========?7IIZZZZZZZZZZZZZ\nZ$ZONNDN8$???+?Z7II??=+II??$ZZZZZZZZZZZZ\nZ$Z8NNDD8$I??I$=I7II?++7ZDDDDN8ZZZZZZZZZ\n$Z$NNNNNOZ??IDZ7IZ$778?8I~ZO$O8ZZZZZZZZZ\n$ZZNNNNN8$IMO$O7II7$ZI?==$$$ZMZZZZZZZZZZ\n$Z$NNMMDD8N7$$Z7I??+II???7??I$ZZZZZZZZZZ\nZZZZNNNNMN7???+?++==+IOI77=+?IZZZZZZZZZZ\nZZ$$D?7NNN7??+++====+?I7IO++?IZZZZZZZZZZ\n$Z$$7ZI7$Z7II?+?+++++$$I?I7$IIZZZZZZZZZZ\n$$$$$I+$7I777I?????$77$$7$O$Z7ZZZZZZZZZZ\nZ$Z$Z7??IZ$77IIII?$7II7I?I77Z7ZZZZZZZZZZ\n$$$$$$II??$$$I7I??I$??IZ887IZ7ZZZZZZZZZZ\n$$$$$ZZ$MNZZZ$$7II7ZZ77$78ZOO$ZZZZZZZZZZ\n$$$$$$$$Z8DZZOZ$$77$8DDDDNDNOZZZZZZZZZZZ\n$ZZ$$$$$$$MZ$OOZZZZZ8NNNNND8Z7ZZZZZZZZZZ\nZ$$$$$$$$$$O$$ZOOOOOOOOOOZO$O7$ZZZZZZZZZ\nZ$$$$$$$$$$$Z$$ZZZOOOOOZZZZ$$~~8ZZZZZZZZ\nZZ$$Z$ZZ$$$Z7$$$ZZZZZZZZZZ77~:=NNOZZZZZZ\nZZ$$$$$ZZ$ZIIOZ$$ZZ$ZZZZZ7?~~:8NNNN8OZZZ\nZZZ$$$$$ZZD+7$Z$7$Z$$$777~~~~+NNNNNDNNNN\nZ$Z$$ZZOMNN=IZO$77$$777?~:~~=DNNNNNDNNNN\n");*/
	return 0;
}

static void __exit shutdown(void)
{
	/*
	 * Unregister the device
	 */
    printk(KERN_INFO "[mgpf] Unplugging character device\n");
	unregister_chrdev(Major, DEVICE_NAME);
}

module_init(startup);
module_exit(shutdown);

