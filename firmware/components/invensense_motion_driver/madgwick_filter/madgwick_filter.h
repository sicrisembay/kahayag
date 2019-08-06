#ifndef _MADGWICK_FILTER_H_
#define _MADGWICK_FILTER_H_

#include "fix16.h"

typedef struct {
    fix16_t q[4];
} madgwick_rec_t;

void madgwick_filter_quat_update(madgwick_rec_t *pRec,
                                 fix16_t ax, fix16_t ay, fix16_t az,
                                 fix16_t gx, fix16_t gy, fix16_t gz,
                                 fix16_t mx, fix16_t my, fix16_t mz);

#endif /* _MADGWICK_FILTER_H_ */
