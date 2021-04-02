#ifndef __MURXLA__CONFIG_H
#define __MURXLA__CONFIG_H

/**
 * Maximum number of actions.
 *
 * There is no real upper limit, but we have to define this statically, because
 * statistics are created in shared memory (and thus no dynamic data structure
 * can be used). If an exception is raised to indicate that the maximum number
 * of actions has been exceeded, increase this value.
 */
#define MURXLA_MAX_N_ACTIONS 100
/**
 * Maximum number of operators.
 *
 * There is no real upper limit, but we have to define this statically, because
 * statistics are created in shared memory (and thus no dynamic data structure
 * can be used). If an exception is raised to indicate that the maximum number
 * of operators has been exceeded, increase this value.
 */
#define MURXLA_MAX_N_OPS 200
/**
 * Maximum number of states.
 *
 * There is no real upper limit, but we have to define this statically, because
 * statistics are created in shared memory (and thus no dynamic data structure
 * can be used). If an exception is raised to indicate that the maximum number
 * of states has been exceeded, increase this value.
 */
#define MURXLA_MAX_N_STATES 100
/**
 * Maximum length of action, operator and state kinds.
 *
 * There is no real upper limit, but we have to define this statically, because
 * statistics are created in shared memory (and thus no dynamic data structure
 * can be used). If an exception is raised to indicate that the maximum length
 * of a kind has been exceeded, increase this value.
 */
#define MURXLA_MAX_KIND_LEN 100

#define MURXLA_BW_MIN 1
#define MURXLA_BW_MAX 128

#define MURXLA_INT_LEN_MAX 50
#define MURXLA_REAL_LEN_MAX 50
#define MURXLA_RATIONAL_LEN_MAX 10
#define MURXLA_STR_LEN_MAX 100

#define MURXLA_SYMBOL_LEN_MAX 128

#define MURXLA_MAX_N_ASSUMPTIONS_CHECK_SAT 5
#define MURXLA_MAX_N_PUSH_LEVELS 5
#define MURXLA_MAX_N_TERMS_GET_VALUE 5

/* mk_term: at least one argument */
#define MURXLA_MK_TERM_N_ARGS -1
/* mk_term: at least two arguemtns */
#define MURXLA_MK_TERM_N_ARGS_BIN -2
/* mk_term: min number of arguments */
#define MURXLA_MK_TERM_N_ARGS_MIN(arity) ((arity) < 0 ? -(arity) : (arity))
/* mk_term: max number of arguments */
#define MURXLA_MK_TERM_N_ARGS_MAX 11

#endif
