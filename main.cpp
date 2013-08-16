/*
double <name> ()
{
	std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > vect;
	
	std::set
	
	std::vector < int > v;
	v.push_back(1);
	
	std::map < std::vector < int >, double > m;
	m[v] = 3.14;
	
	vect.push_back(std::make_pair(std::make_pair(m,"hello World!"),std::make_pair(8.863653865, 12)));
	
	return (3.14 * 8.0000001 + 7.30985793)/18.987345;
}
*/

/*

"\tstd::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > vect;\n\
\tstd::set < std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > > s;\n\
\tstd::vector < int > v;\n\
\tv.push_back(1);\n\
\tstd::map < std::vector < int >, double > m;\n\
\tm[v] = 3.14;\n\
\tvect.push_back(std::make_pair(std::make_pair(m,"hello World!"),std::make_pair(8.863653865, 12)));\n\
\ts.insert(vect);\n\
\tstd::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > vect2;\n\
\tstd::set < std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > > s2;\n\
\tstd::vector < int > v2;\n\
\tv2.push_back(1);\n\
\tstd::map < std::vector < int >, double > m2;\n\
\tm2[v] = 3.14;\n\
\tvect2.push_back(std::make_pair(std::make_pair(m2,"World, Hello!"),std::make_pair(123.863653865, 1882)));\n\
\ts2.insert(vect2);\n"

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char str_MAIN_FOLDER [] = "program/";

char str_include [] = "#include";

char str_CC [] = "CC=g++";
char str_CFLAGS [] = "CFLAGS=-c -Wall -O2";
char str_LDFLAGS [] = "LDFLAGS=";
char str_SOURCES [] = "SOURCES=";
char str_OBJECTS [] = "OBJECTS=$(SOURCES:.cpp=.o)";
char str_EXECUTABLE [] = "EXECUTABLE=prg";
char str_all [] = "all: $(SOURCES) $(EXECUTABLE)";
char str_EXECUTABLE_TO_OBJECTS [] = "$(EXECUTABLE): $(OBJECTS)\n\t@$(CC) $(LDFLAGS) $(OBJECTS) -o $@\n\t@echo \"LD \"$(OBJECTS) -o $EXECUTABLE";
char str_CPP_O [] = ".cpp.o:";
char str_CPP_TO_O [] = "\t@$(CC) $(CFLAGS) $< -o $@\n\t@echo \"CC \" $<";

void reverse(char s[])
{
	int i, j;
	char c;
 
	for(i = 0, j = strlen(s)-1; i<j; i++, j--) 
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void itoa(int n, char s[])
{
	int i, sign;

	if((sign = n) < 0)
		n = -n;
    
	i = 0;

	do
	{
		s[i++] = n % 10 + '0';
	}
	while((n /= 10) > 0);

	if(sign < 0)
		s[i++] = '-';
    
	s[i] = '\0';
	reverse(s);
}

void CreateMakeFile(int count)
{
	FILE * fp = fopen("program/makefile","w");
	
	if(fp == NULL)
		return;
	
	fprintf(fp,"%s\n",str_CC);
	fprintf(fp,"%s\n",str_CFLAGS);
	fprintf(fp,"%s\n",str_LDFLAGS);
	fprintf(fp,"%s\\\n",str_SOURCES);
	
	char path [100];
	char buffer [100];
	
	fprintf(fp,"\tmain.cpp\\\n");
	
	int i = 0;
	
	for(i=0;i<count-1;i++)
	{
		memset(path,0,sizeof(char) * 100);
		memset(buffer,0,sizeof(char) * 100);
		
		itoa(i,buffer);
		strcat(buffer,".cpp");
		
		fprintf(fp,"\t%s\\\n",buffer);
	}
	
	memset(path,0,sizeof(char) * 100);
	memset(buffer,0,sizeof(char) * 100);
		
	itoa(i,buffer);
	strcat(buffer,".cpp");
		
	fprintf(fp,"\t%s\n",buffer);
	
	fprintf(fp,"%s\n",str_OBJECTS);
	fprintf(fp,"%s\n\n",str_EXECUTABLE);
	fprintf(fp,"%s\n\n",str_all);
	fprintf(fp,"%s\n\n",str_EXECUTABLE_TO_OBJECTS);
	fprintf(fp,"%s\n",str_CPP_O);
	fprintf(fp,"%s\n",str_CPP_TO_O);
	
	fclose(fp);
}

void WriteToFile(const char * path, const char * info)
{
	FILE * fp = fopen(path,"w");
	
	if(fp == NULL)
		return;
	
	fprintf(fp,"%s",info);
	
	fclose(fp);
}

void CreateMain(int count)
{
	FILE * fp = fopen("program/main.cpp","w");
	
	if(fp == NULL)
		return;
	
	char path [100];
	char buffer [100];
	
	fprintf(fp,"#include <stdio.h>\n");
	
	for(int i=0;i<count;i++)
	{
		memset(path,0,sizeof(char) * 100);
		memset(buffer,0,sizeof(char) * 100);
		
	//	strcpy(path,"program/");
		
		itoa(i,buffer);
		strcat(buffer,".h");
		
		strcat(path,buffer);
		
		fprintf(fp,"#include \"%s\"\n",path);
	}
	
	fprintf(fp,"\nint main()\n{\n\tdouble res = 0;\n");
	
	for(int i=0;i<count;i++)
	{
		memset(path,0,sizeof(char) * 100);
		memset(buffer,0,sizeof(char) * 100);
		
		itoa(i,buffer);
		
		strcpy(path,"\tres += h_");
		strcat(path,buffer);
		strcat(path,"();\n");
		strcat(path,"\tres /= 1;\n");
		
		fprintf(fp,"%s",path);
	}
	
	char ch1 = '%';
	
	fprintf(fp,"\n\tprintf(\"%cf\\n\",res);\n\tputs(\"OK\");\n\treturn 0;\n}",ch1);
	
	fclose(fp);
}

int main(int argc, char ** argv)
{
	int count = 10;
	
	if(argc > 1)
	{
		count = atoi(argv[1]);
	}

	char dir [100];
	
	strcpy(dir,"program");
	
	mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	char path [100];
	char buffer [100];
	char buffer1 [2000];

	for(int i=0;i<count;i++)
	{
		memset(path,0,sizeof(char) * 100);
		memset(buffer,0,sizeof(char) * 100);
		
		strcpy(path,str_MAIN_FOLDER);
		
		itoa(i,buffer);
		
		strcat(path,buffer);
		strcat(path,".cpp");
		
		memset(buffer1,0,sizeof(char) * 2000);
		
		strcpy(buffer1,"#include \"");
		strcat(buffer1,buffer);
		strcat(buffer1,".h");
		strcat(buffer1,"\"\n");
		strcat(buffer1,"#include <vector>\n#include <string>\n#include <utility>\n#include <map>\n#include <set>\n");
		strcat(buffer1,"\ndouble h_");
		strcat(buffer1,buffer);
	//	strcat(buffer1,"_h");
		strcat(buffer1," ()\n{\n\t\
std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > vect;\n\
\tstd::set < std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > > s;\n\
\tstd::vector < int > v;\n\
\tv.push_back(1);\n\
\tstd::map < std::vector < int >, double > m;\n\
\tm[v] = 3.14;\n\
\tvect.push_back(std::make_pair(std::make_pair(m,\"hello World!\"),std::make_pair(8.863653865, 12)));\n\
\ts.insert(vect);\n\
\tstd::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > vect2;\n\
\tstd::set < std::vector < std::pair< std::pair< std::map < std::vector < int >,double >,std::string >,std::pair< double, int > > > > s2;\n\
\tstd::vector < int > v2;\n\
\tv2.push_back(1);\n\
\tstd::map < std::vector < int >, double > m2;\n\
\tm2[v] = 3.14;\n\
\tvect2.push_back(std::make_pair(std::make_pair(m2,\"World, Hello!\"),std::make_pair(123.863653865, 1882)));\n\
\ts2.insert(vect2);\n\
\treturn (3.14 * 8.0000001 + 7.30985793)/18.987345;\n}");
		
		WriteToFile(path,buffer1);
	//	printf("[%s]",buffer1);
		
		memset(path,0,sizeof(char) * 100);
		memset(buffer,0,sizeof(char) * 100);
		
		strcpy(path,str_MAIN_FOLDER);
		
		itoa(i,buffer);
		
		strcat(path,buffer);
		strcat(path,".h");
		
		memset(buffer1,0,sizeof(char) * 300);
		
		strcpy(buffer1,"double h_");
		strcat(buffer1,buffer);
		strcat(buffer1," ();");
		
		WriteToFile(path,buffer1);
		
		if(i % 1000 == 0)
			printf("%d\n",i);
	}

	CreateMain(count);
	
	CreateMakeFile(count);

	return 0;
}
