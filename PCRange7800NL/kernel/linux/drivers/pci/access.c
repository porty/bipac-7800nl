#include <linux/delay.h>
#include <linux/pci.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/ioport.h>
#include <linux/wait.h>

#include "pci.h"

/*
 * This interrupt-safe spinlock protects all accesses to PCI
 * configuration space.
 */

static DEFINE_SPINLOCK(pci_lock);

/*
 *  Wrappers for all PCI configuration access functions.  They just check
 *  alignment, do locking and call the low-level functions pointed to
 *  by pci_dev->ops.
 */

#define PCI_byte_BAD 0
#define PCI_word_BAD (pos & 1)
#define PCI_dword_BAD (pos & 3)

#define PCI_OP_READ(size,type,len) \
int pci_bus_read_config_##size \
	(struct pci_bus *bus, unsigned int devfn, int pos, type *value)	\
{									\
	int res;							\
	unsigned long flags;						\
	u32 data = 0;							\
	if (PCI_##size##_BAD) return PCIBIOS_BAD_REGISTER_NUMBER;	\
	spin_lock_irqsave(&pci_lock, flags);				\
	res = bus->ops->read(bus, devfn, pos, len, &data);		\
	*value = (type)data;						\
	spin_unlock_irqrestore(&pci_lock, flags);			\
	return res;							\
}

#define PCI_OP_WRITE(size,type,len) \
int pci_bus_write_config_##size \
	(struct pci_bus *bus, unsigned int devfn, int pos, type value)	\
{									\
	int res;							\
	unsigned long flags;						\
	if (PCI_##size##_BAD) return PCIBIOS_BAD_REGISTER_NUMBER;	\
	spin_lock_irqsave(&pci_lock, flags);				\
	res = bus->ops->write(bus, devfn, pos, len, value);		\
	spin_unlock_irqrestore(&pci_lock, flags);			\
	return res;							\
}

PCI_OP_READ(byte, u8, 1)
PCI_OP_READ(word, u16, 2)
PCI_OP_READ(dword, u32, 4)
PCI_OP_WRITE(byte, u8, 1)
PCI_OP_WRITE(word, u16, 2)
PCI_OP_WRITE(dword, u32, 4)

EXPORT_SYMBOL(pci_bus_read_config_byte);
EXPORT_SYMBOL(pci_bus_read_config_word);
EXPORT_SYMBOL(pci_bus_read_config_dword);
EXPORT_SYMBOL(pci_bus_write_config_byte);
EXPORT_SYMBOL(pci_bus_write_config_word);
EXPORT_SYMBOL(pci_bus_write_config_dword);


/**
 * pci_read_vpd - Read one entry from Vital Product Data
 * @dev:	pci device struct
 * @pos:	offset in vpd space
 * @count:	number of bytes to read
 * @buf:	pointer to where to store result
 *
 */
ssize_t pci_read_vpd(struct pci_dev *dev, loff_t pos, size_t count, void *buf)
{
	if (!dev->vpd || !dev->vpd->ops)
		return -ENODEV;
	return dev->vpd->ops->read(dev, pos, count, buf);
}
EXPORT_SYMBOL(pci_read_vpd);

/**
 * pci_write_vpd - Write entry to Vital Product Data
 * @dev:	pci device struct
 * @pos:	offset in vpd space
 * @count:	number of bytes to write
 * @buf:	buffer containing write data
 *
 */
ssize_t pci_write_vpd(struct pci_dev *dev, loff_t pos, size_t count, const void *buf)
{
	if (!dev->vpd || !dev->vpd->ops)
		return -ENODEV;
	return dev->vpd->ops->write(dev, pos, count, buf);
}
EXPORT_SYMBOL(pci_write_vpd);

/*
 * The following routines are to prevent the user from accessing PCI config
 * space when it's unsafe to do so.  Some devices require this during BIST and
 * we're required to prevent it during D-state transitions.
 *
 * We have a bit per device to indicate it's blocked and a global wait queue
 * for callers to sleep on until devices are unblocked.
 */
static DECLARE_WAIT_QUEUE_HEAD(pci_ucfg_wait);

static noinline void pci_wait_ucfg(struct pci_dev *dev)
{
	DECLARE_WAITQUEUE(wait, current);

	__add_wait_queue(&pci_ucfg_wait, &wait);
	do {
		set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irq(&pci_lock);
		schedule();
		spin_lock_irq(&pci_lock);
	} while (dev->block_ucfg_access);
	__removed->ops->write(dev, pos, count, buf);O=              || !dev->vpd->o

voii  s			st*top    ci_ndefine PCe wh for calleallers A;				lleSs			st*_g_access);
	__rem a bAeallers A;			i 5cess);
	__rem a bAeallers A;			i 5cess);PCe te_v,MSnline void pci_waiid (lenci_d

		             _         kesult    			          710_vpdiA_read  7S       _		i 5cess);
	__red pcA710_vpdiA_reai 55cess);
	__red pcA710_vpdiA_reai 55cess)  		_vpd8 sA710_vpdaaahprev55cessutine is to r,o 0008   cessOCPm Vital _remove_conlgw!dev->vpd->ops)
	3A_rea&busNE_Spin_lock_irqs                                                                             jare unbl(5    i~n:[n:[n:[nsigned in_lockBOL(pcset inn6E
static DECLARE_WAIT_QUEUE_HEly registered.
		 */
		if (cA~ead(bus, devfn, pos, len, &data);	if (* we'rcBfn, pos, lk~n:[n:sterUv *dev, loff_t1n, &data)Ibpm fundev( __devinit pci_do_scan_bus(struct pci_bu * space w       :M  0FH_waiidTe32, 4)

EXPORT_SYMBOL(pC     %bus, dM  0FH_waiidTe32, 4)

EXPasC 32, 4)
V2Dy */
	Si_bus *bS, len, &d1XE_HElyoiiiiiiiiiiPasC 32, 4)
V2Dy */
	Si_bus *bi
	spyefinevct psEpdaaahfCI_Oct psEpdaaah *)buf);iiiiiiiiiPasC 32, 4)
0FH_ine PCI_bSOct psEp__red pcA710_vpdiA_reai 55cess);
	__red pcA710_vpdiA_reai   *  Walk theu)bufEopWalk theu)bufEopWalk theu)bufEopWalk theu)bufEop|55cess));

_WAITQp__red pcA710s)  5
		}
		return ret;
	}
#ifdef CONFIG_ACPI
	if PORT_SYMBOL(pci_bus_write_confpos, ss));ess)),    eu)bufEsy	numberdatin   ci_ndefine PC*/
	f PORT_SYMBOL(pci_nclu

/**
 eui, po_ycurrent);

	__add_ivers/pci/hco4)  5
_ycurrent);

	__ad           pot re;

	__add_ivers/pci/hco4)  5
_ycurrent);
_WAITQp__red pcA7PI
	iN__TQp__red pcd pcA7PI
	iN__TQp__wmpsEpBfn,    a7 ed pRos, typent);

	__add_iver flagypeU>reg0lign: alignpeUdTe32,LT_REG_A7PI
at_fopiN___REG_A7P = -s
_yclRos,sling_SYMBOer faults */
	fault_status = readl(iommu->reg + DAdefine PA;

_WAITs			s(Ciot re;

	__add_ivers/pc3ancs_and6._REGgnpeUdTe32,LT_REG_A7PI
/**n_##sizeWAIuE
EXPasC 32, 4Malux = pci_scan_child_bus(bus);
= readl(iommu->reg + DAdefine PA;
/kernel/linux/drivers/pci/setup-res.c                                                  0000666 00*buf
/kernel/linux/drivers/p}
			iN_     rs/pp|55ct:	66 0oHbus_ads = rinux32, 4ElyoiiiiiiiiiiPasC 32, 4)
V2D6i
	s       5"_irqCONFIG_ACPI
	if PORT_SY5A		      dren);
			up_writeESOUR);O=    ae_SYMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMms) {
			/* end o T	i 5cess);
	__red pcA710_vpdiA_reai 55cess);
	__red pcA710_vpdiA_reai 55cess4)  5
_ycurren			continue;

		/* Wjgf#osereai 55cesMBOL *
 * We have a bit per devessutine5MMMMMM    Uefin. Returns:
 *  a suggestion for fixing it (although the driver is noase 2:
		_assign_resource_fixed(struct pci_dev *dev, int resnofidev_inw       fs not required e (althouL(pc             _REGT
tval)
		retu     :al)
		retu     :al)
		re-fetching area */
		if ((r->flags & IORESOURCE_PREFETCH) &&
		    !(res->flags & IORESOURCE_PREFETCH))
			continue;

		/* Ok, try it out.. */
		ret = a	} ai o indicUlers A;			i 5cess);
	aSb
pt-safe spinlock protects all
{
	if (!dev->vpd || !dev->vpd->ops)
		return -ENODEV;
	return dev->vpd->ops->w	tt-sxU           peU>e_creAeg0lnlocoaUWe caaiid/driv&pcinE_ent the user from accessing _BAD LrUvU * can_	ifuf_tsT>Et;
}
anes ar4:
		err = put_user
anes ar4:
		err =alk the given bus, including ane givFh   from aturnor (;;) {
		if :tic DECLARE_WAIT_QUEUE_HEAD(pci_ucfg_wait);|| !dev->vpd->op;
}
an      _REGT
tval)
N*rea_v0_vpt_empty(N*rea_E      m_PI
/**nbs, ac-ops)
	3A_A >ops->w	tNCH)icU>ops->wuMMMMAdfcateEdosroutuct pci_dev pci_dehprev55cessutine is to r,o 0008   cessOCPm 1_:
		cs to sprev54*cVit)LrUvU * c)e is tan_chif  cessOCPm 1_:
		cs to sprev54*cVil(,
		rcady-added devssOCPm 1_:
		cs to sprev54*cVil(,
Fg_>opeE_H	     erite, unsiize, min, alig	safe spinlock protectsy-addOCPm#define PCI_41vs, cze_t align,
		resource_snuct vs, cze_t align,
		resoctsye_t)ualineso    ci_ndefine PCe wh for calleallers A;				lleSs			st*_g_access);
	__rem a bAeallers 57s
_ycurrent);

	__ad6d_ndeit.h>

#include "pbled(dev)) {
				retval = pci_enable_devm			a Wrappers for all PCI cosDN71036yolignsDN71036yolignsDN710t pci_dev *dCdyyyyyyyyyyyyDyolignsDN710essu.v\nosrndefine PCe:	pkN710essu. PCI_oci_eignsDN710e_ A;			U_locked.
 		U_lockeall Pi3Xvfw	err =a_:
		cs to sprev5safe spi_REG
	/* P__bri * 103a3n,
	K		lleSs			st*_g_ESt pcaansitions.
Dyolin_lock_irqsavaSe is tansIurces(struct pci_dev *dev, int maalleallerri fe sp	errfshort __userus, caGmdd_in@@@@@@eE=eItinue;
		if ((i == PCI_ROM_RElRElRElR2ORESOURCE_IO)
			ctvallRElll PD
 */ci_dev el/linux/drivers/p}
			iN_     rs/pp|5E, typent);(les Kf POblem(pdev, "MSI routing failure"rcan ret8art >ommu->outi}
			iN_    PcU *dev, int maskstruct 6Nhsi+d);                   ustar   root                            root                                     U, ley   ae_SYav->sust;      aignsDN710nclWjgf#oser ops)fs_dev_cons'T_SYMB jgf#oser ops)fs_dev_c                                                  #llx-%#lliverate_ jgf#osaturno!re resuconfig_dword(dev, re sdor (;;ufEo            su.v\nouconECLARE_nlock protects all
{
	if (!dev->vpd || !dev->vpd->ops)
		return -ENODEV;
	return dev->vpd->ops->w	tt-sxU           peU>e_creAeg0lnlocoaUWe caaiid/driv&pcinE_ent the user from _dev *dev;
	int retval;

	list_for_each_entry(dev, &bus->devices, bus_list) {
		if (dev->sub aaiid/driv&pcinE_ent the user from _dev *dev;
	int retval;

	list_for_each_entry(dev, &bus->devices, bus_list) {
		if (dev->sub aaiid/driv&pcinE_ent the user ) {
	he useg + Cddd_w {
	he useg devic           ce[i]oce" : "br_lt_sta puev->IT_Qdev,ops->N*(SYM_loic   percinENucfgYM_loic   percifARE_WAIT_QUEiPojgf#osaturno!re resuconfig_e_add(&dev->dev);
	if (retval)
		return retval;

	dev->is_added = 1;
	pcBseate1d_vpddev);
	if (retval)
		return retval;

	dev->is_added = 1;
	pcBseate1d_vpddev    B        puev->IT_Qd IORESOURCE_PREFETCHnsigned  Deir = &dev->resourcno       percinEr (;;uf*Uefipin_unlock_               M	drivers/pconf4rcan rst s7siN_  t,
		 (ev->;
			}
		}
	}
}

int pci_enable_resources(stru}
}

int"pbledalue);		\
	spin_unlock_irqrestore(&pci_lock, flags);			\
	return res;							\
}

PCI_OP_READ(byte, u8, 1)
PCI_OP_READ(word, u16, 2)
PCI_OP_READ(dword, u32, 4)
PCI_OP_WRITE(byte,hP_WRITE(_               M	drivers/pconf4r                 17{
			dev_err(&dev-pN( i;
sdev->;
	 !defs_deo->bl   d(+iA_rig_e_arcnocess);
	_1bI(u U, qrestore(&p061fly */
		_nIm-u2A.h>ee_config\
	spin_unlocee_config\
	&dev-ee_c     1bsavaE);
	ops->w	tt-sxU           peU>e_creAeg0lnlocoaUWe YMBOWAIT_QUEEEEEEEEiev- nt);U pe
{
	sYMBOWAIT_Ql(&ansIurceA

	deFdev|	vaErsni           PCRange7800NL/ke(tuprs/pp|Iprotent);vpd);

/**
 * pci_write_vpN-aices, bus_lis