#include "kernel/types.h"
#include "kernel/riscv.h"
#include "kernel/sysinfo.h"
#include "kernel/stat.h"
#include "user/user.h"


void
sinfo(struct sysinfo *info) {
  if (sysinfo(info) < 0) {
    printf("FAIL: sysinfo failed");
    exit(1);
  }
}

int
testmem() {
 struct sysinfo info;
 printf("testmem: starting\n");

 sinfo(&info);
 uint64 start_mem = info.freemem;
 // FIX 1: Cast to (void*) for %p
 //printf("start mem: %p\n", (void*)start_mem);
 printf("Free memory at start: %lu bytes\n", start_mem);
 sbrk(4096);

 sinfo(&info);
 uint64 end_mem = info.freemem;
 // FIX 1: Cast to (void*) for %p
 //printf("end mem: %p\n", (void*)end_mem);
 printf("Free memory at end:   %lu bytes\n", end_mem);
 if(start_mem > end_mem) {
  printf("testmem: OK (memory decreased)\n");
 } else {
  printf("testmem: FAIL (memory did not decrease)\n");
  return-1;
 }
 return 0;
}

int
testproc() {
 struct sysinfo info;
 printf("testproc: starting\n");

 sinfo(&info);
 uint64 start_nproc = info.nproc;
 // FIX 2: Cast to (int) for %d (easier to read for small numbers)
 printf("start nproc: %d\n", (int)start_nproc);

 int pid = fork();
 if(pid < 0){
 printf("fork failed\n");
 exit(1);
 }

 if(pid == 0){
  sleep(10);
  exit(0);
 } else {
  sinfo(&info);
  uint64 end_nproc = info.nproc;
  // FIX 2: Cast to (int) for %d
  printf("end nproc: %d\n", (int)end_nproc);
  if(end_nproc > start_nproc) {
  printf("testproc: OK (nproc increased)\n");
  } else {
    printf("testproc: FAIL (nproc did not increase)\n");
    return-1;
  }
  wait(0);
 }
 return 0;
}

int
main(int argc, char *argv[]) {
 printf("sysinfotest: start\n");
 if(testmem() == 0 && testproc() == 0){
 printf("sysinfotest: OK\n");
 } else {
  printf("sysinfotest FAIL\n");
 }
 exit(0);
}