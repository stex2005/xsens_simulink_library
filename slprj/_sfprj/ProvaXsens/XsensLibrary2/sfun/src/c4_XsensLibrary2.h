#ifndef __c4_XsensLibrary2_h__
#define __c4_XsensLibrary2_h__

/* Type Definitions */
#ifndef typedef_SFc4_XsensLibrary2InstanceStruct
#define typedef_SFc4_XsensLibrary2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c4_dataWrittenToVector[2];
  uint8_T c4_doSetSimStateSideEffects;
  const mxArray *c4_setSimStateSideEffectsInfo;
  void *c4_fEmlrtCtx;
  int32_T *c4_sfEvent;
  uint8_T *c4_is_active_c4_XsensLibrary2;
  uint8_T *c4_is_c4_XsensLibrary2;
  real_T (*c4_Acceleration)[3];
  real_T *c4_FlagAvailable;
  real_T *c4_do_transition;
} SFc4_XsensLibrary2InstanceStruct;

#endif                                 /*typedef_SFc4_XsensLibrary2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_XsensLibrary2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_XsensLibrary2_get_check_sum(mxArray *plhs[]);
extern void c4_XsensLibrary2_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
