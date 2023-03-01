/**
 ******************************************************************************
 * @file           : app.c
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */

/************************* Libraries Include Files ****************************/
#include "app.h"

/************************* Global Variables ****************************/
ST_transaction_t Trans_Data;
ST_cardData_t Card_Data;
ST_terminalData_t Term_Data;

void appStart(void)
{	
	float max_value = 20000;
	
/*********************************** Card Functions ***********************************/
	
		printf("-------------------------Card Data---------------------\n");
		while (getCardHolderName(&Card_Data));
		printf("-------------------------Next step---------------------\n");

		while (getCardExpiryDate(&Card_Data));
		printf("-------------------------Next step---------------------\n");
		while (getCardPAN(&Card_Data));
		printf("-------------------------Next step---------------------\n");

/******************************* Terminal Functions ***********************************/

		printf("-----------------------Terminal Data-------------------\n");
		while (getTransactionDate(&Term_Data));
			printf("-------------------------Next step---------------------\n");
		 (isCardExpired(&Card_Data, &Term_Data));
		 printf("-------------------------Next step---------------------\n");
		while (getTransactionAmount(&Term_Data));
		printf("-------------------------Next step---------------------\n");
			 (setMaxAmount(&Term_Data, max_value));
		printf("-------------------------Next step---------------------\n");
		if (isBelowMaxAmount(&Term_Data))
		printf("-------------------------Next step---------------------\n");

/*********************************** Server Functions ***********************************/

		Trans_Data.cardHolderData = Card_Data;
		Trans_Data.terminalData = Term_Data;

		printf("-----------------------Server Data-------------------\n");
		recieveTransactionData(&Trans_Data);
}