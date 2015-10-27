/*
 *This file is part of the open-coroco project.
 *
 *  Copyright (C) 2013  Sebastian Chinchilla Gutierrez <tumacher@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


float fast_vector_angle                  (float quadrature_component, float direct_component);
void  fast_vector_angle_and_magnitude(float y,float x, float* magnitude, float* angle);
float extended_fast_atan(float tan_value);

float A_inverse_clark_transformation(float V_sD);
float B_inverse_clark_transformation(float V_sQ,                 float V_sD);
float C_inverse_clark_transformation(float V_sQ,                 float V_sD);




//voltage and current space vectors
float direct_stator_current_i_sD     (float i_sA);
float quadrature_stator_current_i_sQ (float i_sA,float i_sB);

void  switching_states               (int* S_A, int* S_B, int* S_C);
void  floating_switching_states      (float* S_A, float* S_B, float* S_C);


//stator flux-linkage space vector estimation
float direct_stator_flux_linkage_estimator_psi_sD     (float T,float V_sD,float i_sD,float R_s,float psi_sD);
float quadrature_stator_flux_linkage_estimator_psi_sQ (float T,float V_sQ,float i_sQ,float R_s,float psi_sQ);

//electromagnetic torque estimation
float electromagnetic_torque_estimation_t_e(float psi_sD,float i_sQ, float psi_sQ,float i_sD,float pole_pairs);
float DTC_torque_reference_PI(float w_r, float w_r_ref);

//stator flux-linkage reference
float rotor_speed_w_r(float psi_sD, float psi_sQ, float T,float previous_psi_sD,float previous_psi_sQ);

//hysteresis windows
int stator_flux_linkage_hysteresis_controller_d_psi   (float psi_s_ref, float psi_s,float psi_delta_percentage);
int electromagnetic_torque_hysteresis_controller_d_te(float t_e_ref  , float t_e  ,float t_e_delta_percentage);

//output voltages
void optimal_voltage_switching_vector_selection_table(int d_psi,int d_t_e,int alpha,int* S_A, int* S_B, int* S_C);
void voltage_switch_inverter_VSI(int S_A, int S_B, int S_C);

//wrapper
void DTC(void);






















float duty_cycle_to_angle(float duty_cycle);
float phase_A_angle_to_stator_angle(float phase_A_angle);
float stator_angle_to_phase_A(float stator_angle);



