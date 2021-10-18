/* Include files */

#include "XsensLibrary2_sfun.h"
#include "c3_XsensLibrary2.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "XsensLibrary2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c3_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c3_IN_CALIBRATION              ((uint8_T)1U)
#define c3_IN_INOUT                    ((uint8_T)2U)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_b_debug_family_names[4] = { "nargin", "nargout",
  "anatomical_axis", "vector" };

static const char * c3_c_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_d_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_e_debug_family_names[2] = { "nargin", "nargout" };

static const char * c3_f_debug_family_names[3] = { "nargin", "nargout",
  "sf_internal_predicateOutput" };

/* Function Declarations */
static void initialize_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void initialize_params_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct *
  chartInstance);
static void enable_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void disable_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void c3_update_debugger_state_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance);
static void ext_mode_exec_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance);
static void set_sim_state_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_st);
static void c3_set_sim_state_side_effects_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance);
static void finalize_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void sf_gateway_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void mdl_start_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void initSimStructsc3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void c3_CALIBRATION(SFc3_XsensLibrary2InstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static real_T c3_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_feval, const char_T *c3_identifier);
static real_T c3_b_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static boolean_T c3_d_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_DirectionToVector_sRb(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, real_T c3_anatomical_axis, real_T c3_vector[3]);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_e_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_f_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_gRf, const char_T *c3_identifier, real_T
  c3_y[9]);
static void c3_g_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9]);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_h_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_Accelerationbuffer, const char_T
  *c3_identifier, real_T c3_y[15]);
static void c3_i_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[15]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_j_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_mean_accel_b, const char_T *c3_identifier,
  real_T c3_y[3]);
static void c3_k_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3]);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_l_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_RotMatbuffer, const char_T *c3_identifier,
  real_T c3_y[45]);
static void c3_m_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[45]);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static uint8_T c3_n_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_XsensLibrary2, const char_T
  *c3_identifier);
static uint8_T c3_o_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_p_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_dataWrittenToVector, const char_T
  *c3_identifier, boolean_T c3_y[13]);
static void c3_q_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  boolean_T c3_y[13]);
static const mxArray *c3_r_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier);
static const mxArray *c3_s_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static const mxArray *sf_get_hover_data_for_msg(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, int32_T c3_ssid);
static void c3_init_sf_message_store_memory(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static real_T c3_get_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_elementIndex);
static void c3_set_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_elementIndex, real_T c3_elementValue);
static real_T *c3_access_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_rdOnly);
static real_T c3_get_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_elementIndex);
static void c3_set_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance, uint32_T
  c3_elementIndex, real_T c3_elementValue);
static real_T *c3_access_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_rdOnly);
static real_T c3_get_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_elementIndex);
static void c3_set_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance, uint32_T
  c3_elementIndex, real_T c3_elementValue);
static real_T *c3_access_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_rdOnly);
static void init_dsm_address_info(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);
static void init_simulink_io_address(SFc3_XsensLibrary2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc3_XsensLibrary2(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  *chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_doSetSimStateSideEffects = 0U;
  chartInstance->c3_setSimStateSideEffectsInfo = NULL;
  *chartInstance->c3_is_active_c3_XsensLibrary2 = 0U;
  *chartInstance->c3_is_c3_XsensLibrary2 = c3_IN_NO_ACTIVE_CHILD;
}

static void initialize_params_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct *
  chartInstance)
{
  real_T c3_d0;
  real_T c3_d1;
  real_T c3_d2;
  real_T c3_d3;
  sf_mex_import_named("XAxis", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      &c3_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_XAxis = c3_d0;
  sf_mex_import_named("YAxis", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      &c3_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_YAxis = c3_d1;
  sf_mex_import_named("ZAxis", sf_mex_get_sfun_param(chartInstance->S, 3, 0),
                      &c3_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_ZAxis = c3_d2;
  sf_mex_import_named("RotationToInitial", sf_mex_get_sfun_param
                      (chartInstance->S, 0, 0), &c3_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_RotationToInitial = c3_d3;
}

static void enable_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance)
{
  uint32_T c3_prevAniVal;
  c3_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (*chartInstance->c3_is_active_c3_XsensLibrary2 == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_c3_XsensLibrary2 == c3_IN_CALIBRATION) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
  }

  if (*chartInstance->c3_is_c3_XsensLibrary2 == c3_IN_INOUT) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
  }

  _SFD_SET_ANIMATION(c3_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static void ext_mode_exec_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  c3_update_debugger_state_c3_XsensLibrary2(chartInstance);
}

static const mxArray *get_sim_state_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  const mxArray *c3_b_y = NULL;
  const mxArray *c3_c_y = NULL;
  real_T c3_hoistedGlobal;
  const mxArray *c3_d_y = NULL;
  const mxArray *c3_e_y = NULL;
  real_T c3_b_hoistedGlobal;
  const mxArray *c3_f_y = NULL;
  real_T c3_c_hoistedGlobal;
  const mxArray *c3_g_y = NULL;
  const mxArray *c3_h_y = NULL;
  real_T c3_d_hoistedGlobal;
  const mxArray *c3_i_y = NULL;
  const mxArray *c3_j_y = NULL;
  const mxArray *c3_k_y = NULL;
  const mxArray *c3_l_y = NULL;
  real_T c3_e_hoistedGlobal;
  const mxArray *c3_m_y = NULL;
  uint8_T c3_f_hoistedGlobal;
  const mxArray *c3_n_y = NULL;
  uint8_T c3_g_hoistedGlobal;
  const mxArray *c3_o_y = NULL;
  const mxArray *c3_p_y = NULL;
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(15, 1), false);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", *chartInstance->c3_RotMatrix_out, 0,
    0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y",
    *chartInstance->c3_Accelerationbuffer, 0, 0U, 1U, 0U, 2, 3, 5), false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_hoistedGlobal = *chartInstance->c3_Calib_performed;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_hoistedGlobal, 0, 0U, 0U, 0U, 0),
                false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", *chartInstance->c3_RotMatbuffer, 0,
    0U, 1U, 0U, 3, 3, 3, 5), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_b_hoistedGlobal = *chartInstance->c3_beta;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_b_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 4, c3_f_y);
  c3_c_hoistedGlobal = *chartInstance->c3_data_received;
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_c_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 5, c3_g_y);
  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", *chartInstance->c3_gRb, 0, 0U, 1U,
    0U, 2, 3, 3), false);
  sf_mex_setcell(c3_y, 6, c3_h_y);
  c3_d_hoistedGlobal = *chartInstance->c3_gamma;
  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", &c3_d_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 7, c3_i_y);
  c3_j_y = NULL;
  sf_mex_assign(&c3_j_y, sf_mex_create("y", *chartInstance->c3_mean_accel, 0, 0U,
    1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 8, c3_j_y);
  c3_k_y = NULL;
  sf_mex_assign(&c3_k_y, sf_mex_create("y", *chartInstance->c3_mean_accel_b, 0,
    0U, 1U, 0U, 1, 3), false);
  sf_mex_setcell(c3_y, 9, c3_k_y);
  c3_l_y = NULL;
  sf_mex_assign(&c3_l_y, sf_mex_create("y", *chartInstance->c3_mean_rotmat, 0,
    0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_setcell(c3_y, 10, c3_l_y);
  c3_e_hoistedGlobal = *chartInstance->c3_samples;
  c3_m_y = NULL;
  sf_mex_assign(&c3_m_y, sf_mex_create("y", &c3_e_hoistedGlobal, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 11, c3_m_y);
  c3_f_hoistedGlobal = *chartInstance->c3_is_active_c3_XsensLibrary2;
  c3_n_y = NULL;
  sf_mex_assign(&c3_n_y, sf_mex_create("y", &c3_f_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 12, c3_n_y);
  c3_g_hoistedGlobal = *chartInstance->c3_is_c3_XsensLibrary2;
  c3_o_y = NULL;
  sf_mex_assign(&c3_o_y, sf_mex_create("y", &c3_g_hoistedGlobal, 3, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c3_y, 13, c3_o_y);
  c3_p_y = NULL;
  sf_mex_assign(&c3_p_y, sf_mex_create("y",
    chartInstance->c3_dataWrittenToVector, 11, 0U, 1U, 0U, 1, 13), false);
  sf_mex_setcell(c3_y, 14, c3_p_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T c3_dv0[9];
  int32_T c3_i0;
  real_T c3_dv1[15];
  int32_T c3_i1;
  real_T c3_dv2[45];
  int32_T c3_i2;
  real_T c3_dv3[9];
  int32_T c3_i3;
  real_T c3_dv4[3];
  int32_T c3_i4;
  real_T c3_dv5[3];
  int32_T c3_i5;
  real_T c3_dv6[9];
  int32_T c3_i6;
  boolean_T c3_bv0[13];
  int32_T c3_i7;
  c3_u = sf_mex_dup(c3_st);
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
                        "RotMatrix_out", c3_dv0);
  for (c3_i0 = 0; c3_i0 < 9; c3_i0++) {
    (*chartInstance->c3_RotMatrix_out)[c3_i0] = c3_dv0[c3_i0];
  }

  c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "Accelerationbuffer", c3_dv1);
  for (c3_i1 = 0; c3_i1 < 15; c3_i1++) {
    (*chartInstance->c3_Accelerationbuffer)[c3_i1] = c3_dv1[c3_i1];
  }

  *chartInstance->c3_Calib_performed = c3_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 2)), "Calib_performed");
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
                        "RotMatbuffer", c3_dv2);
  for (c3_i2 = 0; c3_i2 < 45; c3_i2++) {
    (*chartInstance->c3_RotMatbuffer)[c3_i2] = c3_dv2[c3_i2];
  }

  *chartInstance->c3_beta = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 4)), "beta");
  *chartInstance->c3_data_received = c3_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 5)), "data_received");
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 6)),
                        "gRb", c3_dv3);
  for (c3_i3 = 0; c3_i3 < 9; c3_i3++) {
    (*chartInstance->c3_gRb)[c3_i3] = c3_dv3[c3_i3];
  }

  *chartInstance->c3_gamma = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 7)), "gamma");
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 8)),
                        "mean_accel", c3_dv4);
  for (c3_i4 = 0; c3_i4 < 3; c3_i4++) {
    (*chartInstance->c3_mean_accel)[c3_i4] = c3_dv4[c3_i4];
  }

  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 9)),
                        "mean_accel_b", c3_dv5);
  for (c3_i5 = 0; c3_i5 < 3; c3_i5++) {
    (*chartInstance->c3_mean_accel_b)[c3_i5] = c3_dv5[c3_i5];
  }

  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 10)),
                        "mean_rotmat", c3_dv6);
  for (c3_i6 = 0; c3_i6 < 9; c3_i6++) {
    (*chartInstance->c3_mean_rotmat)[c3_i6] = c3_dv6[c3_i6];
  }

  *chartInstance->c3_samples = c3_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c3_u, 11)), "samples");
  *chartInstance->c3_is_active_c3_XsensLibrary2 = c3_n_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 12)),
     "is_active_c3_XsensLibrary2");
  *chartInstance->c3_is_c3_XsensLibrary2 = c3_n_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 13)), "is_c3_XsensLibrary2");
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 14)),
                        "dataWrittenToVector", c3_bv0);
  for (c3_i7 = 0; c3_i7 < 13; c3_i7++) {
    chartInstance->c3_dataWrittenToVector[c3_i7] = c3_bv0[c3_i7];
  }

  sf_mex_assign(&chartInstance->c3_setSimStateSideEffectsInfo,
                c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c3_u, 15)), "setSimStateSideEffectsInfo"), true);
  sf_mex_destroy(&c3_u);
  chartInstance->c3_doSetSimStateSideEffects = 1U;
  c3_update_debugger_state_c3_XsensLibrary2(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void c3_set_sim_state_side_effects_c3_XsensLibrary2
  (SFc3_XsensLibrary2InstanceStruct *chartInstance)
{
  if (chartInstance->c3_doSetSimStateSideEffects != 0) {
    chartInstance->c3_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c3_setSimStateSideEffectsInfo);
}

static void sf_gateway_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  int32_T c3_i8;
  int32_T c3_i9;
  uint32_T c3_debug_family_var_map[2];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 0.0;
  int32_T c3_i10;
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  int32_T c3_i11;
  int32_T c3_i12;
  int32_T c3_i13;
  int32_T c3_i14;
  int32_T c3_i15;
  int32_T c3_i16;
  int32_T c3_i17;
  int32_T c3_i18;
  int32_T c3_i19;
  int32_T c3_i20;
  real_T c3_dv7[9];
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  int32_T c3_i24;
  real_T c3_dv8[9];
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  real_T c3_dv9[3];
  real_T c3_dv10[3];
  real_T c3_dv11[3];
  int32_T c3_i31;
  int32_T c3_i32;
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  const mxArray *c3_y = NULL;
  c3_set_sim_state_side_effects_c3_XsensLibrary2(chartInstance);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
  _SFD_DATA_RANGE_CHECK((real_T)*chartInstance->c3_SensorID, 13U);
  for (c3_i8 = 0; c3_i8 < 9; c3_i8++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_RotationMatrix)[c3_i8], 12U);
  }

  for (c3_i9 = 0; c3_i9 < 3; c3_i9++) {
    _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Acceleration)[c3_i9], 11U);
  }

  *chartInstance->c3_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
  if (*chartInstance->c3_is_active_c3_XsensLibrary2 == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_active_c3_XsensLibrary2 = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_XsensLibrary2 = c3_IN_CALIBRATION;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_debug_family_names,
      c3_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    for (c3_i12 = 0; c3_i12 < 15; c3_i12++) {
      (*chartInstance->c3_Accelerationbuffer)[c3_i12] = rtNaN;
    }

    chartInstance->c3_dataWrittenToVector[1U] = true;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    for (c3_i17 = 0; c3_i17 < 15; c3_i17++) {
      _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Accelerationbuffer)[c3_i17], 0U);
    }

    for (c3_i21 = 0; c3_i21 < 45; c3_i21++) {
      (*chartInstance->c3_RotMatbuffer)[c3_i21] = rtNaN;
    }

    chartInstance->c3_dataWrittenToVector[8U] = true;
    chartInstance->c3_dataWrittenToVector[8U] = true;
    for (c3_i28 = 0; c3_i28 < 45; c3_i28++) {
      _SFD_DATA_RANGE_CHECK((*chartInstance->c3_RotMatbuffer)[c3_i28], 2U);
    }

    *chartInstance->c3_samples = 1.0;
    chartInstance->c3_dataWrittenToVector[9U] = true;
    chartInstance->c3_dataWrittenToVector[9U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_samples, 10U);
    *chartInstance->c3_Calib_performed = 0.0;
    chartInstance->c3_dataWrittenToVector[10U] = true;
    chartInstance->c3_dataWrittenToVector[10U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_Calib_performed, 1U);
    c3_DirectionToVector_sRb(chartInstance, chartInstance->c3_XAxis, c3_dv9);
    c3_DirectionToVector_sRb(chartInstance, chartInstance->c3_YAxis, c3_dv10);
    c3_DirectionToVector_sRb(chartInstance, chartInstance->c3_ZAxis, c3_dv11);
    c3_i31 = 0;
    for (c3_i32 = 0; c3_i32 < 3; c3_i32++) {
      c3_set_sRb(chartInstance, c3_i31, c3_dv9[c3_i32]);
      c3_i31 += 3;
    }

    c3_i33 = 0;
    for (c3_i34 = 0; c3_i34 < 3; c3_i34++) {
      c3_set_sRb(chartInstance, c3_i33 + 1, c3_dv10[c3_i34]);
      c3_i33 += 3;
    }

    c3_i35 = 0;
    for (c3_i36 = 0; c3_i36 < 3; c3_i36++) {
      c3_set_sRb(chartInstance, c3_i35 + 2, c3_dv11[c3_i36]);
      c3_i35 += 3;
    }

    ssUpdateDataStoreLog_wrapper(chartInstance->S, 2);
    sf_mex_printf("%s =\\n", "sRb");
    c3_y = NULL;
    sf_mex_assign(&c3_y, sf_mex_create("y", c3_access_sRb(chartInstance, true),
      0, 0U, 1U, 0U, 2, 3, 3), false);
    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "disp", 0U, 1U, 14, c3_y);
    _SFD_SYMBOL_SCOPE_POP();
  } else {
    switch (*chartInstance->c3_is_c3_XsensLibrary2) {
     case c3_IN_CALIBRATION:
      CV_CHART_EVAL(2, 0, c3_IN_CALIBRATION);
      c3_CALIBRATION(chartInstance);
      break;

     case c3_IN_INOUT:
      CV_CHART_EVAL(2, 0, c3_IN_INOUT);
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                   *chartInstance->c3_sfEvent);
      _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_e_debug_family_names,
        c3_debug_family_var_map);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
        c3_sf_marshallIn);
      for (c3_i10 = 0; c3_i10 < 9; c3_i10++) {
        (*chartInstance->c3_RotMatrix_out)[c3_i10] = 0.0;
      }

      c3_i11 = 0;
      for (c3_i13 = 0; c3_i13 < 3; c3_i13++) {
        c3_i15 = 0;
        for (c3_i16 = 0; c3_i16 < 3; c3_i16++) {
          c3_dv7[c3_i15 + c3_i13] = 0.0;
          for (c3_i22 = 0; c3_i22 < 3; c3_i22++) {
            c3_dv7[c3_i15 + c3_i13] += c3_get_RotMatrix_init(chartInstance,
              c3_i22 + c3_i11) * c3_get_gRf(chartInstance, c3_i22 + c3_i15);
          }

          c3_i15 += 3;
        }

        c3_i11 += 3;
      }

      for (c3_i14 = 0; c3_i14 < 3; c3_i14++) {
        c3_i19 = 0;
        for (c3_i20 = 0; c3_i20 < 3; c3_i20++) {
          c3_dv8[c3_i19 + c3_i14] = 0.0;
          c3_i26 = 0;
          for (c3_i27 = 0; c3_i27 < 3; c3_i27++) {
            c3_dv8[c3_i19 + c3_i14] += c3_dv7[c3_i26 + c3_i14] *
              (*chartInstance->c3_RotationMatrix)[c3_i26 + c3_i20];
            c3_i26 += 3;
          }

          c3_i19 += 3;
        }
      }

      for (c3_i18 = 0; c3_i18 < 3; c3_i18++) {
        c3_i23 = 0;
        for (c3_i24 = 0; c3_i24 < 3; c3_i24++) {
          (*chartInstance->c3_RotMatrix_out)[c3_i23 + c3_i18] = 0.0;
          c3_i29 = 0;
          for (c3_i30 = 0; c3_i30 < 3; c3_i30++) {
            (*chartInstance->c3_RotMatrix_out)[c3_i23 + c3_i18] += c3_dv8[c3_i29
              + c3_i18] * c3_get_sRb(chartInstance, c3_i30 + c3_i23);
            c3_i29 += 3;
          }

          c3_i23 += 3;
        }
      }

      chartInstance->c3_dataWrittenToVector[0U] = true;
      chartInstance->c3_dataWrittenToVector[0U] = true;
      for (c3_i25 = 0; c3_i25 < 9; c3_i25++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_RotMatrix_out)[c3_i25], 14U);
      }

      _SFD_SYMBOL_SCOPE_POP();
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
      break;

     default:
      CV_CHART_EVAL(2, 0, 0);

      /* Unreachable state, for coverage only */
      *chartInstance->c3_is_c3_XsensLibrary2 = c3_IN_NO_ACTIVE_CHILD;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
      break;
    }
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_XsensLibrary2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void mdl_start_c3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  c3_init_sf_message_store_memory(chartInstance);
  sim_mode_is_external(chartInstance->S);
}

static void initSimStructsc3_XsensLibrary2(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c3_CALIBRATION(SFc3_XsensLibrary2InstanceStruct *chartInstance)
{
  uint32_T c3_debug_family_var_map[3];
  real_T c3_nargin = 0.0;
  real_T c3_nargout = 1.0;
  boolean_T c3_out;
  uint32_T c3_b_debug_family_var_map[2];
  real_T c3_b_nargin = 0.0;
  real_T c3_b_nargout = 0.0;
  real_T c3_c_nargin = 0.0;
  real_T c3_c_nargout = 0.0;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  int32_T c3_i40;
  static real_T c3_dv12[9] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };

  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  int32_T c3_i44;
  int32_T c3_i45;
  int32_T c3_i46;
  int32_T c3_i47;
  real_T c3_dv13[9];
  int32_T c3_i48;
  int32_T c3_i49;
  int32_T c3_i50;
  int32_T c3_i51;
  int32_T c3_i52;
  int32_T c3_i53;
  int32_T c3_i54;
  int32_T c3_i55;
  int32_T c3_j;
  int32_T c3_k;
  int32_T c3_i56;
  int32_T c3_xoffset;
  int32_T c3_b_j;
  int32_T c3_i57;
  int32_T c3_c_j;
  int32_T c3_b_k;
  int32_T c3_i58;
  int32_T c3_b_xoffset;
  int32_T c3_d_j;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  int32_T c3_i62;
  int32_T c3_i63;
  int32_T c3_i64;
  real32_T c3_varargin_1;
  real_T c3_varargin_2;
  real_T c3_varargin_3;
  real_T c3_varargin_4;
  real_T c3_fileID;
  const mxArray *c3_y = NULL;
  static char_T c3_cv0[7] = { 'f', 'p', 'r', 'i', 'n', 't', 'f' };

  const mxArray *c3_b_y = NULL;
  const mxArray *c3_c_y = NULL;
  static char_T c3_formatSpec[38] = { 'S', 'e', 'n', 's', 'o', 'r', ' ', '%',
    '1', '.', '0', 'f', ' ', 'a', 'c', 'c', 'e', 'l', 'e', 'r', 'a', 't', 'i',
    'o', 'n', ':', ' ', '%', 'f', ' ', '%', 'f', ' ', '%', 'f', ' ', '\\', 'n' };

  const mxArray *c3_d_y = NULL;
  const mxArray *c3_e_y = NULL;
  const mxArray *c3_f_y = NULL;
  const mxArray *c3_g_y = NULL;
  real_T c3_h_y;
  real_T c3_scale;
  int32_T c3_c_k;
  real_T c3_absxk;
  int32_T c3_i65;
  real_T c3_t;
  int32_T c3_i66;
  int32_T c3_i67;
  int32_T c3_i68;
  int32_T c3_i69;
  int32_T c3_i70;
  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  int32_T c3_i74;
  real_T c3_dv14[9];
  int32_T c3_i75;
  int32_T c3_i76;
  int32_T c3_i77;
  int32_T c3_i78;
  _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, *chartInstance->c3_sfEvent);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 3U, 3U, c3_f_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_out, 2U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  if (!chartInstance->c3_dataWrittenToVector[10U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(1U);
  }

  if (!chartInstance->c3_dataWrittenToVector[10U]) {
    _SFD_DATA_READ_BEFORE_WRITE_ERROR(1U);
  }

  c3_out = CV_EML_IF(0, 0, 0, CV_RELATIONAL_EVAL(5U, 0U, 0,
    *chartInstance->c3_Calib_performed, 0.0, -1, 4U,
    *chartInstance->c3_Calib_performed > 0.0));
  _SFD_SYMBOL_SCOPE_POP();
  if (c3_out) {
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, *chartInstance->c3_sfEvent);
    *chartInstance->c3_is_c3_XsensLibrary2 = c3_IN_INOUT;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_d_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_c_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    if (CV_EML_IF(2, 1, 0, CV_RELATIONAL_EVAL(4U, 2U, 0,
          chartInstance->c3_RotationToInitial, 1.0, -1, 0U,
          chartInstance->c3_RotationToInitial == 1.0))) {
      for (c3_i39 = 0; c3_i39 < 9; c3_i39++) {
        c3_set_RotMatrix_init(chartInstance, c3_i39, 0.0);
      }

      for (c3_i41 = 0; c3_i41 < 3; c3_i41++) {
        c3_i44 = 0;
        for (c3_i45 = 0; c3_i45 < 3; c3_i45++) {
          c3_dv13[c3_i44 + c3_i41] = 0.0;
          c3_i48 = 0;
          for (c3_i49 = 0; c3_i49 < 3; c3_i49++) {
            c3_dv13[c3_i44 + c3_i41] += c3_get_gRf(chartInstance, c3_i48 +
              c3_i41) * (*chartInstance->c3_RotationMatrix)[c3_i48 + c3_i45];
            c3_i48 += 3;
          }

          c3_i44 += 3;
        }
      }

      for (c3_i43 = 0; c3_i43 < 3; c3_i43++) {
        c3_i46 = 0;
        for (c3_i47 = 0; c3_i47 < 3; c3_i47++) {
          c3_set_RotMatrix_init(chartInstance, c3_i46 + c3_i43, 0.0);
          c3_i52 = 0;
          for (c3_i53 = 0; c3_i53 < 3; c3_i53++) {
            c3_set_RotMatrix_init(chartInstance, c3_i46 + c3_i43,
                                  c3_get_RotMatrix_init(chartInstance, c3_i46 +
              c3_i43) + c3_dv13[c3_i52 + c3_i43] * c3_get_sRb(chartInstance,
              c3_i53 + c3_i46));
            c3_i52 += 3;
          }

          c3_i46 += 3;
        }
      }

      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    } else {
      for (c3_i38 = 0; c3_i38 < 9; c3_i38++) {
        c3_set_RotMatrix_init(chartInstance, c3_i38, c3_dv12[c3_i38]);
      }

      ssUpdateDataStoreLog_wrapper(chartInstance->S, 0);
    }

    _SFD_SYMBOL_SCOPE_POP();
  } else {
    _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
    _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 2U, 2U, c3_c_debug_family_names,
      c3_b_debug_family_var_map);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargin, 0U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_b_nargout, 1U, c3_sf_marshallOut,
      c3_sf_marshallIn);
    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    c3_i37 = sf_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S,
      1U, 219, 29, 0U, sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 240, 7, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 240U, 7U, *chartInstance->c3_samples), 1, 5) - 1, 0,
      4);
    for (c3_i40 = 0; c3_i40 < 3; c3_i40++) {
      (*chartInstance->c3_Accelerationbuffer)[c3_i40 + 3 * c3_i37] =
        (*chartInstance->c3_Acceleration)[c3_i40];
    }

    chartInstance->c3_dataWrittenToVector[1U] = true;
    chartInstance->c3_dataWrittenToVector[1U] = true;
    for (c3_i42 = 0; c3_i42 < 15; c3_i42++) {
      _SFD_DATA_RANGE_CHECK((*chartInstance->c3_Accelerationbuffer)[c3_i42], 0U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    c3_i50 = sf_array_bounds_check(sfGlobalDebugInstanceStruct, chartInstance->S,
      1U, 263, 25, 2U, sf_eml_array_bounds_check(sfGlobalDebugInstanceStruct,
      chartInstance->S, 1U, 280, 7, MAX_uint32_T, (int32_T)sf_integer_check
      (chartInstance->S, 1U, 280U, 7U, *chartInstance->c3_samples), 1, 5) - 1, 0,
      4);
    for (c3_i51 = 0; c3_i51 < 3; c3_i51++) {
      for (c3_i54 = 0; c3_i54 < 3; c3_i54++) {
        (*chartInstance->c3_RotMatbuffer)[(c3_i54 + 3 * c3_i51) + 9 * c3_i50] =
          (*chartInstance->c3_RotationMatrix)[c3_i51 + 3 * c3_i54];
      }
    }

    chartInstance->c3_dataWrittenToVector[8U] = true;
    chartInstance->c3_dataWrittenToVector[8U] = true;
    for (c3_i55 = 0; c3_i55 < 45; c3_i55++) {
      _SFD_DATA_RANGE_CHECK((*chartInstance->c3_RotMatbuffer)[c3_i55], 2U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    (*chartInstance->c3_samples)++;
    chartInstance->c3_dataWrittenToVector[9U] = true;
    chartInstance->c3_dataWrittenToVector[9U] = true;
    _SFD_DATA_RANGE_CHECK(*chartInstance->c3_samples, 10U);
    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    if (!chartInstance->c3_dataWrittenToVector[9U]) {
      _SFD_DATA_READ_BEFORE_WRITE_ERROR(10U);
    }

    if (CV_EML_IF(0, 1, 0, CV_RELATIONAL_EVAL(4U, 0U, 0,
          *chartInstance->c3_samples, 5.0, -1, 4U, *chartInstance->c3_samples >
          5.0))) {
      for (c3_j = 0; c3_j < 3; c3_j++) {
        (*chartInstance->c3_mean_accel)[c3_j] =
          (*chartInstance->c3_Accelerationbuffer)[c3_j];
      }

      for (c3_k = 0; c3_k < 4; c3_k++) {
        c3_xoffset = (c3_k + 1) * 3;
        for (c3_b_j = 0; c3_b_j < 3; c3_b_j++) {
          (*chartInstance->c3_mean_accel)[c3_b_j] +=
            (*chartInstance->c3_Accelerationbuffer)[c3_xoffset + c3_b_j];
        }
      }

      for (c3_i56 = 0; c3_i56 < 3; c3_i56++) {
        (*chartInstance->c3_mean_accel)[c3_i56] /= 5.0;
      }

      chartInstance->c3_dataWrittenToVector[3U] = true;
      chartInstance->c3_dataWrittenToVector[3U] = true;
      for (c3_i57 = 0; c3_i57 < 3; c3_i57++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_mean_accel)[c3_i57], 7U);
      }

      if (!chartInstance->c3_dataWrittenToVector[8U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(2U);
      }

      if (!chartInstance->c3_dataWrittenToVector[8U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(2U);
      }

      for (c3_c_j = 0; c3_c_j < 9; c3_c_j++) {
        (*chartInstance->c3_mean_rotmat)[c3_c_j] =
          (*chartInstance->c3_RotMatbuffer)[c3_c_j];
      }

      for (c3_b_k = 0; c3_b_k < 4; c3_b_k++) {
        c3_b_xoffset = (c3_b_k + 1) * 9;
        for (c3_d_j = 0; c3_d_j < 9; c3_d_j++) {
          (*chartInstance->c3_mean_rotmat)[c3_d_j] +=
            (*chartInstance->c3_RotMatbuffer)[c3_b_xoffset + c3_d_j];
        }
      }

      for (c3_i58 = 0; c3_i58 < 9; c3_i58++) {
        (*chartInstance->c3_mean_rotmat)[c3_i58] /= 5.0;
      }

      chartInstance->c3_dataWrittenToVector[4U] = true;
      chartInstance->c3_dataWrittenToVector[4U] = true;
      for (c3_i59 = 0; c3_i59 < 9; c3_i59++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_mean_rotmat)[c3_i59], 9U);
      }

      if (!chartInstance->c3_dataWrittenToVector[3U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(7U);
      }

      if (!chartInstance->c3_dataWrittenToVector[3U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(7U);
      }

      for (c3_i60 = 0; c3_i60 < 3; c3_i60++) {
        (*chartInstance->c3_mean_accel_b)[c3_i60] = 0.0;
      }

      c3_i61 = 0;
      for (c3_i62 = 0; c3_i62 < 3; c3_i62++) {
        (*chartInstance->c3_mean_accel_b)[c3_i62] = 0.0;
        for (c3_i63 = 0; c3_i63 < 3; c3_i63++) {
          (*chartInstance->c3_mean_accel_b)[c3_i62] += c3_get_sRb(chartInstance,
            c3_i63 + c3_i61) * (*chartInstance->c3_mean_accel)[c3_i63];
        }

        c3_i61 += 3;
      }

      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      for (c3_i64 = 0; c3_i64 < 3; c3_i64++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_mean_accel_b)[c3_i64], 8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      c3_varargin_1 = *chartInstance->c3_SensorID;
      c3_varargin_2 = (*chartInstance->c3_mean_accel_b)[0];
      c3_varargin_3 = (*chartInstance->c3_mean_accel_b)[1];
      c3_varargin_4 = (*chartInstance->c3_mean_accel_b)[2];
      c3_fileID = 2.0;
      c3_y = NULL;
      sf_mex_assign(&c3_y, sf_mex_create("y", c3_cv0, 10, 0U, 1U, 0U, 2, 1, 7),
                    false);
      c3_b_y = NULL;
      sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_fileID, 0, 0U, 0U, 0U, 0),
                    false);
      c3_c_y = NULL;
      sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_formatSpec, 10, 0U, 1U, 0U, 2,
        1, 38), false);
      c3_d_y = NULL;
      sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_varargin_1, 1, 0U, 0U, 0U, 0),
                    false);
      c3_e_y = NULL;
      sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_varargin_2, 0, 0U, 0U, 0U, 0),
                    false);
      c3_f_y = NULL;
      sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_varargin_3, 0, 0U, 0U, 0U, 0),
                    false);
      c3_g_y = NULL;
      sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_varargin_4, 0, 0U, 0U, 0U, 0),
                    false);
      c3_emlrt_marshallIn(chartInstance, sf_mex_call_debug
                          (sfGlobalDebugInstanceStruct, "feval", 1U, 7U, 14,
                           c3_y, 14, c3_b_y, 14, c3_c_y, 14, c3_d_y, 14, c3_e_y,
                           14, c3_f_y, 14, c3_g_y), "feval");
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      c3_h_y = 0.0;
      c3_scale = 3.3121686421112381E-170;
      for (c3_c_k = 0; c3_c_k < 3; c3_c_k++) {
        c3_absxk = muDoubleScalarAbs((*chartInstance->c3_mean_accel_b)[c3_c_k]);
        if (c3_absxk > c3_scale) {
          c3_t = c3_scale / c3_absxk;
          c3_h_y = 1.0 + c3_h_y * c3_t * c3_t;
          c3_scale = c3_absxk;
        } else {
          c3_t = c3_absxk / c3_scale;
          c3_h_y += c3_t * c3_t;
        }
      }

      c3_h_y = c3_scale * muDoubleScalarSqrt(c3_h_y);
      for (c3_i65 = 0; c3_i65 < 3; c3_i65++) {
        (*chartInstance->c3_mean_accel_b)[c3_i65] /= c3_h_y;
      }

      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      for (c3_i66 = 0; c3_i66 < 3; c3_i66++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_mean_accel_b)[c3_i66], 8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      *chartInstance->c3_gamma = muDoubleScalarAtan2
        ((*chartInstance->c3_mean_accel_b)[1], (*chartInstance->c3_mean_accel_b)
         [2]);
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c3_gamma, 6U);
      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[5U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U);
      }

      if (!chartInstance->c3_dataWrittenToVector[2U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(8U);
      }

      if (!chartInstance->c3_dataWrittenToVector[5U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U);
      }

      *chartInstance->c3_beta = muDoubleScalarAtan2
        (-(*chartInstance->c3_mean_accel_b)[1], (*chartInstance->c3_mean_accel_b)
         [2] / muDoubleScalarSin(*chartInstance->c3_gamma));
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[2U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c3_beta, 3U);
      if (!chartInstance->c3_dataWrittenToVector[6U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(3U);
      }

      if (!chartInstance->c3_dataWrittenToVector[5U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U);
      }

      if (!chartInstance->c3_dataWrittenToVector[6U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(3U);
      }

      if (!chartInstance->c3_dataWrittenToVector[5U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(6U);
      }

      (*chartInstance->c3_gRb)[0] = muDoubleScalarCos(*chartInstance->c3_beta);
      (*chartInstance->c3_gRb)[3] = muDoubleScalarSin(*chartInstance->c3_beta) *
        muDoubleScalarSin(*chartInstance->c3_gamma);
      (*chartInstance->c3_gRb)[6] = muDoubleScalarSin(*chartInstance->c3_beta) *
        muDoubleScalarCos(*chartInstance->c3_gamma);
      (*chartInstance->c3_gRb)[1] = 0.0;
      (*chartInstance->c3_gRb)[4] = muDoubleScalarCos(*chartInstance->c3_gamma);
      (*chartInstance->c3_gRb)[7] = -muDoubleScalarSin(*chartInstance->c3_gamma);
      (*chartInstance->c3_gRb)[2] = -muDoubleScalarSin(*chartInstance->c3_beta);
      (*chartInstance->c3_gRb)[5] = muDoubleScalarCos(*chartInstance->c3_beta) *
        muDoubleScalarSin(*chartInstance->c3_gamma);
      (*chartInstance->c3_gRb)[8] = muDoubleScalarCos(*chartInstance->c3_beta) *
        muDoubleScalarCos(*chartInstance->c3_gamma);
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[7U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[5U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[6U] = true;
      chartInstance->c3_dataWrittenToVector[7U] = true;
      for (c3_i67 = 0; c3_i67 < 9; c3_i67++) {
        _SFD_DATA_RANGE_CHECK((*chartInstance->c3_gRb)[c3_i67], 5U);
      }

      if (!chartInstance->c3_dataWrittenToVector[7U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(5U);
      }

      if (!chartInstance->c3_dataWrittenToVector[4U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(9U);
      }

      if (!chartInstance->c3_dataWrittenToVector[7U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(5U);
      }

      if (!chartInstance->c3_dataWrittenToVector[4U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(9U);
      }

      for (c3_i68 = 0; c3_i68 < 9; c3_i68++) {
        c3_set_gRf(chartInstance, c3_i68, 0.0);
      }

      for (c3_i69 = 0; c3_i69 < 3; c3_i69++) {
        c3_i71 = 0;
        for (c3_i72 = 0; c3_i72 < 3; c3_i72++) {
          c3_dv14[c3_i71 + c3_i69] = 0.0;
          c3_i75 = 0;
          for (c3_i76 = 0; c3_i76 < 3; c3_i76++) {
            c3_dv14[c3_i71 + c3_i69] += (*chartInstance->c3_gRb)[c3_i75 + c3_i69]
              * c3_get_sRb(chartInstance, c3_i75 + c3_i72);
            c3_i75 += 3;
          }

          c3_i71 += 3;
        }
      }

      for (c3_i70 = 0; c3_i70 < 3; c3_i70++) {
        c3_i73 = 0;
        for (c3_i74 = 0; c3_i74 < 3; c3_i74++) {
          c3_set_gRf(chartInstance, c3_i73 + c3_i70, 0.0);
          c3_i77 = 0;
          for (c3_i78 = 0; c3_i78 < 3; c3_i78++) {
            c3_set_gRf(chartInstance, c3_i73 + c3_i70, c3_get_gRf(chartInstance,
                        c3_i73 + c3_i70) + c3_dv14[c3_i77 + c3_i70] *
                       (*chartInstance->c3_mean_rotmat)[c3_i77 + c3_i74]);
            c3_i77 += 3;
          }

          c3_i73 += 3;
        }
      }

      ssUpdateDataStoreLog_wrapper(chartInstance->S, 1);
      *chartInstance->c3_Calib_performed = 1.0;
      chartInstance->c3_dataWrittenToVector[10U] = true;
      chartInstance->c3_dataWrittenToVector[10U] = true;
      _SFD_DATA_RANGE_CHECK(*chartInstance->c3_Calib_performed, 1U);
    } else {
      if (!chartInstance->c3_dataWrittenToVector[1U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U);
      }

      if (!chartInstance->c3_dataWrittenToVector[1U]) {
        _SFD_DATA_READ_BEFORE_WRITE_ERROR(0U);
      }
    }

    _SFD_SYMBOL_SCOPE_POP();
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, *chartInstance->c3_sfEvent);
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)(c3_machineNumber);
  (void)(c3_chartNumber);
  (void)(c3_instanceNumber);
}

static real_T c3_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_feval, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_feval), &c3_thisId);
  sf_mex_destroy(&c3_feval);
  return c3_y;
}

static real_T c3_b_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d4;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d4, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d4;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_feval;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_feval = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_feval), &c3_thisId);
  sf_mex_destroy(&c3_feval);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i79;
  const mxArray *c3_y = NULL;
  real_T c3_u[3];
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  for (c3_i79 = 0; c3_i79 < 3; c3_i79++) {
    c3_u[c3_i79] = (*(real_T (*)[3])c3_inData)[c3_i79];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_c_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv15[3];
  int32_T c3_i80;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv15, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c3_i80 = 0; c3_i80 < 3; c3_i80++) {
    c3_y[c3_i80] = c3_dv15[c3_i80];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_vector;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i81;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_vector = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_vector), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_vector);
  for (c3_i81 = 0; c3_i81 < 3; c3_i81++) {
    (*(real_T (*)[3])c3_outData)[c3_i81] = c3_y[c3_i81];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static boolean_T c3_d_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_sf_internal_predicateOutput;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_sf_internal_predicateOutput = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_sf_internal_predicateOutput), &c3_thisId);
  sf_mex_destroy(&c3_sf_internal_predicateOutput);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

const mxArray *sf_c3_XsensLibrary2_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static void c3_DirectionToVector_sRb(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, real_T c3_anatomical_axis, real_T c3_vector[3])
{
  uint32_T c3_debug_family_var_map[4];
  real_T c3_nargin = 1.0;
  real_T c3_nargout = 1.0;
  int32_T c3_i82;
  int32_T c3_i83;
  int32_T c3_i84;
  static real_T c3_dv16[3] = { 1.0, 0.0, 0.0 };

  int32_T c3_i85;
  static real_T c3_dv17[3] = { -1.0, 0.0, 0.0 };

  int32_T c3_i86;
  static real_T c3_dv18[3] = { 0.0, 0.0, 1.0 };

  int32_T c3_i87;
  static real_T c3_dv19[3] = { 0.0, 0.0, -1.0 };

  int32_T c3_i88;
  static real_T c3_dv20[3] = { 0.0, 1.0, 0.0 };

  static real_T c3_dv21[3] = { 0.0, -1.0, 0.0 };

  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c3_b_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 0U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 1U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_anatomical_axis, 2U,
    c3_sf_marshallOut, c3_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_vector, 3U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  CV_EML_FCN(1, 0);
  _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 2);
  for (c3_i82 = 0; c3_i82 < 3; c3_i82++) {
    c3_vector[c3_i82] = 0.0;
  }

  _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 3);
  if (CV_EML_IF(1, 1, 0, CV_RELATIONAL_EVAL(4U, 1U, 0, c3_anatomical_axis, 1.0,
        -1, 0U, c3_anatomical_axis == 1.0))) {
    _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 4);
    for (c3_i83 = 0; c3_i83 < 3; c3_i83++) {
      c3_vector[c3_i83] = c3_dv16[c3_i83];
    }
  } else {
    _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 5);
    if (CV_EML_IF(1, 1, 1, CV_RELATIONAL_EVAL(4U, 1U, 1, c3_anatomical_axis, 2.0,
          -1, 0U, c3_anatomical_axis == 2.0))) {
      _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 6);
      for (c3_i84 = 0; c3_i84 < 3; c3_i84++) {
        c3_vector[c3_i84] = c3_dv17[c3_i84];
      }
    } else {
      _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 7);
      if (CV_EML_IF(1, 1, 2, CV_RELATIONAL_EVAL(4U, 1U, 2, c3_anatomical_axis,
            3.0, -1, 0U, c3_anatomical_axis == 3.0))) {
        _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 8);
        for (c3_i85 = 0; c3_i85 < 3; c3_i85++) {
          c3_vector[c3_i85] = c3_dv18[c3_i85];
        }
      } else {
        _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 9);
        if (CV_EML_IF(1, 1, 3, CV_RELATIONAL_EVAL(4U, 1U, 3, c3_anatomical_axis,
              4.0, -1, 0U, c3_anatomical_axis == 4.0))) {
          _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 10);
          for (c3_i86 = 0; c3_i86 < 3; c3_i86++) {
            c3_vector[c3_i86] = c3_dv19[c3_i86];
          }
        } else {
          _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 11);
          if (CV_EML_IF(1, 1, 4, CV_RELATIONAL_EVAL(4U, 1U, 4,
                c3_anatomical_axis, 5.0, -1, 0U, c3_anatomical_axis == 5.0))) {
            _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 12);
            for (c3_i87 = 0; c3_i87 < 3; c3_i87++) {
              c3_vector[c3_i87] = c3_dv20[c3_i87];
            }
          } else {
            _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 13);
            if (CV_EML_IF(1, 1, 5, CV_RELATIONAL_EVAL(4U, 1U, 5,
                  c3_anatomical_axis, 6.0, -1, 0U, c3_anatomical_axis == 6.0)))
            {
              _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, 14);
              for (c3_i88 = 0; c3_i88 < 3; c3_i88++) {
                c3_vector[c3_i88] = c3_dv21[c3_i88];
              }
            }
          }
        }
      }
    }
  }

  _SFD_EML_CALL(1U, *chartInstance->c3_sfEvent, -14);
  _SFD_SYMBOL_SCOPE_POP();
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_e_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i89;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i89, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i89;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i90;
  const mxArray *c3_y = NULL;
  real_T c3_u[9];
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  for (c3_i90 = 0; c3_i90 < 9; c3_i90++) {
    c3_u[c3_i90] = (*(real_T (*)[9])c3_inData)[c3_i90];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 9), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i91;
  int32_T c3_i92;
  const mxArray *c3_y = NULL;
  int32_T c3_i93;
  real_T c3_u[9];
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_i91 = 0;
  for (c3_i92 = 0; c3_i92 < 3; c3_i92++) {
    for (c3_i93 = 0; c3_i93 < 3; c3_i93++) {
      c3_u[c3_i93 + c3_i91] = (*(real_T (*)[9])c3_inData)[c3_i93 + c3_i91];
    }

    c3_i91 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_f_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_gRf, const char_T *c3_identifier, real_T
  c3_y[9])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_gRf), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_gRf);
}

static void c3_g_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[9])
{
  real_T c3_dv22[9];
  int32_T c3_i94;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv22, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c3_i94 = 0; c3_i94 < 9; c3_i94++) {
    c3_y[c3_i94] = c3_dv22[c3_i94];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_gRf;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[9];
  int32_T c3_i95;
  int32_T c3_i96;
  int32_T c3_i97;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_gRf = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_gRf), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_gRf);
  c3_i95 = 0;
  for (c3_i96 = 0; c3_i96 < 3; c3_i96++) {
    for (c3_i97 = 0; c3_i97 < 3; c3_i97++) {
      (*(real_T (*)[9])c3_outData)[c3_i97 + c3_i95] = c3_y[c3_i97 + c3_i95];
    }

    c3_i95 += 3;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i98;
  int32_T c3_i99;
  const mxArray *c3_y = NULL;
  int32_T c3_i100;
  real_T c3_u[15];
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_i98 = 0;
  for (c3_i99 = 0; c3_i99 < 5; c3_i99++) {
    for (c3_i100 = 0; c3_i100 < 3; c3_i100++) {
      c3_u[c3_i100 + c3_i98] = (*(real_T (*)[15])c3_inData)[c3_i100 + c3_i98];
    }

    c3_i98 += 3;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 3, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_h_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_Accelerationbuffer, const char_T
  *c3_identifier, real_T c3_y[15])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Accelerationbuffer),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_Accelerationbuffer);
}

static void c3_i_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[15])
{
  real_T c3_dv23[15];
  int32_T c3_i101;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv23, 1, 0, 0U, 1, 0U, 2, 3, 5);
  for (c3_i101 = 0; c3_i101 < 15; c3_i101++) {
    c3_y[c3_i101] = c3_dv23[c3_i101];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_Accelerationbuffer;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[15];
  int32_T c3_i102;
  int32_T c3_i103;
  int32_T c3_i104;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_b_Accelerationbuffer = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_Accelerationbuffer),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_Accelerationbuffer);
  c3_i102 = 0;
  for (c3_i103 = 0; c3_i103 < 5; c3_i103++) {
    for (c3_i104 = 0; c3_i104 < 3; c3_i104++) {
      (*(real_T (*)[15])c3_outData)[c3_i104 + c3_i102] = c3_y[c3_i104 + c3_i102];
    }

    c3_i102 += 3;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i105;
  const mxArray *c3_y = NULL;
  real_T c3_u[3];
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  for (c3_i105 = 0; c3_i105 < 3; c3_i105++) {
    c3_u[c3_i105] = (*(real_T (*)[3])c3_inData)[c3_i105];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_j_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_mean_accel_b, const char_T *c3_identifier,
  real_T c3_y[3])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_mean_accel_b), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_mean_accel_b);
}

static void c3_k_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[3])
{
  real_T c3_dv24[3];
  int32_T c3_i106;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv24, 1, 0, 0U, 1, 0U, 1, 3);
  for (c3_i106 = 0; c3_i106 < 3; c3_i106++) {
    c3_y[c3_i106] = c3_dv24[c3_i106];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_mean_accel_b;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i107;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_b_mean_accel_b = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_mean_accel_b), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_mean_accel_b);
  for (c3_i107 = 0; c3_i107 < 3; c3_i107++) {
    (*(real_T (*)[3])c3_outData)[c3_i107] = c3_y[c3_i107];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  int32_T c3_i108;
  int32_T c3_i109;
  const mxArray *c3_y = NULL;
  int32_T c3_i110;
  real_T c3_u[45];
  int32_T c3_i111;
  int32_T c3_i112;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_i108 = 0;
  for (c3_i109 = 0; c3_i109 < 5; c3_i109++) {
    c3_i110 = 0;
    for (c3_i111 = 0; c3_i111 < 3; c3_i111++) {
      for (c3_i112 = 0; c3_i112 < 3; c3_i112++) {
        c3_u[(c3_i112 + c3_i110) + c3_i108] = (*(real_T (*)[45])c3_inData)
          [(c3_i112 + c3_i110) + c3_i108];
      }

      c3_i110 += 3;
    }

    c3_i108 += 9;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 3, 3, 3, 5),
                false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_l_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_RotMatbuffer, const char_T *c3_identifier,
  real_T c3_y[45])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_RotMatbuffer), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_RotMatbuffer);
}

static void c3_m_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  real_T c3_y[45])
{
  real_T c3_dv25[45];
  int32_T c3_i113;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv25, 1, 0, 0U, 1, 0U, 3, 3, 3,
                5);
  for (c3_i113 = 0; c3_i113 < 45; c3_i113++) {
    c3_y[c3_i113] = c3_dv25[c3_i113];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_RotMatbuffer;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[45];
  int32_T c3_i114;
  int32_T c3_i115;
  int32_T c3_i116;
  int32_T c3_i117;
  int32_T c3_i118;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_b_RotMatbuffer = sf_mex_dup(c3_mxArrayInData);
  c3_thisId.fIdentifier = (const char *)c3_varName;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_RotMatbuffer), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_b_RotMatbuffer);
  c3_i114 = 0;
  for (c3_i115 = 0; c3_i115 < 5; c3_i115++) {
    c3_i116 = 0;
    for (c3_i117 = 0; c3_i117 < 3; c3_i117++) {
      for (c3_i118 = 0; c3_i118 < 3; c3_i118++) {
        (*(real_T (*)[45])c3_outData)[(c3_i118 + c3_i116) + c3_i114] = c3_y
          [(c3_i118 + c3_i116) + c3_i114];
      }

      c3_i116 += 3;
    }

    c3_i114 += 9;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData;
  real32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_mxArrayOutData = NULL;
  c3_u = *(real32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 1, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static uint8_T c3_n_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_is_active_c3_XsensLibrary2, const char_T
  *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_y = c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_XsensLibrary2), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_XsensLibrary2);
  return c3_y;
}

static uint8_T c3_o_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_p_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_dataWrittenToVector, const char_T
  *c3_identifier, boolean_T c3_y[13])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_dataWrittenToVector),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_b_dataWrittenToVector);
}

static void c3_q_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId,
  boolean_T c3_y[13])
{
  boolean_T c3_bv1[13];
  int32_T c3_i119;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_bv1, 1, 11, 0U, 1, 0U, 1, 13);
  for (c3_i119 = 0; c3_i119 < 13; c3_i119++) {
    c3_y[c3_i119] = c3_bv1[c3_i119];
  }

  sf_mex_destroy(&c3_u);
}

static const mxArray *c3_r_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_b_setSimStateSideEffectsInfo, const char_T
  *c3_identifier)
{
  const mxArray *c3_y = NULL;
  emlrtMsgIdentifier c3_thisId;
  c3_y = NULL;
  c3_thisId.fIdentifier = (const char *)c3_identifier;
  c3_thisId.fParent = NULL;
  c3_thisId.bParentIsCell = false;
  sf_mex_assign(&c3_y, c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_setSimStateSideEffectsInfo), &c3_thisId), false);
  sf_mex_destroy(&c3_b_setSimStateSideEffectsInfo);
  return c3_y;
}

static const mxArray *c3_s_emlrt_marshallIn(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  const mxArray *c3_y = NULL;
  (void)chartInstance;
  (void)c3_parentId;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_duplicatearraysafe(&c3_u), false);
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static const mxArray *sf_get_hover_data_for_msg(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, int32_T c3_ssid)
{
  (void)chartInstance;
  (void)c3_ssid;
  return NULL;
}

static void c3_init_sf_message_store_memory(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static real_T c3_get_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_elementIndex)
{
  if (chartInstance->c3_dsmdiag_RotMatrix_init) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 0, "RotMatrix_init",
      c3_elementIndex);
  }

  return (*chartInstance->c3_RotMatrix_init_address)[c3_elementIndex];
}

static void c3_set_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_elementIndex, real_T c3_elementValue)
{
  if (chartInstance->c3_dsmdiag_RotMatrix_init) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 0, "RotMatrix_init",
      c3_elementIndex);
  }

  (*chartInstance->c3_RotMatrix_init_address)[c3_elementIndex] = c3_elementValue;
}

static real_T *c3_access_RotMatrix_init(SFc3_XsensLibrary2InstanceStruct
  *chartInstance, uint32_T c3_rdOnly)
{
  if (chartInstance->c3_dsmdiag_RotMatrix_init) {
    ssAccessDataStore_wrapper(chartInstance->S, 0, "RotMatrix_init", c3_rdOnly);
  }

  return &(*chartInstance->c3_RotMatrix_init_address)[0U];
}

static real_T c3_get_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_elementIndex)
{
  if (chartInstance->c3_dsmdiag_gRf) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 1, "gRf",
      c3_elementIndex);
  }

  return (*chartInstance->c3__indexgRf_address)[c3_elementIndex];
}

static void c3_set_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance, uint32_T
  c3_elementIndex, real_T c3_elementValue)
{
  if (chartInstance->c3_dsmdiag_gRf) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 1, "gRf",
      c3_elementIndex);
  }

  (*chartInstance->c3__indexgRf_address)[c3_elementIndex] = c3_elementValue;
}

static real_T *c3_access_gRf(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_rdOnly)
{
  if (chartInstance->c3_dsmdiag_gRf) {
    ssAccessDataStore_wrapper(chartInstance->S, 1, "gRf", c3_rdOnly);
  }

  return &(*chartInstance->c3__indexgRf_address)[0U];
}

static real_T c3_get_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_elementIndex)
{
  if (chartInstance->c3_dsmdiag_sRb) {
    ssReadFromDataStoreElement_wrapper(chartInstance->S, 2, "sRb",
      c3_elementIndex);
  }

  return (*chartInstance->c3__indexsRb_address)[c3_elementIndex];
}

static void c3_set_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance, uint32_T
  c3_elementIndex, real_T c3_elementValue)
{
  if (chartInstance->c3_dsmdiag_sRb) {
    ssWriteToDataStoreElement_wrapper(chartInstance->S, 2, "sRb",
      c3_elementIndex);
  }

  (*chartInstance->c3__indexsRb_address)[c3_elementIndex] = c3_elementValue;
}

static real_T *c3_access_sRb(SFc3_XsensLibrary2InstanceStruct *chartInstance,
  uint32_T c3_rdOnly)
{
  if (chartInstance->c3_dsmdiag_sRb) {
    ssAccessDataStore_wrapper(chartInstance->S, 2, "sRb", c3_rdOnly);
  }

  return &(*chartInstance->c3__indexsRb_address)[0U];
}

static void init_dsm_address_info(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "RotMatrix_init",
    (void **)&chartInstance->c3_RotMatrix_init_address,
    &chartInstance->c3__indexrix_init);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "gRf", (void **)
    &chartInstance->c3__indexgRf_address, &chartInstance->c3__index);
  ssGetSFcnDataStoreNameAddrIdx_wrapper(chartInstance->S, "sRb", (void **)
    &chartInstance->c3__indexsRb_address, &chartInstance->c3_b__index);
}

static void init_simulink_io_address(SFc3_XsensLibrary2InstanceStruct
  *chartInstance)
{
  chartInstance->c3_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c3_sfEvent = (int32_T *)ssGetDWork_wrapper(chartInstance->S, 0);
  chartInstance->c3_is_active_c3_XsensLibrary2 = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_is_c3_XsensLibrary2 = (uint8_T *)ssGetDWork_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_Acceleration = (real_T (*)[3])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c3_RotationMatrix = (real_T (*)[9])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_RotMatrix_out = (real_T (*)[9])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c3_Accelerationbuffer = (real_T (*)[15])ssGetDWork_wrapper
    (chartInstance->S, 3);
  chartInstance->c3_mean_accel_b = (real_T (*)[3])ssGetDWork_wrapper
    (chartInstance->S, 4);
  chartInstance->c3_mean_accel = (real_T (*)[3])ssGetDWork_wrapper
    (chartInstance->S, 5);
  chartInstance->c3_mean_rotmat = (real_T (*)[9])ssGetDWork_wrapper
    (chartInstance->S, 6);
  chartInstance->c3_gamma = (real_T *)ssGetDWork_wrapper(chartInstance->S, 7);
  chartInstance->c3_beta = (real_T *)ssGetDWork_wrapper(chartInstance->S, 8);
  chartInstance->c3_gRb = (real_T (*)[9])ssGetDWork_wrapper(chartInstance->S, 9);
  chartInstance->c3_RotMatbuffer = (real_T (*)[45])ssGetDWork_wrapper
    (chartInstance->S, 10);
  chartInstance->c3_samples = (real_T *)ssGetDWork_wrapper(chartInstance->S, 11);
  chartInstance->c3_Calib_performed = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 12);
  chartInstance->c3_data_received = (real_T *)ssGetDWork_wrapper
    (chartInstance->S, 13);
  chartInstance->c3_SensorID = (real32_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c3_dsmdiag_RotMatrix_init = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 0,
    "RotMatrix_init");
  chartInstance->c3_dsmdiag_gRf = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 1, "gRf");
  chartInstance->c3_dsmdiag_sRb = (boolean_T)
    ssGetDSMBlockDiagnosticsEnabled_wrapper(chartInstance->S, 2, "sRb");
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

static uint32_T* sf_get_sfun_dwork_checksum(void);
void sf_c3_XsensLibrary2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(121275957U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3097138361U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3020765752U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(4290087709U);
}

mxArray* sf_c3_XsensLibrary2_get_post_codegen_info(void);
mxArray *sf_c3_XsensLibrary2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("by9pKYJbZP52HRvrBcYkGH");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(9);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(9));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,11,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(5);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,3,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      pr[2] = (double)(5);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,1,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(3);
      pr[1] = (double)(3);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxData);
  }

  {
    mxArray* mxPostCodegenInfo = sf_c3_XsensLibrary2_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_XsensLibrary2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_XsensLibrary2_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("early");
  mxArray *fallbackReason = mxCreateString("ext_mode");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c3_XsensLibrary2_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c3_XsensLibrary2_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c3_XsensLibrary2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[12],T\"RotMatrix_out\",},{M[3],M[25],T\"Accelerationbuffer\",},{M[3],M[34],T\"Calib_performed\",},{M[3],M[32],T\"RotMatbuffer\",},{M[3],M[30],T\"beta\",},{M[3],M[38],T\"data_received\",},{M[3],M[31],T\"gRb\",},{M[3],M[29],T\"gamma\",},{M[3],M[27],T\"mean_accel\",},{M[3],M[26],T\"mean_accel_b\",}}",
    "100 S1x5'type','srcId','name','auxInfo'{{M[3],M[28],T\"mean_rotmat\",},{M[3],M[33],T\"samples\",},{M[8],M[0],T\"is_active_c3_XsensLibrary2\",},{M[9],M[0],T\"is_c3_XsensLibrary2\",},{M[15],M[0],T\"dataWrittenToVector\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 15, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_XsensLibrary2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const mxArray* sf_opaque_get_hover_data_for_msg(void* chartInstance,
  int32_T msgSSID)
{
  return sf_get_hover_data_for_msg( (SFc3_XsensLibrary2InstanceStruct *)
    chartInstance, msgSSID);
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_XsensLibrary2InstanceStruct *chartInstance =
      (SFc3_XsensLibrary2InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _XsensLibrary2MachineNumber_,
           3,
           3,
           2,
           0,
           24,
           0,
           0,
           0,
           0,
           0,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_XsensLibrary2MachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_XsensLibrary2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _XsensLibrary2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,0,0,0,"Accelerationbuffer");
          _SFD_SET_DATA_PROPS(1,0,0,0,"Calib_performed");
          _SFD_SET_DATA_PROPS(2,0,0,0,"RotMatbuffer");
          _SFD_SET_DATA_PROPS(3,0,0,0,"beta");
          _SFD_SET_DATA_PROPS(4,0,0,0,"data_received");
          _SFD_SET_DATA_PROPS(5,0,0,0,"gRb");
          _SFD_SET_DATA_PROPS(6,0,0,0,"gamma");
          _SFD_SET_DATA_PROPS(7,0,0,0,"mean_accel");
          _SFD_SET_DATA_PROPS(8,0,0,0,"mean_accel_b");
          _SFD_SET_DATA_PROPS(9,0,0,0,"mean_rotmat");
          _SFD_SET_DATA_PROPS(10,0,0,0,"samples");
          _SFD_SET_DATA_PROPS(11,1,1,0,"Acceleration");
          _SFD_SET_DATA_PROPS(12,1,1,0,"RotationMatrix");
          _SFD_SET_DATA_PROPS(13,1,1,0,"SensorID");
          _SFD_SET_DATA_PROPS(14,2,0,1,"RotMatrix_out");
          _SFD_SET_DATA_PROPS(15,8,0,0,"");
          _SFD_SET_DATA_PROPS(16,9,0,0,"");
          _SFD_SET_DATA_PROPS(17,10,0,0,"RotationToInitial");
          _SFD_SET_DATA_PROPS(18,10,0,0,"XAxis");
          _SFD_SET_DATA_PROPS(19,10,0,0,"YAxis");
          _SFD_SET_DATA_PROPS(20,10,0,0,"ZAxis");
          _SFD_SET_DATA_PROPS(21,11,0,0,"RotMatrix_init");
          _SFD_SET_DATA_PROPS(22,11,0,0,"gRf");
          _SFD_SET_DATA_PROPS(23,11,0,0,"sRb");
          _SFD_STATE_INFO(0,0,0);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(1,0,2);
          _SFD_CH_SUBSTATE_COUNT(2);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_CH_SUBSTATE_INDEX(1,2);
          _SFD_ST_SUBSTATE_COUNT(0,0);
          _SFD_ST_SUBSTATE_COUNT(2,0);
        }

        _SFD_CV_INIT_CHART(2,1,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(1,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(1,1,1,0,6,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(1,0,"DirectionToVector_sRb",0,-1,585);
        _SFD_CV_INIT_EML_IF(1,1,0,72,93,125,585);
        _SFD_CV_INIT_EML_IF(1,1,1,130,151,193,581);
        _SFD_CV_INIT_EML_IF(1,1,2,198,219,261,573);
        _SFD_CV_INIT_EML_IF(1,1,3,266,287,340,561);
        _SFD_CV_INIT_EML_IF(1,1,4,345,366,426,545);
        _SFD_CV_INIT_EML_IF(1,1,5,431,452,-1,525);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,0,75,93,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,1,133,151,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,2,201,219,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,3,269,287,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,4,348,366,-1,0);
        _SFD_CV_INIT_EML_RELATIONAL(1,1,5,434,452,-1,0);
        _SFD_CV_INIT_EML(0,1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,1,0,338,352,-1,1032);
        _SFD_CV_INIT_EML_RELATIONAL(0,1,0,342,352,-1,4);
        _SFD_CV_INIT_EML(2,1,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(2,1,0,13,37,96,146);
        _SFD_CV_INIT_EML_RELATIONAL(2,1,0,17,37,-1,0);
        _SFD_CV_INIT_EML(0,0,0,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_IF(0,0,0,1,18,1,18);
        _SFD_CV_INIT_EML_RELATIONAL(0,0,0,1,18,-1,4);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 5U;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_g_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[3];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          dimVector[2]= 5U;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,3,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)
            c3_h_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1U;
          dimVector[1]= 9U;
          _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(13,SF_SINGLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4294967295U;
          _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)NULL,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(17,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)c3_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 3U;
          dimVector[1]= 3U;
          _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)
            c3_e_sf_marshallIn);
        }

        _SFD_SET_DATA_VALUE_PTR(15,(void *)(NULL));
        _SFD_SET_DATA_VALUE_PTR(16,(void *)(NULL));
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _XsensLibrary2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_XsensLibrary2InstanceStruct *chartInstance =
      (SFc3_XsensLibrary2InstanceStruct *)sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(11U, (void *)chartInstance->c3_Acceleration);
        _SFD_SET_DATA_VALUE_PTR(12U, (void *)chartInstance->c3_RotationMatrix);
        _SFD_SET_DATA_VALUE_PTR(22U, (void *)chartInstance->c3__indexgRf_address);
        _SFD_SET_DATA_VALUE_PTR(14U, (void *)chartInstance->c3_RotMatrix_out);
        _SFD_SET_DATA_VALUE_PTR(18U, (void *)&chartInstance->c3_XAxis);
        _SFD_SET_DATA_VALUE_PTR(19U, (void *)&chartInstance->c3_YAxis);
        _SFD_SET_DATA_VALUE_PTR(20U, (void *)&chartInstance->c3_ZAxis);
        _SFD_SET_DATA_VALUE_PTR(17U, (void *)
          &chartInstance->c3_RotationToInitial);
        _SFD_SET_DATA_VALUE_PTR(23U, (void *)chartInstance->c3__indexsRb_address);
        _SFD_SET_DATA_VALUE_PTR(21U, (void *)
          chartInstance->c3_RotMatrix_init_address);
        _SFD_SET_DATA_VALUE_PTR(0U, (void *)chartInstance->c3_Accelerationbuffer);
        _SFD_SET_DATA_VALUE_PTR(8U, (void *)chartInstance->c3_mean_accel_b);
        _SFD_SET_DATA_VALUE_PTR(7U, (void *)chartInstance->c3_mean_accel);
        _SFD_SET_DATA_VALUE_PTR(9U, (void *)chartInstance->c3_mean_rotmat);
        _SFD_SET_DATA_VALUE_PTR(6U, (void *)chartInstance->c3_gamma);
        _SFD_SET_DATA_VALUE_PTR(3U, (void *)chartInstance->c3_beta);
        _SFD_SET_DATA_VALUE_PTR(5U, (void *)chartInstance->c3_gRb);
        _SFD_SET_DATA_VALUE_PTR(2U, (void *)chartInstance->c3_RotMatbuffer);
        _SFD_SET_DATA_VALUE_PTR(10U, (void *)chartInstance->c3_samples);
        _SFD_SET_DATA_VALUE_PTR(1U, (void *)chartInstance->c3_Calib_performed);
        _SFD_SET_DATA_VALUE_PTR(4U, (void *)chartInstance->c3_data_received);
        _SFD_SET_DATA_VALUE_PTR(13U, (void *)chartInstance->c3_SensorID);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sbpKB2HF9X2qPryphdNXliD";
}

static void sf_check_dwork_consistency(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    const uint32_T *sfunDWorkChecksum = sf_get_sfun_dwork_checksum();
    mxArray *infoStruct = load_XsensLibrary2_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    mxArray* mxRTWDWorkChecksum = sf_get_dwork_info_from_mat_file(S,
      sf_get_instance_specialization(), infoStruct, 3, "dworkChecksum");
    if (mxRTWDWorkChecksum != NULL) {
      double *pr = mxGetPr(mxRTWDWorkChecksum);
      if ((uint32_T)pr[0] != sfunDWorkChecksum[0] ||
          (uint32_T)pr[1] != sfunDWorkChecksum[1] ||
          (uint32_T)pr[2] != sfunDWorkChecksum[2] ||
          (uint32_T)pr[3] != sfunDWorkChecksum[3]) {
        sf_mex_error_message("Code generation and simulation targets registered different sets of persistent variables for the block. "
                             "External or Rapid Accelerator mode simulation requires code generation and simulation targets to "
                             "register the same set of persistent variables for this block. "
                             "This discrepancy is typically caused by MATLAB functions that have different code paths for "
                             "simulation and code generation targets where these code paths define different sets of persistent variables. "
                             "Please identify these code paths in the offending block and rewrite the MATLAB code so that "
                             "the set of persistent variables is the same between simulation and code generation.");
      }
    }
  }
}

static void sf_opaque_initialize_c3_XsensLibrary2(void *chartInstanceVar)
{
  sf_check_dwork_consistency(((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar)->S);
  chart_debug_initialization(((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar);
  initialize_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c3_XsensLibrary2(void *chartInstanceVar)
{
  enable_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_XsensLibrary2(void *chartInstanceVar)
{
  disable_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_XsensLibrary2(void *chartInstanceVar)
{
  sf_gateway_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_ext_mode_exec_c3_XsensLibrary2(void *chartInstanceVar)
{
  ext_mode_exec_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c3_XsensLibrary2(SimStruct* S)
{
  return get_sim_state_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c3_XsensLibrary2(SimStruct* S, const mxArray
  *st)
{
  set_sim_state_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c3_XsensLibrary2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_XsensLibrary2InstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_XsensLibrary2_optimization_info();
    }

    finalize_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_XsensLibrary2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_XsensLibrary2((SFc3_XsensLibrary2InstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

mxArray *sf_c3_XsensLibrary2_get_testpoint_info(void)
{
  const char *infoEncStr[] = {
    "100 S1x2'varName','path'{{T\"is_active_c3_XsensLibrary2\",T\"is_active_c3_XsensLibrary2\"},{T\"is_c3_XsensLibrary2\",T\"is_c3_XsensLibrary2\"}}"
  };

  mxArray *mxTpInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  return mxTpInfo;
}

static void sf_set_sfun_dwork_info(SimStruct *S)
{
  const char *dworkEncStr[] = {
    "100 S1x10'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size','local_queue_dwork_idx','local_queue_id'{{T\"int32\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"uint8\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M1x2[3 5],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[3],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[3],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M1x2[3 3],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M1x2[3 3],M[-1],M[-1]}}",
    "100 S1x4'type','isSigned','wordLength','bias','slope','exponent','isScaledDouble','isComplex','size','local_queue_dwork_idx','local_queue_id'{{T\"double\",,,,,,,M[0],M1x3[3 3 5],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]},{T\"double\",,,,,,,M[0],M[],M[-1],M[-1]}}"
  };

  sf_set_encoded_dwork_info(S, dworkEncStr, 14, 10);
}

static uint32_T* sf_get_sfun_dwork_checksum()
{
  static uint32_T checksum[4] = { 2324514378U, 1871392220U, 1526927771U,
    3397635304U };

  return checksum;
}

static void mdlSetWorkWidths_c3_XsensLibrary2(SimStruct *S)
{
  /* Actual parameters from chart:
     RotationToInitial XAxis YAxis ZAxis
   */
  const char_T *rtParamNames[] = { "RotationToInitial", "XAxis", "YAxis",
    "ZAxis" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for RotationToInitial*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for XAxis*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for YAxis*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for ZAxis*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);
  ssSetInputPortDirectFeedThrough(S, 0, 1);
  ssSetInputPortDirectFeedThrough(S, 1, 1);
  ssSetInputPortDirectFeedThrough(S, 2, 1);
  ssSetStatesModifiedOnlyInUpdate(S, 0);
  ssSetBlockIsPurelyCombinatorial_wrapper(S, 0);
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_XsensLibrary2_optimization_info
      (sim_mode_is_rtw_gen(S), sim_mode_is_modelref_sim(S), sim_mode_is_external
       (S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 3);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    sf_register_codegen_names_for_scoped_functions_defined_by_chart(S);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
    sf_set_sfun_dwork_info(S);
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(490564309U));
  ssSetChecksum1(S,(3297430137U));
  ssSetChecksum2(S,(64137460U));
  ssSetChecksum3(S,(1619989939U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,0);
}

static void mdlRTW_c3_XsensLibrary2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c3_XsensLibrary2(SimStruct *S)
{
  SFc3_XsensLibrary2InstanceStruct *chartInstance;
  chartInstance = (SFc3_XsensLibrary2InstanceStruct *)utMalloc(sizeof
    (SFc3_XsensLibrary2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc3_XsensLibrary2InstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_XsensLibrary2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c3_XsensLibrary2;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_XsensLibrary2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_XsensLibrary2;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_XsensLibrary2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c3_XsensLibrary2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c3_XsensLibrary2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c3_XsensLibrary2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_XsensLibrary2;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_XsensLibrary2;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_XsensLibrary2;
  chartInstance->chartInfo.callGetHoverDataForMsg =
    sf_opaque_get_hover_data_for_msg;
  chartInstance->chartInfo.extModeExec =
    sf_opaque_ext_mode_exec_c3_XsensLibrary2;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c3_XsensLibrary2(chartInstance);
}

void c3_XsensLibrary2_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_XsensLibrary2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_XsensLibrary2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_XsensLibrary2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_XsensLibrary2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
