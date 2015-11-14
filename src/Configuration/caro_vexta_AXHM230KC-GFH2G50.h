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

//vexta_AXHM450KC-GFH4G200_parameters


//-------------------------motor parameters-----------------------------------
#define R_s_0                   0.1111f         //Ohms
#define L_s_d_0                 0.000038671875f //H   0.000089f H
#define L_s_q_0	                0.00003515625f  //(54uH)H   0.000089f H
#define psi_F_0                 0.0067269f      //Wb-t (weber-turn) (kg m2 s-2 A-1)
#define pole_pairs_0            5.0f	        //five pole pairs (five d-axis)
#define gear_ratio              50.0f
#define DEAD_TIME               0.0f            //Dead time for switching from high to low transistors

//-------------------------PID parameters-------------------------------------
#define P_SVM   0.01f
#define I_SVM   0.0000000005f
#define PI_MAX   1.0f
#define PI_MIN  -1.0f


//Admittance controller
#define STIFFNESS 0.00001f
#define DAMPING   0.00001f
#define MAX_SPEED 120.0f


//------------------Battery-----------------------------------
#define UD_PERCENTAGE   0.8f    //0.8f is the max value. 
                                //More than that causes the battery to deliver an oscilating voltage instead of a dc voltaje. 
                                //Furthermore, if you use 100% the current rises too much and the fuse melts.



//Hall sensor parameters
#define HALL_FACTOR 1.0f


//--------------------strain gauge---------------------------
#define STRAIN_GAUGE_REFERENCE_VOLTAGE   0.0f//
#define STRAIN_GAUGE_CONVERSION_FACTOR   2.0f//
//strain gauge resistances
//wheatstrone bridege: 343.3Ohm
//gain voltage: Rg: 51.6Ohm=>G=4+60k/Rg=1166.79



float strain_gauge_reference=STRAIN_GAUGE_REFERENCE_VOLTAGE;
bool reset_strain_gauge_reference   =true;

