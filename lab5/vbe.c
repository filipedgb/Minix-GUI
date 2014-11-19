#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)


/*
 *COPIED CODE FROM: http://web.fe.up.pt/~pfs/aulas/lcom2011/labs/lab2/src/vbe.c
 */

typedef struct {
  /* Mandatory information for all VBE revisions */
  u8_t ModeAttributes[2]; 	/* mode attributes */
  u8_t WinAAttributes; 	/* window A attributes */
  u8_t WinBAttributes; 	/* window B attributes */
  u8_t WinGranularity[2]; 	/* window granularity */
  u8_t WinSize[2];		/* window size */
  u8_t WinASegment[2];		/* window A start segment */
  u8_t WinBSegment[2];		/* window B start segment */
  u8_t WinFuncPtr[4]; 		/* real mode far pointer to window function */
  u8_t BytesPerScanLine[2]; 	/* bytes per scan line */

  /* Mandatory information for VBE 1.2 and above */

  u8_t XResolution[2];      	/* horizontal resolution in pixels/characters */
  u8_t YResolution[2];      	/* vertical resolution in pixels/characters */
  u8_t XCharSize; 		/*character cell width in pixels */
  u8_t YCharSize; 		/*character cell height in pixels */
  u8_t NumberOfPlanes; 	/* number of memory planes */
  u8_t BitsPerPixel; 		/* bits per pixel */
  u8_t NumberOfBanks;		/* number of banks */
  u8_t MemoryModel;		/* memory model type */
  u8_t BankSize;		/* bank size in KB */
  u8_t NumberOfImagePages;	/* number of images */
  u8_t Reserved1;		/* reserved for page function */

  /* Direct Color fields (required for direct/6 and YUV/7 memory models) */
  u8_t RedMaskSize;		/* size of direct color red mask in bits */
  u8_t RedFieldPosition;	/* bit position of lsb of red mask */
  u8_t GreenMaskSize;		/* size of direct color green mask in bits */
  u8_t GreenFieldPosition;	/* bit position of lsb of green mask */
  u8_t BlueMaskSize; 		/* size of direct color blue mask in bits */
  u8_t BlueFieldPosition;	/* bit position of lsb of blue mask */
  u8_t RsvdMaskSize;		/* size of direct color reserved mask in bits */
  u8_t RsvdFieldPosition;	/* bit position of lsb of reserved mask */
  u8_t DirectColorModeInfo;	/* direct color mode attributes */

  /* Mandatory information for VBE 2.0 and above */
  u8_t PhysBasePtr[4];      /* physical address for flat memory frame buffer */
  u8_t Reserved2[4]; 		/* Reserved - always set to 0 */
  u8_t Reserved3[2]; 		/* Reserved - always set to 0 */

  /* Mandatory information for VBE 3.0 and above */
  u8_t LinBytesPerScanLine[2]; /* bytes per scan line for linear modes */
  u8_t BnkNumberOfImagePages; 	/* number of images for banked modes */
  u8_t LinNumberOfImagePages; 	/* number of images for linear modes */
  u8_t LinRedMaskSize; 	/* size of direct color red mask (linear modes) */
  u8_t LinRedFieldPosition; 	/* bit position of lsb of red mask (linear modes) */
  u8_t LinGreenMaskSize; 	/* size of direct color green mask (linear modes) */
  u8_t LinGreenFieldPosition; /* bit position of lsb of green mask (linear  modes) */
  u8_t LinBlueMaskSize; 	/* size of direct color blue mask (linear modes) */
  u8_t LinBlueFieldPosition; 	/* bit position of lsb of blue mask (linear modes ) */
  u8_t LinRsvdMaskSize; 	/* size of direct color reserved mask (linear modes) */
  u8_t LinRsvdFieldPosition;	 /* bit position of lsb of reserved mask (linear modes) */
  u8_t MaxPixelClock[4]; 	/* maximum pixel clock (in Hz) for graphics mode */
  u8_t Reserved4[189]; 		/* remainder of ModeInfoBlock */
} VbeModeInfoBlock_t;



static void vbe_unpack_mode_info(void *buf, vbe_mode_info_t *dst) {

  VbeModeInfoBlock_t *src = buf;

  printf("vbe_unpack_mode_info: src = 0x%p dst = 0x%p\n", src, dst);

  memcpy(&(dst->ModeAttributes), src->ModeAttributes, 2);
  dst->WinAAttributes = src->WinAAttributes;
  dst->WinBAttributes = src->WinBAttributes;
  memcpy(&(dst->WinGranularity), src->WinGranularity, 2);
  memcpy(&(dst->WinSize), src->WinSize, 2);
  memcpy(&(dst->WinASegment), src->WinASegment, 2);
  memcpy(&(dst->WinBSegment), src->WinBSegment, 2);
  memcpy(&(dst->WinFuncPtr), src->WinFuncPtr, 4);
  memcpy(&(dst->BytesPerScanLine), src->BytesPerScanLine, 2);

  /* Mandatory information for VBE 1.2 and above */

  memcpy(&(dst->XResolution), src->XResolution, 2);
  memcpy(&(dst->YResolution), src->YResolution, 2);
  dst->XCharSize = src->XCharSize;
  dst->YCharSize = src->YCharSize;
  dst->NumberOfPlanes = src->NumberOfPlanes;
  dst->BitsPerPixel = src->BitsPerPixel;
  dst->NumberOfBanks = src->NumberOfBanks;
  dst->MemoryModel = src->MemoryModel;
  dst->BankSize = src->BankSize;
  dst->NumberOfImagePages = src->NumberOfImagePages;

  /* Direct Color fields (required for direct/6 and YUV/7 memory models) */
  dst->RedMaskSize = src->RedMaskSize;
  dst->RedFieldPosition = src->RedFieldPosition;
  dst->GreenMaskSize = src->GreenMaskSize;
  dst->GreenFieldPosition = src->GreenFieldPosition;
  dst->BlueMaskSize = src->BlueMaskSize;
  dst->BlueFieldPosition = src->BlueFieldPosition;
  dst->RsvdMaskSize = src->RsvdMaskSize;
  dst->RsvdFieldPosition = src->RsvdFieldPosition;
  dst->DirectColorModeInfo = src->DirectColorModeInfo;

  /* Mandatory information for VBE 2.0 and above */
  memcpy(&(dst->PhysBasePtr), src->PhysBasePtr, 4);

  /* Mandatory information for VBE 3.0 and above */
  memcpy(&(dst->LinBytesPerScanLine), src->LinBytesPerScanLine, 2);
  dst->BnkNumberOfImagePages = src->BnkNumberOfImagePages;
  dst->LinNumberOfImagePages = src->LinNumberOfImagePages;
  dst->LinRedMaskSize = src->LinRedMaskSize;
  dst->LinRedFieldPosition = src->LinRedFieldPosition;
  dst->LinGreenMaskSize = src->LinGreenMaskSize;
  dst->LinGreenFieldPosition = src->LinGreenFieldPosition;
  dst->LinBlueMaskSize = src->LinBlueMaskSize;
  dst->LinBlueFieldPosition = src->LinBlueFieldPosition;
  dst->LinRsvdMaskSize = src->LinRsvdMaskSize;
  dst->LinRsvdFieldPosition = src->LinRsvdFieldPosition;
  memcpy(&(dst->MaxPixelClock), src->MaxPixelClock, 4);
}

/* END OF COPIED CODE */



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

  vbe_unpack_mode_info(map.virtual, vmi_p);

  lm_free(&map); // void lm_free(mmap_t *map);
  
  return 1;
}

