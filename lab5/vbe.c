#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)



int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {
  
  struct reg86u r;
  mmap_t map;

  lm_init();
  lm_alloc(256, &map);

  /* CODE COPIED FROM SLIDES */

  r.u.w.ax = 0x4F01; /* VBE get mode info */
  /* translate the buffer linear address to a far pointer */
  r.u.w.es = PB2BASE(map.phys); /* set a segment base */
  r.u.w.di = PB2OFF(map.phys); /* set the offset accordingly */
  r.u.w.cx = mode;
  r.u.b.intno = 0x10;

  sys_int86(&r);

  memcpy(vmi_p,map.virtual,map.size);

  lm_free(&map); // void lm_free(mmap_t *map);
  
  return 1;
}



int vbe_get_info(VbeInfoBlock_t * v_info, int* pointer) {

  struct reg86u r;
  mmap_t map;

  pointer = lm_init();
  lm_alloc(256, &map);

  /* CODE COPIED FROM SLIDES */

  r.u.w.ax = 0x4F00; /* VBE get mode info */
  /* translate the buffer linear address to a far pointer */
  r.u.w.es = PB2BASE(map.phys); /* set a segment base */
  r.u.w.di = PB2OFF(map.phys); /* set the offset accordingly */
  r.u.b.intno = 0x10;

  sys_int86(&r);

  memcpy(v_info,map.virtual,map.size);

  lm_free(&map); // void lm_free(mmap_t *map);

  return 0;
}



