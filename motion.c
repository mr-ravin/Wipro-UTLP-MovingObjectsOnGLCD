#include "macros.h"
#include<ulk.h>
#include<string.h>
int main(void) PROGRAM_ENTRY;
/*
OBJECTIVE---- MOVING OBJECTS ON GLCD ,DISPLAYING CHOICE ON CLCD AND TAKING CHOICE FROM USER.

INSTITUTE NAME --- MEERUT INSTITUTE OF ENGINEERING AND TECHNOLOGY, Meerut-250005, Uttar Pradesh, INDIA.

GROUP 23--- RAVIN KUMAR (CS-B) [ mr.ravin_kumar@hotmail.com ], MEGHA SHARMA (EI), SHIKHAR KANSAL (EC-C).
*/
void assign()                                                                              	 //function to display data on CLCD.
{
	ulk_fpga_clcd_init();
	ulk_fpga_clcd_display_on();
	ulk_fpga_clcd_display_clear();
	ulk_fpga_clcd_cursor_home();
	ulk_fpga_clcd_display_string("ENTER UR CHOICE: 1.Square 2.Triangle 3.Rectangle");       //choices shown on CLCD.
	//ulk_fpga_clcd_shift_left(60);
	ulk_fpga_clcd_display_off();
}


void square(int t)
{

	int i,j;
    unsigned int *x=0x80500000;
	for(i=0;i<240;i++)
	{
		for(j=0;j<320;j++)
		{
		 	if(i<t)
		 	{
				 *x=0xffffff;
				 x++;

		 	}
			 else
			 {												//condition for square.
				if(((i==t)||(i==(t+100)))&&((j>=t)&&(j<=(t+100))))
				{
					*x=0xff0000;
					x++;
				}
				else if(((j==t)||(j==(t+100)))&&((i<(t+100))))						//condition for square.
				{
					*x=0xff0000;
					x++;
				}
				else
				{
					*x=0xffffff;
					x++;
				}
			 }
	
	         }
	}
}

void rectangle(int t)
{
	int i,j;
	unsigned int *x=0x80500000;
	for(i=0;i<240;i++)
	{
		for(j=0;j<320;j++)
		{  if(i==0)
		   {
			*x=0xffffff;
			x++;
		    }



		   else
		   {
		     	if(((i==t)||(i==(t+50)))&&((j>=t)&&(j<=(t+100))))				//condition for rectangle.
			    {
					*x=0xff0000;
					x++;
				}
				else if(((j==t)||(j==(t+100)))&&((i<(t+50))&&(i>=t))) 			//condition for rectangle.
				{
					*x=0xff0000;
					x++;
				}
	    		        else
				{
					*x=0xffffff;
					x++;
				}
       		    }
 
	      }
	}
}

void triangle(int t)
{
	int i,j;
	unsigned int *x=0x80500000;
	for(i=0;i<240;i++)
	{
		for(j=0;j<320;j++)
		{
		    if((i==100)&&((j>=(t-i))&&(j<=t+i)))			//condition for triangle base.
		    {
		    	*x=0xff0000;
		    	x++;
		    }
			 else if((i==1)&&(j==t))	 			//condition for triangle initial point.
		    {
		     *x=0xff0000;
		     x++;
		    }
			else if(((j==(t-i))||(j==(t+i)))&&((i<100)&&(i>0)))	 //condition for triangle remaining edges.
			{
				*x=0xff0000;
				x++;
			}

			else
			{
				*x=0xffffff;
				x++;
			}
		}
	}
}


void keypressed()							//function to take user choice.
 {
	int i,k,t=50; 		//here with the change in the value of t and i the dimensions of objects changes which provide them motion.
	ulk_scanf_hex(&k);
	switch(k)
	{
	case 1:
            	ulk_fpga_clcd_init();					//case 1 : square.
             	ulk_fpga_clcd_display_on();
             	ulk_fpga_clcd_display_clear();
		        ulk_fpga_clcd_display_string("Square selected ");
              for(i=0;i<19;i++)
              {
	    	    square(t-i);            //dimension of square depends on t-i and i keeps on changing which provide translation to square.
                ulk_proc_delay(500000);
               }
	         	break;
	case 2:
            	ulk_fpga_clcd_init();					//case 2 : triangle.
             	ulk_fpga_clcd_display_on();
             	ulk_fpga_clcd_display_clear();
		        ulk_fpga_clcd_display_string("Triangle selected ");
		for(i=0;i<19;i++)
              {
	    	    triangle(t-i);	//dimension of triangle depends on t-i and i keeps on changing which provide translation to triangle.
                ulk_proc_delay(500000);
               }
                 break;
	case 3:
            	ulk_fpga_clcd_init();					//case 3 : rectangle.
             	ulk_fpga_clcd_display_on();
             	ulk_fpga_clcd_display_clear();
		        ulk_fpga_clcd_display_string("Rectangle selected ");
		         for(i=0;i<19;i++)
              {
	    	    rectangle(t-i);	//dimension of rectangle depends on t-i and i keeps on changing which provide translation to rectangle.
                	ulk_proc_delay(500000);
               }
                  break;
	default:
            	ulk_fpga_clcd_init();
             	ulk_fpga_clcd_display_on();
             	ulk_fpga_clcd_display_clear();
             	ulk_cpanel_printf("%d",k);
		        ulk_fpga_clcd_display_string("wrong choice ");
			}
   ulk_fpga_clcd_display_off();
 }

int main()				//main function
{
 assign();				//display choice
 keypressed();			//taking choice from user and displaying moving objects on GLCD
 return 0;
}

