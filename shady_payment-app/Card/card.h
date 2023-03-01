/*
 ******************************************************************************
 * @file           : card.h
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */
 /*************************  Header File Gaurd  ****************************/
#ifndef CARD_H
#define CARD_H
/************************* Libraries Include Files ****************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "STD_TYPES.h"
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
/************************* Functions Prototypes ****************************/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

void getCardHolderNameTest(ST_cardData_t* cardData);
void getCardExpiryDateTest(ST_cardData_t* cardData);
void getCardPANTest(ST_cardData_t* cardData);

#endif /*  CARD_H Gaurd  */