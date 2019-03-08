//name:学生选修课程系统
//20190228 by 林明洋
//function:假定有n门课程,每门课程有课程编号课程名称课程性质开课
//总学时授课学时实验或上机学时学分
// 等信息,学生可按要求(如总学分不能少于10)自由选课.
// 试设计一选修课程系统提供下列功能:
// 1)系统以菜单方式工作
// 2)课程信息录入功能
// 3)课程信息浏览功能
// 4)查询功能:按学分查询
// 按课程性质查询
// 5)课程信息的删除与修改
// 6)学生选修课程,并将学生所选课程信息存入文件.

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int count;//记录课程数量

//课程信息
typedef struct subject{
  char ID[20];//课程编号
  char name[100];//课程名称
  char property[100];//课程性质
  char course[200];//开课
  int hours;//总学时
  int teach_hours;//授课学时
  int experiment_hours;//实验或上机学时
  int credit;//学分
  struct subject *next;
} LinkList;

LinkList *creat();
void Menu(LinkList *list);
void DataEntry(LinkList *list, int n);
void change(LinkList *list);
void Viewinfo(LinkList *list);
void Search(LinkList *list);
void Select(LinkList *list);
void back(LinkList *list);

int main(){
  LinkList *head;

  head=creat();

  Menu(head);

  return 0;
}

//菜单
void Menu(LinkList *list){
  int func;
	//菜单选项
  printf("请输入功能对应的序号\n");
  printf("1)选修课程\n");
  printf("2)课程信息浏览\n");
  printf("3)查询\n");
  printf("4)课程信息录入\n");
  printf("5)课程信息的删除与修改\n");
  printf("输入\'6\'退出系统\n\n");
	//功能输入
  scanf("%d", &func);
	//功能选择
	if(func<7&&func>0){
	  switch(func){
    	case 1:Select(list);break;
    	case 2:Viewinfo(list);break;
    	case 3:Search(list);break;
    	case 4:DataEntry(list,count);break;
    	case 5:change(list);break;
    	case 6:;
  	}
	}
	else{
		printf("输入错误!\n");
		Menu(list);
	}
}

//课程信息录入
void DataEntry(LinkList *list, int n){
	LinkList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}//移动指针

	in = (LinkList*)malloc(sizeof(LinkList));

	//输入信息提示
	puts("按提示输入课程信息:");
  printf("课程编号:");
  scanf("%s",&in->ID);
  printf("课程名称:");
  scanf("%s",&in->name);
  printf("课程性质:");
  scanf("%s",&in->property);
  printf("实验或上机学时:");
  scanf("%d",&in->experiment_hours);
  printf("授课学时:");
  scanf("%d",&in->teach_hours);
  printf("学分:");
  scanf("%d",&in->credit);
  printf("总学时:");
  scanf("%d",&in->hours);
  printf("开课:");
  scanf("%s",&in->course);

	in->next = t->next;//填充in节点的指针域，也就是说把in的指针域指向t的下一个节点
	t->next = in;//填充t节点的指针域，把t的指针域重新指向in
  count++;//记录课程数量

  back(list);//返回菜单
}

//课程信息的删除与修改
void change(LinkList *list){//n为第n个节点
  LinkList *t = list, *in;
  int a,n;
	int i = 0;

  puts("输入要更改或删除的课程序号: ");
  scanf("%d",&n);

	while (i < n && t != NULL) {
    in = t;
		t = t->next;
		i++;
	}

  puts("1)更改课程信息\n2)删除课程信息\n");
  scanf("%d",&a);
	//更改课程信息
  if(a == 1){
    if (t != NULL){
      int j;
		  puts("选择要修改的项");
      printf("1)课程编号\n2)课程名称\n3)课程性质\n4)实验或上机学时\n");
      printf("5)授课学时\n6)学分\n7)总学时\n8)开课\n");
		  scanf("%d",&j);
      switch(j){
        case 1:printf("课程编号:");scanf("%s", &t->ID);break;
        case 2:printf("课程名称:");scanf("%s", &t->name);break;
        case 3:printf("课程性质:");scanf("%s", &t->property);break;
        case 4:printf("实验或上机学时:");scanf("%d", &t->experiment_hours);break;
        case 5:printf("授课学时:");scanf("%d", &t->teach_hours);break;
        case 6:printf("学分:");scanf("%d", &t->credit);break;
        case 7:printf("总学时:");scanf("%d", &t->hours);break;
        case 8:printf("开课:");scanf("%s", &t->course);break;
      }
	  }
	  else {
		  puts("课程信息不存在");
	  }
  }
	// 删除课程信息
  else if(a == 2){
    if (t != NULL) {
		  in->next = t->next;
      count--;
		  free(t);
	  }
	  else {
		  puts("节点不存在");
	  }
  }
	//错误处理
  else{
    puts("输入错误!");
  }

	back(list);
}

//建立链表储存信息
LinkList *creat(){
	LinkList *head, *end;//定义头节点,尾部节点；
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	end = head;         //若是空链表则头尾节点一样
	end->next = NULL;    //结束创建
	return head;
}

//课程信息浏览
void Viewinfo(LinkList *list){
  LinkList *h = list;

  while (h->next != NULL) {
		h = h->next;
		//显示课程信息
		printf("(%d)************************\n",count);
    printf("课程编号:%s\n课程名称:%s\n课程性质:%s\n", h->ID,
         h->name, h->property);
    printf("总学时:%d\n授课学时:%d\n实验或上机学时:%d\n", h->hours,
         h->teach_hours, h->experiment_hours);
    printf("学分:%d\n开课:%s\n", h->credit,h->course);
    printf("***************************\n\n");
	}
  back(list);
}

//查询
void Search(LinkList *list){
  int credit,flag=0,i=0,j=0;
  LinkList *t = list;

  printf("输入学分来查询: ");
  scanf("%d",&credit);

  while (i < count+1){
    if(credit==t->credit){
			j++;//给信息编序号
      printf("(%d)************************\n",j);
      printf("课程编号:%s\n课程名称:%s\n课程性质:%s\n", t->ID,
         t->name, t->property);
      printf("总学时:%d\n授课学时:%d\n实验或上机学时:%d\n", t->hours,
         t->teach_hours, t->experiment_hours);
      printf("学分:%d\n开课:%s\n", t->credit,t->course);
      printf("***************************\n\n");
    }
		t = t->next;
		i++;
    flag=1;
	}

  if(flag==0){
    printf("无符合条件课程\n");
  }

  back(list);
}

//选修课程
void Select(LinkList *list){
  int num[11]={1};
  FILE *fp;
  fp=fopen("选课结果.txt","w+");

	for(int i=1;num[i-1]!=0;i++){
		LinkList *t = list;
		int j=0;

		printf("请输入序号选择课程(输入0退出):");
		scanf("%d",&num[i]);
		//结束选项
		if(num[i]==0){
			break;
		}
		//输出文本
		while (j < num[i] && t != NULL) {
			t = t->next;
			j++;
		}
		fprintf(fp,"(%d)课程名称:%s\n", i, t->name);
	}
	fclose(fp);

  back(list);
}

//返回菜单
void back(LinkList *list){
    char a;
    getchar();
    printf("输入回车返回菜单\n");
    scanf("%c", &a);
    if(a=='\n')Menu(list);
    else{
      puts("输入错误!\n");
      back(list);
    }
}
