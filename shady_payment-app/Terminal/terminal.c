/**
 ******************************************************************************
 * @file           : terminal.c
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */
 /************************* Libraries Include Files ****************************/
#include "terminal.h"

/**
***************************************************************************
function name: getTransactionDate
function purpose: get the transaction Date.
restrictions:	1- month must be between 1 : 12
                2- year should be 2023 or more.
                3- symbol / between day,month and year.
                4- must follow the form [DD,MM,YYYY].

***************************************************************************
**/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    EN_terminalError_t terminal_error = 0;
    uint8_t len = 0,j=0;
    uint8_t DD[3] = { 0 };
    uint8_t MM[3] = { 0 };
    uint8_t YY[5] = { 0 };
    uint16_t day = 0,month = 0, year = 0;

   printf("Please enter the transaction date in form DD/MM/YYYY: ");     
   gets(termData->transactionDate);                     // Scan the date from user
   len = (strlen(termData->transactionDate));           // get length of input
   
   DD[0] = termData->transactionDate[0];
   DD[1] = termData->transactionDate[1];
   DD[2] = NULL;
   day = atoi(DD);                      // convert day value of asci into inters 
   
   MM[0] = termData->transactionDate[3];
   MM[1] = termData->transactionDate[4];
   MM[2] = NULL;
   month = atoi(MM);                    // convert month value of asci into inters

   YY[0] = termData->transactionDate[6];
   YY[1] = termData->transactionDate[7];
   YY[2] = termData->transactionDate[8];
   YY[3] = termData->transactionDate[9];
   YY[4] = NULL;
   year = atoi(YY);                     // convert year value of asci into inters

   if (len != 10 )
   {
       printf("Wrong Date \n");
       terminal_error = WRONG_DATE;
   }
   else if (   termData->transactionDate[2] != '/'
            || termData->transactionDate[5] != '/')
   {
       printf("Wrong Symbol Between Day,Month and Year \n");
       terminal_error = WRONG_DATE;
   }
   else if (day > 31)
   {
       printf("Wrong Day \n");
       terminal_error = WRONG_DATE;
   }
   else if (month > 12)
   {
       printf("Wrong Month \n");
       terminal_error = WRONG_DATE;
   }
   else if(year < 2023)
   {
       printf("Wrong Year \n");
       terminal_error = WRONG_DATE;
   }
   else
   {
       printf("Date Accepted\n");
       terminal_error = TERMINAL_OK; 
   }
   return terminal_error;
}
/**
***************************************************************************
function name: isCardExpired
function purpose: check if the card is expired.
restrictions: 1- Card Expiration Date should be bigger than transaction Date

***************************************************************************
**/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
    EN_terminalError_t expired_card_error = 0;
    uint8_t MM_transfer[3] = { 0 };
    uint8_t YY_transfer[5] = { 0 };
    uint8_t MM_expired[3] = { 0 };
    uint8_t YY_expired[5] = { 0 };
    uint16_t month_trans = 0;
    uint16_t year_trans = 0;
    uint16_t month_exp = 0;
    uint16_t year_exp = 0;

    MM_transfer[0] = termData->transactionDate[3];
    MM_transfer[1] = termData->transactionDate[4];
    MM_transfer[2] = NULL;
    month_trans = atoi(MM_transfer);

    
    YY_transfer[0] = termData->transactionDate[8];
    YY_transfer[1] = termData->transactionDate[9];
    YY_transfer[2] = NULL;
    year_trans = atoi(YY_transfer);

    MM_expired[0] = cardData->cardExpirationDate[0];
    MM_expired[1] = cardData->cardExpirationDate[1];
    MM_expired[2] = NULL;
    month_exp = atoi(MM_expired);

    YY_expired[0] = cardData->cardExpirationDate[3];
    YY_expired[1] = cardData->cardExpirationDate[4];
    YY_expired[2] = NULL;
    year_exp = atoi(YY_expired);
    

    if (year_trans > year_exp)
    {
        printf("Expired Card, Wrong Year\n");
        expired_card_error = EXPIRED_CARD;
    }
    else if (year_trans == year_exp)
    {
        if (month_trans > month_exp)
        {
            printf("Expired Card, Wrong month\n");
            expired_card_error = EXPIRED_CARD;
        }
        else
        {
            printf("Valid Card\n");
            expired_card_error = TERMINAL_OK;
        }
    }
    else
    {
        printf("Valid Card\n");
        expired_card_error = TERMINAL_OK;
    }
    return expired_card_error;
}
/**
***************************************************************************
function name: getTransactionAmount
function purpose: Get Transaction Amount from user.
restrictions: 1- Transaction Amount Can't be zero or less.

***************************************************************************
**/

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t transaction_error = 0;
    printf("Please Enter Your Transaction Amount: ");
    scanf_s("%f", &termData->transAmount);

    if (termData->transAmount <= 0)
    {
        printf("Wrong Amount Value\n");
        transaction_error = INVALID_AMOUNT;
    }
    else
    {
        printf("Valid Amount Value\n");
        transaction_error = TERMINAL_OK;
    }
    return transaction_error;
}

/**
***************************************************************************
function name: isBelowMaxAmount
function purpose: Check if transaction Amount is More than the Max Amount.
restrictions: 1- transaction Amount Can't be More than the Max Amount.

***************************************************************************
**/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t below_max_error = 0;
    if ((termData->transAmount) <= (termData->maxTransAmount))
    {
        printf(" Valid Process: Transaction Amount is below Max Amount\n");
        below_max_error = TERMINAL_OK ;
    }
    else
    {
        printf(" Process Failed: Transaction Amount is more than Max Amount\n");
        below_max_error = EXCEED_MAX_AMOUNT;
    }
    return below_max_error;
}

/**
***************************************************************************
function name: setMaxAmount
function purpose: Get the Max Amount.
restrictions: 1- Max Amount Can't be zero or less.

***************************************************************************
**/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
    EN_terminalError_t max_amount_error = 0;
 
    if (maxAmount <= 0)
    {
        printf("Wrong Max Amount Value\n");
        max_amount_error = INVALID_MAX_AMOUNT;
    }
    else
    {
        printf("Valid Max Amount Value\n");
        termData->maxTransAmount = maxAmount;
        max_amount_error = TERMINAL_OK;
    }
    return max_amount_error;
}







void getTransactionDateTest(ST_terminalData_t* termData)
{
    if (getTransactionDate(termData) == TERMINAL_OK)
    {
        printf("TransactionDate ==> Test PASSED");
    }
    else
    {
        printf("TransactionDate ==> Test FAILED");
    }
}
void isCardExpriedTest(ST_terminalData_t* CardData,ST_terminalData_t* termData)
{
    if (isCardExpired(CardData , termData) == TERMINAL_OK)
    {
        printf("isCardExpried ==> Test PASSED");
    }
    else
    {
        printf("isCardExpried ==> Test FAILED");
    }
}
void getTransactionAmountTest(ST_terminalData_t* termData)
{
    if (getTransactionAmount(termData) == TERMINAL_OK)
    {
        printf("getTransactionAmount ==> Test PASSED");
    }
    else
    {
        printf("getTransactionAmount ==> Test FAILED");
    }
}
void isBelowMaxAmountTest(ST_terminalData_t* termData)
{
    if (isBelowMaxAmount(termData) == TERMINAL_OK)
    {
        printf("isBelowMaxAmount ==> Test PASSED");
    }
    else
    {
        printf("isBelowMaxAmount ==> Test FAILED");
    }
}
void setMaxAmountTest(ST_terminalData_t* termData,float maxAmount)
{
    if (setMaxAmount(termData, maxAmount) == TERMINAL_OK)
    {
        printf("setMaxAmount ==> Test PASSED");
    }
    else
    {
        printf("setMaxAmount ==> Test FAILED");
    }
}