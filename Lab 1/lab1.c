#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("data.csv","r");
	char *endin, *endout, *endsms, *arr[5];
	double  minin, minout, price = 0.0;
	int sms = 0;
	do
	{
		int counter = 0;
		char buff[1024];
		fgets(buff, 1024, (FILE*)fp); 
		char *point = strtok(buff,",");
	
		while( point != NULL )
		{
			arr[counter] = point;
			point = strtok(NULL,",");
			counter++;
		}
		
		if (!(strcmp(arr[1],"915783624")))
		{
			minout += strtold(arr[3], &endout);
			sms += strtol(arr[4], &endsms, 10);
		}
		
		if (!(strcmp(arr[2],"915783624")))
		{
			minin += strtold(arr[3], &endin);
		}
	}
	while((getc(fp))!=EOF);
	
	if (sms < 10) 
		sms = 0;
	else 
		sms -= 10;
	
	price = minout * 2 + sms * 1 + minin * 0;
	printf("%s %.2f %s", "Total price is", price, "Rub\n");
	
	return 0;
}
