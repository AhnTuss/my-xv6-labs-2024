 #include "kernel/types.h"
 struct sysinfo{
 uint64 freemem;
 uint64 nproc;
 };
 // uint64 getFreeMem(void);
 // uint64 getNproc(void);
 int sysinfo(struct sysinfo*);