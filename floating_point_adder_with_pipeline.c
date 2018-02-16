#include<stdio.h>
#include<conio.h>

  void Compare(int i);
  void Right_Shift(int i);
  void Align(int i);
  void Add(int i);
  void Normalize(int i);

	int A_sign_18[6]={ 0 , 0 , 1 , 1 , 0 , 0 },			//Array of Signs of A
	      B_sign_18[6]={ 0 , 1 , 0 , 1 , 0 , 1 },			//Array of Signs of B
	      Sum_sign_18[6],						//Array of Signs of Sum
	      A_exp_18[6]={ 0x85 , 0x85 , 0x84 , 0x87 , 0x00 , 0x00 },	//Array of Exponents of A
	      B_exp_18[6]={ 0x86 , 0x85 , 0x85 , 0x85 , 0x00 , 0x85 },	//Array of Exponents of B
	      Sum_exp_18[6],						//Array of Exponents of Sum
	      shift;							//Shifts required to align Mantissa

	short int clock;							//To simulate a Sequential execution 
	
			     //Array of Mantissa's of A
	unsigned long int A_mantissa_18[6]={ 0x460000 , 0x420000 , 0x5c0000 , 0x0c0000 , 0x000000 ,  0x000000 },
			     //Array of Mantissa's of B
			     B_mantissa_18[6]={ 0x320000 , 0x1e0000 , 0x160000 , 0x0a0000 , 0x000000 , 0x620000 },
			     //Array of Mantissa's of Sum
			     Sum_mantissa_18[6],
	     		     //Masks for Normalization
			     mask1,
			     mask2,
			     //Array of Normalized Sum
			     x[6];

  void main()
  {
	for(clock=0;clock<10;clock++)
		{
			switch(clock)
			{
				case 0:	
				{
					Compare(0);			//Comparison of Pair 1
					printf("\nEND OF STAGE 0");					
                    break;
				}

				case 1:
				{
					Right_Shift(0);		//Right Shifting of Pair 1
					Compare(1);			//Comparison of Pair 2
					printf("\nEND OF STAGE 1");
					break;
				}
				case 2:
				{
					Align(0);			//Alignment of Pair 1
					Right_Shift(1);		//Right Shifting of Pair 2 
					Compare(2);			//Comparison of Pair 3
					printf("\nEND OF STAGE 2");
					break;
				}
				case 3:
				{
					Add(0);		     	//Addition of Pair 1
					Align(1);			//Alignment of Pair 2
					Right_Shift(2);		//Right Shifting of Pair 3
					Compare(3);			//Comparison of Pair 4
					printf("\nEND OF STAGE 3");
					break;
				}
				case 4:
				{
					Normalize(0);			//Normalization of Pair 1
					Add(1);			//Addition of Pair 2
					Align(2);			//Alignment of Pair 3
					Right_Shift(3);			//Right Shifting of Pair 4
					Compare(4);			//Comparison of Pair 5
					printf("\nEND OF STAGE 4");
					break;
				}
				case 5:
				{
					Normalize(1); 			//Normalization of Pair 2
					Add(2);			//Addition of Pair 3
					Align(3);			//Alignment of Pair 4
					Right_Shift(4);			//Right Shifting of Pair 5
					Compare(5);			//Comparison of Pair 6
					printf("\nEND OF STAGE 5");
					break;
				}
				case 6:
				{
					Normalize(2);			//Normalization of Pair 3
					Add(3);			//Addition of Pair 4
					Align(4);			//Alignment of Pair 5
					Right_Shift(5);			//Right Shifting of Pair 6
					printf("\nEND OF STAGE 6");
					break;
				}
				case 7:
				{
					Normalize(3);			//Normalization of Pair 4
					Add(4);			//Addition of Pair 5
					Align(5);			//Alignment of Pair 6
					printf("\nEND OF STAGE 7");
					break;
				}
				case 8:
				{
					Normalize(4);			//Normalization of Pair 5
					Add(5);			//Addition of Pair 6
					printf("\nEND OF STAGE 8");
					break;
				}
				case 9:
				{
					Normalize(5);			//Normalization of Pair 6
					printf("\nEND OF STAGE 9");
					break;
				}
			}
			getch();
	 }
 }
void Compare(int i)
{
	printf("\n------------------------------Comparison of Exponent's--------------------------------");

	//Loop to determine the shift and the greater number
	if(A_exp_18[i]>B_exp_18[i])
	{
		shift=A_exp_18[i]-B_exp_18[i];
	 //	printf("\nA is greater\n");
	}
	else if(A_exp_18[i]<B_exp_18[i])
	{
		shift=B_exp_18[i]-A_exp_18[i];
	   //	printf("\nB is greater\n");
	}
	else
	{
		shift=0;
	}
	
	//Including the 1 from "1.m" into the Mantissa
	mask1=0x400000;
	printf("\nTestbench %d",i+1);
	A_mantissa_18[i]=A_mantissa_18[i]>>1;
	B_mantissa_18[i]=B_mantissa_18[i]>>1;
	A_mantissa_18[i]=A_mantissa_18[i]|mask1;
	B_mantissa_18[i]=B_mantissa_18[i]|mask1;
	A_exp_18[i]=A_exp_18[i]+1;
	B_exp_18[i]=B_exp_18[i]+1;
}

void Right_Shift(int i)
{
	printf("\n----------------------------Right Shifting of Mantissa's------------------------------");
		
		//Aligning the Mantissa based on the number of Right shifts required and making the exponents same
		printf("\nTestbench %d",i+1);
		if(A_exp_18[i]<B_exp_18[i])
		{
			A_mantissa_18[i]=A_mantissa_18[i]>>shift;
			A_exp_18[i]=A_exp_18[i]+shift;
			Sum_sign_18[i]=B_sign_18[i];
		}
		else if(A_exp_18[i]>B_exp_18[i])
		{
			B_mantissa_18[i]=B_mantissa_18[i]>>shift;
			B_exp_18[i]=B_exp_18[i]+shift;
			Sum_sign_18[i]=A_sign_18[i];
		}
		else
		{
			A_mantissa_18[i]=A_mantissa_18[i];
			B_mantissa_18[i]=B_mantissa_18[i];
			Sum_sign_18[i]=A_sign_18[i];
		}
		Sum_exp_18[i]=A_exp_18[i];
}







void Align(int i)
{
	printf("\n--------------------------------------Alignment---------------------------------------");

	//Determining the smaller mantissa and taking it's 2's complement
	printf("\nTestbench %d",i+1);
	if(A_sign_18[i]!=B_sign_18[i])
	{
		if(A_mantissa_18[i]<B_mantissa_18[i])
		{
			A_mantissa_18[i]=(~A_mantissa_18[i])+1;
		}
		else
		{
			B_mantissa_18[i]=(~B_mantissa_18[i])+1;
		}
	}
	else
	{
		A_mantissa_18[i]=A_mantissa_18[i];
		B_mantissa_18[i]=B_mantissa_18[i];
	}
}

void Add(int i)
{	
	printf("\n--------------------------------------Addition----------------------------------------");

	//Addition of the Mantissa's
	printf("\nTestbench %d",i+1);
	Sum_mantissa_18[i]=A_mantissa_18[i]+B_mantissa_18[i];
	Sum_exp_18[i]=A_exp_18[i];
}

void Normalize(int i)
{
	printf("\n------------------------------------Normalization-------------------------------------");

	//Normalization of the Mantissa's
	printf("\nTestbench %d",i+1);
	mask2=0x7fffff;
		if(A_sign_18[i]!=B_sign_18[i])			//For Sign(A) != Sign(B)
		{
			if(A_sign_18[i]==0&B_sign_18[i]==1)		//For A=+ve & B=-ve
			{
				if(A_mantissa_18[i]==0)		//For A=0
				{
					Sum_mantissa_18[i]=Sum_mantissa_18[i]<<2;
					 x[i]=Sum_mantissa_18[i]&mask2;
					 x[i]=x[i]>>1;
					 Sum_exp_18[i]=Sum_exp_18[i]-1;
				printf("\nNormalized Value of Sum is %d %x %lx\n" , Sum_sign_18[i], Sum_exp_18[i], x[i]);
				}
				else					//For A !=0
				{
					Sum_mantissa_18[i]=Sum_mantissa_18[i]<<2;
					x[i]=Sum_mantissa_18[i]&mask2;
					Sum_exp_18[i]=Sum_exp_18[i]-2;
					printf("\nNormalized Value of Sum is %d %x %lx\n", Sum_sign_18[i], Sum_exp_18[i],x[i]);
				}
			}

			else						//For Sign(A) != Sign(B)
			{
				Sum_mantissa_18[i]=Sum_mantissa_18[i]<<2;
				x[i]=Sum_mantissa_18[i]&mask2;
				Sum_exp_18[i]=Sum_exp_18[i]-2;
				printf("\nNormalized Value of Sum is %d %x %lx\n", Sum_sign_18[i], Sum_exp_18[i] ,x[i]);
			}
		}
		else							//For Sign(A) = Sign(B)
		{
			if(A_sign_18[i]==0&B_sign_18[i]==0)		//Both A & B = +ve
			{
				if(A_mantissa_18[i]==0)		//For A=0
				{
					x[i]=Sum_mantissa_18[i]&mask2;
					Sum_exp_18[i]=Sum_exp_18[i]-1;
				}
				
                else					//For A != 0
				{
					x[i]=Sum_mantissa_18[i]&mask2;
				}
			}
			else if(A_sign_18[i]==1&B_sign_18[i]==1)	//Both A & B = -ve
			{
				Sum_mantissa_18[i]=Sum_mantissa_18[i]<<1;
				Sum_exp_18[i]=Sum_exp_18[i]-1;
				x[i]=Sum_mantissa_18[i]&mask2;
			}
		    else{}
			printf("\nNormalized Value of Sum is %d %x %lx\n", Sum_sign_18[i], Sum_exp_18[i], x[i]);
		}
}

