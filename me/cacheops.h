#define IXILT		0x00	/* Icache index load tag */
#define IXIST		0x01	/* Icache index store tag */
#define IXIINV		0x03	/* Icache index invalidate */
#define IXHINV		0x08	/* Icache hit invalidate */
#define DXILT		0x10	/* Dcache index load tag */
#define DXIST		0x11	/* Dcache index store tag */
#define DXIINV		0x13	/* Dcache index invalidate */
#define DXIWBINV	0x14	/* Dcache index writeback invalidate */
#define DXHINV		0x19	/* Dcache hit invalidate */
#define DXHWB		0x1a	/* Dcache hit writeback */
#define DXHWBINV	0x1b	/* Dcache hit writeback invalidate */

#define TAG_SIZE	128
#define LINE_SIZE	64
