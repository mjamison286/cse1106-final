#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>

#define PIN 17
#define MAX 10
#define PATH "../status.txt"

int addReading(double*, int);
int checkTemp(double, int, int);
double calculateAverage(double*, int);
int saveToFile(FILE*, double*, int);
void changeRange(int*, int*);
void displayAll(double*, int, int, int);

int lowest = 68;
int highest = 76;

int main(int argc, char* argv[])
{
	double readings[MAX];
	int readingCount = 0;
	
	FILE* fptr;
	
	gpioInitialise();
	gpioSetMode(PIN, PI_OUTPUT);

	while(1)
	{
		int choice;
		
		printf("-- Temperature Controller --\n");
		printf("1 - Add a reading (up to %d)\n", MAX);
		printf("2 - Display all readings\n");
		printf("3 - Calculate the average of the readings\n");
		printf("4 - Change the acceptable temperature range\n");
		printf("5 - Save readings to a file\n");
		printf("6 - Exit\n\n");
		
		scanf("%d", &choice);
		while(getchar() != '\n');
		
		switch(choice)
		{
			case 1:
				if(addReading(readings, count++) != 0)
				{
					count--;
				}
				
				checkTemp(readings[count - 1]);
				
				break;
			case 2:
				displayAll(readings, count);
				break;
			case 3:
				double average = calculateAverage(readings, count);
				printf("The calculated average is: %lf\n", average);
				break;
			case 4:
				changeRange(&lowest, &highest);
				break;
			case 5:
				if(saveToFile(fptr, readings, count) != 0)
				{
					printf("Failed to save to file.\n");
				}
				break;
			case 6:
				fclose(fptr);
				free(fptr);
				gpioWrite(PIN, 0);
				gpioTerminate();
				return 0;
			default:
				printf("Invalid choice. Try again.\n\n");
				break;
		}
	}
	
	gpioWrite(PIN, 0);
	gpioTerminate();
	return 0;
}

int addReading(double* array, int index)
{
	if(index >= MAX)
	{
		printf("You already have the maximum amount of readings.\n");
		return 1;
	}
	
	double reading;
	
	printf("Enter the temperature reading: ");
	
	scanf("%lf", &reading);
	
	array[index] = reading;
	
	return 0;
}

int checkTemp(double reading)
{
	if(reading > highest || reading < lowest)
	{
		gpioWrite(PIN, 1);
		return 1;
	}
	else
	{
		gpioWrite(PIN, 0);
		return 0;
	}
}

double calculateAverage(double* array, int count)
{
	double sum = 0;
	
	for(int i = 0; i < count; i++)
	{
		sum += array[i];
	}
	
	return sum / count;
}

int saveToFile(FILE* file, double* array, int count);
{
	file = fopen(PATH, "a");
	
	if(file == NULL)
	{
		printf("Could not open the file.\n");
		return 1;
	}
	
	for(int i = 0; i < count; i++)
	{
		if(checkTemp(array[i], lowest, highest) == 0)
		{
			fprintf("%lf	-	NORMAL\n", array[i]);
		}
		else
		{
			fprintf("%lf	-	WARNING\n", array[i]);
		}
	}
	
	fclose(file);
	free(file);
	
	return 0;
}

void changeRange(int* lptr, int* hptr)
{
	int lowest;
	int highest;
	
	printf("Enter the lowest acceptable temperature, to the nearest degree: ");
	scanf("%d", &lowest);
	while(getchar() != '\n');
	
	printf("Enter the highest acceptable temperature, to the nearest degree: ");
	scanf("%d", &highest);
	while(getchar() != '\n');
	
	*lptr = lowest;
	*hptr = highest;
}

void displayAll(double* array, int count)
{
	for(int i = 0 ; i < count; i++)
	{
		if(checkTemp(array[i], lowest, highest) == 0)
		{
			printf("%lf		-	NORMAL\n", array[i]);
		}
		else
		{
			printf("%lf		-	WARNING\n", array[i]);
		}
	}
}
