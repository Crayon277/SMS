#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<windows.h>

#define configure_path "C:\\王道专用\\SMS\\SMS\\configure.txt"   //这个要绝对路径
#define read_mode 1
#define write_mode 2

#define line_len 128

#define M1 "search       student information"
#define M2 "delete       student information"
#define M3 "add          student information"
#define M4 "modify       student information"
#define M5 "add          user account"
#define M6 "update       user account"
#define M7 "delete       user account"
#define M8 "search       user account"
#define M9 "exit"

#define islegal_select(a) (a>=1 && a<=9)
#define islegal_score(a) (a>=0 && a<=100)

#define NAME_SIZE 32
#define PWD_SIZE 32
typedef char USER_NAME;
typedef char USER_PWD;
typedef int USER_ROLE;  //用户权限，1是管理员，0是学生

typedef int STU_ID;
typedef int ADMIN_ID;

typedef char STU_NAME;
typedef char STU_GENDER;
typedef double ACHIEVEMENT;



enum{Math,English,DS,WEB,OS}course;

typedef struct user_account_info {
	USER_NAME user_name[NAME_SIZE];
	USER_PWD user_pwd[PWD_SIZE];
	USER_ROLE user_role;
	
	union {
		STU_ID stu_id;
		ADMIN_ID admin_id;
	}CORRESPOND_ID;


	struct user_account_info * link;
}USER_ACCOUNT,*pUSER_ACCOUNT;


typedef struct student_info{
	STU_ID stu_id;
	STU_NAME stu_name[NAME_SIZE];
	STU_GENDER stu_gender;
	ACHIEVEMENT score[5];
	struct student_info * link;
}STU,*pSTU;



void init_list(pUSER_ACCOUNT *pp_user, pSTU * pp_stu);

void file_open_user(FILE **fp_user_account, int mode);

void file_open_stu(FILE **fp_stu_info, int mode);

//发现有修改就要存盘
int save_stu_file(pSTU head);
int save_user_file(pUSER_ACCOUNT head);


void assign_list(FILE *fp_user_acc, FILE *fp_stu_info, pUSER_ACCOUNT pp_acc, pSTU  pp_stu);

void trim_space(char*src);

void insert_user_list(pUSER_ACCOUNT head, pUSER_ACCOUNT pNEW_user);

void insert_stu_list_by_id(pSTU head, pSTU pNEW_stu);

void show_stu_user_list(pUSER_ACCOUNT user_head, pSTU  stu_head); //测试用

void show_stu_info(pSTU stu);

void delete_stu_info(pSTU stu, pSTU head);  //

void show_user_info(pUSER_ACCOUNT user);


pUSER_ACCOUNT check_if_user_exist_id(pUSER_ACCOUNT head, int id);
pUSER_ACCOUNT check_if_user_exist_name(pUSER_ACCOUNT head, char * check_name);


void insert_stu_list_by_score(pSTU head, pSTU p_stu);  // 待实现

void init_system(pUSER_ACCOUNT pp_acc, pSTU  pp_stu);  //带头节点。之前就先初始化

//pSTU search_stu_list(pSTU head ,int );   //函数指针   ############################################

//pUSER_ACCOUNT search_user_list(pUSER_ACCOUNT head,);  //函数指针########################################

int check_list(pUSER_ACCOUNT login, pUSER_ACCOUNT  head); //从 head里面找是否有login的信息  //登陆成功返回权限，密码错误返回-1，无信息返回-2

USER_ROLE LOGIN_USER();       // 登陆输入用户名到文件里面找，找到了返回它的用户权限

void MAIN_FUN(int check_mode,pUSER_ACCOUNT USER_LIST,pSTU STU_LIST);

void show_scroll();  //################

int show_admin_menu(int *select_mode);

int show_stu_menu(int *select_mode);

void show_title(int select_mode);

int check_user_authority(pUSER_ACCOUNT pUser);

pSTU sort_stu_list(pSTU head);

int search_student_info_all(pSTU head);

int search_student_info_id(pSTU head);

int search_student_info_name(pSTU head);

int inquire_student_score(pSTU head);

int inquire_student_rank(pSTU head);

int see_all_rank(pSTU head);

int search_student_info_fun(pSTU head , int select_mode);//查找学生信息的功能
			

int delete_student_info_id(pSTU head);

int delete_student_info_name(pSTU head);

int delete_student_info_fun(pSTU head, int select_mode);



int add_student_info(pSTU head);   //具体de添加动作

int add_student_info_fun(pSTU head, int select_mode);//添加界面和选择



int modify_stu_id(pSTU modi,int * temp_stu_id);

int modify_stu_name(pSTU modi,char * temp_stu_name);

int modify_stu_gender(pSTU modi , char *temp_gender);

int modify_stu_score(pSTU modi, int whichone , double *temp_score);

int modify_student_info(pSTU head, pSTU modi);

int modify_student_info_id(pSTU head);

int modify_student_info_name(pSTU head);

int modify_student_info_fun(pSTU head, int select_mode);



int add_user_account(pUSER_ACCOUNT head);

int add_user_account_fun(pUSER_ACCOUNT head, int select_mode);




int update_user_name(pUSER_ACCOUNT pmodi);

int update_user_password(pUSER_ACCOUNT pmodi);

int update_user_role(pUSER_ACCOUNT pmodi);

int update_user_account(pUSER_ACCOUNT pmodi,pUSER_ACCOUNT head);

int update_user_account_id(pUSER_ACCOUNT head);

int update_user_account_name(pUSER_ACCOUNT head);


int update_user_account_fun(pUSER_ACCOUNT head, int select_mode);






int delete_user_account_id(pUSER_ACCOUNT head);

int delete_user_account_name(pUSER_ACCOUNT head);

int delete_user_account_fun(pUSER_ACCOUNT head, int select_mode);




int search_user_account_id(pUSER_ACCOUNT head);

int search_user_account_name(pUSER_ACCOUNT head);

int search_user_account_fun(pUSER_ACCOUNT head, int select_mode);





