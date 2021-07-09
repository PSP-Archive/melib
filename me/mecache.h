#ifndef MECACHE_H
#define MECACHE_H

#ifdef __cplusplus
extern "C" {
#endif

void pspMeDcacheWritebackAll();
void pspMeDcacheWritebackInvalidateAll();
void pspMeDcacheInvalidateAll();
void pspMeDcacheWritebackRange();
void pspMeIcacheInvalidateRange();
void pspMeIcacheInvalidateAll();

#ifdef __cplusplus
}
#endif

#endif
