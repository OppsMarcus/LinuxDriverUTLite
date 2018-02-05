//--- Simplest USB device driver for UTLite USB tester -----------------
//--- This version v0.01 is device identification only. ----------------

#include <linux/module.h>          // Connect Linux kernel headers
#include <linux/kernel.h>
#include <linux/usb.h>

#define USB_VENDOR_ICBOOK 0xB00C   // IC Book USB Vendor ID
#define USB_DEVICE_UTLITE 0x0001   // UTLite USB tester Product ID


//--- Structure for Vendor:Device detection, must be nul-terminated ---
static struct usb_device_id utlite_table[] =
{
    { USB_DEVICE(USB_VENDOR_ICBOOK, USB_DEVICE_UTLITE) },
    { 0 }   // List terminator = 0
};
MODULE_DEVICE_TABLE (usb, utlite_table);

//--- This function called by Linux kernel when driver installed ---
//--- Probe function: device detection restrict after VID:DID match ---
//--- Output to kernel log added --- 
static int utlite_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "UTLite tester (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
    return 0;
}

//--- This function called by Linux kernel when driver un-installed --- 
//--- Output to kernel log added --- 
static void utlite_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "UTLite tester removed\n");
}

//--- This structure used by kernel as standard entry points list --- 
static struct usb_driver utlite_driver =
{
    .name = "UTLite",
    .id_table = utlite_table,          // vid:did sequence for device detection
    .probe = utlite_probe,             // pointer to INSTALL function
    .disconnect = utlite_disconnect,   // pointer to UN-INSTALL function
};

//--- This function called by Linux kernel when driver installed ---
//--- Standard entry point for driver registration ---
static int __init utlite_init(void)
{
    return usb_register(&utlite_driver);    // use list reference
}

//--- This function called by Linux kernel when driver un-installed ---
//--- Standard entry point for driver un-registration ---
static void __exit utlite_exit(void)
{
    usb_deregister(&utlite_driver);    // use list reference
}
 
//--- Standard declarations ---
MODULE_LICENSE("GPL");       // License string
module_init(utlite_init);    // Driver start entry point
module_exit(utlite_exit);    // Driver stop entry point
MODULE_AUTHOR("IC Book Labs");
MODULE_DESCRIPTION("USB UTLite Tester simplest driver v0.01");

