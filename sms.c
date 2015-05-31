#include"sms.h"


void init_list(pUSER_ACCOUNT *pp_user, pSTU * pp_stu){
	if (pp_user != NULL){
		(*pp_user) = (pUSER_ACCOUNT)calloc(1, sizeof(USER_ACCOUNT));
	}
	if (pp_stu != NULL){
		(*pp_stu) = (pSTU)calloc(1, sizeof(STU));
	}
}

void destroy_user_list(pUSER_ACCOUNT p_user){
	if (p_user == NULL){
		return 0;
	}
	else{
		destroy_user_list(p_user->link);
		free(p_user);
	}
}

void destroy_stu_list(pSTU p_stu){
	if (p_stu == NULL){
		return 0;
	}
	else{
		destroy_stu_list(p_stu->link);
		free(p_stu);
	}
}

void file_open_user(FILE **fp_user_account,int mode){
	FILE *fp_config;
	char line[line_len];

	fp_config = fopen(configure_path, "r");

	if (fp_config == NULL){
		printf("****SYSTEM ERROR****\n");
		system("pause");
		exit(EXIT_FAILURE);
	}

	while (memset(line, 0, sizeof(line)), fscanf(fp_config, "%32[^\n]\n", line) != EOF){
		if (strstr(line, "user_account")){
			switch (mode){
			case 1:
				*fp_user_account = fopen(line, "r");
				break;
			case 2:
				*fp_user_account = fopen(line, "w");
				break;
			}
			if (*fp_user_account == NULL){
				printf("****SYSTEM ERROR*****\n");
				system("pause");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}
	fclose(fp_config);
}

void file_open_stu(FILE **fp_stu_info ,int mode){
	FILE *fp_config;
	char line[line_len];
	

	fp_config = fopen(configure_path, "r");

	if (fp_config == NULL){
		printf("****SYSTEM ERROR****\n");
		system("pause");
		exit(EXIT_FAILURE);
	}
	while (memset(line, 0, sizeof(line)), fscanf(fp_config, "%32[^\n]\n", line) != EOF){
		if (strstr(line, "stu_account")){
			switch (mode){
			case 1:
				*fp_stu_info = fopen(line, "r");
				break;
			case 2:
				*fp_stu_info = fopen(line, "w");
				break;
			}
			if (*fp_stu_info == NULL){
				printf("****SYSTEM ERROR*****\n");
				system("pause");
				exit(EXIT_FAILURE);
			}
			break;
		}
	}
	fclose(fp_config);
}


void init_system(pUSER_ACCOUNT pp_acc, pSTU  pp_stu){
	FILE //*fp_config,
		*fp_user_acc,
		*fp_stu_info;

	//fp_config = fopen(configure_path, "r");

	//if (fp_config == NULL){
	//	printf("****SYSTEM ERROR****\n");
	//	system("pause");
	//	exit(EXIT_FAILURE);
	//}
	file_open_stu(&fp_stu_info,read_mode);
	//rewind(fp_config);
	file_open_user(&fp_user_acc,read_mode);

	assign_list(fp_user_acc, fp_stu_info, pp_acc, pp_stu);

	//fclose(fp_config);
	fclose(fp_stu_info);
	fclose(fp_user_acc);
}




void assign_list(FILE *fp_user_acc, FILE *fp_stu_info, pUSER_ACCOUNT pp_acc, pSTU  pp_stu){
	pUSER_ACCOUNT pNEW_user_link;
	pSTU pNEW_stu_link;
	char line[line_len];

	while (memset(line, 0, sizeof(line)), fgets(line, line_len, fp_user_acc)!=NULL){    //user_account.txt在结尾多了一个回车符。出错
		trim_space(line);
		pNEW_user_link = (pUSER_ACCOUNT)calloc(1, sizeof(USER_ACCOUNT));
		sscanf(line, "%s %s %d %d", pNEW_user_link->user_name, pNEW_user_link->user_pwd, &pNEW_user_link->user_role, &pNEW_user_link->CORRESPOND_ID.admin_id);
		insert_user_list(pp_acc, pNEW_user_link);
	}

	while (memset(line, 0, sizeof(line)), fgets(line, line_len, fp_stu_info) != NULL){ //line_len读取得长度不够
		trim_space(line);
		pNEW_stu_link = (pSTU)calloc(1, sizeof(STU));
		sscanf(line, "%d %s %c %lf %lf %lf %lf %lf", &pNEW_stu_link->stu_id, pNEW_stu_link->stu_name, &pNEW_stu_link->stu_gender, &pNEW_stu_link->score[Math], &pNEW_stu_link->score[English], &pNEW_stu_link->score[DS], &pNEW_stu_link->score[WEB], &pNEW_stu_link->score[OS]);
		insert_stu_list_by_id(pp_stu, pNEW_stu_link);
	}
	
}

void insert_user_list(pUSER_ACCOUNT head, pUSER_ACCOUNT pNEW_user){
	pUSER_ACCOUNT ptraver = head;


	while (ptraver->link != NULL && ptraver->link->CORRESPOND_ID.admin_id < pNEW_user->CORRESPOND_ID.admin_id){
		ptraver = ptraver->link;
	}

	pNEW_user->link = ptraver->link;
	ptraver->link = pNEW_user;

}



void insert_stu_list_by_id(pSTU head, pSTU pNEW_stu){
	pSTU ptraver = head;

	while (ptraver->link != NULL && ptraver->link->stu_id < pNEW_stu->stu_id){
		ptraver = ptraver->link;
	}

	pNEW_stu->link = ptraver->link;
	ptraver->link = pNEW_stu;

}



void trim_space(char*src)  

{
	int fast_index, last_index;
	for (fast_index = 0, last_index = -1; src[fast_index] != 0; fast_index++)
	{
		if (!isspace(src[fast_index]))
		{

			src[++last_index] = src[fast_index];

		}
		else

		{

			if (last_index != -1 && !isspace(src[last_index]))

			{

				src[++last_index] = ' ';

			}

		}

	}

	src[++last_index] = 0;

}



void show_stu_user_list(pUSER_ACCOUNT user_head, pSTU  stu_head){    //显示当前链表中的账户和学生信息
	pUSER_ACCOUNT pUSER_traver = user_head->link;
	pSTU pSTU_traver = stu_head->link;

	printf("USER ACCOUNT: \n");
	while (pUSER_traver != NULL){
		printf("%d %s %s %d\n", pUSER_traver->CORRESPOND_ID.admin_id, pUSER_traver->user_name, pUSER_traver->user_pwd, pUSER_traver->user_role);
		pUSER_traver = pUSER_traver->link;
	}
	printf("STUDENT INFO:\n");
	while (pSTU_traver != NULL){
		printf("%d %s %c %5.2lf %5.2lf %5.2lf %5.2lf %5.2lf\n", pSTU_traver->stu_id, pSTU_traver->stu_name, pSTU_traver->stu_gender, pSTU_traver->score[Math], pSTU_traver->score[English], pSTU_traver->score[DS], pSTU_traver->score[WEB], pSTU_traver->score[OS]);
		pSTU_traver = pSTU_traver->link;
	}
}



void show_stu_info(pSTU stu){   //
	//int index;
	printf("\nID : %d%5sName : %s%5sSex : %c\n", stu->stu_id, " ", stu->stu_name, " ", stu->stu_gender);
	printf("Math    : %.2lf\n", stu->score[0]);  //用映射函数封装成1个函数  ############
	printf("English : %.2lf\n", stu->score[1]);
	printf("DS      : %.2lf\n", stu->score[2]);
	printf("WEB     : %.2lf\n", stu->score[3]);
	printf("OS      : %.2lf\n", stu->score[4]);
}

void show_stu_info_v2(pSTU stu){
	pSTU ptraver = stu->link;
	printf("------------------------------------------------------------------------------\n");
	printf("%5sID%5sName%5sGender%5sMath%5sEnglish%8sDS%8sWEB%8sOS\n","","","","","","","","");
	while (ptraver != NULL) {
		printf("%7d%9s%8c%12.2f%12.2f%10.2f%11.2f%10.2f\n", ptraver->stu_id, ptraver->stu_name, ptraver->stu_gender, ptraver->score[Math], ptraver->score[English], ptraver->score[DS], ptraver->score[WEB], ptraver->score[OS]);
		ptraver = ptraver->link;
	}
	printf("------------------------------------------------------------------------------\n");
	system("pause");//################################
}
int save_stu_file(pSTU head){
	FILE *fp_stu_info;
	pSTU ptraver = head->link;
	file_open_stu(&fp_stu_info, write_mode);
	while (ptraver != NULL){
		fprintf(fp_stu_info, "%d%3s%s%3s%c%3s%7.2lf%7.2lf%7.2lf%7.2lf%7.2lf\n", ptraver->stu_id, " ", ptraver->stu_name, " ", ptraver->stu_gender, " ", ptraver->score[Math], ptraver->score[English], ptraver->score[DS], ptraver->score[WEB], ptraver->score[OS]); //格式是这样存放的么？有没有\n
		ptraver = ptraver->link;
	}
	fclose(fp_stu_info);
	return 1;
}

int save_user_file(pUSER_ACCOUNT head){  
	FILE *fp_user_account;
	pUSER_ACCOUNT ptraver = head->link;
	file_open_user(&fp_user_account, write_mode);
	while (ptraver != NULL){
		fprintf(fp_user_account, "%s%3s%s%3s%d%3s%d\n", ptraver->user_name,"", ptraver->user_pwd, "",ptraver->user_role,"", ptraver->CORRESPOND_ID);
		ptraver = ptraver->link;
	}
	fclose(fp_user_account);
	return 1;
}



void delete_stu_info(pSTU stu,pSTU head){
	pSTU delete = stu->link;
	char confirm;
	FILE *fp_stu_info;
	
	
	printf("\nPlease confirm the one you want to remove :\n");
	show_stu_info(delete);
	
	while (fflush(stdin), printf("Y/N ? "),(confirm = getchar()) != EOF){
		if ('Y' == confirm){

			stu->link = delete->link;
			free(delete);

			save_stu_file(head);
			
			break;
		}
		else if('N' == confirm){
			break;
		}
	}
	
}


void show_user_info(pUSER_ACCOUNT user){
	printf("ID        : %d\n", user->user_role ? user->CORRESPOND_ID.admin_id : user->CORRESPOND_ID.stu_id);
	printf("USER NAME : %s\n", user->user_name);
	printf("USER ROLE : %s\n", user->user_role ? "ADMIN" : "STUDENT");
}

void show_user_info_v2(pUSER_ACCOUNT head){
	pUSER_ACCOUNT ptraver =head->link;
	printf("------------------------------------------------------\n");
	printf("%5sID%5s%USER_NAME%8sUSER_ROLE\n", "", "", "");
	while (ptraver != NULL){
		printf("%7d%14s%17s\n", ptraver->user_role ? ptraver->CORRESPOND_ID.admin_id : ptraver->CORRESPOND_ID.stu_id, ptraver->user_name, ptraver->user_role ? "ADMIN" : "STUDENT");
		ptraver = ptraver->link;
	}
	printf("------------------------------------------------------\n");
	system("pause");
}


USER_ROLE LOGIN_USER(pUSER_ACCOUNT  head){  // 登陆输入用户名到文件里面找，找到了返回它的用户权限
	pUSER_ACCOUNT login;
	FILE *check;
	int index = 0;
	char ch;

	login = (pUSER_ACCOUNT)calloc(1, sizeof(USER_ACCOUNT));
	//char str_checkmode[32];
	check = fopen(configure_path, "r");
	if (check == NULL){
		printf("***SYSTEM ERROR***\n");
		return -1;
	}

	printf("Enter User Name: ");
	scanf("%s", &login->user_name);   //这里应该先检查有没有这个用户！！！#######

	printf("Enter Password: ");
	
	while (fflush(stdin),(ch = getch()) != '\r'){
		if (index < 32){
			login->user_pwd[index++] = ch;
			printf("*");
		}
		else{
			return -1;      //密码不能超过32位。
		}
	}

	return  check_list(login, head);   
	

	
}




void MAIN_FUN(int check_mode , pUSER_ACCOUNT USER_LIST , pSTU STU_LIST){  //#####加一个循环
	int select_mode;
	while (1){
		if (check_mode){
			system("cls");
			show_admin_menu(&select_mode);
			switch (select_mode){
			case 1:
				search_student_info_fun(STU_LIST, select_mode);
				break;
			case 2:
				delete_student_info_fun(STU_LIST, select_mode);
				break;
			case 3:
				add_student_info_fun(STU_LIST, select_mode);
				break;
			case 4:
				modify_student_info_fun(STU_LIST, select_mode);
				break;
			case 5:
				//check_user_authority(USER_LIST);    //###########check 
				add_user_account_fun(USER_LIST, select_mode);
				break;
			case 6:
				update_user_account_fun(USER_LIST, select_mode);
				break;
			case 7:
				delete_user_account_fun(USER_LIST, select_mode);
				break;
			case 8:
				search_user_account_fun(USER_LIST, select_mode);
				break;
			case 9:
				exit(EXIT_SUCCESS);
			}
		}
		else{
			system("cls");
			show_stu_menu(&select_mode);
			switch (select_mode){
			case 1:
				search_student_info_fun(STU_LIST, select_mode);
				break;
			case 9:
				exit(EXIT_SUCCESS);
			}
		}
	}
}


int check_list(pUSER_ACCOUNT login, pUSER_ACCOUNT  head){
	pUSER_ACCOUNT ptraver = head->link;
	while (ptraver != NULL){
		if (strcmp(ptraver->user_name, login->user_name) == 0){
			if (strcmp(ptraver->user_pwd, login->user_pwd) == 0){
				return ptraver->user_role;  // success
			}
			return -1; // pwd fail
		}
		ptraver = ptraver->link;
	}
	return -2; // no this user.
}

void show_scroll(){  //#######  主界面的条幅
	printf("***********************************************************************************************\n");
	printf("**************     ***********    ***********    ************   *************     *************\n");
	printf("*************  ***  *********  **  *********  **  ***********   ************  ***  ************\n");
	printf("**************  ************  ****  *******  ****  **********   *************  ****************\n");
	printf("*****************  ********  ******  *****  ******  *********   ***************  **************\n");
	printf("*************  ***  ******  ********  ***  ********  ********   ************  ***  ************\n");
	printf("***************   *******  **********     **********  *******   **************    *************\n");
	printf("***********************************************************************************************\n");
	printf("********************WELCOME TO MY SMIS*********************************************************\n");
	printf("\n\n");
}


int show_admin_menu(int *select_mode){
	show_scroll();
	printf("%10s%-3d%s\n", " ", 1, M1);
	printf("%10s%-3d%s\n", " ", 2, M2);
	printf("%10s%-3d%s\n", " ", 3, M3);
	printf("%10s%-3d%s\n", " ", 4, M4);
	printf("%10s%-3d%s\n", " ", 5, M5);
	printf("%10s%-3d%s\n", " ", 6, M6);
	printf("%10s%-3d%s\n", " ", 7, M7);
	printf("%10s%-3d%s\n", " ", 8, M8);
	printf("%10s%-3d%s\n", " ", 9, M9);
	printf("\n\nWhat you want to do ? : ");
	
	while (1){
		fflush(stdin);
		scanf("%d", select_mode);
		if (islegal_select(*select_mode)){
			return 0;
		}
		else{
			printf("Try 1~9               : ");
		}
	}

}

int show_stu_menu(int * select_mode){
	show_scroll();
	printf("%10s%-3d%s\n", " ", 1, M1);
	printf("%10s%-3d%s\n", " ", 9, M9);
	printf("\n\nWhat you want to do ? : ");

	while (1){
		fflush(stdin);
		scanf("%d", select_mode);
		if (1 == (*select_mode) || 9 == (*select_mode)){
			return 0;
		}
		else{
			printf("Try 1 or 9            : ");
		}
	}
}


int search_student_info_id(pSTU head){
	int search_id;
	pSTU ptraver = head->link;
	system("cls");
	printf("Search By ID\n\n");

	while (fflush(stdin), printf("The ID of student you want to know : "),scanf("%d", &search_id) != EOF){
		ptraver = head->link;
		while (ptraver != NULL){
			if (ptraver->stu_id == search_id){
				show_stu_info(ptraver);
				break;
			}
			ptraver = ptraver->link;
		}
		if (ptraver == NULL){
			printf("No such a student which ID is: %d\n", search_id);
		}
	}
	return 0;
}

int search_student_info_name(pSTU head){  //这两个用函数指针封装
	char search_name[NAME_SIZE];
	pSTU ptraver = head->link;
	system("cls");
	printf("Search By Name\n\n");

	while (fflush(stdin), printf("The Name of student you want to know : "), scanf("%s", search_name) != EOF){
		ptraver = head->link;
		while (ptraver != NULL){
			if (strcmp(ptraver->stu_name,search_name) == 0){
				show_stu_info(ptraver);
				break;
			}
			ptraver = ptraver->link;
		}
		if (ptraver == NULL){
			printf("No such a student which name is: %s\n", search_name);
		}
	}
	return 0;
}

double sum_score(pSTU stu){
	double sum = 0;
	int	index = 0;
	while (5-index)
	{
		sum += stu->score[index];
		index++;
	}
	return sum;
}

void insert_stu_list_score(pSTU pSORT, pSTU pNEW){
	pSTU ptraver = pSORT;
	
	if (ptraver->link != NULL){
		while (ptraver->link != NULL && sum_score(ptraver->link) < sum_score(pNEW)){
			ptraver = ptraver->link;
		}
		pNEW->link = ptraver->link;
		ptraver->link = pNEW;
	}
	else{
		ptraver->link = pNEW;
	}
}

int search_student_info_all(pSTU head){
	show_stu_info_v2(head);
}



pSTU sort_stu_list(pSTU head){
	pSTU pSORT,
		pNEW,
		ptraver=head->link;

	init_list(NULL, &pSORT);
		
	while (ptraver != NULL){
		pNEW = (pSTU)calloc(1, sizeof(STU));
		(*pNEW) = (*ptraver);
		pNEW->link = NULL;
		insert_stu_list_score(pSORT, pNEW);
		ptraver = ptraver->link;
	}
	return pSORT;
}

int inquire_student_score(pSTU head){
	

}

int inquire_student_rank(pSTU head){
	pSTU psort = sort_stu_list(head),
		ptraver = psort->link;
	int rank = 1;
	int rank_id;
	char confirm_see;
	system("cls");
	
	while (fflush(stdin), printf("You want to know whose rank ? \n"), printf("ID : "), scanf("%d", &rank_id) != EOF){
		while (ptraver != NULL){
			if (ptraver->stu_id == rank_id){
				printf("Your rank is : %d\n", rank);
				break;
			}
			ptraver = ptraver->link;
			rank++;
		}
		if (ptraver == NULL){
			printf("The ID doesn't exist!\n");
		}
		else{
			break;
		}
	}
	while (fflush(stdin), printf("If you want to see all rank? (Y/N)"), scanf("%c", &confirm_see)){
		if ('Y' == confirm_see){
			see_all_rank(psort);
			return 1;
		}
		else if('N' == confirm_see){
			return 0;
		}
	}

}

int see_all_rank(pSTU psort){
	pSTU ptraver = psort->link;
	int index = 1;
	double sum;
	printf("----------------------------------------------------------------------------------------\n");
	printf("%5s%5sID%5sName%5sGender%5sMath%5sEnglish%8sDS%8sWEB%8sOS%8sSUM\n","Rank" ,"", "", "", "", "", "", "", "");
	while (ptraver != NULL) {
		sum = sum_score(ptraver);
		printf("%5d%7d%9s%8c%12.2f%12.2f%10.2f%11.2f%10.2f%11.2f\n",index, ptraver->stu_id, ptraver->stu_name, ptraver->stu_gender, ptraver->score[Math], ptraver->score[English], ptraver->score[DS], ptraver->score[WEB], ptraver->score[OS],sum);
		ptraver = ptraver->link;
		index++;
	}
	printf("----------------------------------------------------------------------------------------\n");
	system("pause");
}

int search_student_info_fun(pSTU head,int select_mode){
	int choose;
	
	while (1){
		system("cls");
		show_title(select_mode);
		fflush(stdin);
		scanf("%d", &choose);
		if (1 == choose){
			search_student_info_id(head);
		}
		else if (2 == choose){
			search_student_info_name(head);
		}
		else if (3 == choose){
			search_student_info_all(head);
		}
		else if (4 == choose){
			inquire_student_rank(head);
		}
		else if(9 == choose){
			return 0;
		}
	}

}


int delete_student_info_id(pSTU head){
	int delete_id;
	pSTU ptraver = head;
	system("cls");
	printf("Delete By ID\n\n");

	while (fflush(stdin), printf("The ID of student you want to remove : "), scanf("%d", &delete_id) != EOF){
		ptraver = head;
		while (ptraver->link != NULL){    
			if (ptraver->link->stu_id == delete_id){              //可以封装一个search函数
				delete_stu_info(ptraver,head);
				break;
			}
			ptraver = ptraver->link;
		}
		if (ptraver->link == NULL){
			printf("The student which id is %d doesn't exist\n", delete_id);
		}
	}
}

int delete_student_info_name(pSTU head){
	char delete_name[NAME_SIZE];
	pSTU ptraver = head;
	system("cls");
	printf("Delete By Name\n\n");

	while (fflush(stdin), printf("The Name of student you want to remove : "), scanf("%s", delete_name) != EOF){
		ptraver = head;
		while (ptraver->link != NULL){
			if (strcmp(ptraver->link->stu_name,delete_name) == 0){              //可以封装一个search函数
				delete_stu_info(ptraver, head);
				break;
			}
			ptraver = ptraver->link;
		}
		if (ptraver->link == NULL){
			printf("The student which name is %s doesn't exist\n", delete_name);
		}
	}
}


int delete_student_info_fun(pSTU head,int select_mode){ //涉及修改应立即放回文件 #######
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		fflush(stdin);
		scanf("%d", &choose);
		if (1 == choose){
			delete_student_info_id(head);
		}
		else if (2 == choose){
			delete_student_info_name(head);
		}
		else if (9 == choose){
			return 0;
		}
	}
}


int add_student(pSTU head){
	pSTU pNEW,
		ptraver = head->link;
	int index,
		flag = 0;
	pNEW = (pSTU)calloc(1, sizeof(STU));
	while (fflush(stdin), flag = 0, printf("\nThe ID for this student is      : "), scanf("%d", &pNEW->stu_id)){
		while (ptraver != NULL){
			if (ptraver->stu_id == pNEW->stu_id){
				printf("The ID already exist! Please check it again! \n");
				flag = 1;
				break;
			}
			ptraver = ptraver->link; 
		}
		if (!flag){
			if (pNEW->stu_id >= 10000 && pNEW->stu_id <= 19999){
				break;
			}
			else{
				printf("The ID must be 10000~19999.\n");
			}
		}
	}
	fflush(stdin);
	printf("The name of the student is       : "); scanf("%s", pNEW->stu_name);
	
	while (fflush(stdin),printf("Gender of  this student          : "), scanf("%c", &pNEW->stu_gender)){
		if ('m' == pNEW->stu_gender || 'f' == pNEW->stu_gender){
			break;
		}
		else{
			printf("The Gender of student must be m or f.\n");
		}
	}
	
	while (fflush(stdin),printf("Score of Math of this student    : "), scanf("%lf", &pNEW->score[Math])){
		if (islegal_score(pNEW->score[Math])){
			break;
		}
		else{
			printf("The score you input were to large! [0,100] .\n");
		}
	}
	//fflush(stdin);
	while (fflush(stdin),printf("Score of English of this student : "), scanf("%lf", &pNEW->score[English])){
		if (islegal_score(pNEW->score[English])){
			break;
		}
		else{
			printf("The score you input were to large! [0,100] .\n");
		}
	}
	
	//fflush(stdin);
	while (fflush(stdin),printf("Score of DS of this student      : "), scanf("%lf", &pNEW->score[DS])){
		if (islegal_score(pNEW->score[DS])){
			break;
		}
		else{
			printf("The score you input were to large! [0,100] .\n");
		}
	}
	//fflush(stdin);
	while (fflush(stdin),printf("Score of WEB of this student     : "), scanf("%lf", &pNEW->score[WEB])){
		if (islegal_score(pNEW->score[WEB])){
			break;
		}
		else{
			printf("The score you input were to large! [0,100] .\n");
		}
	}
	//fflush(stdin);
	while (fflush(stdin),printf("Score of OS of this student      : "), scanf("%lf", &pNEW->score[OS])){
		if (islegal_score(pNEW->score[OS])){
			break;
		}
		else{
			printf("The score you input were to large! [0,100] .\n");
		}
	}

	insert_stu_list_by_id(head,pNEW);
	save_stu_file(head);
	printf("This information has been saved.\n\n");
	
}

int add_student_info(pSTU head){
	static int add_index = 0;
	int flag = 1;
	char confirm_continue;
	system("cls");

	while (1){
		add_student(head);
		add_index++;
		printf("If you want to continue ? : \n");
		printf("(Y/N) ");
		while (fflush(stdin), scanf("%c", &confirm_continue) != EOF){   
			if ('Y' == confirm_continue){
				//add_student_info(head);
				break;
			}
			else if ('N' == confirm_continue){
				printf("\nYou have add %d new students.\n", add_index);
				add_index = 0;  //下一次执行de时候不会出现直接出现if语句里面
				Sleep(1000);
				return 0;
			}
		}

	}

}

int add_student_info_fun(pSTU head,int select_mode){   //增加学生信息的功能
	int choose;
	while (1){ 
		system("cls");
		show_title(select_mode);
		fflush(stdin);
		scanf("%d", &choose);
		if (1 == choose){
			add_student_info(head);
		}
		else if( 9 == choose){
			return 0;
		}
	}
}

int modify_stu_id(pSTU modi,int * temp_stu_id){
	//int temp_stu_id;

	printf("You want to modify student ID\n");
	printf("%d  ----->    ", modi->stu_id);
	scanf("%d", temp_stu_id);
}

int modify_stu_name(pSTU modi, char *temp_stu_name){
	char stu_name[NAME_SIZE];
	printf("You want to modify student NAME\n");
	printf("%s  ----->    ", modi->stu_name);
	scanf("%s", stu_name);
	strcpy(temp_stu_name, stu_name);
}

int modify_stu_gender(pSTU modi, char *temp_gender){
	printf("You want to modify student GENDER\n");
	printf("%c  ----->    ", modi->stu_gender);
	scanf("%c", temp_gender);
}

int modify_stu_score(pSTU modi, int whichone, double *temp_score){
	if (Math == whichone ){
		printf("You want to modify MATH\n");
		printf("%5.2lf  ----->    ", modi->score[Math]);
		fflush(stdin);
		scanf("%lf", &temp_score[Math]);
	}
	else if ( English == whichone ){
		printf("You want to modify ENGLISH\n");
		printf("%5.2lf  ----->    ", modi->score[English]);
		fflush(stdin);
		scanf("%lf", &temp_score[English]);
	}
	else if (DS == whichone){
		printf("You want to modify DS\n");
		printf("%5.2lf  ----->    ", modi->score[DS]);
		fflush(stdin);
		scanf("%lf", &temp_score[DS]);
	}
	else if (WEB == whichone){
		printf("You want to modify WEB\n");
		printf("%5.2lf  ----->    ", modi->score[WEB]);
		fflush(stdin);
		scanf("%lf", &temp_score[WEB]);
	}
	else {
		printf("You want to modify OS\n");
		printf("%5.2lf  ----->    ", modi->score[OS]);
		fflush(stdin);
		scanf("%lf", &temp_score[OS]);
	}
}

int modify_student_info(pSTU head, pSTU modi){
	//FILE *fp_stu_info;
	int temp_stu_id,
		choose_modify;
	char temp_stu_name[NAME_SIZE];
	char temp_gender;
	char confirm_modi;
	double temp_score[5];

	memset(temp_score, 0, sizeof(temp_score));
	memset(temp_stu_name, 0, sizeof(temp_stu_name));

	printf("The current data of this student is : \n");
	show_stu_info(modi);

	while (1){
		printf("choose one to modify :\n");
		printf(" 1   STU_ID\n");
		printf(" 2   STU_NAME\n");
		printf(" 3   STU_GENDER\n");
		printf(" 4   STU_SCORE MATH\n");
		printf(" 5   STU_SCORE ENGLISH\n");
		printf(" 6   STU_SCORE DS\n");
		printf(" 7   STU_SCORE WEB\n");
		printf(" 8   STU_SCORE OS\n");
		printf(" 9   ALL OF SCORE\n");
		printf(" 0   ALL OF ABOVE\n");
		printf("-1   IF YOU WANT TO CANCLE THIS STEP\n\n");
		scanf("%d", &choose_modify);
		if (-1 == choose_modify){
			printf("You are leaving this manipulate .....\n");
			Sleep(1000);
			return 0;
		}
		if (1 == choose_modify || 0 == choose_modify){
			modify_stu_id(modi, &temp_stu_id);
		}
		if (2 == choose_modify || 0 == choose_modify){
			modify_stu_name(modi, temp_stu_name);
		}
		if (3 == choose_modify || 0 == choose_modify){
			modify_stu_gender(modi, &temp_gender);
		}
		if (4 == choose_modify || 0 == choose_modify || 9 == choose_modify){
			modify_stu_score(modi, Math, temp_score);
		}
		if (5 == choose_modify || 0 == choose_modify || 9 == choose_modify){
			modify_stu_score(modi, English, temp_score);
		}
		if (6 == choose_modify || 0 == choose_modify || 9 == choose_modify){
			modify_stu_score(modi, DS, temp_score);
		}
		if (7 == choose_modify || 0 == choose_modify || 9 == choose_modify){
			modify_stu_score(modi, WEB, temp_score);
		}
		if (8 == choose_modify || 0 == choose_modify || 9 == choose_modify){
			modify_stu_score(modi, OS, temp_score);
		}

		while (fflush(stdin), printf("Confirm change? (Y/N) "), scanf("%c", &confirm_modi) != EOF){
			if ('Y' == confirm_modi){
				switch (choose_modify){
				case 1:
					modi->stu_id = temp_stu_id;
					break;
				case 2:
					strcpy(modi->stu_name, temp_stu_name);
					break;
				case 3:
					modi->stu_gender = temp_gender;
					break;
				case 4:
					modi->score[Math] = temp_score[Math];
					break;
				case 5:
					modi->score[English] = temp_score[English];
					break;
				case 6:
					modi->score[DS] = temp_score[DS];
					break;
				case 7:
					modi->score[WEB] = temp_score[WEB];
					break;
				case 8:
					modi->score[OS] = temp_score[OS];
					break;
				case 9:
					modi->score[Math] = temp_score[Math];
					modi->score[English] = temp_score[English];
					modi->score[DS] = temp_score[DS];
					modi->score[WEB] = temp_score[WEB];
					modi->score[OS] = temp_score[OS];
					break;
				case 0:
					modi->stu_id = temp_stu_id;
					strcpy(modi->stu_name, temp_stu_name);
					modi->stu_gender = temp_gender;
					modi->score[Math] = temp_score[Math];
					modi->score[English] = temp_score[English];
					modi->score[DS] = temp_score[DS];
					modi->score[WEB] = temp_score[WEB];
					modi->score[OS] = temp_score[OS];
				}
				printf("--------------------------------------------------------\n");
				show_stu_info(modi);
				printf("--------------------------------------------------------\n");
				save_stu_file(head);
				return 0;
			}
			else if ('N' == confirm_modi){
				break;
			}

			
		}
		

	}

}

int modify_student_info_id(pSTU head){
	pSTU ptraver = head->link;
	int modify_id;
	static int modify_index = 0;
	char modify_confirm;
	
	
	
	while (fflush(stdin), system("cls"),printf("Modify Student file By ID\n\n"), printf("The student you want to modify his/her file which ID is : "), scanf("%d", &modify_id) != EOF){
		ptraver = head->link;
		while (ptraver != NULL){
			if (ptraver->stu_id == modify_id){
				modify_student_info(head, ptraver);
				modify_index++;
				break;
			}
			ptraver = ptraver->link;
		}

		if (ptraver == NULL){
			printf("The student you want modify is not exist!.\n");
			//Sleep(1000);
		}

		if (modify_index > 0){
			while (fflush(stdin), printf("If you want to continue this manipulate? (Y/N) "), scanf("%c", &modify_confirm) != EOF){
				if ('Y' == modify_confirm){
					//modify_student_info_id(head);
					break;
				}
				else if ('N' == modify_confirm){
					printf("You have changed %d student files.\n", modify_index);
					modify_index = 0;
					return 0;
				}
			}

		}
	}

}


int modify_student_info_name(pSTU head){
	pSTU ptraver = head->link;
	char modify_name[NAME_SIZE];
	static int modify_index = 0;
	char modify_confirm;

	system("cls");
	printf("Modify Student file By Name\n\n");

	
	

	while (fflush(stdin), printf("The student you want to modify his/her file which Name is : "), scanf("%s", modify_name) != EOF){
		ptraver = head->link;
		while (ptraver != NULL){
			if (strcmp(ptraver->stu_name, modify_name) == 0){
				modify_student_info(head, ptraver);
				modify_index++;
				break;
			}
			ptraver = ptraver->link;
		}

		if (ptraver == NULL){
			printf("The student you want modify is not exist!.\n");
		}

		if (modify_index > 0){
			while (fflush(stdin), printf("If you want to continue this manipulate? (Y/N) "), scanf("%c", &modify_confirm) != EOF){
				if ('Y' == modify_confirm){
					//modify_student_info_id(head);
					break;
				}
				else if ('N' == modify_confirm){
					printf("You have changed %d student files.\n", modify_index);
					modify_index = 0;
					return 0;
				}
			}

		}
	}
}

int modify_student_info_fun(pSTU head,int select_mode){
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		scanf("%d", &choose);

		if (1 == choose){
			modify_student_info_id(head);
		}
		else if (2 == choose){
			modify_student_info_name(head);
		}
		else if(9 == choose){
			return 0;
		}
	}
}


pUSER_ACCOUNT check_if_user_exist_id(pUSER_ACCOUNT head, int id){
	pUSER_ACCOUNT ptraver = head;

	while (ptraver->link != NULL){
		if (1 == ptraver->link->user_role){
			if (id == ptraver->link->CORRESPOND_ID.admin_id){
				return ptraver;
			}
		}
		else{
			if (id == ptraver->link->CORRESPOND_ID.stu_id ){
				return ptraver;
			}
		}
		ptraver = ptraver->link;
	}
	return NULL;
}


pUSER_ACCOUNT check_if_user_exist_name(pUSER_ACCOUNT head, char * check_name){
	pUSER_ACCOUNT ptraver = head;

	while (ptraver->link != NULL){
		if (strcmp(ptraver->link->user_name,check_name) == 0){
			return ptraver;
		}
		ptraver = ptraver->link;
	}
	return NULL;
}

int add_user_account(pUSER_ACCOUNT head){
	pUSER_ACCOUNT pNEW;
	char check_pwd[PWD_SIZE];
	
	

	while (fflush(stdin), pNEW = (pUSER_ACCOUNT)calloc(1, sizeof(USER_ACCOUNT)), printf("Entitle a AUTHORITY for this user : (1 for admin / 0 for student)"), scanf("%d", &pNEW->user_role)!=EOF){
		memset(check_pwd, 0, sizeof(check_pwd));
		
		if (1 == pNEW->user_role){
			fflush(stdin);
			printf("Entitle admin ID for this user : ");scanf("%d",&pNEW->CORRESPOND_ID.admin_id);   //因为是联合，所以这个位置不管你变量名是不是不已不已，但存的数据都是一样的，所以stu的会和admin的比
			if (check_if_user_exist_id(head, pNEW->CORRESPOND_ID.admin_id)){
				printf("This user already exist ! \n");
				continue;
			}
			else{
				printf("Give me her/his Name : "); scanf("%s", pNEW->user_name);
				
				while (fflush(stdin), printf("Enter password       : "), scanf("%s", pNEW->user_pwd)!=EOF){
					printf("Confirm password      : "); scanf("%s", check_pwd);
					if (strcmp(check_pwd, pNEW->user_pwd) == 0){
						printf("User Account have been successful added !\n");
						insert_user_list(head, pNEW);
						save_user_file(head);
						Sleep(1000);
						return 0;
					}
					else{
						printf("Password not match!\n");
					}
				}
				
			}
		}
		else if (0 == pNEW->user_role){
			fflush(stdin);
			printf("Entitle STU ID for this user : ");scanf("%d",&pNEW->CORRESPOND_ID.stu_id);
			//check_if_user_exist(head, pNEW->CORRESPOND_ID.stu_id);
			if (check_if_user_exist_id(head, pNEW->CORRESPOND_ID.stu_id)){
				printf("This user already exist ! \n");
				continue;
			}
			else{
				printf("Give me her/his Name : "); scanf("%s", pNEW->user_name);

				while (fflush(stdin), printf("Enter password       : "), scanf("%s", pNEW->user_pwd) != EOF){
					printf("Confirm password      : "); scanf("%s", check_pwd);  //提供两种选择明文，暗文###########
					if (strcmp(check_pwd, pNEW->user_pwd) == 0){
						printf("User Account have been successful added !\n");
						insert_user_list(head, pNEW);
						save_user_file(head);
						Sleep(1000);
						return 0;
					}
					else{
						printf("Password not match!\n");
					}
				}

			}

		}
	}
	
}


int add_user_account_fun(pUSER_ACCOUNT head,int select_mode){
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		
		scanf("%d", &choose);
		if (1 == choose){
			add_user_account(head);
		}
		else{
			return 0;
		}
		
	}
}



int update_user_name(pUSER_ACCOUNT pmodi,char * modi_name){
	char modi_temp_name[NAME_SIZE];
	printf("You want to modify :\n");
	printf("%s  ------->     ", pmodi->user_name);
	scanf("%s", modi_temp_name);
	strcpy(modi_name, modi_temp_name);
	return 1;
}

int update_user_password(pUSER_ACCOUNT pmodi,char *modi_pwd){
	char modi_temp_pwd[PWD_SIZE],
		confirm_pwd[PWD_SIZE];
	int times = 3,
		index;
	char pwd;
	printf("You want to modify password:\n");
	
	while (fflush(stdin), times){
		printf("Please enter the current password : "); scanf("%s", modi_temp_pwd);
		if (strcmp(modi_temp_pwd, pmodi->user_pwd) == 0){
			while (index = 0, printf("Enter the New password : ")){
				while (fflush(stdin), (pwd = getch()) != '\r'){
					modi_temp_pwd[index++] = pwd;
					printf("*");
				}
				printf("\n");
				printf("Confirm the password   : ");
				while (fflush(stdin), (pwd = getch()) != '\r'){
					confirm_pwd[index++] = pwd;
					printf("*");
				}
				printf("\n");
				if (strcmp(modi_temp_pwd,confirm_pwd) == 0){
					strcpy(modi_pwd, modi_temp_pwd);
					return 1;
				}
				else{
					printf("Password isn't identify ! try again\n");
				}
			}
		}
		else{
			printf("\nInvalid Password . \n");
			times--;
		}
	}
	printf("You have tried three times.. Check your password again!\n");
	Sleep(1000);
	return 0;
}

int update_user_role(pUSER_ACCOUNT pmodi,int *role){
	printf("You want to modify :\n");
	printf("%d  -------->   ", pmodi->user_role);
	scanf("%d", role);
	return 1;
}



int update_user_account(pUSER_ACCOUNT pmodi,pUSER_ACCOUNT head){
	int choose;
	char modi_name[NAME_SIZE];
	char modi_pwd[PWD_SIZE];
	char confirm_modi;
	int modi_role;
	int step_res;
	
	printf("The current account information is :\n");
	show_user_info(pmodi);
	while (1){
		step_res = 1;
		memset(modi_name, 0, sizeof(modi_name));
		memset(modi_pwd, 0, sizeof(modi_pwd));
		printf("choose which you want to modify\n");
		printf(" 1   USER_NAME\n");
		printf(" 2   USER_PASSWORD\n");
		printf(" 3   USER_ROLE\n");
		printf(" 4   ALL OF ABOVE\n");
		printf("-1   CANCLE THIS MANIPULATE\n");
		printf(": ");
		fflush(stdin);
		scanf("%d", &choose);
		if (-1 == choose){
			return 0;
		}
		if (1 == choose || 4 == choose){
			update_user_name(pmodi, modi_name);
		}
		if (2 == choose || 4 == choose){            //################失败就不要再往下了
			step_res = update_user_password(pmodi, modi_pwd);
		}
		if (step_res && (3 == choose || 4 == choose)){
			update_user_role(pmodi, &modi_role);
		}
		else{
			printf("Operation Failed . \n");
			continue;
		}


		while (fflush(stdin), printf("If you confirm your manipulating? (Y/N) "), scanf("%c", &confirm_modi)){
			if ('Y' == confirm_modi){
				switch (choose){
				case 1:
					strcpy(pmodi->user_name, modi_name);
					break;
				case 2:
					strcpy(pmodi->user_pwd, modi_pwd);
					break;
				case 3:
					pmodi->user_role = modi_role;
					break;
				case 4:
					strcpy(pmodi->user_name, modi_name);
					strcpy(pmodi->user_pwd, modi_pwd);
					pmodi->user_role = modi_role;
					break;
				}
				save_user_file(head);
				printf("Your modification was successful saved . \n");
				Sleep(1000);
				return 1;

			}
			else if ('N' == confirm_modi){
				return 0;
			}
		}
	
	}
}

int update_user_account_id(pUSER_ACCOUNT head){
	pUSER_ACCOUNT pmodi;
	int modi_id;
	while (fflush(stdin), printf("Enter the ID of account you want to modify : "),scanf("%d", &modi_id)){
		//scanf("%d", &modi_id);
		if (pmodi = check_if_user_exist_id(head, modi_id)){
			update_user_account(pmodi->link,head);
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
	
}

int update_user_account_name(pUSER_ACCOUNT head){
	pUSER_ACCOUNT pmodi;
	char check_name[NAME_SIZE];

	while (fflush(stdin), printf("Input the name of user you want to modify : "), scanf("%s", check_name)){
		if (pmodi = check_if_user_exist_name(head, check_name)){
			update_user_account(pmodi->link,head);
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
}

int update_user_account_fun(pUSER_ACCOUNT head,int select_mode){
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		scanf("%d", &choose);
		if (1 == choose){
			update_user_account_id(head);
		}
		else if (2 == choose){
			update_user_account_name(head);
		}
		else{
			return 0;
		}
	}
}


int delete_user_account(pUSER_ACCOUNT pmodi, pUSER_ACCOUNT head){
	pUSER_ACCOUNT pdelete = pmodi->link;
	char confirm_delete;
	printf("Confirm that you want to delete :\n");
	show_user_info(pdelete);
	while (fflush(stdin), printf("( Y/N ):"),scanf("%c",&confirm_delete)){
		if ('Y' == confirm_delete){
			printf("Deleting ....\n");
			pmodi->link = pdelete->link;
			free(pdelete);
			printf("Deleting successful\n");
			Sleep(1000);
			save_user_file(head);
			return 1;
		}
		else if ('N' == confirm_delete){
			return 0;
		}

	}
	
}

int delete_user_account_id(pUSER_ACCOUNT head){
	pUSER_ACCOUNT pmodi;
	int modi_id;
	while (fflush(stdin), printf("Enter the ID of account you want to delete : "), scanf("%d", &modi_id)){
		//scanf("%d", &modi_id);
		if (pmodi = check_if_user_exist_id(head, modi_id)){
			delete_user_account(pmodi, head);
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
}

int delete_user_account_name(pUSER_ACCOUNT head){
	pUSER_ACCOUNT pmodi;
	char check_name[NAME_SIZE];

	while (fflush(stdin), printf("Input the name of user you want to delete : "), scanf("%s", check_name)){
		if (pmodi = check_if_user_exist_name(head, check_name)){
			delete_user_account(pmodi, head);
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
}

int delete_user_account_fun(pUSER_ACCOUNT head,int select_mode){
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		scanf("%d", &choose);
		
		if (1 == choose){
			delete_user_account_id(head);
		}
		else if (2 == choose){
			delete_user_account_name(head);
		}
		else{
			return 0;
		}
		
	}
}


int search_user_account_id(pUSER_ACCOUNT head){
	pUSER_ACCOUNT psearch;
	int modi_id;
	while (fflush(stdin), printf("Enter the ID of account you want to search : "), scanf("%d", &modi_id)!=EOF){
		//scanf("%d", &modi_id);
		if (psearch = check_if_user_exist_id(head, modi_id)){
			//delete_user_account(pmodi, head);
			show_user_info(psearch->link);
			system("pause");
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
}

int search_user_account_name(pUSER_ACCOUNT head){
	pUSER_ACCOUNT psearch;
	char check_name[NAME_SIZE];

	while (fflush(stdin), printf("Input the name of user you want to search: "), scanf("%s", check_name)!=EOF){
		if (psearch = check_if_user_exist_name(head, check_name)){
			//delete_user_account(pmodi, head);
			show_user_info(psearch->link);
			system("pause");
			return 0;
		}
		else{
			printf("The account doesn't exist!\n");
		}
	}
}


int search_user_account_fun(pUSER_ACCOUNT head,int select_mode){
	int choose;

	while (1){
		system("cls");
		show_title(select_mode);
		scanf("%d", &choose);

		if (1 == choose){
			search_user_account_id(head);
		}
		else if (2 == choose){
			search_user_account_name(head);
		}
		else if (3 == choose){
			show_user_info_v2(head);
			//system("pause");
		}
		else{
			return 0;
		}
	}
}


void show_title(int select_mode){
	switch (select_mode){
	case 1:
		printf("%s\n\n", M1);
		printf("%d  %s\n", 1, "SEARCH BY ID");
		printf("%d  %s\n", 2, "SEARCH BY NAME");
		printf("%d  %s\n", 3, "SEARCH ALL");
		printf("%d  %s\n", 4, "INQUIRE RANK");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 2:
		printf("%s\n\n", M2);
		printf("%d  %s\n", 1, "DELETE BY ID");
		printf("%d  %s\n", 2, "DELETE BY NAME");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 3:
		printf("%s\n\n", M3); 
		printf("%d  %s\n", 1, "ADD STUDENT");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 4:
		printf("%s\n\n", M4); 
		printf("%d  %s\n", 1, "MODIFY STUDENT INFO BY ID");
		printf("%d  %s\n", 2, "MODIFY STUDENT INFO BY NAME");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 5:
		printf("%s\n\n", M5); 
		printf("%d  %s\n", 1, "ADD USER ACCOUNT");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 6:
		printf("%s\n\n", M6);
		printf("%d  %s\n", 1, "UPDATE USER ACCOUNT BY ID");
		printf("%d  %s\n", 2, "UPDATE USER ACCOUNT BY NAME");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 7:
		printf("%s\n\n", M7); 
		printf("%d  %s\n", 1, "DELETE USER ACCOUNT BY ID");
		printf("%d  %s\n", 2, "DELETE USER ACCOUNT BY NAME");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	case 8:
		printf("%s\n\n", M8); 
		printf("%d  %s\n", 1, "SEARCH USER BY ID");
		printf("%d  %s\n", 2, "SEARCH USER BY NAME");
		printf("%d  %s\n", 3, "SEARCH ALL");
		printf("%d  %s\n", 9, "return menu");
		printf("Which one you want to do? : ");
		break;
	}
}

