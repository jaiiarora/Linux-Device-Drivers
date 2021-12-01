/*
 * silly copy- a  pointless system call 
 * that copies the len bytes from 'src' to 'dst'
 * using kernel as an intermediary.
 */

#include <linux/syscalls.h>
#include <linux/kernel.h>

SYSCALL_DEFINE3(silly_copy, unsigned long*, src, unsigned long*, dst, unsigned long, len)
{
	unsigned long buff;
	/*copy src, which is in users address space into buff */
	if (copy_from_user(&buff, src, len))
		return -EFAULT;
	
	if (copy_to_user(dst, &buff, len))
		return -EFAULT;

	//RETURN AMOUNT OF DATA COPIED
	return len;
}

		
