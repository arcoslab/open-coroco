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
#define R_s_0                   0.78f    //Ohms
#define L_s_d_0                 0.0001f  //0.000038671875f  //H   0.000089f H
#define L_s_q_0	                0.0001f  //0.00003515625f  //(54uH)H   0.000089f H
#define psi_F_0                 0.0075f  //0.0016f//0.005f    //0.0016f  //Wb-t (weber-turn) (kg m2 s-2 A-1)
#define pole_pairs_0            5.0f	    //five pole pairs (five d-axis)
#define gear_ratio              200.0f   //200:1
#define DEAD_TIME               0.0f            //Dead time for switching from high to low transistors
#define MAX_GEAR_CYCLES 100.0f
//-------------------------PID parameters-------------------------------------

/*
#define P_SVM   0.005f
#define I_SVM   0.0000000001f
#define PI_MAX   1.0f
#define PI_MIN  -1.0f
*/

//working but oscillating
#define P_SVM   0.005f
#define I_SVM   0.0000000001f
#define PI_MAX   1.0f
#define PI_MIN  -1.0f
//Admittance controller
#define STIFFNESS 0.00005f//0.00001f
#define DAMPING   0.00005f
#define MAX_SPEED 200.0f


//------------------Battery-----------------------------------
#define UD_PERCENTAGE   0.7f    //0.8f is the max value. 
                                //More than that causes the battery to deliver an oscilating voltage instead of a dc voltaje. 
                                //Furthermore, if you use 100% the current rises too much and the fuse melts.



//Hall sensor parameters
#define HALL_FACTOR 1.0f


//--------------------strain gauge---------------------------
#define STRAIN_GAUGE_REFERENCE_VOLTAGE   0.0f//
#define STRAIN_GAUGE_CONVERSION_FACTOR      9.0f//0.273f//
//strain gauge resistances
//wheatstrone bridege: 343.3Ohm
//gain voltage: Rg: 51.6Ohm=>G=4+60k/Rg=1166.79
/*
37g=>0.03V=>0.037/0.03=1.233
148g=>0.10V=>0.148/0.10=1.48
121g=>0.07V=>0.121/0.07=1.172
366g=>0.23V=>0.366/0.23=1.59

mg/V=882/0.17=5.188

Torque  =d*F
        =d*m*g

d=19.5cm
g=9.8m/s^2

mg/V=

=>T=V *mg*d/V
=>T=V* 0.803*9.8*.195/0.17    =V*9.02
*/




/*
0.803g
0.17Vpp

*/



float strain_gauge_reference=STRAIN_GAUGE_REFERENCE_VOLTAGE;
bool reset_strain_gauge_reference   =true;

