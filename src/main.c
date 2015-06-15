/*
 * main.c
 * 
 * Copyright 2015 Michael Davenport <Davenport.physics@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <string.h>

typedef struct MagContainer {
	
	int i;
	float mag[4];
	
} MagContainer;

typedef struct TotalContainer {
	
	char string[4];
	
	float tot[4];
	
} TotalContainer;

static int NumberOfAtoms = 0;
static char Filename[128] = {'\0'};

void Initialize();
void Read_and_Write_data();

int main(int argc, char **argv)
{
	
	Initialize();
	Read_and_Write_data();
	
	return 0;
}

void Initialize() {
	
	printf("How many atoms are present? -> ");
	scanf("%d", &NumberOfAtoms);
	getchar();
	
	printf("Please type in the file you wish to use -> ");
	fgets(Filename, 128, stdin);
	
	int x;
	for (x = 0;x < 128;x++) {
	
		if (Filename[x] == '\n')
			Filename[x] = '\0';
		
	}
	
}

void Read_and_Write_data() {
	
	FILE *fp = fopen(Filename, "r");
	
	if (fp == NULL) {
	
		printf("%s not found", Filename);
		return;
		
	}
	
	/*
	 * skips the first two lines
	 * 
	 * */
	char buffer[256];
	fgets(buffer, 256, fp);
	fgets(buffer, 256, fp);
	
	/*
	 * Creates a new file called $Filename-New. This is where the data
	 * will be outputted to.
	 * */
	char NewFilename[256] = {'\0'};
	strncpy(NewFilename, Filename, strlen(Filename));
	strncat(NewFilename, "-NEW", 4);
	NewFilename[255] = '\0';
	FILE *fpp = fopen(NewFilename, "w");
	
	int x;
	for (x = 0;x < NumberOfAtoms;x++) {
		
		MagContainer temp;
		fscanf(fp, "%d%f%f%f%f", &temp.i, &temp.mag[0], &temp.mag[1], &temp.mag[2], &temp.mag[3]);
		fprintf(fpp, "%d,%f,%f,%f,%f\n", temp.i, temp.mag[0], temp.mag[1], temp.mag[2], temp.mag[3]);
		
	}
	/*
	 * Skips the ------- line
	 * Reads the last line and outputs to the $Filename-New File
	 * 
	 * */
	fgets(buffer, 256, fp);
	fgets(buffer, 256, fp);
	TotalContainer temp;
	fscanf(fp, "%s%f%f%f%f", temp.string, &temp.tot[0], &temp.tot[1], &temp.tot[2], &temp.tot[3]);
	fprintf(fpp,"%s,%f,%f,%f,%f", temp.string, temp.tot[0], temp.tot[1], temp.tot[2], temp.tot[3]);
	
	fclose(fp);
	fclose(fpp);
	
}
