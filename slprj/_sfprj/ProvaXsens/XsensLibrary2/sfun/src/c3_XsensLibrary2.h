#ifndef __c3_XsensLibrary2_h__
#define __c3_XsensLibrary2_h__

/* Type Definitions */
#ifndef struct_tag_sL6LJlPlxhdTxZzXh5NTaQC
#define struct_tag_sL6LJlPlxhdTxZzXh5NTaQC

struct tag_sL6LJlPlxhdTxZzXh5NTaQC
{
  int32_T intNumBits;
};

#endif                                 /*struct_tag_sL6LJlPlxhdTxZzXh5NTaQC*/

#ifndef typedef_c3_sL6LJlPlxhdTxZzXh5NTaQC
#define typedef_c3_sL6LJlPlxhdTxZzXh5NTaQC

typedef struct tag_sL6LJlPlxhdTxZzXh5NTaQC c3_sL6LJlPlxhdTxZzXh5NTaQC;

#endif                                 /*typedef_c3_sL6LJlPlxhdTxZzXh5NTaQC*/

#ifndef typedef_SFc3_XsensLibrary2InstanceStruct
#define typedef_SFc3_XsensLibrary2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  real_T c3_XAxis;
  real_T c3_YAxis;
  real_T c3_ZAxis;
  real_T c3_RotationToInitial;
  boolean_T c3_dataWrittenToVector[13];
  uint8_T c3_doSetSimStateSideEffects;
  const mxArray *c3_setSimStateSideEffectsInfo;
  real_T (*c3_RotMatrix_init_address)[9];
  int32_T c3__indexrix_init;
  boolean_T c3_dsmdiag_RotMatrix_init;
  real_T (*c3__indexgRf_address)[9];
  int32_T c3__index;
  boolean_T c3_dsmdiag_gRf;
  real_T (*c3__indexsRb_address)[9];
  int32_T c3_b__index;
  boolean_T c3_dsmdiag_sRb;
  void *c3_fEmlrtCtx;
  int32_T *c3_sfEvent;
  uint8_T *c3_is_active_c3_XsensLibrary2;
  uint8_T *c3_is_c3_XsensLibrary2;
  real_T (*c3_Acceleration)[3];
  real_T (*c3_RotationMatrix)[9];
  real_T (*c3_RotMatrix_out)[9];
  real_T (*c3_Accelerationbuffer)[15];
  real_T (*c3_mean_accel_b)[3];
  real_T (*c3_mean_accel)[3];
  real_T (*c3_mean_rotmat)[9];
  real_T *c3_gamma;
  real_T *c3_beta;
  real_T (*c3_gRb)[9];
  real_T (*c3_RotMatbuffer)[45];
  real_T *c3_samples;
  real_T *c3_Calib_performed;
  real_T *c3_data_received;
  real32_T *c3_SensorID;
} SFc3_XsensLibrary2InstanceStruct;

#endif                                 /*typedef_SFc3_XsensLibrary2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c3_XsensLibrary2_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c3_XsensLibrary2_get_check_sum(mxArray *plhs[]);
extern void c3_XsensLibrary2_method_dispatcher(SimStruct *S, int_T method, void *
  data);

#endif
