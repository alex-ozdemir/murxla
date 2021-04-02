#ifndef __MURXLA__STATISTICS_H
#define __MURXLA__STATISTICS_H

#include "config.hpp"
#include "op.hpp"

namespace murxla {

namespace statistics {

struct Statistics
{
  uint64_t d_results[3];
  char d_op_kinds[MURXLA_MAX_N_OPS][MURXLA_MAX_KIND_LEN];
  uint64_t d_ops[MURXLA_MAX_N_OPS];
  uint64_t d_ops_ok[MURXLA_MAX_N_OPS];
  char d_state_kinds[MURXLA_MAX_N_STATES][MURXLA_MAX_KIND_LEN];
  uint64_t d_states[MURXLA_MAX_N_STATES];
  char d_action_kinds[MURXLA_MAX_N_ACTIONS][MURXLA_MAX_KIND_LEN];
  uint64_t d_actions[MURXLA_MAX_N_ACTIONS];
  uint64_t d_actions_ok[MURXLA_MAX_N_ACTIONS];

  void print() const;
};

}  // namespace statistics
}  // namespace murxla
#endif
