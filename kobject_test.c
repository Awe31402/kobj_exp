#include <linux/device.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/stat.h>
#include <linux/init.h>

/* release kobject */
void kobj_test_release(struct kobject *kobject);

/* read attribute */
ssize_t kobj_test_show(struct kobject *kobject, struct attribute *attr, char *buf);

/* write attribute*/
ssize_t kobj_test_store(struct kobject *kobject, struct attribute *attr, const char *buf, size_t count);

char info[1024];
/*
 * define an attribute "kobject_test" 
 * we can read & write & execute it.
 */
struct attribute test_attr = {
	.name = "info",
	.mode = S_IRUGO | S_IWUGO,
};

/*
 * there's only one attribute in the definition
 */
static struct attribute *def_attrs[] = {
	&test_attr,
	NULL,
};

struct sysfs_ops kobject_test_sysops = {
	.show	= kobj_test_show,
	.store	= kobj_test_store,
};

struct kobj_type ktype = {
	.release	= kobj_test_release,
	.sysfs_ops	= &kobject_test_sysops,
	.default_attrs	= def_attrs,
};

void kobj_test_release(struct kobject *kobj)
{
	/* 
	 * notice: it just an example
	 * it often will be more complicated in real case
	 */
	pr_info("%s()\n", __func__);
}

ssize_t kobj_test_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	pr_info("call %s()\n", __func__);
	pr_info("attrname %s\n", attr->name);
	sprintf(buf, "%s\n", info);
	return strlen(attr->name) + 2;
}

ssize_t kobj_test_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count)
{
	pr_info("call %s()\n", __func__);
	pr_info("write %s\n", buf);
	strcpy(info, buf);
	return count;
}
struct kobject kobj;

static int kobj_test_init(void)
{
	pr_info("%s()\n", __func__);

	/* initialize kobject and add it to kernel */
	kobject_init_and_add(&kobj, &ktype, NULL, "kobject_test");

	return 0;
}

static void kobject_test_exit(void)
{
	pr_info("%s()\n", __func__);
	kobject_del(&kobj);
}

MODULE_LICENSE("Dual BSD/GPL");
module_init(kobj_test_init);
module_exit(kobject_test_exit);


