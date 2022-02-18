#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <stdbool.h>
#include <execinfo.h>

static void __attribute__((constructor)) InitHooks();

static void* (*libc_malloc)(size_t)=NULL;
static void (*libc_free)(void*)=NULL;

static bool intialized = false;

void BT (void)
{
  static int btInProgress = false;
  void *array[10];
  char **strings;
  int size, i;

  if(btInProgress) return;

  btInProgress = true;
  size = backtrace (array, 10);
  strings = backtrace_symbols (array, size);
  if (strings != NULL)
  {
    fprintf(stdout,"Obtained %d stack frames.\n", size);
    for (i = 0; i < size; i++)
      fprintf(stdout,"%s\n", strings[i]);
  }

  libc_free (strings);
  btInProgress = false;
}

void InitHooks()
{
    //fprintf(stderr,"Calling InitHooks, intialized = %d\n",intialized);
    libc_malloc = dlsym(RTLD_NEXT, "malloc");
    libc_free   = dlsym(RTLD_NEXT, "free");
}

void* malloc(size_t size)
{
    BT();
    void* ptr = libc_malloc(size);
    fprintf(stderr,"malloc : [%ld] Bytes @ [%p]\n",size,ptr);
    return ptr;
}

void free(void* ptr)
{
    fprintf(stderr,"free : [%p]\n",ptr);
    BT();
    libc_free(ptr);
    ptr = NULL;
}