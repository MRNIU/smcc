
/**
 * @file smccc.c
 * @brief smccc 实现
 * @author Zone.N (Zone.Niuzh@hotmail.com)
 * @version 1.0
 * @date 2024-05-24
 * @copyright MIT LICENSE
 * https://github.com/MRNIU/smccc
 * @par change log:
 * <table>
 * <tr><th>Date<th>Author<th>Description
 * <tr><td>2024-05-24<td>Zone.N (Zone.Niuzh@hotmail.com)<td>创建文件
 * </table>
 */

#include "smccc.h"

// 内联汇编实现（GCC 风格）
static inline void arm_smccc_hvc(unsigned long a0, unsigned long a1,
                                 unsigned long a2, unsigned long a3,
                                 unsigned long a4, unsigned long a5,
                                 unsigned long a6, unsigned long a7,
                                 struct arm_smccc_res *res) {
  register unsigned long x0 __asm__("x0") = a0;
  register unsigned long x1 __asm__("x1") = a1;
  register unsigned long x2 __asm__("x2") = a2;
  register unsigned long x3 __asm__("x3") = a3;
  register unsigned long x4 __asm__("x4") = a4;
  register unsigned long x5 __asm__("x5") = a5;
  register unsigned long x6 __asm__("x6") = a6;
  register unsigned long x7 __asm__("x7") = a7;

  __asm__ volatile(
      "hvc #0\n"            // 触发 HVC 调用
      "stp x0, x1, [%8]\n"  // 保存 x0-x3 到 res->a0-a3
      "stp x2, x3, [%8, #16]"
      : "=r"(x0), "=r"(x1), "=r"(x2), "=r"(x3), "=r"(x4), "=r"(x5), "=r"(x6),
        "=r"(x7)
      : "r"(x0), "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(x6), "r"(x7),
        "r"(res)
      : "memory");
}

static inline void arm_smccc_smc(unsigned long a0, unsigned long a1,
                                 unsigned long a2, unsigned long a3,
                                 unsigned long a4, unsigned long a5,
                                 unsigned long a6, unsigned long a7,
                                 struct arm_smccc_res *res) {
  register unsigned long x0 __asm__("x0") = a0;
  register unsigned long x1 __asm__("x1") = a1;
  register unsigned long x2 __asm__("x2") = a2;
  register unsigned long x3 __asm__("x3") = a3;
  register unsigned long x4 __asm__("x4") = a4;
  register unsigned long x5 __asm__("x5") = a5;
  register unsigned long x6 __asm__("x6") = a6;
  register unsigned long x7 __asm__("x7") = a7;

  __asm__ volatile(
      "smc #0\n"            // 触发 SMC 调用
      "stp x0, x1, [%8]\n"  // 保存 x0-x3 到 res->a0-a3
      "stp x2, x3, [%8, #16]"
      : "=r"(x0), "=r"(x1), "=r"(x2), "=r"(x3), "=r"(x4), "=r"(x5), "=r"(x6),
        "=r"(x7)
      : "r"(x0), "r"(x1), "r"(x2), "r"(x3), "r"(x4), "r"(x5), "r"(x6), "r"(x7),
        "r"(res)
      : "memory");
}

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_suspend(
    struct PowerState power_state, uint64_t entry_point_address,
    uint64_t context_id) {
  return SMCCC_PSCI_SUCCESS;
}

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_off() { return SMCCC_PSCI_SUCCESS; }

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_on(uint64_t target_cpu,
                                              uint64_t entry_point_address,
                                              uint64_t context_id) {
  struct arm_smccc_res res;
  arm_smccc_hvc(SMCCC_PSCI_CPU_ON_64,  // a0: 服务编号
                target_cpu,            // a1: 目标核心的 MPIDR
                entry_point_address,   // a2: 入口地址（物理地址）
                context_id,            // a3: 上下文 ID（通常为 0）
                0, 0, 0, 0,            // a4-a7: 保留或未使用
                &res);
  return res.a0;
}
