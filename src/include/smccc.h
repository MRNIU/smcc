
/**
 * @file smccc.h
 * @brief smccc 头文件
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
 * @see https://developer.arm.com/documentation/den0022/fb/?lang=en
 */

#ifndef SMCC_SRC_INCLUDE_SMCCC_H_
#define SMCC_SRC_INCLUDE_SMCCC_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SMCCC_PSCI_VERSION (0x84000000U)
#define SMCCC_PSCI_CPU_SUSPEND_32 (0x84000001U)
#define SMCCC_PSCI_CPU_SUSPEND_64 (0xC4000001U)
#define SMCCC_PSCI_CPU_OFF (0x84000002U)
#define SMCCC_PSCI_CPU_ON_32 (0x84000003U)
#define SMCCC_PSCI_CPU_ON_64 (0xC4000003U)
#define SMCCC_PSCI_AFFINITY_INFO_32 (0x84000004U)
#define SMCCC_PSCI_AFFINITY_INFO_64 (0xC4000004U)
#define SMCCC_PSCI_MIGRATE_32 (0x84000005U)
#define SMCCC_PSCI_MIGRATE_64 (0xC4000005U)
#define SMCCC_PSCI_MIGRATE_INFO_TYPE (0x84000006U)
#define SMCCC_PSCI_MIGRATE_INFO_UP_CPU_32 (0x84000007U)
#define SMCCC_PSCI_MIGRATE_INFO_UP_CPU_64 (0xC4000007U)
#define SMCCC_PSCI_SYSTEM_OFF (0x84000008U)
#define SMCCC_PSCI_SYSTEM_RESET (0x84000009U)
#define SMCCC_PSCI_SYSTEM_RESET2_32 (0x84000012U)
#define SMCCC_PSCI_SYSTEM_RESET2_64 (0xC4000012U)
#define SMCCC_PSCI_MEM_PROTECT (0x84000013U)
#define SMCCC_PSCI_MEM_PROTECT_CHECK_RANGE_32 (0x84000014U)
#define SMCCC_PSCI_MEM_PROTECT_CHECK_RANGE_64 (0xC4000014U)
#define SMCCC_PSCI_FEATURES (0x8400000AU)
#define SMCCC_PSCI_CPU_FREEZE (0x8400000BU)
#define SMCCC_PSCI_CPU_DEFAULT_SUSPEND_32 (0x8400000CU)
#define SMCCC_PSCI_CPU_DEFAULT_SUSPEND_64 (0xC400000CU)
#define SMCCC_PSCI_NODE_HW_STATE_32 (0x8400000DU)
#define SMCCC_PSCI_NODE_HW_STATE_64 (0xC400000DU)
#define SMCCC_PSCI_SYSTEM_SUSPEND_32 (0x8400000EU)
#define SMCCC_PSCI_SYSTEM_SUSPEND_64 (0xC400000EU)
#define SMCCC_PSCI_SET_SUSPEND_MODE (0x8400000FU)
#define SMCCC_PSCI_STAT_RESIDENCY_32 (0x84000010U)
#define SMCCC_PSCI_STAT_RESIDENCY_64 (0xC4000010U)
#define SMCCC_PSCI_STAT_COUNT_32 (0x84000011U)
#define SMCCC_PSCI_STAT_COUNT_64 (0xC4000011U)

/// 返回值
enum SMCCC_PSCI_ReturnValue {
  SMCCC_PSCI_SUCCESS = 0,
  SMCCC_PSCI_NOT_SUPPORTED = -1,
  SMCCC_PSCI_INVALID_PARAMETERS = -2,
  SMCCC_PSCI_DENIED = -3,
  SMCCC_PSCI_ALREADY_ON = -4,
  SMCCC_PSCI_ON_PENDING = -5,
  SMCCC_PSCI_INTERNAL_FAILURE = -6,
  SMCCC_PSCI_NOT_PRESENT = -7,
  SMCCC_PSCI_DISABLED = -8,
  SMCCC_PSCI_INVALID_ADDRESS = -9,
};

/// 电源状态编码
/// @see DEN0022F.b_Power_State_Coordination_Interface.pdf#6.5
struct StateID {
  // [15:12] Core is last in Power Level:
  // 0: Core Level
  // 1: Cluster Level
  // 2: System Level
  uint16_t core_last : 4;

  // [11:8] System Level Local Power State
  // 0: Run
  // 2: Retention
  // 3: Powerdown
  uint16_t system_state : 4;

  // [7:4] Cluster Level Local Power State
  // 0: Run
  // 2: Retention
  // 3: Powerdown
  uint16_t cluster_state : 4;

  // [3:0] Core Level Local Power State
  // 0: Run
  // 1: Standby
  // 2: Retention
  // 3: Powerdown
  uint16_t core_state : 4;
} __attribute__((packed));

/// 电源状态
/// @see DEN0022F.b_Power_State_Coordination_Interface.pdf#5.4.2
struct PowerState {
  // [31:26] Reserved. Must be zero.
  uint32_t reserved1 : 6;
  // [25:24] PowerLevel
  // Level 0: for cores
  // Level 1: for clusters
  // Level 2: for system
  uint32_t power_level : 2;
  // [23:17] Reserved. Must be zero.
  uint32_t reserved0 : 7;
  // [16] StateType
  uint32_t state_type : 1;
  // [15:0] StateID
  struct StateID state_id;
} __attribute__((packed));

/**
 * Suspend execution on a core or higher-level topology node.
 * @param power_state 电源状态
 * @param entry_point_address 用于恢复的地址
 * @param context_id 上下文标识
 * @return SMCCC_PSCI_ReturnValue 返回值
 * @see DEN0022F.b_Power_State_Coordination_Interface.pdf#5.1.2
 */
enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_suspend(
    struct PowerState power_state, uint64_t entry_point_address,
    uint64_t context_id);

/**
 * Power down the calling core
 * @return SMCCC_PSCI_ReturnValue 返回值
 * @see DEN0022F.b_Power_State_Coordination_Interface.pdf#5.1.3
 */
enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_off();

/**
 * Power up a core
 * @param target_cpu 低功耗状态
 * Bits[40:63]: Must be zero
 * Bits[32:39] Aff3: Match Aff3 of target core MPIDR
 * Bits[24:31] Must be zero
 * Bits[16:23] Aff2: Match Aff2 of target core MPIDR
 * Bits[8:15] Aff1: Match Aff1 of target core MPIDR
 * Bits[0:7] Aff0: Match Aff0 of target core MPIDR
 * @param entry_point_address 启动地址
 * @param context_id 上下文标识
 * @return SMCCC_PSCI_ReturnValue 返回值
 * @see DEN0022F.b_Power_State_Coordination_Interface.pdf#5.1.4
 */
enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_on(uint64_t target_cpu,
                                              uint64_t entry_point_address,
                                              uint64_t context_id);

#ifdef __cplusplus
}
#endif

#endif /* SMCC_SRC_INCLUDE_SMCCC_H_ */
