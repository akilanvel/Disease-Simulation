#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

int main() {

	//create variables to hold values from input file
	int requiredInfectious = 0; //number of infectious agents required in a neighborhood to infect a susceptible
	int infectiousPeriod = 0; //number of days it takes for an infected agent to recover
	int frequency = 0; //how frequently the region should be displayed in days
	int numSusceptible = 0; //count of susceptible agents
	int numInfectious = 0; //count of infectious agents
	int numRecovered = 0; //count of recoevered agents
	int numVaccinated = 0; //count of vaccinated agents
	bool noInfectious = 0; //whether there are no infectious agents
	int numRows = 0; //number of columns in grid

	//read input parameters from input file
	cout << "Enter the name of the file from which the input will be read (including .txt)" << endl;
	string temporaryName; //name of input file
	cin >> temporaryName; //get name of input file
	ifstream inputFile;
	inputFile.open(temporaryName.c_str()); //initialize input file stream
	if (!inputFile) { //check if file was opened
		cout << "Unable to open " << temporaryName << "." << endl;
	}
	char x; //placeholder variable for letters
	for (int i = 0; i < 10; i++) { //ignore the word before the number
		inputFile >> x;
	}
	inputFile >> requiredInfectious; //input requiredInfectious
	for (int i = 0; i < 17; i++) { //ignore the word before the number
		inputFile >> x;
	}
	inputFile >> infectiousPeriod; //input infectious period
	for (int i = 0; i < 8; i++) { //ignore the word before the number
		inputFile >> x;
	}
	inputFile >> frequency; //input frequency

	//read input for grid and output it
	char temp;//temp character for reading in next letter.
	//bool lmao = true;
	char tempp;//tempp value used to test where commas where to find number of rows
	vector<char> temporary;//temporary vector used to hold values to be inputed into the grid vector later
	for (int i = 0; inputFile.get(temp); i++) {//iterates through the input file to read in all values
		if (i > 0) {// tests for every input value besides the first
			if (temp == ',') {
			} else if (temp == 's') {//tests if file reads in a susceptable agent
				numSusceptible++;//adds 1 to numsusceptible if true
				temporary.push_back(temp);//inputs the susceptable agent into the temporary vector for later
				if (tempp != ',') {//checks for new row by the lack of a comma and if so adds one to num rows
					numRows++;
				}
			} else if (temp == 'i') {//tests if file reads in infectious agent
				numInfectious++;//adds 1 to numinfectious if true
				temporary.push_back(temp);//inputs the infectious agent into the temporary vector for later
				if (tempp != ',') {// checks for new row by the lack of a comma and if so adds one to num rows
					numRows++;
				}
			} else if (temp == 'v') {//tests if file reads in vaccinated agent
				numVaccinated++;//adds 1 to numvaccinated if true
				temporary.push_back(temp);//inputs the vaccinated agent into the temporary vector for later
				if (tempp != ',') {// checks for new row by the lack of a comma and if so adds one to num rows
					numRows++;
				}
			} else if (temp == 'r') {//tests if file reads in recovered agent
				numRecovered++;//adds 1 to numrecovered if true
				temporary.push_back(temp);//inputs the vaccinated agent into the temporary vector for later
				if (tempp != ',') {//checks for new row by the lack of a comma and if so adds one to num rows.
					numRows++;
				}
			}
		}
		tempp = temp;//sets tempp to temp for the next iteration for finding new rows
	}
	cout << endl;
	cout << "Number of susceptible individuals: " << numSusceptible << endl;
	cout << "Number of infectious individuals: " << numInfectious << endl;
	cout << "Number of recovered individuals: " << numRecovered << endl;
	cout << "Number of vaccinated individuals: " << numVaccinated << endl;//couts important information counted from the file

	vector<vector<char> > grid(numRows);//creates 2d vector grid that will be used for the rest fo the function
	int index = 0;//counting variable
	for (int i = 0; i < numRows; i++) {//loop to iterate through temporary vector to input into the grid vector
		for (int x = 0; x < numRows; x++) {//loop to iterate through the number of rows
			grid[i].push_back(temporary[index]);//Pushing back each row with a vector
			index++;//Moving on to the next section
		}
	}

	cout << "DAY: 0" << endl;

	//Printing out the board on day 0 using the values appended to grid above
	for (int i = 0; i < numRows; i++) {
		for (int x = 0; x < numRows; x++) {
			cout << grid[i][x] << " ";
		}
		cout << endl;
	}
	cout << endl;

	vector<vector<char> > grid2(numRows);//A temporary grid that stores changes computed off the original
	//Copying the elements from grid to grid2
	for (int i = 0; i < numRows; i++) {
		for (int x = 0; x < numRows; x++) {
			grid2[i].push_back(grid[i][x]);//Pushing back element by element
		}
	}

	//Helps determine when a infected cell will be recovered. 
	vector<vector<int> > count(numRows);
	for (int i = 0; i < numRows; i++) {
		for (int x = 0; x < numRows; x++) {//Iterate through the rows and columns of grid
			if (grid[i][x] == 'i') {
				count[i].push_back(infectiousPeriod);//The initial value is the infectious period from the file
			} else {
				count[i].push_back(0);//A recovered cell or a cell not yet infected has a value of 0
			}
		}
	}


	bool notDone = true;//notdone must be false to exit the simulation
	int dayCounter=1;//This is 1 because day 0 has already been printed
	vector<int> maxInfectious;//The index of the max of this vector is the peak day
	maxInfectious.push_back(numInfectious);//Appending day 0's infectious value
	//run simulation
	while (notDone) {
		bool print = false;
		int numInfectiouss = 0;//The daily value of infectious
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numRows; x++) {
				int numNeighborhood = 0;//This is the number of infectious(i's) in the neighborhood of an s
				if (grid[i][x] == 'i') {
					numInfectious++;//Increment the daily value
				}
				if (grid[i][x] == 's') {//We calculate numneighborhood by finding every 's'.
					//TOP LEFT
					if (i != 0) {//If it is not on the top row
						if (x == 0) {//If it is in the first column(left)
							if (grid[i - 1][numRows - 1] == 'i') {//checking on the other side(right), and up one row(special case)
								numNeighborhood++;
							}
						} else {//If it is not in the first column
							if (grid[i - 1][x - 1] == 'i') {//Check normally, up and to the left.
								numNeighborhood++;
							}
						}
					}
					//Top Right
					if (i != 0) {
                                                if (x == numRows - 1) {
                                                        if (grid[i - 1][0] == 'i') {//Checking the other side(left), and up one row(special case)
                                                                numNeighborhood++;
                                                        }
                                                } else {
                                                        if (grid[i - 1][x + 1] == 'i') {//Checking up(i-1) and to the right(x+1)
                                                                numNeighborhood++;
                                                        }
                                                }
                                        }
					//Down Left
 					if (i != numRows - 1) {//If it is not on the bottom
                                                if (x == 0) {
                                                        if (grid[i + 1][numRows - 1] == 'i') {//Special case 
                                                                numNeighborhood++;
                                                        }
                                                } else {
                                                        if (grid[i + 1][x - 1] == 'i') {//Check normally, down and to the left
                                                                numNeighborhood++;
                                                        }
                                                }
                                        }
					//Down Right
					if (i != numRows - 1) {//If it not on the bottom
                                                if (x == numRows - 1) {//If it is on the rightmost column
                                                        if (grid[i + 1][0] == 'i') {//Special case
                                                                numNeighborhood++;
                                                        }
                                                } else {
                                                        if (grid[i + 1][x + 1] == 'i') {//Check normally, down(i+1) and to the right(x+1)
                                                                numNeighborhood++;
                                                        }
                                                }
                                        }

					//Directly Above
					if (i != 0) {
                                               	if (grid[i - 1][x] == 'i') {
                                                        numNeighborhood++;
                                                }
                                        }

					//Directly Below
					if (i != numRows - 1) {
                                                if (grid[i + 1][x] == 'i') {
                                                        numNeighborhood++;
                                                }
	                                }
					if (x != numRows - 1) {
                                                if (grid[i][x + 1] == 'i') {
                                                        numNeighborhood++;
                                                }
                                        } else if (x == numRows - 1) {
						if (grid[i][0] == 'i') {
							numNeighborhood++;
						}
					}
					if (x != 0) {
                                                if (grid[i][x - 1] == 'i') {
                                                        numNeighborhood++;
	                                        }
                                        } else if (x == 0) {//
						if (grid[i][numRows - 1] == 'i') {
							numNeighborhood++;
						}
					}
				}
				if (numNeighborhood >= requiredInfectious) {
					grid2[i][x] -= 10; //ascii values
					count[i][x] = infectiousPeriod + 1;//+1 because we decrement even current day values below
				}
			}
		}
	
		//This is the countdown, decrementing every cell that has a count > 0. Once it is zero, it turns back to recovered.
		for (int i = 0; i < numRows; i++) {
                        for (int x = 0; x < numRows; x++) {//Iterate element by element
                                if (count[i][x] > 0) {//s,r,v cells not affected
                                        count[i][x]--;
                                        if (count[i][x] == 0) {
                                                grid2[i][x] = 'r';//Once a cell hits zero, it is done being infectious
                                        }
                                }
                        }
                }
		
		//We are done with the day, we want to make the new day=old day
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numRows; x++) {//Iterate
				grid[i][x] = grid2[i][x];//Set element by element
			}
		}
		
		//We dont want to print the days that are not multiples of the display
		if (dayCounter % frequency == 0) {
			print = true;
			cout << "DAY: " << dayCounter << endl;
			for (int i = 0; i < numRows; i++) {
				for (int x = 0; x < numRows; x++) {
					cout << grid[i][x] << " ";//Printing element by element
				}
				cout << endl;
			}
			cout << endl;
		}

		//Used to find the max infectious
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numRows; x++) {
				if (grid[i][x] == 'i') {
					numInfectiouss++;//Every time we find an i, we increment the value for that day
				}
			}
		}
		maxInfectious.push_back(numInfectiouss);//Appending the number of infectious on that day

		//We want to determine whether we are done with the simulation
		bool test = true;//Assumes we are done
		for (int i = 0; i < numRows; i++) {
			for (int x = 0; x < numRows; x++) {
				if (grid[i][x] !=  'r'  && grid[i][x] != 'v' && grid[i][x] != 's') {//In other words, if the cell contains an i, the simulation is not over
					test = false;//
				}
			}
		}
		notDone = !test;//If the above if does not trigger, then notdone=!true=false, and we exit the main while loop
	
		//This is printing the final day.
		if (notDone == false && dayCounter % frequency != 0) {//If the final day is a multiple of display, it will already be printed. We don't want that.
			cout << "DAY: " << dayCounter << endl;
			for (int i = 0; i < numRows; i++) {
				for (int x = 0; x < numRows; x++) {
					cout << grid[i][x] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}

		dayCounter++;//Move to the next day
	}

	//print out post-simulation required information
	int temppp = 0;//This is a placeholder that increases every time a larger value appears
	int indexx = 0;//This is the index that has the highest infectious
	for (int i = 0; i < maxInfectious.size(); i++) {
		if (maxInfectious[i] > temppp) {
			temppp = maxInfectious[i];//Change max value
			indexx = i;//Change index of max value
		}
	}
	cout << "Outbreak ends: Day " << dayCounter - 1 << endl;
	cout << "Peak day: Day " << indexx << endl;

	//The final values on the end of the outbreak
	numSusceptible = 0;
	numInfectious = 0;
	numRecovered = 0;
	numVaccinated = 0;
	
	//Iterating through grid and incrementing every time a type of cell is found
	for (int i = 0; i < numRows; i++) {
		for (int x = 0; x < numRows; x++) {
			if (grid[i][x] == 's') {
				numSusceptible++;
			} else if (grid[i][x] == 'i') {
				numInfectious++;
			} else if (grid[i][x] == 'r') {
				numRecovered++;
			} else if (grid[i][x] == 'v') {
				numVaccinated++;
			}
		}
	}

	//Printing the final counts
	cout << "S: " << numSusceptible << endl;
	cout << "I: " << numInfectious << endl;
	cout << "R: " << numRecovered << endl;
	cout << "V: " << numVaccinated << endl;
	cout << endl;

	return 0;
}
