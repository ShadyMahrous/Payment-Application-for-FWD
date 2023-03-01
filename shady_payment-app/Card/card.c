/**
 ******************************************************************************
 * @file           : card.c
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */
 /************************* Libraries Include Files ****************************/

#include "card.h"

/************************* Card Module Functions ****************************/
/**
***************************************************************************
function name: getCardHolderName
function purpose: get the name of card holder.
restrictions:	1- card name must be between 20 : 24 charcters
				2- card name Can't contain spaces

***************************************************************************
**/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	EN_cardError_t card_error = 0;
	uint8_t len = 0;
	uint8_t i = 0;
	uint8_t flag;

	printf("please enter your card name[20 : 24]: \n");
		 
	gets(cardData->cardHolderName);									// scan the string of card holder name
	len = (strlen(cardData->cardHolderName));						// to get the lengh of input name
	for (i = 0; i <= len; i++)
	{
		if(cardData->cardHolderName[i] == 32 )
		{ 
			flag = 1;
			break;
		}
		else
		{
			flag = 0;
		}
	}
	if ((len >= 20 && len <= 24) && flag == 0)
	{
		printf("Card Name Accepted\n");
		card_error = CARD_OK;
	}
	else
	{
		printf("Wrong Card Name\n");
		card_error = WRONG_NAME;
	}
	
	return card_error;
}

/**
***************************************************************************
function name: getCardExpiryDate
function purpose: get the card Expiration Date.
restrictions:	1- month must be between 1 : 12
				2- year should be between 2023:2026
				3- symbol / between month and year
				4- must follow the form [MM,YY]

***************************************************************************
**/

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	EN_cardError_t card_error = 0;				//local variables
	
	uint8_t mm[3] = { 0 }, yy[3] = { 0 };
	uint16_t month = 0, year = 0,len = 0;
	

	printf("\nplease enter your card expiratione date in form [MM/YY]:  ");
							
	gets(cardData->cardExpirationDate);				// scan card expiration date
	len = (strlen(cardData->cardExpirationDate));

	mm[0] = cardData->cardExpirationDate[0];
	mm[1] = cardData->cardExpirationDate[1];
	mm[2] = 0;
	month = atoi(mm);					// convert saved month values of asci into inters

	yy[0] = cardData->cardExpirationDate[3];
	yy[1] = cardData->cardExpirationDate[4];
	yy[2] = 0;
	year = atoi(yy);					// convert saved year values of asci into inters
	
	if (len == 5										// check the length of input
		&& cardData->cardExpirationDate[2] == '/' 		// check the char / between month and year
		&& month <= 12 									// check if entered month not greater than 12
		&& (year >=23 && year <=26) )					// chek year range higher and lower by 3 years
	{
		printf("Date Accepted\n");
		card_error = CARD_OK;
	}
	else
	{
		printf("Wrong Expiration Date\n");
		card_error = WRONG_EXP_DATE;
	}
	return card_error;
}

/**
***************************************************************************
function name: getCardPAN
function purpose: get the primary Account Number.
restrictions:	1- PAN must be between 16 : 19 Numbers.
				2- PAN Can't Have Letters

***************************************************************************
**/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t card_error = CARD_OK;
	uint8_t len = 0,i = 0, alph_flag = 0;

	printf("Please enter your card PAN [16:19]: ");
	gets(cardData->primaryAccountNumber);
	
	len= (strlen(cardData->primaryAccountNumber));

	for (i = 0; i <= len; i++)
	{	
		if (((cardData->primaryAccountNumber[i]) >= 'a') && ((cardData->primaryAccountNumber[i]) <= 'z')
			|| ((cardData->primaryAccountNumber[i]) >= 'A') && ((cardData->primaryAccountNumber[i]) <= 'Z'))
		{
			alph_flag = 1;
			break;
		}
		else
		{
			alph_flag = 0;
		}
	}
	if ((len >= 16) && (len <= 19) && alph_flag == 0)
	{
		printf("Card PAN Accepted\n");
		card_error = CARD_OK;
	}
	else
	{
		printf("Your PAN isn't Correct or have alphapetic Letter\n");
		card_error = WRONG_PAN;
	}
	return card_error;
}



void getCardHolderNameTest(ST_cardData_t* cardData)
{
	if (getCardHolderName(cardData) == CARD_OK)
	{
		printf("CardHolderName ==> Test PASSED");
	}
	else
	{
		printf("CardHolderName ==> Test FAILED");
	}
}
void getCardExpiryDateTest(ST_cardData_t* cardData)
{
	if (getCardExpiryDate(cardData) == CARD_OK)
	{
		printf("CardExpiryDate ==> Test PASSED");
	}
	else
	{
		printf("CardExpiryDate ==> Test FAILED");
	}
}
void getCardPANTest(ST_cardData_t* cardData)
{
	if (getCardPAN(cardData) == CARD_OK)
	{
		printf("CardPANTest ==> Test PASSED");
	}
	else
	{
		printf("CardPANTest ==> Test FAILED");
	}
}