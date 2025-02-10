# smccc
C functions and constants for Arm SMCCC and PSCI

Ref: https://github.com/google/smccc

Support:

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_suspend(
    struct PowerState power_state, uint64_t entry_point_address,
    uint64_t context_id);

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_off();

enum SMCCC_PSCI_ReturnValue smccc_psci_cpu_on(uint64_t target_cpu,
                                              uint64_t entry_point_address,
                                              uint64_t context_id);
