#include <gtest.h>
#include "arithm.h"

TEST(Arithm, can_create_exression)
{
	ASSERT_NO_THROW(Arithm A);
}

TEST(Arithm, can_enter)
{
	Arithm A;

	ASSERT_NO_THROW(A.Enter("123"));
}

TEST(Arithm, can_enter_string)
{
	Arithm A;
	A.Enter("123");

	ASSERT_NO_THROW(A.Print());
}

// ------------------------namber----------------
TEST(Arithm, can_translate)
{
	Arithm A;
	A.Enter("123");

	ASSERT_NO_THROW(A.Translate());
}

TEST(Arithm, can_translate_bad_exp)
{
	Arithm A;
	A.Enter("df23");

	ASSERT_NO_THROW(A.Translate());
}

TEST(Arithm, _1_ok)
{
	Arithm A;
	A.Enter("1");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, _d_ok)
{
	Arithm A;
	A.Enter("d");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, _12345_ok)
{
	Arithm A;
	A.Enter("12345");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, _d123_neok)
{
	Arithm A;
	A.Enter("d123");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, _1b3_neok)
{
	Arithm A;
	A.Enter("1b3");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, negative_1_ok)
{
	Arithm A;
	A.Enter("-1");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, negative_d_neok)
{
	Arithm A;
	A.Enter("-d");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, negative_12345_ok)
{
	Arithm A;
	A.Enter("-12345");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, negative_d123_neok)
{
	Arithm A;
	A.Enter("-d123");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, negative_1b3_neok)
{
	Arithm A;
	A.Enter("-1b3");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, brackets_1_ok)
{
	Arithm A;
	A.Enter("(1)");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, brackets_d_neok)
{
	Arithm A;
	A.Enter("(d)");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, brackets_12345_ok)
{
	Arithm A;
	A.Enter("(12345)");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, brackets_neg12345_ok)
{
	Arithm A;
	A.Enter("(-12345)");

	EXPECT_EQ(true, A.Translate());
}

TEST(Arithm, brackets_d123_neok)
{
	Arithm A;
	A.Enter("(d123)");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, brackets_1b3_neok)
{
	Arithm A;
	A.Enter("(1b3)");

	EXPECT_EQ(false, A.Translate());
}

TEST(Arithm, not_enough_brackets)
{
	Arithm A;
	A.Enter("(123");

	EXPECT_EQ(false, A.Translate());
}

//--------------------------------------operations----------------------------------
//--------------------------------add---------------------------------
TEST(Arithm, can_add_two_namber)
{
	Arithm A,B;
	A.Enter("1+1");
	B.Enter("12+345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_add_two_negativ)
{
	Arithm A,B;
	A.Enter("-1++1");
	B.Enter("+12+-345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_not_add_bad_simbol)
{
	Arithm A,B;
	A.Enter("d+1");
	B.Enter("12+d");

	EXPECT_EQ(true, A.Translate());
}

//----------------------------------------sub----------------------------
TEST(Arithm, can_sub_two_namber)
{
	Arithm A,B;
	A.Enter("1-1");
	B.Enter("12-345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_sub_two_negativ)
{
	Arithm A,B;
	A.Enter("-1-1");
	B.Enter("12--345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_not_sub_bad_simbol)
{
	Arithm A,B;
	A.Enter("d-1");
	B.Enter("12-d");

	EXPECT_EQ(true, A.Translate());
}

//-------------------------------Mul--------------------------
TEST(Arithm, can_mul_two_namber)
{
	Arithm A,B;
	A.Enter("1*2");
	B.Enter("12*-345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_not_mul_bad_simbol)
{
	Arithm A,B;
	A.Enter("d*1");
	B.Enter("12*d");

	EXPECT_EQ(true, A.Translate());
}

//------------------------------div------------------
//-------------------------------Mul--------------------------
TEST(Arithm, can_div_two_namber)
{
	Arithm A,B;
	A.Enter("1/2");
	B.Enter("12/-345");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, can_not_div_bad_simbol)
{
	Arithm A,B;
	A.Enter("d/+1");
	B.Enter("12/d");

	EXPECT_EQ(true, A.Translate());
}

//-------------------combination---------------
TEST(Arithm, comb_bracket_sub_and_add)
{
	Arithm A,B;
	A.Enter("(-12)+-34");
	B.Enter("12+(34+56)-7");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, comb_bracket_div_and_mult)
{
	Arithm A,B;
	A.Enter("(-12)*-34/4");
	B.Enter("(34/56)*-7");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

TEST(Arithm, comb_all)
{
	Arithm A,B;
	A.Enter("(-12)*-34+3");
	B.Enter("1/(34+56)*-7");

	EXPECT_EQ(true, A.Translate());
	EXPECT_EQ(true, B.Translate());
}

//---------------------------compute----------------
TEST(Arithm, can_compute)
{
	Arithm A;
	A.Enter("34+3");
	
	ASSERT_NO_THROW(A.Compute());
}

TEST(Arithm, can_not_compute_bad_exp)
{
	Arithm A;
	A.Enter("(34+3");
	
	ASSERT_ANY_THROW(A.Compute());
}

TEST(Arithm, can_compute_easy_exp)
{
	Arithm A;
 	A.Enter("4+3");
	
	EXPECT_EQ(7, A.Compute());
}

TEST(Arithm, compute_add)
{
	Arithm A;
 	A.Enter("4+3");
	
	EXPECT_EQ(7, A.Compute());
}

TEST(Arithm, compute_any_add)
{
	Arithm A;
 	A.Enter("4+3+1+2");
	
	EXPECT_EQ(10, A.Compute());
}

TEST(Arithm, compute_sub)
{
	Arithm A;
 	A.Enter("4-3");
	
	EXPECT_EQ(1, A.Compute());
}

TEST(Arithm, compute_any_sub)
{
	Arithm A;
 	A.Enter("15-5-1");
	
	EXPECT_EQ(9, A.Compute());
}

TEST(Arithm, compute_mul)
{
	Arithm A;
 	A.Enter("5*3");
	
	EXPECT_EQ(15, A.Compute());
}

TEST(Arithm, compute_any_mul)
{
	Arithm A;
 	A.Enter("10*5*2");
	
	EXPECT_EQ(100, A.Compute());
}

TEST(Arithm, compute_div)
{
	Arithm A;
 	A.Enter("12/6");
	
	EXPECT_EQ(2, A.Compute());
}

TEST(Arithm, compute_any_div)
{
	Arithm A;
 	A.Enter("15/5/3");
	
	EXPECT_EQ(1, A.Compute());
}

TEST(Arithm, right_priority)
{
	Arithm A;
 	A.Enter("3+2*2");
	
	EXPECT_EQ(7, A.Compute());
}

TEST(Arithm, compute_add_with_brackets)
{
	Arithm A;
 	A.Enter("(12+3)+4");
	
	EXPECT_EQ(19, A.Compute());
}

TEST(Arithm, compute_combo_with_brackets_1)
{
	Arithm A;
 	A.Enter("(3+2)*2");
	
	EXPECT_EQ(10, A.Compute());
}

TEST(Arithm, compute_combo_with_brackets_2)
{
	Arithm A;
 	A.Enter("(12-2)/5");
	
	EXPECT_EQ(2, A.Compute());
}

TEST(Arithm, more_expression_add_and_mul)
{
	Arithm a1,a2,a3,a4,a5,a6;
 	a1.Enter("(2+2)*2");
	a2.Enter("7+(4+3)");
	a3.Enter("2*2+3/3");
	a4.Enter("4*4/2*2");
	a5.Enter("4*4/(2*2)");
	a6.Enter("(2+(6-2*(4/2)))/2");
	
	EXPECT_EQ(8, a1.Compute());
	EXPECT_EQ(14, a2.Compute());
	EXPECT_EQ(5, a3.Compute());
	EXPECT_EQ(16, a4.Compute());
	EXPECT_EQ(4, a5.Compute());
	EXPECT_EQ(2, a6.Compute());
}

TEST(Arithm, compute_string)
{
	EXPECT_EQ(2, Compute("(2+(6-2*(4/2)))/2"));
}