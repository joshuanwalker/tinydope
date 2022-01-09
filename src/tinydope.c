// WRITTEN BY: Michael Brown
// October 2002
// EMAIL: brown12321@hotmail.com

//This is the first dopewars game I have ever made. It is real addictive so 
//give it a try. Please email me if you find any bugs in the game. I will
//email you the patch for it within a couple of days....

//If you need to use snippets of this code please email me for permission!
//I will have to be credited in your program for the snippet that is used.

//ENJOY!!:)~

                       /////**BEST PLAYED IN FULL SCREEN!!**\\\\\\\/

#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>




//Main structure to hold most of the games information
struct STATS
{
	int days;
	int life;
	long money;
	long bank;
	long debt;
	int coat;
	int max_coat;
	int drugs[6];
	char *location; //Pointer used to point to area[] <-- Global array for jet locations!
};

//Structure to old hold what the user payed for the drugs....
//I put this in here so the when the user jets to another location and he wants to
//sell something. He will know what he payed for it so he/she doesn't loose money
struct LAST
{
	int d0;
	int d1;
	int d2;
	int d3;
	int d4;
	int d5;
};

//Structure to hold the records of the high scores.
struct High
{
	char Name[20];
	int HS;
};

//GLOBAL DECLARATIONS
char *area[10]; //Locations are stored here and accessed with *loocation in STATS structure
int drug[6]; // Global int to hold how much of each drug selling for a each location.

char str[25]; //Temp to store the user city and state.

//FUNCTION PROTOTYPES

int getnum();
void getstring();
int High_Low();
void Cities();   //Prints cities that are currently in the game
int JAIL();  //Draws the Jail.
int NO_POC(); //Not enouph puckets message
int Bank(long M, long B); // Draws Bank Menu
int Bookie(); //Draws Bookie Brown's Menu
//Rand_Event()
//Below--> char loc[] is takes in the current location the user is at
		 //*c takes how many pockets the user has
		 //*m is the money the user currently has on him/her
		 //d[] is the drugs
         //*mc is for the max allowed pockets
		 //*l is the life points
int Rand_Event(char loc[], int *c, long *m, int d[], int *mc, int *l);



//******************************** MAIN ****************************************
int main()
{
	int i;//loop variable
	int z;// menu variable
	int y;// menu and drug units variable.
	int j=0; //loop variable
	int choice;
	long a; //variable used for money: bank and debt.
	
	
	
	//declaring and initializing c1[] elements 1-8
	//element area[0] is used for the city the user is in.
	char *c1[] = {
				 "Orlando, FL",            // = area[1]
				 "Las Vegas, NV",          // = area[2]
			     "Amsterdam, Netherlands", // = area[3]
				 "Dublin, Ireland",        // = area[4]
				 "Washington D.C.",        // = area[5]
				 "Miami, FL",              // = area[6]
				 "Los Angeles, CA",        // = area[7]
				 "New York, NY",		   // = area[8]
				};
	//Gaining access to the structures I need to use
	struct STATS stats;
	struct LAST old;
	
	//For random number generator
	srand((int)time(NULL));
	


	
	//Below sets elements 1-9 of the *area[10] array to city's above. 
	//array *area[0] is being reserved for the user to enter their
	//own city and state...
//  area[0] --> saved for user input
	area[1] = c1[0];
	area[2] = c1[1];
	area[3] = c1[2];
	area[4] = c1[3];
	area[5] = c1[4];
	area[6] = c1[5];
	area[7] = c1[6];
	area[8] = c1[7];

	//Setting all elements of the drug array to 0.....
	for(i=0; i<=5; i++)
		stats.drugs[i] = 0;

	//Setting all old drugs values to 0;
	old.d0 = 0;
	old.d1 = 0;
	old.d2 = 0;
	old.d3 = 0;
	old.d4 = 0;
	old.d5 = 0;

	stats.life = 10; // 10 life points.
	stats.days = 1;  ///Day # 1 (start day)
	stats.debt = 10000; //Initial Loan from Bookie
	stats.coat = 0;     //Sets your coat to 0 becuase you are not carrying anything yet.
	stats.max_coat = 100; //Max you can carry
	stats.money = 10000; //Loan money you start the game with
	stats.bank = 0;  //Initial banking account total

	High_Low(); //Funtion to print out the High and low prices of the drugs....
	Cities();
	printf("\n\n\tEnter your City and State:> ");
	getstring();
	
	area[0] = str; //stores str in area[0] --> which is the start city
	stats.location = area[0]; //Start location = user city and state-->(area[0])
	//rec.Name = name;
	
	
	//Filling each elemnet with initial drug values for start city.
	drug[0] = rand()%10000;
	drug[1] = rand()%1000;
	drug[2] = rand()%100;
	drug[3] = rand()%1000;
	drug[4] = rand()%10000;
	drug[5] = rand()%10000;

MB:
	choice = 0;
	
	
	//If the 29th day
	if(stats.days == 29)
	{
		
		printf("One more day left. Hope your debt is paid off!\n");
		
	}
	
	//If it's the last day
	if(stats.days == 30)
	{
		
		printf("This is your last day.....\n");
		
	}
	//THe loop below is used if you get busted going into the 30th day. I have to have this test
	//here becuase the day increments twice if you go to jail and the day would be 31. There was
	//no Test case for greater than 30 so here it is and it adds the core to the record.
	if(stats.days > 30)
	{
		y = 0;
		a = 0;
		
		if(stats.debt == 0 || stats.money - stats.debt >= 0)
		{
			
			
		    a = (stats.money + stats.bank) - stats.debt; // temp int to add score to record.
			y = a;
		
			//Add(&y); // passing total money to add funtion
		
			
			printf("\n\t\t");
			for(i=0;i<=40;i++)
				putchar(220);
			printf("\n\n\t\tThis is how much money you ended up with!\n");
			printf("\t\t");
			printf("\n");
			printf("\t\tMoney: $%d\n\t\t", a);
			for(i=0;i<=40;i++)
			putchar(220);
		}
		//if debt != 0 or money - debt < 0
		if(stats.debt != 0 && stats.money - stats.debt < 0)
		{
			
			printf("\t");
			for(i=0;i<=55;i++)
				putchar(220);
			printf("\n\n\tBookie Brown and his boys fitted you for cement shoes!.\n");
			printf("\tNow your swimming with the fish! :)~\n\n");
			printf("\tDebt:  $%d\n", stats.debt);
			printf("\t");
			for(i=0;i<=55;i++)
				putchar(220);
		}
		printf("\n\nThanks for Playing\n\n");
		
		exit(0);
	}
		
	
	printf("\n");
	printf("Life: ");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);// Changing color of text
	putchar(177);
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // Changing color of text
	for(i=2;i<=stats.life;i++)
		putchar(177);
	printf("\n\n");
	printf("Current Location: %s\n\n", stats.location); // Printing current location
	printf("Money: $%d\n\n", stats.money);  //Printing your money that you are carrying.	
	printf("\t\t\t\t Day %d of 30\n", stats.days);  // Prints which day your on.
		
	//drawing top of menu box
	printf("\t\t");
	putchar(213);
	for(i=0;i<=20/*45*/;i++)
		putchar(205);
	putchar(209);
	for(i=1; i<=24;i++)
		putchar(205);
	putchar(184);	
	printf("\n");
	
	//Main 2 column headers
	printf("\t\t");
	putchar(179);
	printf("      MAIN MENU      ");
	putchar(179);
	printf("     COAT  %-2.3d/%-2.3d      ", stats.coat, stats.max_coat);
	putchar(179);
	printf("\n");

	//Drawing line to finish boxing in column headers
	printf("\t\t");
	putchar(198);
	for(i=0;i<=20;i++)
		putchar(205);
	putchar(216);
	for(i=1;i<=24;i++)
		putchar(205);
	putchar(181);
	printf("\n");

	//Drawing main menu
	printf("\t\t");
	putchar(179);
	printf("[1] Buy Drugs        ");
	putchar(179);
	printf(" Coke:     %-13d", stats.drugs[0]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[2] Sell Drugs       ");
	putchar(179);
	printf(" Weed:     %-13d", stats.drugs[1]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[3] Jet              ");
	putchar(179);
	printf(" Ecstacy:  %-13d", stats.drugs[2]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[4] Bank             ");
	putchar(179);
	printf(" Acid:     %-13d", stats.drugs[3]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[5] Bookie Brown     ");
	putchar(179);
	printf(" Crack:    %-13d", stats.drugs[4]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[6] High Scores      ");
	putchar(179);
	printf(" Heroin:   %-13d", stats.drugs[5]);
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(179);
	printf("[7] EXIT             ");
	putchar(179);
	printf("                        ");
	putchar(179);
	printf("\n");
	printf("\t\t");
	putchar(212);
	for(i=0;i<=20;i++)
		putchar(205);
	putchar(207);
	for(i=1;i<=24;i++)
		putchar(205);
	putchar(190);
	printf("\n\n\tEnter Choice ");
	putchar(175);
	printf(" ");

	choice = getnum();
	
	///If the user selects to buy drugs
	if(choice == 1)
	{
B:		y = 0;// Clear back to 0
		z = 0;
		
		//Printing menu for the drugs that are for sale and their prices
		printf("\t\t\t    ");
		putchar(213);
		for(i=0;i<20;i++)
			putchar(205);
		putchar(184);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("   DRUGS FOR SALE   ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(198);
		for(i=0;i<20;i++)
			putchar(205);
		putchar(181);
		printf("\n");
		//For coke
		printf("\t\t\t    ");
		putchar(179);
		printf(" [1] Coke:    $%-4d ", drug[0]); 
		putchar(179);
		printf("\n");
		//For weed
		printf("\t\t\t    ");
		putchar(179);
		printf(" [2] Weed:    $%-4d ", drug[1]);
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf(" [3] Ecstacy: $%-4d ", drug[2]);
		putchar(179);
		printf("\n");
		//FOr Acid
		printf("\t\t\t    ");
		putchar(179);
		printf(" [4] Acid:    $%-4d ", drug[3]);
		putchar(179);
		printf("\n");
		//For Crack
		printf("\t\t\t    ");
		putchar(179);
		printf(" [5] Crack:   $%-4d ", drug[4]);
		putchar(179);
		printf("\n");
		//FOr Herioin
		printf("\t\t\t    ");
		putchar(179);
		printf(" [6] Heroin:  $%-4d ", drug[5]);
		putchar(179);
		printf("\n");
		//Back to main menu
		printf("\t\t\t    ");
		putchar(179);
		printf(" [7] Back to menu   ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(212);
		for(i=0;i<20;i++)
			putchar(205);
		putchar(190);
		printf("\n");
		printf("\t\t\t  Money to spend:  $%d", stats.money);
		printf("\n\nWhat do you want to buy?> ");
					
		z = getnum();
		
		if(z == 1)
		{ 
			
			//Testing to see if drug is available
			if(drug[0] == 0)
			{
				printf("\n\nCoke is Dry!\n\n");
				
				goto B;
			}

			y = 0;
			printf("\n\nHow many units of coke:> ");
			y = getnum();
			
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}
			//Testing to make sure you have enough money for the drugs.
			if((y * drug[0]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d0 = drug[0]; //storing price payed for drugs
				stats.drugs[0] += y; //Adding units to coke
				stats.money -= y * drug[0]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat

				//Making sure you have enough pckets
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y; //subtracting units user just inputed
					stats.money += y * drug[0]; //Giving money back to user
					stats.drugs[0] -= y; //subtracting units baught from coke total.
					
					goto B;
				}	
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}		
			
		}
		if(z == 2)
		{

			//Testing to see if drug is available
			if(drug[1] == 0)
			{
				printf("\n\nWeed is Dry!\n\n");
				
				goto B;
			}

			y = 0;
			printf("\n\nHow many units of weed:> ");
			y = getnum();
			
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}
			
			if((y * drug[1]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d1 = drug[1]; //storing price payed for drug
				stats.drugs[1] += y;
				stats.money -= y * drug[1]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y;
					stats.money += y * drug[1];
					stats.drugs[1] -= y;
					
					goto B;
				}			
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}			
			
		}
		if(z == 3)
		{

			//Testing to see if drug is available
			if(drug[2] == 0)
			{
				printf("\n\nEcstacy is Dry!\n\n");
				
				goto B;
			}

			y = 0;
			printf("\n\nHow many units of ecstacy:> ");			
			y = getnum();
			
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}
			if((y * drug[2]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d2 = drug[2]; //storing price payed for drug
				stats.drugs[2] += y;
				stats.money -= y * drug[2]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y;
					stats.money += y * drug[2];
					stats.drugs[2] -= y;
					
					goto B;
				}				
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}		
			
		}
		if(z == 4)
		{

			//Testing to see if drug is available
			if(drug[3] == 0)
			{
				printf("\n\nAcid is Dry!\n\n");
				
				goto B;
			}

			y = 0;
			printf("\n\nHow many units of acid:> ");
			y = getnum();
		
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}

			if((y * drug[3]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d3 = drug[3]; //storing price payed
				stats.drugs[3] += y;
				stats.money -= y * drug[3]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y;
					stats.money += y * drug[3];
					stats.drugs[3] -= y;
					
					goto B;
				}				
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}
			
		}
		if(z == 5)
		{

			//Testing to see if drug is available
			if(drug[4] == 0)
			{
				printf("\n\nCrack is Dry!\n\n");
				
				goto B;
			}

			y = 0;
			printf("\n\nHow many units of crack:> ");
			y = getnum();
				
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}

			if((y * drug[4]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d4 = drug[4]; // storing price payed for drug
				stats.drugs[4] += y;
				stats.money -= y * drug[4]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y;
					stats.money += y * drug[4];
					stats.drugs[4] -= y;
					
					goto B;
				}
				
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}
						
		}
		if(z == 6)
		{
			printf("6");

			//Testing to see if drug is available
			if(drug[5] == 0)
			{
				printf("\n\nHeroin is Dry!\n\n");
				
				goto B;
			}

			
			y=0;

			printf("\n\nHow many units of heroin:> ");
			y = getnum();
			
			if(y > 900)
			{
				printf("INVLAID AMOUNT\n\n");
				
				goto B;
			}
			
			if((y * drug[5]) < stats.money)
			{
				if(y == 0)
					goto B;
				old.d5 = drug[5]; // storing price payed
				stats.drugs[5] += y;
				stats.money -= y * drug[5]; //subtracting how much spent on drugs
				stats.coat += y; //Adding drugs to coat
				if(stats.max_coat < stats.coat)
				{
					printf("Not enough pockets. Go buy some!\n\n");
					stats.coat -= y;
					stats.money += y * drug[5];
					stats.drugs[5] -= y;
					
					goto B;
				}
				
					
			}
			else
			{
				printf("NOT ENOUGH MONEY!\n\n");
				
				goto B;
			}
			
			
		}
		if(z == 7)
			goto MB;

		if(z < 1 || z > 7)
		{
			printf("\n\nINVALID INPUT\n\n");
			
			goto B;
		}		
	
		printf("\nDo you want to buy more drugs? (y or n):> ");
		y =getchar();
		if(y == 'y' || y == 'Y')
			goto B;
		else
			goto MB;
	
	}
	/// If user selects to sell drugs
	if(choice == 2)
	{
S:
		z = 0;
		y = 0;
		

		//Drawing sell menu with current prices and last payed prices
		printf("\n\t      ");
		putchar(213);
		for(i=0;i<=20;i++)
			putchar(205);
		putchar(209);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(209);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(184);
		printf("\n");
		
		printf("\t      ");
		putchar(179);
		printf("      YOUR COAT      ");
		putchar(179);
		printf(" SELL PRICES ");
		putchar(179);
		printf(" LAST PAYED  ");
		putchar(179);
		printf("\n");
		
		printf("\t      ");
		putchar(198);
		for(i=0;i<=20;i++)
			putchar(205);
		putchar(216);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(216);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(181);
		printf("\n");
		
		//For Coke
		printf("\t      ");
		putchar(179);
		printf(" [1] Coke:     %-3d   ",stats.drugs[0]);
		putchar(179);
		printf("    $%-8d", drug[0]);
		putchar(179);
		printf("    $%-8d", old.d0);
		putchar(179);
		printf("\n");
		//For Weed
		printf("\t      ");
		putchar(179);
		printf(" [2] Weed:     %-3d   ",stats.drugs[1]);
		putchar(179);
		printf("    $%-8d", drug[1]);
		putchar(179);
		printf("    $%-8d", old.d1);
		putchar(179);
		printf("\n");
		//For Ecstacy
		printf("\t      ");
		putchar(179);
		printf(" [3] Ecstacy:  %-3d   ",stats.drugs[2]);
		putchar(179);
		printf("    $%-8d", drug[2]);
		putchar(179);
		printf("    $%-8d", old.d2);
		putchar(179);
		printf("\n");
		//For Acid
		printf("\t      ");
		putchar(179);
		printf(" [4] Acid:     %-3d   ",stats.drugs[3]);
		putchar(179);
		printf("    $%-8d", drug[3]);
		putchar(179);
		printf("    $%-8d", old.d3);
		putchar(179);
		printf("\n");
		//For Crack
		printf("\t      ");
		putchar(179);
		printf(" [5] Crack:    %-3d   ",stats.drugs[4]);
		putchar(179);
		printf("    $%-8d", drug[4]);
		putchar(179);
		printf("    $%-8d", old.d4);
		putchar(179);
		printf("\n");
		//For Heroin
		printf("\t      ");
		putchar(179);
		printf(" [6] Heroin:   %-3d   ",stats.drugs[5]);
		putchar(179);
		printf("    $%-8d", drug[5]);
		putchar(179);
		printf("    $%-8d", old.d5);
		putchar(179);
		printf("\n");
		//For return to main menu
		printf("\t      ");
		putchar(179);
		printf(" [7] Return to menu  ");
		putchar(179);
		printf("             ");
		putchar(179);
		printf("             ");
		putchar(179);
		printf("\n");

		//Bottom Line
		printf("\t      ");
		putchar(212);
		for(i=0;i<=20;i++)
			putchar(205);
		putchar(207);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(207);
		for(i=0;i<=12;i++)
			putchar(205);
		putchar(190);
		printf("\n\n");
		
		printf("What do you want to sell?> ");
		//scanf("%d", &choice);
		z = getnum();

		if(z == 1)
		{

			//Testing to see if user has coke to sell
			if(stats.drugs[0] == 0)
			{
				printf("\n\nYou don't have any coke to sell!\n\n");
				
				goto S;
			}
			
			//Testing to see if drug is available
			if(drug[0] == 0)
			{
				printf("\n\nCoke is Dry!\n\n");
				
				goto S;
			}

			y = 0;
			printf("\n\nHow many units of coke do you want to sell:> ");
			y = getnum();
			if(y > 900)
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}
			if(y > stats.drugs[0])
			{
				printf("\n\nYou don't have %d units of coke to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[0]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[0] -= y;
				stats.money += (y * drug[0]);
			}
			if(stats.drugs[0] == 0)
					old.d0 = 0;
		}
		if(z == 2)
		{

			//Testing to see if drug is available
			if(drug[1] == 0)
			{
				printf("\n\nWeed is Dry!\n\n");
				
				goto S;
			}
			
			//Testing to see if user has any to sell
			if(stats.drugs[1] == 0)
			{
				printf("\n\nYou don't have any weed to sell!\n\n");
				
				goto S;
			}
			y = 0;
			printf("\n\nHow many units of weed do you want to sell:> ");
			y = getnum();
			if(y > 900)
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}
			if(y > stats.drugs[1])
			{
				printf("\n\nYou don't have %d units of weed to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[1]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[1] -= y;
				stats.money += (y * drug[1]);
			}
			if(stats.drugs[1] == 0)
				old.d1 = 0;
		}
		if(z == 3)
		{


			//Testing to see if drug is available
			if(drug[2] == 0)
			{
				printf("\n\nEcstacy is Dry!\n\n");
				
				goto S;
			}

			//Testing to see if the user has any to sell
			if(stats.drugs[2] == 0)
			{
				printf("\n\nYou don't have any exstacy to sell!\n\n");
				
				goto S;
			}
			y = 0;
			printf("\n\nHow many units exstacy do you want to sell:> ");
			y = getnum();
			if(y > 900)
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}
			if(y > stats.drugs[2])
			{
				printf("\n\nYou don't have %d units of exstacy to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[2]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[2] -= y;
				stats.money += (y * drug[2]);
			}
			if(stats.drugs[2] == 0)
				old.d2 = 0;
		}
		if(z == 4)
		{

			//Testing to see if drug is available
			if(drug[3] == 0)
			{
				printf("\n\nAcid is Dry!\n\n");
				
				goto S;
			}

			if(stats.drugs[3] == 0)
			{
				printf("\n\nYou don't have any acid to sell!\n\n");
				
				goto S;
			}
			y = 0;
			printf("\n\nHow many units of acid do you want to sell:> ");
			y = getnum();
			if(y > 900 )
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}	
			if(y > stats.drugs[3])
			{
				printf("\n\nYou don't have %d units of acid to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[3]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[3] -= y;
				stats.money += (y * drug[3]);
			}
			if(stats.drugs[3] == 0)
				old.d3 = 0;
		}
		if(z == 5)
		{


			//Testing to see if drug is available
			if(drug[4] == 0)
			{
				printf("\n\nCrack is Dry!\n\n");
				
				goto S;
			}

			if(stats.drugs[4] == 0)
			{
				printf("\n\nYou don't have any crack to sell!\n\n");
				
				goto S;
			}
			y = 0;
			printf("\n\nHow many units of crack do you want to sell:> ");
			y = getnum();
			if(y > 900 )
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}	
			if(y > stats.drugs[4])
			{
				printf("\n\nYou don't have %d units of crack to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[4]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[4] -= y;
				stats.money += (y * drug[4]);
			}
			if(stats.drugs[4] == 0)
				old.d4 = 0;
		}
		if(z == 6)
		{

			//Testing to see if drug is available
			if(drug[5] == 0)
			{
				printf("\n\nHeroin is Dry!\n\n");
				
				goto S;
			}

			if(stats.drugs[5] == 0)
			{
				printf("\n\nYou don't have any heroin to sell!\n\n");
				
				goto S;
			}
			y = 0;
			printf("\n\nHow many units of heroin do you want to sell:> ");
			y = getnum();
			if(y > 900 )
			{
				printf("\n\nINVALID AMOUNT!\n\n");
				
				goto S;
			}
			if(y > stats.drugs[5])
			{
				printf("\n\nYou don't have %d units of heroin to sell.",y);
				printf(" You only have %d units to sell.\n\n", stats.drugs[5]);
				
				goto S;
			}
			else
			{
				stats.coat -= y;
				stats.drugs[5] -= y;
				stats.money += (y * drug[5]);
			}
			if(stats.drugs[5]  == 0)
				old.d5 = 0;
			
		}
		if(z == 7)
			goto MB;
		if(z < 1 || z > 7)
		{
			printf("\n\nINVALID CHOICE\n\n");
			
			goto S;
		}
		
		printf("\nDo you want to sell anymore: (y/n)> ");
		y = getchar();
		if(y == 'y' || y == 'Y')
			goto S;
		else 
			goto MB;
		
	}

	///If the user selects to jet to a different city
	if(choice == 3)
	{
	    //Testing to see if money == 0 and bank > 0)
		if(stats.days < 30)
		{
			if(stats.money == 0 && stats.bank != 0)
			{
				
				printf("\n\n\t");
				putchar(218);
				for(i=0;i<61;i++)
					putchar(196);
				putchar(191);
				printf("\n");
				printf("\t");
				putchar(179);
				printf("You need to have some money on you to travel to another city!");
				putchar(179);
				printf("\n");
				printf("\t");
				putchar(179);
				printf("It looks like you have money in the bank: $%d        ", stats.bank);
				putchar(179);
				printf("\n");
				printf("      ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<61;i++)
					putchar(196);
				putchar(217);
				printf("\n");
				printf("      ");
				putchar(179);
				printf("\n");
				printf("      ");
				putchar(219);
				printf("\n\n\n");
				
				goto MB;
			}
			//Testing to see if money == 0 and bank == 0)
			if(stats.money == 0 && stats.bank == 0)
			{
				
				printf("\n\n\t");
				putchar(218);
				for(i=0;i<61;i++)
					putchar(196);
				putchar(191);
				printf("\n");
				printf("\t");
				putchar(179);
				printf("You need to have some money on you to travel to another city!");
				putchar(179);
				printf("\n");
				printf("\t");
				putchar(179);
				printf("It looks like you don't even have money in your bank account!");
				putchar(179);
				printf("\n");
				printf("\t");
				putchar(179);
				printf("Go see Bookie Brown!                                         ");
				putchar(179);
				printf("\n");
				printf("      ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<61;i++)
					putchar(196);
				putchar(217);
				printf("\n");
				printf("      ");
				putchar(179);
				printf("\n");
				printf("      ");
				putchar(219);
				printf("\n\n\n");
				
				goto MB;
			}
		}
		
		//Checking to see if it is day 30..
		if(stats.days == 30)
		{
			y = 0;
			a = 0;
			
			if(stats.debt == 0 || stats.money - stats.debt >= 0)
			{
				
				
				a = (stats.money + stats.bank) - stats.debt; // temp int to add score to record.
				y = a;
				
				//Add(&y); // passing total money to add funtion
				
				
				printf("\n\t\t");
				for(i=0;i<=40;i++)
					putchar(220);
				printf("\n\n\t\tThis is how much money you ended up with!\n");
				printf("\t\t");
				printf("\n");
				printf("\t\tMoney: $%d\n\t\t", a);
				for(i=0;i<=40;i++)
					putchar(220);
			}
			
			//if debt != 0 or money - debt < 0
			if(stats.debt != 0 && stats.money - stats.debt < 0)
			{
				
				printf("\t");
				for(i=0;i<=55;i++)
					putchar(220);
				printf("\n\n\tBookie Brown and his boys fitted you for cement shoes!.\n");
				printf("\tNow your swimming with the fish! :)~\n\n");
				printf("\tDebt:  $%d\n", stats.debt);
				printf("\t");
				for(i=0;i<=55;i++)
					putchar(220);
			}
			printf("\n\nThanks for Playing\n\n");
			
			
			y = 0;
			//Asking if user wants to play again...
			printf("\n\nWant to play again? (y/n):> ");
			y = getchar();
			if(y == 'y' || y == 'Y')//getch() == 'y' || getch() == 'Y')
			{
			//Setting all elements of the drug array to 0.....
				for(i=0; i<=5; i++)
					stats.drugs[i] = 0;

				//Setting all old drugs values to 0;
				old.d0 = 0;
				old.d1 = 0;
				old.d2 = 0;
				old.d3 = 0;
				old.d4 = 0;
				old.d5 = 0;

				stats.life = 10; // 10 life points.
				stats.days = 1;  ///Day # 1 (start day)
				stats.debt = 10000; //Initial Loan from Bookie
				stats.coat = 0;     //Sets your coat to 0 becuase you are not carrying anything yet.
				stats.max_coat = 100; //Max you can carry
				stats.money = 10000; //Loan money you start the game with
				stats.bank = 0;  //Initial banking account total
				stats.location = area[0]; //Start location = Daytona Beach, FL (area[0])
				High_Low(); //Funtion to print out the High and low prices of the drugs....

				drug[0] = rand()%10000;
				drug[1] = rand()%1000;
				drug[2] = rand()%100;
				drug[3] = rand()%1000;
				drug[4] = rand()%10000;
				drug[5] = rand()%10000;
				goto MB;
			}
			else
			{
				putchar(y);
				printf("\n\n\t\t\tThanks for Playing\n\n");
				exit(0);
			}
		}
J:		
		y = 0;
		
		printf("\nCurrent Location: %s\n\n", stats.location);
		
		//Drawing Jet menu
		printf("\t\t\t");
		putchar(213);
		for(i=0;i<27;i++)
			putchar(205);
		putchar(184);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("         LOCATIONS         ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(198);
		for(i=0;i<27;i++)
			putchar(205);
		putchar(181);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[1] %-23s", area[0]);
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[2] Orlando, FL            ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[3] Las Vegas, NV          ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[4] Amsterdam, Netherlands ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[5] Dublin, Ireland        ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[6] Washington D.C.        ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[7] Miami, FL              ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[8] Los Angeles, CA        ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[9] New York, NY           ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(179);
		printf("[0] Back to menu           ");
		putchar(179);
		printf("\n");
		printf("\t\t\t");
		putchar(212);
		for(i=0;i<27;i++)
			putchar(205);
		putchar(190);
		printf("\n");
		printf("\nEnter destination:> ");
		y = getnum();
				
		drug[0] = rand()%10000;
		drug[1] = rand()%1000;
		drug[2] = rand()%100;
		drug[3] = rand()%1000;
		drug[4] = rand()%10000;
		drug[5] = rand()%10000;

		if(y == 1)
		{
			if(stats.location == area[0])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}				
			if(stats.location != area[0])
			{
				stats.location = area[0];
				stats.debt += ((stats.debt/100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank/100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				
				//This if state test to see if the coat and money came back as 0.
				//If it did, this means that they were busted by the cops so I wanted to
				//set the old drugs values back to 0. 
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();    //Jail Cell Screen
					stats.days++; //incrementing day for the time spent in jail
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++; //Incrementing day after day spent in jail
				goto MB;
			}				
		}

		if(y == 2)
		{
			if(stats.location == area[1])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[1])
			{
				stats.location = area[1];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 3)
		{
			
			if(stats.location == area[2])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[2])
			{
				stats.location = area[2];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 4)
		{
			if(stats.location == area[3])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[3])
			{
				stats.location = area[3];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 5)
		{
			if(stats.location == area[4])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[4])
			{
				stats.location = area[4];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 6)
		{
			if(stats.location == area[5])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[5])
			{
				stats.location = area[5];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y ==7 )
		{
			if(stats.location == area[6])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[6])
			{
				stats.location = area[6];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 8)
		{
			if(stats.location == area[7])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[7])
			{
				stats.location = area[7];
				
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}
		if(y == 9)
		{
			if(stats.location == area[8])
			{
				printf("\n\nAlready in %s\n\n", stats.location);
				
				goto J;
			}
			if(stats.location != area[8])
			{
				stats.location = area[8];
				stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
				stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				Rand_Event(stats.location, &stats.coat, &stats.money, stats.drugs, &stats.max_coat,&stats.life);
				if(stats.money == 0 && stats.coat == 0)
				{
					old.d0 = 0;
					old.d1 = 0;
					old.d2 = 0;
					old.d3 = 0;
					old.d4 = 0;
					old.d5 = 0;
					JAIL();
					stats.days++;
					stats.debt += ((stats.debt / 100) * 40); // intrest per day debt isn't paid
					stats.bank += ((stats.bank / 100) * 15); //interest per day for bank account.
				}
				stats.days++;
				goto MB;
			}
			
		}		
		if(y ==0) 
			goto MB;
		
		//Testing for invalid input
		if(y <0 || y >9)
		{
			putchar(y);
			printf("\n\nINVALID CHOICE\n\n\n\n");
			
			goto J;
		}		
	}

	///If user selects to go to the bank
	if(choice == 4)
	{
BK:		//Setting variable back to 0.
		y = 0;
		a = 0;
		choice = 0;

		
		Bank(stats.money, stats.bank);//Starting to draw the Bank Menu
		printf("Choose one:> ");
		choice = getnum();
		
		//Start testing inout from user to see what they want to do
		if(choice == 1)
		{
			printf("\n\nHow much do you want to deposit:> ");
			a=getnum();

			//Testing input
			if(a > stats.money)
			{
				printf("\n\nYou don't have $%d to deposit!\n\n", a);
				
				goto BK;
			}				
			stats.bank += a;
			stats.money -= a;
		}
		if(choice == 2)
		{
			printf("\n\nHow much do you want to withdraw:> ");
			a = getnum();

			//Testing input
			if(a > stats.bank)
			{
				printf("\n\nYou don't have $%d to withdraw!\n\n", a);
				
				goto BK;
			}
			stats.bank -= a;
			stats.money += a;
		}
		if(choice ==3 )
			goto MB;

		//Testing Bank menu choices
		if(choice < 1 || choice >3)
		{
			printf("\n\nINVALID CHOICE\n\n\n\n\n\n");
			
			goto BK;
		}
		goto MB;
	}

	//If user selects to see the bookie*********************************************
	//BOOKIE BROWN
	if(choice == 5)
	{
BB:
		y = 0;
		a = 0;
		choice = 0;
		

		Bookie();//Drawing Bookie menu.
	
		printf("\t\t\t  Current debt: $%d\n\n", stats.debt);
		printf("\t\t\t  Money on you: $%d\n\n", stats.money);
		printf("Choose one:> ");
		y = getnum();
	
		if(y ==1 )
		{
			if(stats.debt == 0)
			{
				printf("\nYou don't owe me any money!\n\n");
				
				goto BB;
			}
			printf("\n\nHow much do you want to pay me:> ");
			a = getnum();
			
			//Testing input
			if(a > stats.debt)
			{
				printf("\n\nYou don't owe me: $%d\n\n", a);
				
				goto BB;
			}
			if(a > stats.money)
			{
				printf("\n\nYou don't have $%d on you.\n\n", a);
				
				goto BB;
			}
			stats.debt -= a;
			stats.money -= a;
		}
		if(y == 2)
		{

			printf("\n\nHow much do you want to barrow:> ");
			a = getnum();
			
			//Testing input
			if(a > 10000)
			{
				printf("\n\nMax you can barrow is: $10,000\n\n");
				
				goto BB;
			}
			stats.debt += a;
			stats.money += a;
		}
		if(y == 3)
			goto MB;


		if (choice == 0)
		{
			goto MB;
		}

		if(choice < 1 || choice > 3)
		{
			printf("\n\nINVALID CHOICE\n\n\n\n");
			
			goto BB;
		}

		goto MB;
	}

	if(choice == 6)
	{
		printf("Not supported....\n");
		goto MB;
	}

	//To exit the program
	if(choice == 7)
	{
		
		printf("\n\n\t\t\t\tThanks for playing!\n\n");
	}

	//Testing user input
	if(choice < 1 || choice > 7)
	{
		putchar(choice);
		printf("\n\nINVALID INPUT\n");
		
		goto MB;
	}
	return 0;
}

//Precondition: This function will take in an array of the current location,
//				a pointer pointing to coat and money, takes in the array of drugs 
//				carrying,the max_coat, and the life of the user.. 
//Postcondition: This funtion will generate random number for random events throughout 
//		         the game and then return all variables back to main.

//Everything in this Rand_Event() function relys on RNG,"Random Number Generators". I used
//Random number to determine when certain events happen through-out the game
int Rand_Event(char loc[], int *c, long *m, int d[], int *mc, int *l)
{
	int a, b, i, choice;
	char y= 0;
	a = rand()%40 + 1;
	
	//Random events below deal with Officer HARDASS that is always on your case.
	//If the random number a == (1 || 10 || 20) then Officer HARDASS will be
	//after the user.
	if(a <= 7 )
	{
		
		printf("\n\t\t ");
		putchar(219);
		putchar(196);
		putchar(196);
		putchar(180);
		printf(" You land in %s  ", loc);
		printf("\n\t\t ");
		putchar(179);
		printf("\n\t\t ");
		putchar(179);
		printf("\n\t\t ");
		putchar(192);
		putchar(196);
		putchar(196);
		putchar(194);
		for(i=0;i<32;i++)
			putchar(196);
		putchar(191);
		printf("\n\t\t    ");
		putchar(179);
		for(i=0;i<32;i++)
			printf(" ");
		putchar(179);
		printf("\n\t\t    ");
		putchar(179);
		printf(" Officer HARD ASS is after you! ");
		putchar(179);
		printf("\n\t\t    ");
		putchar(179);
		for(i=0;i<32;i++)
			printf(" ");
		putchar(179);
		printf("\n\t\t    ");
		putchar(192);
		for(i=0;i<32;i++)
			putchar(196);
		putchar(217);
		printf("\n\n\n");
		
		
HA:		
		choice = 0;
		printf("\n\t\t\t\tLife: ");
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);// Changing color of text
		putchar(177);
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // Changing color of text
		for(i=2;i<=*l;i++)
			putchar(177);
		
		printf("\n\n\t\t\t     ");
		putchar(219);
		for(i=0;i<20;i++)
			putchar(196);
		putchar(219);
		printf("\n\t\t\t     ");
		putchar(179);
		printf(" [1] Fight the cop  ");
		putchar(179);
		printf("\n\t\t\t     ");
		putchar(179);
		printf(" [2] Run            ");
		putchar(179);
		printf("\n\t\t\t     ");
		putchar(219);
		for(i=0;i<20;i++)
			putchar(196);
		putchar(219);
		printf("\n\n");
		printf("\t\t\tCHOICE:> ");
		choice = getnum();
		
		if(choice == 2)
		{	
			b = rand()%3 + 1;
			
			if(b == 1)
			{
				
				//Displaying message and drawing message box
				printf("\n\t   ");
				putchar(218);
				for(i=0;i<58;i++)
					putchar(196);
				putchar(191);
				printf("\n\t   ");
				putchar(179);
				printf("                                                          ");
				putchar(179);
				printf("\n\t   ");
				putchar(179);
				printf(" You run down an alley and get away from Officer HARDASS! ");
				putchar(179);
				printf("\n\t   ");
				putchar(179);
				printf("                                                          ");
				putchar(179);
				printf("\n         ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<58;i++)
					putchar(196);
				putchar(217);
				printf("\n\t ");
				putchar(219);
				printf("\n\n\n");
				
				return(loc,c,m,d,mc,*l);
			}
			if(b == 2)
			{
				
				//Displaying message and drawing message box
				printf("\n\t\t    ");
				putchar(218);
				for(i=0;i<37;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t    ");
				putchar(179);
				printf("                                     ");
				putchar(179);
				printf("\n\t\t    ");
				putchar(179);
				printf(" Officer HARDASS is still after you! ");
				putchar(179);
				printf("\n\t\t    ");
				putchar(179);
				printf("                                     ");
				putchar(179);
				printf("\n\t\t  ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<37;i++)
					putchar(196);
				putchar(217);
				printf("\n\t\t  ");
				putchar(219);
				printf("\n\n\n\n\n");

				
				
				goto HA;
			}
			if(b == 3)
			{
				
				printf("\n      ");
				putchar(218);
				for(i=0;i<71;i++)
					putchar(196);
				putchar(191);
				printf("\n      ");
				putchar(179);
				printf("                                                                       ");
				putchar(179);
				printf("\n      ");
				putchar(179);
				printf("You got busted by Officer HARDASS. He takes all your drugs and money!  ");
				putchar(179);
				printf("\n      ");
				putchar(179);
				printf("I hope you had some money in the bank!                                 ");
				putchar(179);
				printf("\n      ");
				putchar(179);
				printf("                                                                       ");
				putchar(179);
				printf("\n    ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<71;i++)
					putchar(196);
				putchar(217);
				printf("\n    ");
				putchar(219);
				printf("\n\n\n");
				*c = 0;
				*m = 0;
				for(i = 0; i < 6; i++)
					d[i] = 0;
				
				return(loc,c,m,d,mc,*l);			
			}
			
		}
		if(choice == 1)
		{
			a = rand()%5 + 1;
			b = rand()%5 + 1;
			
			if(a == 1)
			{	
			//Drawing message box and message
				printf("\n\t\t");
				putchar(218);
				for(i=0;i<45;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t");
				putchar(179);
				for(i=0;i<45;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t");
				putchar(179);
				printf(" You shoot at Officer HARDASS and kill him!  ");
				putchar(179);
				printf("\n\t\t");
				putchar(179);
				for(i=0;i<45;i++)
					printf(" ");
				putchar(179);
				printf("\n\t      ");
				putchar(218);
				putchar(196);
				putchar(193);
				for(i=0;i<45;i++)
					putchar(196);
				putchar(217);
				printf("\n\t      ");
				putchar(219);
				printf("\n\n\n");

				
				
				return(loc,c,m,d,mc,*l);
			}
			if(b <= 3)
			{
				

				//Starting message box for shooting and missing
				printf("\n\t\t     ");
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t     ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(218);
				putchar(196);
				putchar(197);
				printf(" You shoot and miss Officer HARDASS.   ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");

				//Start drawing message box for cops shooting at you and hitting you
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(219);
				putchar(196);
				putchar(197);
				printf(" Officer HARDASS shoots and hits you!  ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");

				//Starting to draw message box for saying he is still after you
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(192);
				putchar(196); 
				putchar(197);
				printf(" He is still after you!                ");
				putchar(179);
				printf("\n\t\t     ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t     ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\n\n");
				*l -= 1; // Life points --> Looses 1 for getting shot
				

				//If life == 0 then game over..
				if(*l == 0)
				{
					
					printf("\n\n\n\n\t\t\tOfficer HARDASS killed you\n\n");
					printf("\t\t\t\tGAME OVER!\n\n");
					exit(0);
				}
				
				goto HA;				
			}
			
			if((a > 1 || b > 3))
			{
				
				
				//Starting message box for shooting and missing
				printf("\n\t\t     ");
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t     ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(218);
				putchar(196);
				putchar(197);
				printf(" You shoot and miss Officer HARDASS.   ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");

				//Start drawing message box for cops shooting at you and hitting you
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(219);
				putchar(196);
				putchar(197);
				printf(" Officer HARDASS shoots and misses you!");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");

				//Starting to draw message box for saying he is still after you
				putchar(218);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(191);
				printf("\n\t\t   ");
				putchar(179);
				printf(" ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t   ");
				putchar(192);
				putchar(196); 
				putchar(197);
				printf(" He is still after you!                ");
				putchar(179);
				printf("\n\t\t     ");
				putchar(179);
				for(i=0;i<39;i++)
					printf(" ");
				putchar(179);
				printf("\n\t\t     ");
				putchar(192);
				for(i=0;i<39;i++)
					putchar(196);
				putchar(217);
				printf("\n\n\n");
				
				
				goto HA;
			}
		}
		else
		{
			printf("\n\nINVALID CHOICE!\n\n");
			
			
			goto HA;
		}
	}
	
	//Random events below deal with finding drugs randomly throughout the game
	//If the random number a is == (2 || 21) These events will take place. 
	//It checks to see if a drug is == 0 then it will say that you found so many
	//that drug..
	if(a == 8 || a == 9)
	{
		
		
		if(d[0] == 0)
		{
			
			*c += 6; //adding 6 units of coke...
			
			//Checking to make sure user has enough pocket space in his/her coat...
			if(*c > *mc) 
			{
				NO_POC();
				*c -= 6; //subtracting 6 units of coke
			}
			else //There is enough room.
			{	
				
				printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 6 units of coke!              ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[0] += 6;
			}
			
			return(loc,c,m,d,mc,*l); 
		}

		if(d[1] == 0)
		{
			*c += 15;
			if(*c > *mc)
			{
				NO_POC();
				*c -= 15;
			}
			else
			{	
				
				printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 15 units of weed!             ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[1] += 15;
			}
			
			return(loc,c,m,d,mc,*l);
		}

		if(d[2] == 0)
		{
			*c += 25;
			if(*c > *mc)
			{
				NO_POC();
				*c -= 25;
			}
			else
			{	
				
				printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 25 units of ecstacy!          ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[2] += 25;
			}
			
			return(loc,c,m,d,mc,*l);
		}

		if(d[3] == 0)
		{
			*c += 7;
			if(*c > *mc)
			{
				NO_POC();
				*c -= 7;
			}
			else
			{	
				
				printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 7 units of acid!              ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[3] += 7;
			}
			
			return(loc,c,m,d,mc,*l);
		}

		if(d[4] == 0)
		{
			*c += 3;
			if(*c > *mc)
			{
				NO_POC();
				*c -= 3;
			}
			else
			{	
				
			printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 3 units of crack!             ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[4] += 3;
			}
			
			return(loc,c,m,d,mc,*l);
		}

		if(d[5] == 0)
		{
			*c += 5;
			if(*c > *mc)
			{
				NO_POC();
				*c -= 5;
			}
			else
			{	
				
				printf("\n\t    ");
				putchar(218);
				printf("\n\t");
				putchar(219);
				putchar(196);
				putchar(196);
				putchar(196);
				putchar(197);
				printf(" YOU LAND IN %s", loc);
				printf("\n\t    ");
				putchar(192);
				printf("\n");
				printf("\n\t    ");
				putchar(218);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(191);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" While walking down a alley, you find a brown paper bag.");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				printf(" You look inside and find 5 units of heroin!              ");
				putchar(179);
				printf("\n\t    ");
				putchar(179);
				for(i=0;i<56;i++)
					printf(" ");
				putchar(179);
				printf("\n\t    ");
				putchar(192);
				for(i=0;i<56;i++)
					putchar(196);
				putchar(217);
				printf("\n\n");
				d[5] += 5;
			}
			
			return(loc,c,m,d,mc,*l);
		}
	
	}
	
	// Random events below will say that the user has lost drugs. If the random number 
	//a == (7 || 12) then if a drug is == 0 it will subtract that many units of
	//that drug saying that you lost them.
	if(a == 10 || a == 11)
	{
		
		
		if(d[0] >= 5)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 5 unit(s) of coke!                 ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
		
			d[0] -= 5;
			*c -= 5;
			
			return(loc,c,m,d,mc,*l);
		}
		if(d[1] >= 10)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 10 unit(s) of weed!                ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
			d[1] -= 10;
			*c -= 10;
			
			return(loc,c,m,d,mc,*l);
		}
		if(d[2] >= 10)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 10 unit(s) of ecstacy!             ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
			d[2] -= 10;
			*c -= 10;
			
			return(loc,c,m,d,mc,*l);
		}
		if(d[3] >= 10)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 10 unit(s) of acid!                ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
			d[3] -= 10;
			*c -= 10;
			
			return(loc,c,m,d,mc,*l);
		}
		if(d[4] >= 5)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 5 unit(s) of crack!                ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
			d[4] -= 5;
			*c -= 5;
			
			return(loc,c,m,d,mc,*l);
		}
		if(d[5] >= 5)
		{
			printf("\n\t    ");
			putchar(218);
			printf("\n\t");
			putchar(219);
			putchar(196);
			putchar(196);
			putchar(196);
			putchar(197);
			printf(" YOU LAND IN %s", loc);
			printf("\n\t    ");
			putchar(192);
			printf("\n");
			printf("\n\t    ");
			putchar(218);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(191);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" After walking for a while you check your drugs and ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			printf(" notice you lost 5 unit(s) of heroin!               ");
			putchar(179);
			printf("\n\t    ");
			putchar(179);
			for(i=0;i<52;i++)
				printf(" ");
			putchar(179);
			printf("\n\t    ");
			putchar(192);
			for(i=0;i<52;i++)
				putchar(196);
			putchar(217);
			printf("\n\n");
			d[5] -= 5;
			*c -= 5;
			
			return(loc,c,m,d,mc,*l);
		}
	}

/*	///THis random event below only used when a == 40 says that you get the idea to rob
	//somone so you do. WHen you robb someone there are 3 different amounts that you 
	//can find inside the wallet. I generate a random number (1,2,or3) to find out how
	//much is in the wallet.
	if(a == 12)
	{
		
		a = rand()%3 + 1;
		printf("\n\tYou get the bright idea to robb someone........\n");
		printf("\n\tSo, you find someone and follow them down an alley..........\n");
		printf("\n\tYou kick this guys ass and steal his wallet! Inside is: ");
		if(a == 1)
		{
			*m += 1000;
			printf("$1000\n\n");
		}
		if(a == 2)
		{
			*m += 500;
			printf("$500\n\n");
		}
		if(a == 3)
		{
			*m += 100;
			printf("$100\n\n");
		}
		
		return(loc,c,m,d,mc,*l);
	}
*/
	//If a == 13,14,15, 16, or 17 then you will be able to buy more pockets
	if(a == 13 || a == 14 || a == 15 || a == 16 || a == 17)
	{
		
		printf("\t\t\nDo you want to purchase 100 more pockets for $1000.00? (y/n)> ");
		y = getchar();
		if(y == 'y' || y == 'Y')//getch() == 'y' || getch() == 'Y')
		{
			putchar(y);
			if(*m < 1000)
			{
				printf("\n\nNOT ENOUGH MONEY!\n\n");
				
				return(loc,c,m,d,mc,*l);
			}
			*mc += 100;
			*m -= 1000;
			return(loc,c,m,d,mc,*l);
		}
		else
		{
			putchar(y);
			return(loc,c,m,d,mc,*l);
		}
	}
	return(loc,c,m,d,mc,*l);
}





//Used to display what cities are already in the game. This is displayed when
//the user is ask to input their city and state.
void Cities()
{
	int i;


	printf("\n\t\t          ");
	printf("Current places in the game!\n\n");
		
	printf("\t\t\t   ");
	putchar(213);
	for(i=0;i<=21;i++)
		putchar(205);
	putchar(184);
	printf("\n");

	printf("\t\t\t   ");
	putchar(179);
	printf("Orlando, FL           ");
	putchar(179);
	printf("\n");
	
	printf("\t\t\t   ");
	putchar(179);
	printf("Las Vegas, NV         ");
	putchar(179);
	printf("\n");
	
	printf("\t\t\t   ");
	putchar(179);
	printf("Amsterdam, Netherlands");
	putchar(179);
	printf("\n");
	
	printf("\t\t\t   ");
	putchar(179);
	printf("Dublin, Ireland       ");
	putchar(179);
	printf("\n");

	printf("\t\t\t   ");
	putchar(179);
	printf("Washington D.C.       ");
	putchar(179);
	printf("\n");

	printf("\t\t\t   ");
	putchar(179);
	printf("Miami, FL             ");
	putchar(179);
	printf("\n");

	printf("\t\t\t   ");
	putchar(179);
	printf("Los Angeles, CA       ");
	putchar(179);
	printf("\n");

	printf("\t\t\t   ");
	putchar(179);
	printf("New York, NY          ");
	putchar(179);

	printf("\n");
	
	printf("\t\t\t   ");
	putchar(212);
	for(i=0;i<=21;i++)
		putchar(205);
	putchar(190);
	printf("\n\n\t");
	for(i=0;i<63;i++)
		putchar(220);
}

//Printf out a picture of a jail cell. If the user gets busted by the cops then he/she
//gets to spend A day in jail and loose all money and drugs...
int JAIL()
{	
	int i,j;
	

	//Top of jail cell
	for(i=0;i<80;i++)
		putchar(177);
	for(i=0;i<80;i++)
		putchar(177);
	for(i=0;i<80;i++)
		putchar(177);
	
	//sides of jails cell and bars
	for(j=0;j<20;j++)
	{
		for(i=0;i<4;i++)
			putchar(177);
		printf("    ");
		for(i=0;i<17;i++)
		{
			putchar(179);
			printf("   ");
		}
		for(i=0;i<4;i++)
			putchar(177);
		
	}
	//DRAWING BODY, WALLS, AND BARS
	for(i=0;i<4;i++) //start line 1
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<5;i++)
	{
		printf("   ");
		putchar(179);
	}
	
	printf("***");
	putchar(179);
	for(i=0;i<10;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//------------------end line 1

	for(j=0;j<=2;j++)//Drawing 3 lines for the head
	{
		for(i=0;i<4;i++) 
			putchar(177);
		printf("    ");
		putchar(179);
		for(i=0;i<4;i++)
		{
			printf("   ");
			putchar(179);
		}
		printf("  *");
		putchar(179);
		printf("   ");
		putchar(179);
		printf("*  ");
		putchar(179);
		for(i=0;i<9;i++)
		{
			printf("   ");
			putchar(179);
		}
		printf("   ");
		for(i=0;i<4;i++)
				putchar(177);
	}//end 3 lines of head

	for(i=0;i<4;i++) //Drawing last part of head
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<5;i++)
	{
		printf("   ");
		putchar(179);
	}
	
	printf("***");
	putchar(179);
	for(i=0;i<10;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//------------------end drawing head

	for(j=0;j<=1;j++) //Start drawing torso down to shoulders
	{
		for(i=0;i<4;i++) 
			putchar(177);
		printf("    ");
		putchar(179);
		for(i=0;i<5;i++)
		{
			printf("   ");
			putchar(179);
		}
		
		printf(" * ");
		putchar(179);
		for(i=0;i<10;i++)
		{
			printf("   ");
			putchar(179);
		}	
		printf("   ");
		for(i=0;i<4;i++)
			putchar(177);
	} //----------------- end start of torso

	for(i=0;i<4;i++) //Torso and shoulders
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<5;i++)
	{
		printf("   ");
		putchar(179);
	}
	
	printf("***");
	putchar(179);
	for(i=0;i<10;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);

	//Starting to draw torso and arms
	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<4;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf("  *");
		putchar(179);
	printf(" * ");
	putchar(179);
	printf("*  ");
		putchar(179);
	for(i=0;i<9;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------end line 1
	
	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<4;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf(" * ");
		putchar(179);
	printf(" * ");
	putchar(179);
	printf(" * ");
		putchar(179);
	for(i=0;i<9;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------end line 2

	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<4;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf("*  ");
		putchar(179);
	printf(" * ");
	putchar(179);
	printf("  *");
		putchar(179);
	for(i=0;i<9;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------End drawing rest of torso and arms

	//Start drawing legs
	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<5;i++)
	{
		printf("   ");
		putchar(179);
	}
	
	printf("* *");
	putchar(179);
	for(i=0;i<10;i++)
	{
		printf("   ");
		putchar(179);
	}	
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------End line 1

	for(i=0;i<4;i++)
		putchar(177);
	printf("    ");
	for(i=0;i<17;i++)
	{
		putchar(179);
		printf("   ");
	}
	for(i=0;i<4;i++)
		putchar(177);
	//---------------end line 2

	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<4;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf("  *");
	putchar(179);
	printf("   ");
	putchar(179);
	printf("*  ");
	putchar(179);
	for(i=0;i<9;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------end line 3

	for(i=0;i<4;i++) 
		putchar(177);
	printf("    ");
	putchar(179);
	for(i=0;i<4;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf(" * ");
	putchar(179);
	printf("   ");
	putchar(179);
	printf(" * ");
	putchar(179);
	for(i=0;i<9;i++)
	{
		printf("   ");
		putchar(179);
	}
	printf("   ");
	for(i=0;i<4;i++)
		putchar(177);
	//----------------end line 4

	//Bottom of jail cell
	for(i=0;i<80;i++)
		putchar(177);
	for(i=0;i<80;i++)
		putchar(177);
	for(i=0;i<80;i++)
		putchar(177);
	//-----------------End drawing bottom
	printf("\n\n");
	printf("\tOfficer HARDASS has put you in jail for 24 hours! Sucks to be you!\n\n");
	
	return 0;
}

//******************** DOPE WARS LOGO AND START UP MENU **********************
int High_Low()
{
	int i;
	int a;
	int counter = 0;
	while(counter != 5)
	{
		counter++;
	   	a = rand()%15 + 1; //I don't want a=0 --> becuase it is black and the BG is Black
		//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a); //Random color
		
		//Printing Dope Wars Logo
		printf("\n\n\n");
		printf("\t\t\t ");
		putchar(219);
		printf("                          ");
		putchar(219);
		printf("\n");
		printf("\t\t\t ");
		putchar(192);
		putchar(196);
		putchar(196);
		putchar(194);
		for(i=0;i<20;i++)
			putchar(196);
		putchar(194);
		putchar(196);
		putchar(196);
		putchar(217);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("                    ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("     D  O  P  E     ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("                    ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("     W  A  R  S     ");
		putchar(179);
		printf("\n");
		printf("\t\t\t    ");
		putchar(179);
		printf("                    ");
		putchar(179);
		printf("\n");
		printf("\t\t\t ");
		putchar(218);
		putchar(196);
		putchar(196);
		putchar(193);
		for(i=0;i<20;i++)
			putchar(196);
		putchar(193);
		putchar(196);
		putchar(196);
		putchar(191);
		printf("\n");
		printf("\t\t\t ");
		putchar(219);
		printf("                          ");
		putchar(219);
		printf("\n\n\n\n\n\n");

	}
	

//	
	//Finished Draeing Dope Wars Logo
	
	
	
	//A little info about the game
	printf("Below shows you how high each drug can get....\n\n\t");
	putchar(16);
	printf(" COKE:    $10,000\n\t");
	putchar(16);
	printf(" WEED:    $1,000\n\t");
	putchar(16);
	printf(" EXSTACY: $100\n\t");
	putchar(16);
	printf(" ACID:    $1,000\n\t");
	putchar(16);
	printf(" CRACK:   $10,000\n\t");
	putchar(16);
	printf(" HEROIN:  $10,000\n");

	printf("\n\nThis will give you an idea on when to buy and sell.\n\n");
	printf("Bookie Brown gives you a loan of $10,000 to start the game...");
	printf("\nThe object of the game is to pay off your bookie within 30 days and end up\n");
	printf("a millionaire. You can fly to different cities, buy drugs when they are\n");
	printf("low and sell them when they are high! If you don't pay off your bookie,\n");
	printf("then he will hunt you down. If you put money in the bank, it will draw \n");
	printf("interest every day. The longer you go without paying off your debt the bigger\n");
	printf("it gets...\n\n");
	printf("\nENJOY!\n\n");

	
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);// Changing color of text
	printf("WRITTEN BY: Michael Brown -- email: brown12321@hotmail.com\n\n\n");
	//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);// Changing color of text
	
	

	return 0;	
}

//Function used to print out a message if the user find drugs randomly through-out the game.
//If the user doesn't have enough pockets to carry the drugs that him/her find, then a call
//will be made to this function....
int NO_POC()
{
	int i;

	printf("\n\t     ");
	putchar(218);
	for(i=0;i<55;i++)
		putchar(196);
	putchar(191);
	printf("\n\t     ");
	putchar(179);
	for(i=0;i<55;i++)
		printf(" ");
	putchar(179);
	printf("\n\t     ");
	putchar(179);
	printf(" You found some drugs.......                           ");
	putchar(179);
	printf("\n\t     ");
	putchar(179);
	printf(" To bad you don't have enough pockets to hold them...  ");
	putchar(179);
	printf("\n\t     ");
	putchar(179);
	for(i=0;i<55;i++)
		printf(" ");
	putchar(179);
	printf("\n\t   ");
	putchar(218);
	putchar(196);
	putchar(193);
	for(i=0;i<55;i++)
		putchar(196);
	putchar(217);
	printf("\n\t   ");
	putchar(219);
	printf("\n\n\n");

	return 0;
}
//********************* THis function draws the Bank menu ***********************
int Bank(long M, long B)
{
	int i;

	printf("\t\t\t    ");
	putchar(213);
	for(i=0;i<23;i++)
		putchar(205);
	putchar(184);
	printf("\n");
	printf("\t\t\t    ");
	putchar(179);
	printf("     BROWN'S BANK      ");
	putchar(179);
	printf("\n");
	printf("\t\t\t    ");
	putchar(198);
	for(i=0;i<23;i++)
		putchar(205);
	putchar(181);
	printf("\n");
	printf("\t\t\t    ");
	putchar(179);
	printf("[1] Deposit            ");
	putchar(179);
	printf("\n");
	printf("\t\t\t    ");
	putchar(179);
	printf("[2] Withdraw           ");
	putchar(179);
	printf("\n");
	printf("\t\t\t    ");
	putchar(179);
	printf("[3] Return to menu     ");
	putchar(179);
	printf("\n");
	printf("\t\t\t    ");
	putchar(198);
	for(i=0;i<23;i++)
		putchar(205);
	putchar(181);
	printf("\n");
	printf("\t\t\t    ");
	putchar(179);
	printf("Account: $%-13d", B);
	putchar(179);
	printf("\n");
	printf("\t\t\t    ");
	putchar(212);
	for(i=0;i<23;i++)
		putchar(205);
	putchar(190);
	printf("\n\t\t         ");
	printf("Money able to deposit:  $%d\n\n", M);

	return 0;
}


//***********************This function draws the Bookie Menu ********************
int Bookie()
{
	int i;

	printf("\t\t\t ");
	putchar(213);
	for(i=0;i<24;i++)
		putchar(205);
	putchar(184);
	printf("\n");
	printf("\t\t\t ");
	putchar(179);
	printf("     BOOKIE  BROWN      ");
	putchar(179);
	printf("\n");
	printf("\t\t\t ");
	putchar(198);
	for(i=0;i<24;i++)
		putchar(205);
	putchar(181);
	printf("\n");
	printf("\t\t\t ");
	putchar(179);
	printf("[1] Pay off             ");
	putchar(179);
	printf("\n");
	printf("\t\t\t ");
	putchar(179);
	printf("[2] Barrow              ");
	putchar(179);
	printf("\n");
	printf("\t\t\t ");
	putchar(179);
	printf("[3] Return to menu      ");
	putchar(179);
	printf("\n");
	printf("\t\t\t ");
	putchar(212);
	for(i=0;i<24;i++)
		putchar(205);
	putchar(190);
	printf("\n\n");

	return 0;
}

int getnum()
{
	char buf[16] = {'\0','\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0', };
	char* p;
	long int i;


	if (fgets(buf, sizeof(buf),stdin) != NULL)
	{
		i = strtol(buf, &p, 10);

		if (buf[0] != '\n' && (*p == '\n' || *p == '\0'))
		{
			return i;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

void getstring()
{
	
		char* p;


		if (fgets(str, sizeof(str),stdin) != NULL)
		{
				if ((p = strchr(str, '\n')) != NULL)
				*p = '\0';
		}
}
