/**
 * @brief
 * timer
 *
 * @copyright
 * Copyright (c)  2020  Xiaomi Corporation (authors: Haowen Qiu)
 *
 * @copyright
 * See LICENSE for clarification regarding multiple authors
 */

#ifndef K2_CSRC_TIMER_H_
#define K2_CSRC_TIMER_H_

#include "k2/csrc/log.h"

namespace k2 {
class Timer {
 public:
  Timer() {
    K2_CHECK_CUDA_ERROR(cudaEventCreate(&time_start_));
    K2_CHECK_CUDA_ERROR(cudaEventCreate(&time_end_));
    Reset();
  }

  ~Timer() {
    K2_CHECK_CUDA_ERROR(cudaEventDestroy(time_start_));
    K2_CHECK_CUDA_ERROR(cudaEventDestroy(time_end_));
  }

  void Reset() { K2_CHECK_CUDA_ERROR(cudaEventRecord(time_start_, 0)); }

  double Elapsed() {
    K2_CHECK_CUDA_ERROR(cudaEventRecord(time_end_, 0));
    K2_CHECK_CUDA_ERROR(cudaEventSynchronize(time_end_));

    float ms_elapsed;
    K2_CHECK_CUDA_ERROR(
        cudaEventElapsedTime(&ms_elapsed, time_start_, time_end_));
    return ms_elapsed / 1e3;
  }

 private:
  cudaEvent_t time_start_;
  cudaEvent_t time_end_;
};

}  // namespace k2

#endif  // K2_CSRC_TIMER_H_
