
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

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_suspend(
    struct PowerState power_state, uint64_t entry_point_address,
    uint64_t context_id) {
  return SMCCC_PSCI_SUCCESS;
}

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_off() { return SMCCC_PSCI_SUCCESS; }

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_on(uint64_t target_cpu,
                                              uint64_t entry_point_address,
                                              uint64_t context_id) {
  return SMCCC_PSCI_SUCCESS;
}
