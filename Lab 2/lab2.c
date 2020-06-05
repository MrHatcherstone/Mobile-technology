  /*Протарифицировать абонента с IP-адресом 217.15.20.194 с коэффициентом k: 0,5руб/Мб*/
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  
int main(void) 
{		
	long int InternetPeriod = 0; //Подсчёт трафика за 1 минуту
	long int InternetAll = 0; //Подсчёт общего трафика
	char arr[49][49]; //тут будет строка из отсортированного файла
	char hour[6];
	char min[6]; //current
	char minprev[4]; //previous
	char time[3][3]; //тут будет хранится дата и время в отдельных ячейках
	char *endinternet;
	
	FILE *fIN = fopen("sorted.csv", "r");
	FILE *fOUT = fopen("graph.plt", "w");
	
	if(fIN == NULL) 
	{
		perror("Unable to open source file!");
		exit(1);
	}

	if(fOUT == NULL) 
	{
		perror("Unable to open destination file!");
		exit(1);
	}

	char *line = NULL;
	size_t len = 0;

	int counter2 = 0;
	float period;
	
	//настройка выходного документа для корректной постройки графика
	fprintf (fOUT, "%s\n","set terminal jpeg");
	fprintf (fOUT, "%s\n","set terminal jpeg size 2000, 500");
	fprintf (fOUT, "%s\n\n","set output \"res.jpg\""); 
	fprintf (fOUT, "%s\n","set xdata time");
	fprintf (fOUT, "%s\n","set timefmt \"%H:%M\"");
	fprintf (fOUT, "%s\n","set ylabel \"Kb\"");
	fprintf (fOUT, "%s\n\n","set xrange[\"10:32\":\"12:29\"]");
	fprintf (fOUT, "%s\n\n","plot '-' using 1:2 w linespoints");
	
	while(getline(&line, &len, fIN) != -1) 
	{
		int counter = 0;
		char *point = strtok(line, ",");
		
		while( point != NULL )
		{
			strcpy(arr[counter++],point);
			point = strtok(NULL,",");
		}
		// разделение на дату и число
		char *timer = strtok(arr[0], " ");
		int i =0;
		
		while( timer != NULL )
		{
			strcpy(time[i++],timer);
			timer = strtok(NULL," ");
		}
		
		timer = strtok(time[1], ":");
		i = 0;
		// разделение времени на час минута секунда
		while( timer != NULL )
		{
			strcpy(time[i++],timer);
			timer = strtok(NULL,":");
		}
		
		if (!(strcmp(arr[4],"217.15.20.194")))
		{	
			strcpy(min,time[1]);
			strcpy(hour,time[0]);
			
			InternetAll += strtol(arr[12], &endinternet, 10);
			InternetPeriod += strtol(arr[12], &endinternet, 10);
			period = InternetPeriod / 1024; // в выходной файле трафик в Кб
		
			if ((counter2>0))
			{
				if (strcmp(min,minprev))
				{
					fprintf (fOUT, "%s:%s %.2f\n",hour,min, period);
					InternetPeriod = 0;			
				}	
			}
			else
			{
				counter2++;
			}
			strcpy(minprev,min); // текущая минута стал прошедшей 
		}	
	}

	fprintf (fOUT, "%s:%s %.2f\n%s",hour, minprev, period, "e"); //gnuplot требует символ "e" в конце документа
	
	float Result = InternetAll/1048576; //общий трафик в Мб
	float amount = InternetAll / 1048576 * 0.5; //кф 0.5 руб/Мб
	
	printf("%s %4.f %s\n","Total internet flow:", Result , "Mb");
	printf("%s %.2f %s", "Total cost:", amount, "Rub\n");
	
	fclose(fIN);
	fclose(fOUT);
	free(line);
	return 0;
}