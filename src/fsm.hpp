#ifndef __SMTMBT__FSM_HPP_INCLUDED
#define __SMTMBT__FSM_HPP_INCLUDED

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "util.hpp"

namespace smtmbt {
class Action;
class State;

struct ActionTuple
{
  ActionTuple(Action* a, State* next)
      : d_action(a), d_next(next){};

  Action* d_action;
  State* d_next;
};

class State
{
  friend class FSM;

 public:
  State() : d_id(""), d_is_final(false) {}
  State(std::string& id, bool is_final) : d_id(id), d_is_final(is_final) {}
  const std::string& get_id() { return d_id; }
  bool is_final() { return d_is_final; }
  State* run(RNGenerator& rng);
  void add_action(Action* action, uint32_t weight, State* next = nullptr);

 private:
  std::string d_id;
  bool d_is_final;
  std::vector<ActionTuple> d_actions;
  std::vector<uint32_t> d_weights;
};

class FSM
{
 public:
  FSM(RNGenerator& rng) : d_rng(rng) {}
  FSM() = delete;
  State* new_state(std::string id = "", bool is_final = false);
  void set_init_state(State* init_state);
  void check_states();
  void run();

 private:
  RNGenerator& d_rng;
  std::vector<std::unique_ptr<State>> d_states;
  State* d_cur_state;
};

}  // namespace smtmbt
#endif
