#include<stdio.h>
#include<conio.h>

void main()
  {
	int A_sign_18[6]={ 0 , 0 , 1 , 1 , 0 , 0},  		//Array of Signs of A
	        B_sign_18[6]={ 0 , 1 , 0 , 1 , 0 , 1},		//Array of Signs of B
	        Sum_sign_18[6],					//Array of Signs of Sum
	        A_exp_18[6]={ 0x85 , 0x85 , 0x84 , 0x87 , 0x00 , 0x00 }, //Array of Exponents of A
	        B_exp_18[6]={ 0x86 , 0x85 , 0x85 , 0x85 , 0x00 , 0x85 },	 //Array of Exponents of B
	        Sum_exp_18[6],						 //Array of Exponents of Sum
	        shift,						//Shifts required to align Mantissa
	        i=0;						//Index of elements of array

		     //Array of Mantissa's of A
    unsigned long int A_mantissa_18[6]={ 0x460000, 0x420000, 0x5c0000, 0x0c0000, 0x000000, 0x000000 },
		     //Array of Mantissa's of B
	                  B_mantissa_18[6]={ 0x320000, 0x1e0000, 0x160000, 0x0a0000, 0x000000, 0x620000 },
		     //Array of Mantissa's of Sum
		     Sum_mantissa_18[6],
		     //Masks for Normalization
		     mask1=0x400000,
		     mask2=0x7fffff,
		     //Array of Normalized Sum
		     x[6];
  
for(i=0;i<6;i++)   			//Loop to access each element of the array sequentially
	{
	
		printf("Testbench %d\n",i+1);  
		printf("A is %d %x %lx\n",A_sign_18[i],A_exp_18[i],A_mantissa_18[i]);
		printf("B is %d %x %lx\n",B_sign_18[i],B_exp_18[i],B_mantissa_18[i]);

printf("\n------------------------------Comparison of Exponent's--------------------------------");
		
		//Loop to determine the shift and the greater number

		if(A_exp_18[i]>B_exp_18[i])		
		{
			shift=A_exp_18[i]-B_exp_18[i];
			printf("\nA is greater\n");
		}
		else if(A_exp_18[i]<B_exp_18[i])
		{
			shift=B_exp_18[i]-A_exp_18[i];
			printf("\nB is greater\n");
		}

		else
		{
			shift=0;
		}

//Including the 1 from "1.m" into the Mantissa
		A_mantissa_18[i]=A_mantissa_18[i]>>1;
		B_mantissa_18[i]=B_mantissa_18[i]>>1;
		A_mantissa_18[i]=A_mantissa_18[i]|mask1;
		B_mantissa_18[i]=B_mantissa_18[i]|mask1;
		A_exp_18[i]+=1;
		B_exp_18[i]+=1;
		printf("\nExtra shifted no's are \n%d %x %lx\n%d %x %lx", A_sign_18[i], A_exp_18[i], A_mantissa_18[i], B_sign_18[i], B_exp_18[i], B_mantissa_18[i]);
		printf("\nNo. of shifts = %d\n",shift);

printf("\n----------------------------Right Shifting of Mantissa's------------------------------");

		//Aligning the Mantissa based on the number of shifts required and making the exponents same
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
		printf("\nAlligned no. A is%d %x %lx\n",A_sign_18[i],A_exp_18[i],A_mantissa_18[i]);
		printf("\nAlligned mantissa of B is %d %x %lx\n", B_sign_18[i], B_exp_18[i], B_mantissa_18[i]);


printf("\n--------------------------------------Alignment---------------------------------------");

		//Determining the smaller mantissa and taking it's 2's complement
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
			printf("\nMantissa's after 2's complement %lx %lx\n", A_mantissa_18[i], B_mantissa_18[i]);
		}

		else
		{
			A_mantissa_18[i]=A_mantissa_18[i];
			B_mantissa_18[i]=B_mantissa_18[i];
			printf("\n2's complement is not required as signs are same\n");
		}

printf("\n--------------------------------------Addition----------------------------------------");
	
		//Addition of the Mantissa's
		Sum_mantissa_18[i]=A_mantissa_18[i]+B_mantissa_18[i];
		printf("\nSum is %d %x %lx\n" , Sum_sign_18[i] ,Sum_exp_18[i],Sum_mantissa_18[i]);

printf("\n------------------------------------Normalization-------------------------------------");

		//Normalization of the Mantissa's
		
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
				printf("\nNormalized Value of Sum is %d %x %lx\n", Sum_sign_18[i], Sum_exp_18[i], x[i]);
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
			printf("\nNormalized Value of Sum is %d %x %lx\n", Sum_sign_18[i], Sum_exp_18[i],x[i]);
		}
	    getch();
	}
  }
