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





void sensorless_pure_speed_SVM_pi_controller2(
    float reference_frequency, 
    float frequency, 
    float P,
    float I,
    float PI_max,
    float PI_min,
    float* i_error,
    float* pi)
 
{
    float  error         = 0.0f;
    float  p_error       = 0.0f;

    error     = reference_frequency-frequency;
    p_error   = P*error;    
    *i_error += I*error;    
    *pi       = p_error+*i_error; 

    if      (*pi > PI_max) { *pi = PI_max; }
    else if (*pi < PI_min) { *pi = PI_min; }
}





