// Auto-generated file. Do not edit!
//   Template: src/f16-spmm/neonfp16arith.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <arm_neon.h>

#include <xnnpack/spmm.h>


void xnn_f16_spmm_ukernel_8x1__neonfp16arith(
    uint32_t m,
    uint32_t n,
    const void*restrict input,
    const void*restrict weights,
    const int32_t*restrict widx_dmap,
    const uint32_t*restrict nidx_nnzmap,
    void*restrict output,
    const struct xnn_f16_output_params params[restrict static 1])
{
  assert(m != 0);

  const __fp16*restrict a = input;
  __fp16*restrict c = output;

  const float16x8_t vscale = vld1q_dup_f16((const __fp16*) &params->scale);
  const float16x8_t vmax = vld1q_dup_f16((const __fp16*) &params->max);
  const float16x8_t vmin = vld1q_dup_f16((const __fp16*) &params->min);

  size_t i = m;
  while XNN_LIKELY(i >= 8) {
    const __fp16*restrict w = weights;
    const int32_t* dmap = widx_dmap;
    const uint32_t* nnzmap = nidx_nnzmap;
    size_t j = n;
    do {
      uint32_t nnz = *nnzmap++;
      float16x8_t vacc01234567 = vld1q_dup_f16(w); w += 1;
      if XNN_LIKELY(nnz != 0) {
        do {
          const intptr_t diff = *dmap++;
          const float16x8_t va01234567 = vld1q_f16(a);
          a = (const __fp16*restrict) ((uintptr_t) a + (uintptr_t) diff);
          const float16x8_t vb = vld1q_dup_f16(w); w += 1;
          vacc01234567 = vfmaq_f16(vacc01234567, va01234567, vb);
        } while (--nnz != 0);
      }
      float16x8_t vout01234567 = vmulq_f16(vacc01234567, vscale);
      vout01234567 = vminq_f16(vout01234567, vmax);
      vout01234567 = vmaxq_f16(vout01234567, vmin);
      vst1q_f16(c, vout01234567);
      c += m;
    } while (--j != 0);
    c -= m * n;
    c += 8;
    a += 8;
    i -= 8;
  }
  if XNN_UNLIKELY(i != 0) {
    if (i & 4) {
      const __fp16*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t j = n;
      do {
        uint32_t nnz = *nnzmap++;
        float16x4_t vacc0123 = vld1_dup_f16(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float16x4_t va0123 = vld1_f16(a);
            a = (const __fp16*restrict) ((uintptr_t) a + (uintptr_t) diff);
            const float16x4_t vb = vld1_dup_f16(w); w += 1;
            vacc0123 = vfma_f16(vacc0123, va0123, vb);
          } while (--nnz != 0);
        }
        float16x4_t vout0123 = vmin_f16(vacc0123, vget_low_f16(vmax));
        vout0123 = vmax_f16(vout0123, vget_low_f16(vmin));
        vst1_f16(c, vout0123);
        c += m;
      } while (--j != 0);
      c -= m * n;
      c += 4;
      a += 4;
    }
    if (i & 2) {
      const __fp16*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t j = n;
      do {
        uint32_t nnz = *nnzmap++;
        float16x4_t vacc01 = vld1_dup_f16(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float16x4_t va01 = vreinterpret_f16_f32(vld1_dup_f32(__builtin_assume_aligned(a, 1)));
            a = (const __fp16*restrict) ((uintptr_t) a + (uintptr_t) diff);
            const float16x4_t vb = vld1_dup_f16(w); w += 1;
            vacc01 = vfma_f16(vacc01, va01, vb);
          } while (--nnz != 0);
        }
        float16x4_t vout01 = vmin_f16(vacc01, vget_low_f16(vmax));
        vout01 = vmax_f16(vout01, vget_low_f16(vmin));
        vst1_lane_f32(__builtin_assume_aligned(c, 1), vreinterpret_f32_f16(vout01), 0);
        c += m;
      } while (--j != 0);
      c -= m * n;
      c += 2;
      a += 2;
    }
    if (i & 1) {
      const __fp16*restrict w = weights;
      const int32_t* dmap = widx_dmap;
      const uint32_t* nnzmap = nidx_nnzmap;
      size_t j = n;
      do {
        uint32_t nnz = *nnzmap++;
        float16x4_t vacc0 = vld1_dup_f16(w); w += 1;
        if XNN_LIKELY(nnz != 0) {
          do {
            const intptr_t diff = *dmap++;
            const float16x4_t va0 = vld1_dup_f16(a);
            a = (const __fp16*restrict) ((uintptr_t) a + (uintptr_t) diff);
            const float16x4_t vb = vld1_dup_f16(w); w += 1;
            vacc0 = vfma_f16(vacc0, va0, vb);
          } while (--nnz != 0);
        }
        float16x4_t vout0 = vmin_f16(vacc0, vget_low_f16(vmax));
        vout0 = vmax_f16(vout0, vget_low_f16(vmin));
        vst1_lane_f16(c, vout0, 0);
        c += m;
      } while (--j != 0);
      c -= m * n;
      c += 1;
      a += 1;
    }
  }
}
