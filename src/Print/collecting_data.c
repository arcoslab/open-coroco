bool collecting_sensorless_data = true;
bool transmitting_to_python = false;

#define SAMPLES 300
#define COLLECTING_SPEED_DELAY 0

float hall_angle=0.0f;
float PID_angle[SAMPLES];
bool  inductance_measure=true;
int collected_pointer=0;
bool serial_print_collected_data=false; 


float data_x=0.0f;
float data_y=0.0f;




void collecting_floating_data(void)
{
    timer=timer+1.0f;
    if (timer<0.0f)
        timer=0.0f;
    if (timer >=16777210.0f)
        timer =0.0f;

    if      (print_selection==0)    {   data_x=timer        ;   data_y=hall_freq        ;   }
    else if (print_selection==1)    {   data_x=i_sD         ;   data_y=i_sQ             ;   }
    else if (print_selection==2)    {   data_x=V_sD         ;   data_y=V_sQ             ;   }
    else if (print_selection==3)    {   data_x=timer        ;   data_y=U_d              ;   }
    else if (print_selection==4)    {   data_x=psi_sD       ;   data_y=psi_sQ           ;   }
    else if (print_selection==5)    {   data_x=timer        ;   data_y=t_e              ;   }
    else if (print_selection==6)    {   data_x=timer        ;   data_y=constant_speed_angle   ;   }
    else if (print_selection==7)    {   data_x=timer        ;   data_y=strain_gauge     ;   }
    else if (print_selection==8)    {   data_x=stiffness    ;   data_y=damping          ;   }
    else if (print_selection==9)    {   data_x=timer        ;   data_y=electric_angle   ;   }
    else if (print_selection==10)   {   data_x=timer        ;   data_y=i_sA             ;   }
    else if (print_selection==11)   {   data_x=timer        ;   data_y=i_sB             ;   }
    else if (print_selection==12)   {   data_x=timer        ;   data_y=-i_sA-i_sB       ;   }
    else if (print_selection==13)   {   data_x=timer        ;   data_y=w_r              ;   }
    else if (print_selection==14)   {   data_x=timer        ;   data_y=w_r_NO_i         ;   }
    else if (print_selection==15)   {   data_x=psi_sD_NO_i  ;   data_y=psi_sQ_NO_i      ;   }
    else if (print_selection==16)   {   data_x=timer        ;   data_y=t_e_NO_i         ;   }
    else if (print_selection==17)   {   data_x=timer        ;   data_y=acceleration_angle         ;   }
    else if (print_selection==18)   {   data_x=timer        ;   data_y=psi_s            ;   }
    else if (print_selection==19)   {   data_x=timer        ;   data_y=V_s              ;   }  
    else if (print_selection==20)   {   data_x=ref_freq_SVM ;   data_y=reference_electric_angle;   }   
    else                            {   data_x=timer        ;   data_y=timer            ;   }
    

}




void print_ascii_data(void)
{
    if      (print_selection==0)    printf("%10.0f %3.2f \n",   data_x,data_y);
    else if (print_selection==1)    printf(" %3.2f %3.2f \n",   data_x,data_y);
    else if (print_selection==2)    printf(" %3.2f %3.2f \n",   data_x,data_y);
    else if (print_selection==3)    printf("%10.0f %3.2f \n",   data_x,data_y);
    else if (print_selection==4)    printf("%3.6f %3.6f \n",    data_x,data_y);
    else if (print_selection==5)    printf("%10.0f %3.3f \n",   data_x,data_y);
    else if (print_selection==6)    printf("%10.0f %3.5f \n",   data_x,data_y);
    else if (print_selection==7)    printf("%10.0f %3.3f \n",   data_x,data_y);
    else if (print_selection==8)    printf("%10.2f %10.2f \n",  data_x,data_y);
    else if (print_selection==9)    printf("%10.0f %10.2f \n",  data_x,data_y);
    else if (print_selection==10)   printf("%10.0f %3.2f \n",   data_x,data_y);
    else if (print_selection==11)   printf("%10.0f %3.2f \n",   data_x,data_y);
    else if (print_selection==12)   printf("%10.0f %3.2f \n",   data_x,data_y);
    else if (print_selection==13)   printf("%10.0f %3.3f \n",   data_x,data_y);
    else if (print_selection==14)   printf("%10.0f %3.3f \n",   data_x,data_y);
    else if (print_selection==15)   printf("%3.6f %3.6f \n",    data_x,data_y);
    else if (print_selection==16)   printf("%10.0f %3.3f \n",   data_x,data_y);
    else if (print_selection==17)   printf("%10.0f %5.5f \n",   data_x,data_y);
    else if (print_selection==18)   printf("%10.0f %3.6f \n",    data_x,data_y);
    else if (print_selection==19)   printf("%10.0f %3.2f \n",   data_x,data_y);
    else                            printf("%10.0f %10.0f \n",  data_x,data_y);  
}

union float_union_t
{
    float f;
    char byte[sizeof(float)];
};


void print_regular_data(void)
{
    char checksum=0;
    printf ("X")   ;

    checksum=           print_float_as_bytes(data_x       );
    checksum=checksum  +print_float_as_bytes(data_y);

    printf ("%c", checksum);
    printf ("m");

}


char print_float_as_bytes(float floating_value)
{
    unsigned int i=0;
    char checksum=0;
    union float_union_t float_byte;

    //hack for serial transmition (transmiting 0.01f causes a transmition error)
    if (floating_value==0.01f)
        floating_value= 0.010000001f;

    float_byte.f=floating_value;

    while (i<sizeof(float))
    {
      printf("%c",float_byte.byte[i]);
      checksum=checksum+float_byte.byte[i];
      i++;
    }
    return checksum;
}

