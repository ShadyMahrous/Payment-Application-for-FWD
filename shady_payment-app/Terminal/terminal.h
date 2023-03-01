/**
 ******************************************************************************
 * @file           : terminal.h
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */
 /*************************  Header File Gaurd  ****************************/
#ifndef TERMINAL_H
#define TERMINAL_H
/************************* Libraries Include Files ****************************/
#include "card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;
/************************* Functions Prototypes ****************************/
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);


void getTransactionDateTest(ST_terminalData_t* termData);
void isCardExpriedTest(ST_terminalData_t* CardData, ST_terminalData_t* termData);
void getTransactionAmountTest(ST_terminalData_t* termDataoid);
void isBelowMaxAmountTest(ST_terminalData_t* termData);
void setMaxAmountTest(ST_terminalData_t* termData, float maxAmount);

#endif /*  TERMINAL_H Gaurd  */ 
