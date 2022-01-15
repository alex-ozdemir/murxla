#ifdef MURXLA_USE_CVC5

#ifndef __MURXLA__CVC5_SOLVER_H
#define __MURXLA__CVC5_SOLVER_H

#include "cvc5/cvc5.h"
#include "fsm.hpp"
#include "solver.hpp"

namespace murxla {
namespace cvc5 {

/* -------------------------------------------------------------------------- */
/* Cvc5Sort                                                                   */
/* -------------------------------------------------------------------------- */

class Cvc5Sort : public AbsSort
{
  friend class Cvc5Solver;

 public:
  /** Get wrapped cvc5 sort from Murxla sort. */
  static ::cvc5::api::Sort& get_cvc5_sort(Sort sort);
  /** Convert vector of cvc5 sorts to vector of Murxla sorts. */
  static std::vector<Sort> cvc5_sorts_to_sorts(
      ::cvc5::api::Solver* cvc5, const std::vector<::cvc5::api::Sort>& sorts);
  /** Convert vector of Murxla sorts to vector of cvc5 sorts. */
  static std::vector<::cvc5::api::Sort> sorts_to_cvc5_sorts(
      const std::vector<Sort>& sorts);

  Cvc5Sort(::cvc5::api::Solver* cvc5, ::cvc5::api::Sort sort)
      : d_solver(cvc5), d_sort(sort)
  {
  }

  ~Cvc5Sort() override {}
  size_t hash() const override;
  bool equals(const Sort& other) const override;
  bool not_equals(const Sort& other) const override;
  std::string to_string() const override;
  bool is_array() const override;
  bool is_bag() const override;
  bool is_bool() const override;
  bool is_bv() const override;
  bool is_dt() const override;
  bool is_dt_parametric() const override;
  bool is_dt_well_founded() const override;
  bool is_fp() const override;
  bool is_fun() const override;
  bool is_int() const override;
  bool is_real() const override;
  bool is_reglan() const override;
  bool is_rm() const override;
  bool is_seq() const override;
  bool is_set() const override;
  bool is_string() const override;
  bool is_uninterpreted() const override;
  uint32_t get_bv_size() const override;
  uint32_t get_fp_exp_size() const override;
  uint32_t get_fp_sig_size() const override;
  std::string get_dt_name() const override;
  uint32_t get_dt_num_cons() const override;
  std::vector<std::string> get_dt_cons_names() const override;
  uint32_t get_dt_cons_num_sels(const std::string& name) const override;
  std::vector<std::string> get_dt_cons_sel_names(
      const std::string& name) const override;
  Sort get_array_index_sort() const override;
  Sort get_array_element_sort() const override;
  Sort get_bag_element_sort() const override;
  uint32_t get_fun_arity() const override;
  Sort get_fun_codomain_sort() const override;
  std::vector<Sort> get_fun_domain_sorts() const override;
  Sort get_seq_element_sort() const override;
  Sort get_set_element_sort() const override;

 private:
  ::cvc5::api::Solver* d_solver;
  ::cvc5::api::Sort d_sort;
};

/* -------------------------------------------------------------------------- */
/* Cvc5Term                                                                   */
/* -------------------------------------------------------------------------- */

class Cvc5Term : public AbsTerm
{
  friend class Cvc5Solver;

 public:
  /** Get wrapped cvc5 term from Murxla term. */
  static ::cvc5::api::Term& get_cvc5_term(Term term);
  /** Convert vector of cvc5 terms to vector of Murxla terms. */
  static std::vector<Term> cvc5_terms_to_terms(
      RNGenerator& rng,
      ::cvc5::api::Solver* cvc5,
      const std::vector<::cvc5::api::Term>& terms);
  /** Convert vector of Murxla terms to vector of cvc5 terms. */
  static std::vector<::cvc5::api::Term> terms_to_cvc5_terms(
      const std::vector<Term>& terms);
  /** Map operator kinds to Bitwuzla operator kinds. */
  static std::unordered_map<Op::Kind, ::cvc5::api::Kind> s_kinds_to_cvc5_kinds;
  /** Map Bitwuzla operator kinds to operator kinds. */
  static std::unordered_map<::cvc5::api::Kind, Op::Kind> s_cvc5_kinds_to_kinds;

  /** Solver-specific operators. */
  // BV
  inline static const Op::Kind OP_BV_REDAND = "bvredand";
  inline static const Op::Kind OP_BV_REDOR  = "bvredor";
  inline static const Op::Kind OP_BV_ULTBV  = "cvc5-OP_BV_ULTBV";
  inline static const Op::Kind OP_BV_SLTBV  = "cvc5-OP_BV_SLTBV";
  inline static const Op::Kind OP_BV_ITE    = "cvc5-OP_BV_ITE";
  inline static const Op::Kind OP_INT_TO_BV = "int2bv";
  // Datatypes
  inline static const Op::Kind OP_DT_SIZE = "dt.size";
  // Int
  inline static const Op::Kind OP_BV_TO_NAT = "bv2nat";
  inline static const Op::Kind OP_INT_IAND  = "iand";
  inline static const Op::Kind OP_INT_POW2  = "int.pow2";
  // Real
  inline static const Op::Kind OP_REAL_PI = "real.pi";
  //  Strings
  inline static const Op::Kind OP_STRING_UPDATE  = "str.update";
  inline static const Op::Kind OP_STRING_TOLOWER = "str.tolower";
  inline static const Op::Kind OP_STRING_TOUPPER = "str.toupper";
  inline static const Op::Kind OP_STRING_REV     = "str.rev";

  /* Special value kinds that have its own node kind in cvc5, only used
   * for getKind(). */
  inline static const Op::Kind OP_REGEXP_EMPTY = "cvc5-OP_REGEXP_EMPTY";
  inline static const Op::Kind OP_REGEXP_SIGMA = "cvc5-OP_REGEXP_SIGMA";
  inline static const Op::Kind OP_REGEXP_STAR  = "re.*";
  inline static const Op::Kind OP_SET_EMPTY    = "cvc5-OP_SET_EMPTY";
  inline static const Op::Kind OP_SET_UNIVERSE = "cvc5-OP_SET_UNIVERSE";

  Cvc5Term(RNGenerator& rng, ::cvc5::api::Solver* cvc5, ::cvc5::api::Term term)
      : d_rng(rng), d_solver(cvc5), d_term(term)
  {
  }

  ~Cvc5Term() override {}
  size_t hash() const override;
  bool equals(const Term& other) const override;
  std::string to_string() const override;
  bool is_bool_value() const override;
  bool is_bv_value() const override;
  bool is_fp_value() const override;
  bool is_int_value() const override;
  bool is_real_value() const override;
  bool is_seq_value() const override;
  bool is_set_value() const override;
  bool is_string_value() const override;
  const Op::Kind& get_kind() const override;
  std::vector<Term> get_children() const override;
  bool is_indexed() const override;
  size_t get_num_indices() const override;
  std::vector<std::string> get_indices() const override;
  uint32_t get_bv_size() const override;
  uint32_t get_fp_exp_size() const override;
  uint32_t get_fp_sig_size() const override;
  Sort get_array_index_sort() const override;
  Sort get_array_element_sort() const override;
  uint32_t get_fun_arity() const override;
  Sort get_fun_codomain_sort() const override;
  std::vector<Sort> get_fun_domain_sorts() const override;

 private:
  /** The associated solver RNG. */
  RNGenerator& d_rng;
  /** The associated cvc5 solver instance. */
  ::cvc5::api::Solver* d_solver = nullptr;
  /** The wrapped cvc5 term. */
  ::cvc5::api::Term d_term;
};

/* -------------------------------------------------------------------------- */
/* Cvc5Solver                                                                 */
/* -------------------------------------------------------------------------- */

class Cvc5Solver : public Solver
{
 public:
  /** Solver-specific actions. */
  inline static const Action::Kind ACTION_CHECK_ENTAILED =
      "cvc5-check-entailed";
  inline static const Action::Kind ACTION_SIMPLIFY = "cvc5-simplify";
  inline static const Action::Kind ACTION_GET_DIFFICULTY =
      "cvc5-get-difficulty";
  inline static const Action::Kind ACTION_GET_INTERPOLANT =
      "cvc5-get-interpolant";
  inline static const Action::Kind ACTION_SORT_SUBSTITUTE =
      "cvc5-sort-substitute";
  inline static const Action::Kind ACTION_TERM_SUBSTITUTE =
      "cvc5-term-substitute";

  /** Constructor. */
  Cvc5Solver(SolverSeedGenerator& sng) : Solver(sng), d_solver(nullptr) {}
  /** Destructor. */
  ~Cvc5Solver() override;

  OpKindSet get_unsupported_op_kinds() const override;
  OpKindSortKindMap get_unsupported_op_sort_kinds() const override;
  SortKindSet get_unsupported_var_sort_kinds() const override;
  SortKindSet get_unsupported_array_index_sort_kinds() const override;
  SortKindSet get_unsupported_array_element_sort_kinds() const override;
  SortKindSet get_unsupported_bag_element_sort_kinds() const override;
  SortKindSet get_unsupported_seq_element_sort_kinds() const override;
  SortKindSet get_unsupported_set_element_sort_kinds() const override;
  SortKindSet get_unsupported_fun_sort_domain_sort_kinds() const override;
  SortKindSet get_unsupported_fun_sort_codomain_sort_kinds() const override;
  SortKindSet get_unsupported_fun_domain_sort_kinds() const override;
  SortKindSet get_unsupported_fun_codomain_sort_kinds() const override;
  SortKindSet get_unsupported_dt_sel_codomain_sort_kinds() const override;
  SortKindSet get_unsupported_get_value_sort_kinds() const override;

  void new_solver() override;

  void delete_solver() override;

  ::cvc5::api::Solver* get_solver();

  bool is_initialized() const override;

  const std::string get_name() const override;

  void configure_fsm(FSM* fsm) const override;
  void configure_opmgr(OpKindManager* opmgr) const override;
  void configure_options(SolverManager* smgr) const override;

  bool is_unsat_assumption(const Term& t) const override;

  std::string get_option_name_incremental() const override;
  std::string get_option_name_model_gen() const override;
  std::string get_option_name_unsat_assumptions() const override;
  std::string get_option_name_unsat_cores() const override;

  bool option_incremental_enabled() const override;
  bool option_model_gen_enabled() const override;
  bool option_unsat_assumptions_enabled() const override;
  bool option_unsat_cores_enabled() const override;

  Term mk_var(Sort sort, const std::string& name) override;

  Term mk_fun(const std::string& name,
              const std::vector<Term>& args,
              Term body) override;

  Term mk_value(Sort sort, bool value) override;
  Term mk_value(Sort sort, const std::string& value) override;
  Term mk_value(Sort sort,
                const std::string& num,
                const std::string& den) override;
  Term mk_value(Sort sort, const std::string& value, Base base) override;

  Term mk_special_value(Sort sort,
                        const AbsTerm::SpecialValueKind& value) override;

  Sort mk_sort(const std::string& name) override;
  Sort mk_sort(SortKind kind) override;
  Sort mk_sort(SortKind kind, uint32_t size) override;
  Sort mk_sort(SortKind kind, uint32_t esize, uint32_t ssize) override;
  Sort mk_sort(SortKind kind, const std::vector<Sort>& sorts) override;
  std::vector<Sort> mk_sort(SortKind kind,
                            const std::vector<std::string>& dt_names,
                            const std::vector<std::vector<Sort>>& param_sorts,
                            const std::vector<AbsSort::DatatypeConstructorMap>&
                                constructors) override;

  Sort instantiate_sort(Sort param_sort,
                        const std::vector<Sort>& sorts) override;

  Term mk_const(Sort sort, const std::string& name) override;
  Term mk_term(const Op::Kind& kind,
               const std::vector<Term>& args,
               const std::vector<uint32_t>& indices) override;
  Term mk_term(const Op::Kind& kind,
               const std::vector<std::string>& str_args,
               const std::vector<Term>& args) override;
  Term mk_term(const Op::Kind& kind,
               Sort sort,
               const std::vector<std::string>& str_args,
               const std::vector<Term>& args) override;

  Sort get_sort(Term term, SortKind sort_kind) const override;

  void assert_formula(const Term& t) override;

  Result check_sat() override;
  Result check_sat_assuming(const std::vector<Term>& assumptions) override;

  std::vector<Term> get_unsat_assumptions() override;

  std::vector<Term> get_unsat_core() override;

  std::vector<Term> get_value(const std::vector<Term>& terms) override;

  void push(uint32_t n_levels) override;
  void pop(uint32_t n_levels) override;

  void print_model() override;

  void set_logic(const std::string& logic) override;

  void reset() override;
  void reset_assertions() override;

  void set_opt(const std::string& opt, const std::string& value) override;

  //
  // get_model()
  // get_proof()
  //

  void check_sort(Sort sort) override;
  void check_term(Term term) override;
  void check_value(Term term) override;

  std::unordered_map<std::string, std::string> get_required_options(
      TheoryId theory) const override;

 private:
  /**
   * Helper to get the DatatypeConstructor of given name from a datatype sort.
   */
  ::cvc5::api::DatatypeConstructor getDatatypeConstructor(
      ::cvc5::api::Sort dt_sort, const std::string& ctor_name);
  /**
   * Helper to get the DatatypeSelector of given name for the given constructor
   * from a datatype sort.
   */
  ::cvc5::api::DatatypeSelector getDatatypeSelector(
      ::cvc5::api::Sort dt_sort,
      const std::string& ctor_name,
      const std::string& sel_name);
  /**
   * Helper to get the Term representation of the DatatypeConstructor of given
   * name from a datatype sort.
   */
  ::cvc5::api::Term getDatatypeConstructorTerm(::cvc5::api::Sort dt_sort,
                                               const std::string& ctor_name);
  /**
   * Helper to get the Term representation of the DatatypeSelector of given
   * name for the given constructor from a datatype sort.
   */
  ::cvc5::api::Term getDatatypeSelectorTerm(::cvc5::api::Sort dt_sort,
                                            const std::string& ctor_name,
                                            const std::string& sel_name);

  /** The wrapped cvc5 solver instance. */
  ::cvc5::api::Solver* d_solver;

  /** Options set via set_opt(). */
  std::vector<std::pair<std::string, std::string>> d_enabled_options;

  /** Logic set via set_logic(). */
  std::string d_logic = "";
};

}  // namespace cvc5
}  // namespace murxla

#endif

#endif

