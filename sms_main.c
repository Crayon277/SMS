#include"sms.h"


int main(int argc, char*argv[]){
	pUSER_ACCOUNT USER_LIST;    // ÿ�β���������������������
	pSTU  STU_LIST;   //�������ٷŻ�ȥ
	USER_ROLE check_mode;

	int tries = 3;  //��ೢ��3�Σ�
		  
	char try_renter;

	init_list(&USER_LIST, &STU_LIST);

	init_system(USER_LIST, STU_LIST);

	//show_stu_user_list(USER_LIST, STU_LIST);
	while (tries){   
		check_mode = LOGIN_USER(USER_LIST);
		if (1 == check_mode|| 0 == check_mode){
			break;
		}
		else if (-1 == check_mode){
			printf("\nInvalid Password!!\n");
			printf("Do you want to renter the password?   (Y/N)\n");
			while (fflush(stdin), (try_renter = getchar()) != EOF){
				if ('Y' == try_renter){    //����Ӧ��ֻ��������������  #########
					break;
				}
				else if('N' == try_renter){
					exit(EXIT_FAILURE);
				}
				else{
					printf("Are you kidding me? ");
					printf("(Y/N)\n");
				}
			}
			
		}
		else{ 
			printf("\nNo such user!!");  
			system("pause");      //�޸��ⲿ�� ######�ÿ���
		}
		system("cls");
		tries--;
	}

	if (tries == 0){
		printf("Thank you for using this SMIS. SEE YOU!");
		system("pause");
		exit(EXIT_FAILURE);
	}


	MAIN_FUN(check_mode, USER_LIST, STU_LIST);	



	system("pause");
	return 0;

}