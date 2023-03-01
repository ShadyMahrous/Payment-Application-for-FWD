/**
 ******************************************************************************
 * @file           : server.c
 * @author         : Eng: Shady Mahrous
 ******************************************************************************
 */
 /************************* Libraries Include Files ****************************/
#include "server.h"

uint8_t counter = 0;
static uint8_t sequence_number = 0;


ST_accountsDB_t account_database[255] =
{
	{ 1500.0,  RUNNING, "2003004005006007" },
	{ 1000.0,  BLOCKED, "2003004005006015" },
	{ 2000.0,  RUNNING, "2003004005006023" },
	{ 2500.0,  BLOCKED, "2003004005006031" },
	{ 3000.0,  RUNNING, "2003004005006049" },
	{ 3500.0,  BLOCKED, "2003004005006056" },
	{ 40000.0, RUNNING, "2003004005006064" },
	{ 4500.0,  BLOCKED, "2003004005006072" },
	{ 55000.0, BLOCKED, "2003004005006080" },
	{ 50000.0, RUNNING, "2003004005006098" }
};

ST_transaction_t transaction_database[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	printf("Function ==> recieve Transaction Data \n");
	EN_transState_t transaction_error;
	
	uint8_t max_value = 0;
	uint8_t saving_flag = 1;
	float transaction_value = 0;

	if (isValidAccount(&transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		printf("Fraud Card\n");
		transData->transState = FRAUD_CARD;
		transaction_error = FRAUD_CARD;
		saveTransaction(transData);
	}
	else if (isCardExpired(&transData->cardHolderData , &transData->terminalData) == EXPIRED_CARD )
	{
		printf("Expired Card\n");
		transData->transState = FRAUD_CARD;
		transaction_error = FRAUD_CARD;
		saveTransaction(transData);
	}
	else if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		printf("DECLINED INSUFFECIENT FUND \n");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		transaction_error = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
	}

	else if (isBlockedAccount(&account_database[counter]) == BLOCKED_ACCOUNT)
	{
		printf("DECLINED STOLEN CARD \n");
		
		transData->transState = DECLINED_STOLEN_CARD;
		transaction_error = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
	}
	else if (isBelowMaxAmount(&transData->terminalData) == EXCEED_MAX_AMOUNT)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		transaction_error = INTERNAL_SERVER_ERROR;
		saveTransaction(transData);
	}
	else
	{
		saving_flag = saveTransaction(transData);
		if (saving_flag == 0)
		{
			transaction_value = transData->terminalData.transAmount;
			printf("APPROVED \n");
			printf("Transaction Value= %f\n", transaction_value);
		
			transaction_database[counter].transState = APPROVED;
			account_database[counter].balance = account_database[counter].balance - transaction_value;
			printf("New Balance in Account = %f\n\n", account_database[counter].balance);
			transaction_error = APPROVED;
		}
		else
		{
			printf(" SAVING FAILED \n");
			transData->transState = SAVING_FAILED;
			transaction_error = SAVING_FAILED;
		}
	}
	listSavedTransactions();
	return transaction_error;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	printf("Function ==> is Valid Account \n");
	EN_serverError_t server_error;
	uint8_t valid_flag = 0;
	uint8_t i = 0;
	for ( i= 0; i <= 254; i++)
	{	
		if (strcmp( (cardData->primaryAccountNumber) , (account_database[i].primaryAccountNumber) ) == 0 )
		{
			valid_flag = 1;
			counter = i;
			break;			
		}
		else
		{	
			valid_flag = 0;
		}
	}
	if (valid_flag == 1)
	{
		printf("Valid Account\n");
		printf("Reference Account:%s \n\n", account_database[counter].primaryAccountNumber);
		server_error = SERVER_OK;
	}
	else
	{
		printf("Account Not Found\n\n");
		server_error = ACCOUNT_NOT_FOUND;
	}
	return server_error;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	printf("Function ==> is Blocked Account \n");
	EN_serverError_t account_error = 0;
	accountRefrence->state = account_database[counter].state;
	
	if (accountRefrence->state == RUNNING)
	{
		printf("Running Account \n\n");

		account_error = SERVER_OK;
	}
	else if (accountRefrence->state == BLOCKED)
	{
		printf("Blocked Account \n\n");

		account_error = BLOCKED_ACCOUNT;
	}
	else
	{}
	return account_error;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	printf("Function ==> is Amount Available \n");
	EN_serverError_t Amount_error;
	if (termData->transAmount <= account_database[counter].balance)
	{
		printf("Balance OK\n\n");
		Amount_error = SERVER_OK;
	}
	else
	{
		printf("Low Balance\n\n");
		Amount_error = LOW_BALANCE;
	}
	return Amount_error;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	printf("Function ==> save Transaction \n");
	EN_serverError_t save_error;
	sequence_number++;
	transData->transactionSequenceNumber = sequence_number;
	
	if ((transData->transactionSequenceNumber) >= 255)
	{
		save_error = SAVING_FAILED;
		printf("Process Failed to Save Transaction\n");
	}
	else
	{
		transaction_database[sequence_number].cardHolderData = transData->cardHolderData;
		transaction_database[sequence_number].terminalData = transData->terminalData;
		transaction_database[sequence_number].transactionSequenceNumber = transData->transactionSequenceNumber;
		transaction_database[sequence_number].transState = transData->transState;
		save_error = SERVER_OK;
		printf("Process Done: Transaction Saved\n\n");
	}
	return save_error;
}

void listSavedTransactions(void)
{
	printf("#############################  \n");
	printf("Transaction Sequence Number: %d  \n", transaction_database[sequence_number].transactionSequenceNumber);
	printf("Transaction Date: %s  \n", transaction_database[sequence_number].terminalData.transactionDate);
	printf("Transaction Amount: %f  \n", transaction_database[sequence_number].terminalData.transAmount);
	switch (transaction_database[sequence_number].transState)
	{
	case APPROVED:
	{
		printf("Transaction State: APPROVED \n");
		break;}
	case DECLINED_INSUFFECIENT_FUND:
	{
		printf("Transaction State: DECLINED_INSUFFECIENT_FUND \n");
		break;}
	case DECLINED_STOLEN_CARD:
	{
		printf("Transaction State: DECLINED_STOLEN_CARD \n");
		break;}
	case FRAUD_CARD:
	{
		printf("Transaction State: FRAUD_CARD \n");
		break;}
	case INTERNAL_SERVER_ERROR:
	{
		printf("Transaction State: INTERNAL_SERVER_ERROR \n");
		break;}

	default:
		break;}
	printf("Terminal Max Amount %f  \n", transaction_database[sequence_number].terminalData.maxTransAmount );
	printf("CardHolder Name: %s \n", transaction_database[sequence_number].cardHolderData.cardHolderName );
	printf("PAN: %s  \n", transaction_database[sequence_number].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date: %s  \n", transaction_database[sequence_number].cardHolderData.cardExpirationDate);
	printf("#############################\n");
}
