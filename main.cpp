/*
 * Copyright (c) 2010-2016 Stephane Poirier
 *
 * stephane.poirier@oifii.org
 *
 * Stephane Poirier
 * 3532 rue Ste-Famille, #3
 * Montreal, QC, H2X 2L1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <string>
#include <fstream>
#include <vector>

#include <iostream>
#include <sstream>
using namespace std;
//#include <stdlib.h>

#include <ctime>
#include <windows.h>

int main(int argc, char *argv[])
{
	///////////////////
	//read in arguments
	///////////////////
	char wavfoldername[2048] = {"."};
	double maxdetectionduration_s = 1.0f;
	if(argc>1)
	{
		//first argument is the maximum wav file length in seconds, i.e. longer wav files shall be ignored
		strcpy_s(wavfoldername, 2048-1, argv[1]);
	}
	if(argc>2)
	{
		//second argument is the segment length in seconds
		maxdetectionduration_s = atof(argv[2]);
	}

	////////////////////////////////////////////
	//execute cmd line to get all .wav filenames
	////////////////////////////////////////////
	string path = wavfoldername;
	string quote;
	quote = "\"";
	path = path + "\\" + "*.wav";
	string command = "DIR " + quote + path + quote + " /S /B /O:N > filenames.txt";
	//system("DIR *.wav /S /B /O:N > filenames.txt");
	system(command.c_str());

	///////////////////////////////////////
	//load filenames.txt into string vector
	///////////////////////////////////////
	vector<string> filenames;
	ifstream ifs("filenames.txt");
	string temp;
	while(getline(ifs,temp))
		filenames.push_back(temp);


	//////////////////////////////////////////////////////////
	//browse throught filenames and call spipitchdetection.exe
	//////////////////////////////////////////////////////////
	string cmdbuffer;
	char pCharBuffer[64];
	sprintf_s(pCharBuffer, 64-1, "%f", maxdetectionduration_s);

	vector<string>::iterator it;	
	int i=filenames.size();
	for ( it=filenames.begin() ; it < filenames.end(); it++ )
	{
		cout << *it << endl; //*it is a .wav filename
		cmdbuffer = "spipitchdetection.exe " + quote + *it + quote + " " + pCharBuffer;
		cout << cmdbuffer << endl;
		system(cmdbuffer.c_str()); 

		Sleep(maxdetectionduration_s*1000);
		cout << endl << "remaining number of files = " << i << endl;
		Sleep(0.1*maxdetectionduration_s*1000);
		i--;
	}	
	return 0;
}