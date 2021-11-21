/*
 * scull.h
 * */

#ifndef _SCULL_H_ 
#define _SCULL_H_

#include <linux/ioctl.h>

#ifndef SCULL_MAJOR
#define SCULL_MAJOR 0 /* Using 0 by default */
#endif

/*
 *  "sculldev->data" points to an array of pointers
 *  Each array is of size SCULL_QSET long
 */

#ifndef SCULL_QUANTUM
#define SCULL_QUANTUM 4000
#endif

#ifndef SCULL_QSET
#define SCULL_QSET 1000
#endif

/*
 * Representation of scull quantum set
 */

struct scull_qset{
	//data contains address pointer to the array start 
	void **data;
	//next quantum set
	struct scull_qset *next;
};

//the memory device scull
struct scull_dev {
	struct scull_qset* data; //pointer to the first quantum set
	int quantum; //current quantum size
	int qset; //current array size
	unsigned long size; //amount of data stored here
	unsigned  int access_key; //used by sculluid and scullpriv
	struct semaphore sem; // mutual exclusion semaphore
	struct cdev cdev; //char device structure
};

/*
 * Split minor in two parts
 * */


#define TYPE(minor) (((minor) >> 4) & 0xf) /*high nibble*/
#define NUM(minor) ((minor) & 0xf) /*lower nibble*/

/*
 * Configurable parameters
 */

extern int scull_major; // in main.c
extern int scull_nr_devs; 
extern int scull_quantum;
extern int scull_qset;


/*
 * Prototypes for shared functions
 */

//still remaining


#endif


