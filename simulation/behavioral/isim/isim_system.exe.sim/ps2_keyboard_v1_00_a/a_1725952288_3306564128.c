/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0xc3576ebc */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "C:/Users/superman/Desktop/DerekLab7/pcores/ps2_keyboard_v1_00_a/hdl/vhdl/user_logic.vhd";
extern char *IEEE_P_2592010699;
extern char *IEEE_P_3620187407;
extern char *IEEE_P_3499444699;

unsigned char ieee_p_2592010699_sub_1605435078_503743352(char *, unsigned char , unsigned char );
unsigned char ieee_p_2592010699_sub_1690584930_503743352(char *, unsigned char );
char *ieee_p_2592010699_sub_1735675855_503743352(char *, char *, char *, char *, char *, char *);
char *ieee_p_3499444699_sub_1438165383_3536714472(char *, char *, char *, char *, int );
unsigned char ieee_p_3499444699_sub_2368615388_3536714472(char *, char *, char *, int );


static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_0(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    unsigned char t11;
    unsigned char t12;

LAB0:    xsi_set_current_line(177, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 1792U);
    t4 = xsi_signal_has_event(t1);
    if (t4 == 1)
        goto LAB7;

LAB8:    t3 = (unsigned char)0;

LAB9:    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 11064);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(178, ng0);
    t1 = xsi_get_transient_memory(8U);
    memset(t1, 0, 8U);
    t5 = t1;
    memset(t5, (unsigned char)2, 8U);
    t6 = (t0 + 11272);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 8U);
    xsi_driver_first_trans_fast(t6);
    xsi_set_current_line(179, ng0);
    t1 = (t0 + 11336);
    t2 = (t1 + 56U);
    t5 = *((char **)t2);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB5:    xsi_set_current_line(181, ng0);
    t2 = (t0 + 3912U);
    t6 = *((char **)t2);
    t2 = (t0 + 11272);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t6, 8U);
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(182, ng0);
    t1 = (t0 + 4232U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 11336);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = t3;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB7:    t2 = (t0 + 1832U);
    t5 = *((char **)t2);
    t11 = *((unsigned char *)t5);
    t12 = (t11 == (unsigned char)3);
    t3 = t12;
    goto LAB9;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_1(char *t0)
{
    char t9[16];
    char t11[16];
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    unsigned int t5;
    unsigned int t6;
    unsigned int t7;
    char *t8;
    char *t10;
    char *t12;
    char *t13;
    int t14;
    unsigned int t15;
    unsigned char t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;

LAB0:    xsi_set_current_line(187, ng0);

LAB3:    t1 = (t0 + 1192U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 3752U);
    t4 = *((char **)t1);
    t5 = (7 - 7);
    t6 = (t5 * 1U);
    t7 = (0 + t6);
    t1 = (t4 + t7);
    t10 = ((IEEE_P_2592010699) + 4024);
    t12 = (t11 + 0U);
    t13 = (t12 + 0U);
    *((int *)t13) = 7;
    t13 = (t12 + 4U);
    *((int *)t13) = 1;
    t13 = (t12 + 8U);
    *((int *)t13) = -1;
    t14 = (1 - 7);
    t15 = (t14 * -1);
    t15 = (t15 + 1);
    t13 = (t12 + 12U);
    *((unsigned int *)t13) = t15;
    t8 = xsi_base_array_concat(t8, t9, t10, (char)99, t3, (char)97, t1, t11, (char)101);
    t15 = (1U + 7U);
    t16 = (8U != t15);
    if (t16 == 1)
        goto LAB5;

LAB6:    t13 = (t0 + 11400);
    t17 = (t13 + 56U);
    t18 = *((char **)t17);
    t19 = (t18 + 56U);
    t20 = *((char **)t19);
    memcpy(t20, t8, 8U);
    xsi_driver_first_trans_fast(t13);

LAB2:    t21 = (t0 + 11080);
    *((int *)t21) = 1;

LAB1:    return;
LAB4:    goto LAB2;

LAB5:    xsi_size_not_matching(8U, t15, 0);
    goto LAB6;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_2(char *t0)
{
    char t5[16];
    char t19[16];
    char *t1;
    char *t2;
    char *t3;
    char *t6;
    char *t7;
    int t8;
    unsigned int t9;
    unsigned char t10;
    char *t11;
    char *t12;
    char *t13;
    char *t14;
    char *t15;
    char *t16;
    char *t17;
    char *t20;
    char *t21;
    int t22;
    unsigned char t23;
    char *t24;
    char *t25;
    char *t26;
    char *t27;
    char *t28;
    char *t29;
    unsigned char t30;
    char *t31;
    char *t32;
    char *t33;
    char *t34;
    char *t35;

LAB0:    xsi_set_current_line(188, ng0);
    t1 = (t0 + 3752U);
    t2 = *((char **)t1);
    t1 = (t0 + 19344U);
    t3 = (t0 + 19840);
    t6 = (t5 + 0U);
    t7 = (t6 + 0U);
    *((int *)t7) = 0;
    t7 = (t6 + 4U);
    *((int *)t7) = 7;
    t7 = (t6 + 8U);
    *((int *)t7) = 1;
    t8 = (7 - 0);
    t9 = (t8 * 1);
    t9 = (t9 + 1);
    t7 = (t6 + 12U);
    *((unsigned int *)t7) = t9;
    t10 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t2, t1, t3, t5);
    if (t10 != 0)
        goto LAB3;

LAB4:    t15 = (t0 + 3752U);
    t16 = *((char **)t15);
    t15 = (t0 + 19344U);
    t17 = (t0 + 19848);
    t20 = (t19 + 0U);
    t21 = (t20 + 0U);
    *((int *)t21) = 0;
    t21 = (t20 + 4U);
    *((int *)t21) = 7;
    t21 = (t20 + 8U);
    *((int *)t21) = 1;
    t22 = (7 - 0);
    t9 = (t22 * 1);
    t9 = (t9 + 1);
    t21 = (t20 + 12U);
    *((unsigned int *)t21) = t9;
    t23 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t16, t15, t17, t19);
    if (t23 != 0)
        goto LAB5;

LAB6:
LAB7:    t28 = (t0 + 4072U);
    t29 = *((char **)t28);
    t30 = *((unsigned char *)t29);
    t28 = (t0 + 11464);
    t31 = (t28 + 56U);
    t32 = *((char **)t31);
    t33 = (t32 + 56U);
    t34 = *((char **)t33);
    *((unsigned char *)t34) = t30;
    xsi_driver_first_trans_fast(t28);

LAB2:    t35 = (t0 + 11096);
    *((int *)t35) = 1;

LAB1:    return;
LAB3:    t7 = (t0 + 11464);
    t11 = (t7 + 56U);
    t12 = *((char **)t11);
    t13 = (t12 + 56U);
    t14 = *((char **)t13);
    *((unsigned char *)t14) = (unsigned char)3;
    xsi_driver_first_trans_fast(t7);
    goto LAB2;

LAB5:    t21 = (t0 + 11464);
    t24 = (t21 + 56U);
    t25 = *((char **)t24);
    t26 = (t25 + 56U);
    t27 = *((char **)t26);
    *((unsigned char *)t27) = (unsigned char)2;
    xsi_driver_first_trans_fast(t21);
    goto LAB2;

LAB8:    goto LAB2;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_3(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    unsigned char t5;
    unsigned char t6;
    unsigned char t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;
    char *t12;

LAB0:    xsi_set_current_line(192, ng0);

LAB3:    t1 = (t0 + 4072U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 4232U);
    t4 = *((char **)t1);
    t5 = *((unsigned char *)t4);
    t6 = ieee_p_2592010699_sub_1690584930_503743352(IEEE_P_2592010699, t5);
    t7 = ieee_p_2592010699_sub_1605435078_503743352(IEEE_P_2592010699, t3, t6);
    t1 = (t0 + 11528);
    t8 = (t1 + 56U);
    t9 = *((char **)t8);
    t10 = (t9 + 56U);
    t11 = *((char **)t10);
    *((unsigned char *)t11) = t7;
    xsi_driver_first_trans_fast(t1);

LAB2:    t12 = (t0 + 11112);
    *((int *)t12) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_4(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(196, ng0);

LAB3:    t1 = xsi_get_transient_memory(32U);
    memset(t1, 0, 32U);
    t2 = t1;
    memset(t2, (unsigned char)2, 32U);
    t3 = (t0 + 11592);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    memcpy(t7, t1, 32U);
    xsi_driver_first_trans_fast(t3);

LAB2:
LAB1:    return;
LAB4:    goto LAB2;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_5(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    unsigned char t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    unsigned char t10;
    unsigned char t11;
    unsigned char t12;
    char *t13;

LAB0:    xsi_set_current_line(201, ng0);
    t1 = (t0 + 1992U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t4 = (t3 == (unsigned char)2);
    if (t4 != 0)
        goto LAB2;

LAB4:    t1 = (t0 + 1792U);
    t4 = xsi_signal_has_event(t1);
    if (t4 == 1)
        goto LAB7;

LAB8:    t3 = (unsigned char)0;

LAB9:    if (t3 != 0)
        goto LAB5;

LAB6:
LAB3:    t1 = (t0 + 11128);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(202, ng0);
    t1 = (t0 + 11656);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = (unsigned char)0;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(203, ng0);
    t1 = xsi_get_transient_memory(4U);
    memset(t1, 0, 4U);
    t2 = t1;
    memset(t2, (unsigned char)2, 4U);
    t5 = (t0 + 11720);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 4U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(204, ng0);
    t1 = xsi_get_transient_memory(11U);
    memset(t1, 0, 11U);
    t2 = t1;
    memset(t2, (unsigned char)2, 11U);
    t5 = (t0 + 11784);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 11U);
    xsi_driver_first_trans_fast(t5);
    xsi_set_current_line(205, ng0);
    t1 = xsi_get_transient_memory(32U);
    memset(t1, 0, 32U);
    t2 = t1;
    memset(t2, (unsigned char)2, 32U);
    t5 = (t0 + 11848);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    t8 = (t7 + 56U);
    t9 = *((char **)t8);
    memcpy(t9, t1, 32U);
    xsi_driver_first_trans_fast(t5);
    goto LAB3;

LAB5:    xsi_set_current_line(207, ng0);
    t2 = (t0 + 3592U);
    t6 = *((char **)t2);
    t12 = *((unsigned char *)t6);
    t2 = (t0 + 11656);
    t7 = (t2 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t13 = *((char **)t9);
    *((unsigned char *)t13) = t12;
    xsi_driver_first_trans_fast(t2);
    xsi_set_current_line(208, ng0);
    t1 = (t0 + 4872U);
    t2 = *((char **)t1);
    t1 = (t0 + 11720);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 4U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(209, ng0);
    t1 = (t0 + 4552U);
    t2 = *((char **)t1);
    t1 = (t0 + 11784);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t2, 11U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(210, ng0);
    t1 = (t0 + 5032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 11912);
    t5 = (t1 + 56U);
    t6 = *((char **)t5);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    *((unsigned char *)t8) = t3;
    xsi_driver_first_trans_fast(t1);
    goto LAB3;

LAB7:    t2 = (t0 + 1832U);
    t5 = *((char **)t2);
    t10 = *((unsigned char *)t5);
    t11 = (t10 == (unsigned char)3);
    t3 = t11;
    goto LAB9;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_6(char *t0)
{
    char t15[16];
    char t17[16];
    char t30[16];
    char t33[16];
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned char t6;
    char *t7;
    unsigned char t8;
    unsigned char t9;
    unsigned char t10;
    unsigned int t11;
    unsigned int t12;
    unsigned int t13;
    char *t14;
    char *t16;
    char *t18;
    char *t19;
    int t20;
    unsigned int t21;
    unsigned char t22;
    char *t23;
    char *t24;
    char *t25;
    char *t26;
    int t27;
    unsigned int t28;
    unsigned int t29;
    int t31;
    unsigned int t32;
    int t34;
    char *t35;
    char *t36;
    char *t37;
    char *t38;
    static char *nl0[] = {&&LAB3, &&LAB4, &&LAB5};

LAB0:    xsi_set_current_line(218, ng0);
    t1 = (t0 + 11976);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(220, ng0);
    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    t6 = *((unsigned char *)t2);
    t1 = (t0 + 12040);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    *((unsigned char *)t7) = t6;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(221, ng0);
    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    t1 = (t0 + 12104);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    memcpy(t7, t2, 4U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(222, ng0);
    t1 = (t0 + 4392U);
    t2 = *((char **)t1);
    t1 = (t0 + 12168);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    memcpy(t7, t2, 11U);
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(224, ng0);
    t1 = (t0 + 3432U);
    t2 = *((char **)t1);
    t6 = *((unsigned char *)t2);
    t1 = (char *)((nl0) + t6);
    goto **((char **)t1);

LAB2:    t1 = (t0 + 11144);
    *((int *)t1) = 1;

LAB1:    return;
LAB3:    xsi_set_current_line(227, ng0);
    t3 = (t0 + 5352U);
    t4 = *((char **)t3);
    t8 = *((unsigned char *)t4);
    t9 = (t8 == (unsigned char)3);
    if (t9 != 0)
        goto LAB6;

LAB8:
LAB7:    goto LAB2;

LAB4:    xsi_set_current_line(235, ng0);
    t1 = (t0 + 5352U);
    t2 = *((char **)t1);
    t6 = *((unsigned char *)t2);
    t8 = (t6 == (unsigned char)3);
    if (t8 != 0)
        goto LAB11;

LAB13:
LAB12:    goto LAB2;

LAB5:    xsi_set_current_line(247, ng0);
    t1 = (t0 + 12040);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)0;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(249, ng0);
    t1 = (t0 + 11976);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)3;
    xsi_driver_first_trans_fast_port(t1);
    xsi_set_current_line(250, ng0);
    t1 = (t0 + 4392U);
    t2 = *((char **)t1);
    t11 = (10 - 8);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = (t15 + 0U);
    t4 = (t3 + 0U);
    *((int *)t4) = 8;
    t4 = (t3 + 4U);
    *((int *)t4) = 0;
    t4 = (t3 + 8U);
    *((int *)t4) = -1;
    t20 = (0 - 8);
    t21 = (t20 * -1);
    t21 = (t21 + 1);
    t4 = (t3 + 12U);
    *((unsigned int *)t4) = t21;
    t4 = (t0 + 19860);
    t7 = (t17 + 0U);
    t14 = (t7 + 0U);
    *((int *)t14) = 0;
    t14 = (t7 + 4U);
    *((int *)t14) = 7;
    t14 = (t7 + 8U);
    *((int *)t14) = 1;
    t27 = (7 - 0);
    t21 = (t27 * 1);
    t21 = (t21 + 1);
    t14 = (t7 + 12U);
    *((unsigned int *)t14) = t21;
    t8 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t1, t15, t4, t17);
    if (t8 == 1)
        goto LAB24;

LAB25:    t14 = (t0 + 4392U);
    t16 = *((char **)t14);
    t21 = (10 - 8);
    t28 = (t21 * 1U);
    t29 = (0 + t28);
    t14 = (t16 + t29);
    t18 = (t30 + 0U);
    t19 = (t18 + 0U);
    *((int *)t19) = 8;
    t19 = (t18 + 4U);
    *((int *)t19) = 0;
    t19 = (t18 + 8U);
    *((int *)t19) = -1;
    t31 = (0 - 8);
    t32 = (t31 * -1);
    t32 = (t32 + 1);
    t19 = (t18 + 12U);
    *((unsigned int *)t19) = t32;
    t19 = (t0 + 19868);
    t24 = (t33 + 0U);
    t25 = (t24 + 0U);
    *((int *)t25) = 0;
    t25 = (t24 + 4U);
    *((int *)t25) = 7;
    t25 = (t24 + 8U);
    *((int *)t25) = 1;
    t34 = (7 - 0);
    t32 = (t34 * 1);
    t32 = (t32 + 1);
    t25 = (t24 + 12U);
    *((unsigned int *)t25) = t32;
    t9 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t14, t30, t19, t33);
    t6 = t9;

LAB26:    if (t6 != 0)
        goto LAB21;

LAB23:    t1 = (t0 + 4392U);
    t2 = *((char **)t1);
    t11 = (10 - 8);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t2 + t13);
    t3 = (t15 + 0U);
    t4 = (t3 + 0U);
    *((int *)t4) = 8;
    t4 = (t3 + 4U);
    *((int *)t4) = 0;
    t4 = (t3 + 8U);
    *((int *)t4) = -1;
    t20 = (0 - 8);
    t21 = (t20 * -1);
    t21 = (t21 + 1);
    t4 = (t3 + 12U);
    *((unsigned int *)t4) = t21;
    t4 = (t0 + 19876);
    t7 = (t17 + 0U);
    t14 = (t7 + 0U);
    *((int *)t14) = 0;
    t14 = (t7 + 4U);
    *((int *)t14) = 7;
    t14 = (t7 + 8U);
    *((int *)t14) = 1;
    t27 = (7 - 0);
    t21 = (t27 * 1);
    t21 = (t21 + 1);
    t14 = (t7 + 12U);
    *((unsigned int *)t14) = t21;
    t6 = ieee_std_logic_unsigned_equal_stdv_stdv(IEEE_P_3620187407, t1, t15, t4, t17);
    if (t6 != 0)
        goto LAB30;

LAB31:    t1 = (t0 + 5512U);
    t2 = *((char **)t1);
    t6 = *((unsigned char *)t2);
    t8 = (t6 == (unsigned char)3);
    if (t8 != 0)
        goto LAB32;

LAB33:
LAB22:    goto LAB2;

LAB6:    xsi_set_current_line(229, ng0);
    t3 = (t0 + 1032U);
    t5 = *((char **)t3);
    t10 = *((unsigned char *)t5);
    t3 = (t0 + 4392U);
    t7 = *((char **)t3);
    t11 = (10 - 10);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t3 = (t7 + t13);
    t16 = ((IEEE_P_2592010699) + 4024);
    t18 = (t17 + 0U);
    t19 = (t18 + 0U);
    *((int *)t19) = 10;
    t19 = (t18 + 4U);
    *((int *)t19) = 1;
    t19 = (t18 + 8U);
    *((int *)t19) = -1;
    t20 = (1 - 10);
    t21 = (t20 * -1);
    t21 = (t21 + 1);
    t19 = (t18 + 12U);
    *((unsigned int *)t19) = t21;
    t14 = xsi_base_array_concat(t14, t15, t16, (char)99, t10, (char)97, t3, t17, (char)101);
    t21 = (1U + 10U);
    t22 = (11U != t21);
    if (t22 == 1)
        goto LAB9;

LAB10:    t19 = (t0 + 12168);
    t23 = (t19 + 56U);
    t24 = *((char **)t23);
    t25 = (t24 + 56U);
    t26 = *((char **)t25);
    memcpy(t26, t14, 11U);
    xsi_driver_first_trans_fast(t19);
    xsi_set_current_line(230, ng0);
    t1 = (t0 + 19856);
    t3 = (t0 + 12104);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    memcpy(t14, t1, 4U);
    xsi_driver_first_trans_fast(t3);
    xsi_set_current_line(231, ng0);
    t1 = (t0 + 12040);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)1;
    xsi_driver_first_trans_fast(t1);
    goto LAB7;

LAB9:    xsi_size_not_matching(11U, t21, 0);
    goto LAB10;

LAB11:    xsi_set_current_line(236, ng0);
    t1 = (t0 + 1032U);
    t3 = *((char **)t1);
    t9 = *((unsigned char *)t3);
    t1 = (t0 + 4392U);
    t4 = *((char **)t1);
    t11 = (10 - 10);
    t12 = (t11 * 1U);
    t13 = (0 + t12);
    t1 = (t4 + t13);
    t7 = ((IEEE_P_2592010699) + 4024);
    t14 = (t17 + 0U);
    t16 = (t14 + 0U);
    *((int *)t16) = 10;
    t16 = (t14 + 4U);
    *((int *)t16) = 1;
    t16 = (t14 + 8U);
    *((int *)t16) = -1;
    t20 = (1 - 10);
    t21 = (t20 * -1);
    t21 = (t21 + 1);
    t16 = (t14 + 12U);
    *((unsigned int *)t16) = t21;
    t5 = xsi_base_array_concat(t5, t15, t7, (char)99, t9, (char)97, t1, t17, (char)101);
    t21 = (1U + 10U);
    t10 = (11U != t21);
    if (t10 == 1)
        goto LAB14;

LAB15:    t16 = (t0 + 12168);
    t18 = (t16 + 56U);
    t19 = *((char **)t18);
    t23 = (t19 + 56U);
    t24 = *((char **)t23);
    memcpy(t24, t5, 11U);
    xsi_driver_first_trans_fast(t16);
    xsi_set_current_line(237, ng0);
    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    t1 = (t0 + 19376U);
    t6 = ieee_p_3499444699_sub_2368615388_3536714472(IEEE_P_3499444699, t2, t1, 0);
    if (t6 != 0)
        goto LAB16;

LAB18:    xsi_set_current_line(240, ng0);
    t1 = (t0 + 4712U);
    t2 = *((char **)t1);
    t1 = (t0 + 19376U);
    t3 = ieee_p_3499444699_sub_1438165383_3536714472(IEEE_P_3499444699, t15, t2, t1, 1);
    t4 = (t15 + 12U);
    t11 = *((unsigned int *)t4);
    t12 = (1U * t11);
    t6 = (4U != t12);
    if (t6 == 1)
        goto LAB19;

LAB20:    t5 = (t0 + 12104);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    t16 = (t14 + 56U);
    t18 = *((char **)t16);
    memcpy(t18, t3, 4U);
    xsi_driver_first_trans_fast(t5);

LAB17:    goto LAB12;

LAB14:    xsi_size_not_matching(11U, t21, 0);
    goto LAB15;

LAB16:    xsi_set_current_line(238, ng0);
    t3 = (t0 + 12040);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    t7 = (t5 + 56U);
    t14 = *((char **)t7);
    *((unsigned char *)t14) = (unsigned char)2;
    xsi_driver_first_trans_fast(t3);
    goto LAB17;

LAB19:    xsi_size_not_matching(4U, t12, 0);
    goto LAB20;

LAB21:    xsi_set_current_line(251, ng0);
    t25 = (t0 + 5032U);
    t26 = *((char **)t25);
    t10 = *((unsigned char *)t26);
    t22 = ieee_p_2592010699_sub_1690584930_503743352(IEEE_P_2592010699, t10);
    t25 = (t0 + 12232);
    t35 = (t25 + 56U);
    t36 = *((char **)t35);
    t37 = (t36 + 56U);
    t38 = *((char **)t37);
    *((unsigned char *)t38) = t22;
    xsi_driver_first_trans_fast(t25);
    xsi_set_current_line(252, ng0);
    t1 = (t0 + 5032U);
    t2 = *((char **)t1);
    t6 = *((unsigned char *)t2);
    t8 = (t6 == (unsigned char)3);
    if (t8 != 0)
        goto LAB27;

LAB29:
LAB28:    goto LAB22;

LAB24:    t6 = (unsigned char)1;
    goto LAB26;

LAB27:    xsi_set_current_line(254, ng0);
    t1 = (t0 + 11976);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    *((unsigned char *)t7) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    goto LAB28;

LAB30:    xsi_set_current_line(257, ng0);
    t14 = (t0 + 12296);
    t16 = (t14 + 56U);
    t18 = *((char **)t16);
    t19 = (t18 + 56U);
    t23 = *((char **)t19);
    *((unsigned char *)t23) = (unsigned char)3;
    xsi_driver_first_trans_fast(t14);
    xsi_set_current_line(259, ng0);
    t1 = (t0 + 11976);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    goto LAB22;

LAB32:    xsi_set_current_line(261, ng0);
    t1 = (t0 + 12296);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    *((unsigned char *)t7) = (unsigned char)2;
    xsi_driver_first_trans_fast(t1);
    xsi_set_current_line(263, ng0);
    t1 = (t0 + 11976);
    t2 = (t1 + 56U);
    t3 = *((char **)t2);
    t4 = (t3 + 56U);
    t5 = *((char **)t4);
    *((unsigned char *)t5) = (unsigned char)2;
    xsi_driver_first_trans_fast_port(t1);
    goto LAB22;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_7(char *t0)
{
    char *t1;
    char *t2;
    unsigned char t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;
    char *t8;

LAB0:    xsi_set_current_line(268, ng0);

LAB3:    t1 = (t0 + 5032U);
    t2 = *((char **)t1);
    t3 = *((unsigned char *)t2);
    t1 = (t0 + 12360);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t6 = (t5 + 56U);
    t7 = *((char **)t6);
    *((unsigned char *)t7) = t3;
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t8 = (t0 + 11160);
    *((int *)t8) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_8(char *t0)
{
    char *t1;
    char *t2;
    unsigned int t3;
    unsigned int t4;
    unsigned int t5;
    char *t6;
    char *t7;
    char *t8;
    char *t9;
    char *t10;
    char *t11;

LAB0:    xsi_set_current_line(269, ng0);

LAB3:    t1 = (t0 + 4392U);
    t2 = *((char **)t1);
    t3 = (10 - 8);
    t4 = (t3 * 1U);
    t5 = (0 + t4);
    t1 = (t2 + t5);
    t6 = (t0 + 12424);
    t7 = (t6 + 56U);
    t8 = *((char **)t7);
    t9 = (t8 + 56U);
    t10 = *((char **)t9);
    memcpy(t10, t1, 8U);
    xsi_driver_first_trans_fast_port(t6);

LAB2:    t11 = (t0 + 11176);
    *((int *)t11) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}

static void ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_9(char *t0)
{
    char t1[16];
    char t9[16];
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    unsigned int t6;
    unsigned int t7;
    unsigned int t8;
    char *t10;
    char *t11;
    int t12;
    unsigned int t13;
    char *t14;
    unsigned int t15;
    unsigned char t16;
    char *t17;
    char *t18;
    char *t19;
    char *t20;
    char *t21;
    char *t22;

LAB0:    xsi_set_current_line(271, ng0);

LAB3:    t2 = (t0 + 5672U);
    t3 = *((char **)t2);
    t2 = (t0 + 19392U);
    t4 = (t0 + 4392U);
    t5 = *((char **)t4);
    t6 = (10 - 8);
    t7 = (t6 * 1U);
    t8 = (0 + t7);
    t4 = (t5 + t8);
    t10 = (t9 + 0U);
    t11 = (t10 + 0U);
    *((int *)t11) = 8;
    t11 = (t10 + 4U);
    *((int *)t11) = 1;
    t11 = (t10 + 8U);
    *((int *)t11) = -1;
    t12 = (1 - 8);
    t13 = (t12 * -1);
    t13 = (t13 + 1);
    t11 = (t10 + 12U);
    *((unsigned int *)t11) = t13;
    t11 = ieee_p_2592010699_sub_1735675855_503743352(IEEE_P_2592010699, t1, t3, t2, t4, t9);
    t14 = (t1 + 12U);
    t13 = *((unsigned int *)t14);
    t15 = (1U * t13);
    t16 = (32U != t15);
    if (t16 == 1)
        goto LAB5;

LAB6:    t17 = (t0 + 12488);
    t18 = (t17 + 56U);
    t19 = *((char **)t18);
    t20 = (t19 + 56U);
    t21 = *((char **)t20);
    memcpy(t21, t11, 32U);
    xsi_driver_first_trans_fast(t17);

LAB2:    t22 = (t0 + 11192);
    *((int *)t22) = 1;

LAB1:    return;
LAB4:    goto LAB2;

LAB5:    xsi_size_not_matching(32U, t15, 0);
    goto LAB6;

}


extern void ps2_keyboard_v1_00_a_a_1725952288_3306564128_init()
{
	static char *pe[] = {(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_0,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_1,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_2,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_3,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_4,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_5,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_6,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_7,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_8,(void *)ps2_keyboard_v1_00_a_a_1725952288_3306564128_p_9};
	xsi_register_didat("ps2_keyboard_v1_00_a_a_1725952288_3306564128", "isim/isim_system.exe.sim/ps2_keyboard_v1_00_a/a_1725952288_3306564128.didat");
	xsi_register_executes(pe);
}
