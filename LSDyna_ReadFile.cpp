#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <functional>
#include <tuple>
#include <optional>

using namespace std;

// Create a class to define the settings of individual keywords by creating methods with their names
// This way, each keyword can have distinct settings 
// Eeach keyword method gives the same two outputs
// The first output is the number of columns the keyword has per line 
// The second output is a string vector containing the keyword data after evaluation and ready for printing 
class KeywordSettings {
private:
	vector<string> defaultValuesList;
	int bigger_integer, max_size;

public:

	// Create a method to define whether a string is a number 
	// Change the string to double and save the number of characters processed
	// Return true if the number of characters processed matches the size of the string 
	bool isStringNumber(const string& input_aux) {
		try {
			size_t pos;
			double result = stod(input_aux, &pos);
			return pos == input_aux.size();
		}
		catch (...) {
			return false;
		}
	}

	// Create a method to erase the blank spaces (strip the string) 
	// The non-whitespaces are caught and used for this purpose 
	string stripString(const string& str) {
		size_t start = str.find_first_not_of(" \t\n\r\f\v");
		size_t end = str.find_last_not_of(" \t\n\r\f\v");
		return (start == string::npos) ? "" : str.substr(start, end - start + 1);
	}

	// Create a method for the keyword "control_termination"
	// The method contains an optional input string 
	// This is done because a keyword method is called two times when reading a file
	// The first time it is only needed to define the number of columns so no input vector is given
	// The second call is used to input the data and evaluate it using the keyword method 
	tuple<int, vector<string>> control_termination(const vector<string>& strVec = {}) {
		int ColumnNumber;
		vector<string> importedData;
		importedData = strVec;
		vector<string> checkedData(importedData.size());
		if (!strVec.empty()) {
			ColumnNumber = 8;
			// Define the vector of default values 
			defaultValuesList = { "0.0", "0", "0.0", "0.0", "10E8", "0" };
			// Get the maximum size of the keyword
			bigger_integer = ceil(static_cast<double>(defaultValuesList.size()) / ColumnNumber);
			max_size = bigger_integer * ColumnNumber;
			// Check for the maximum size 
			if (max_size < importedData.size()) {

				cout << "The input file format for the keyword " << "*CONTROL_TERMINATION" << " is not correct!" << endl;
				exit(EXIT_FAILURE);
			}
			// Check for the minimum size
			if (importedData.size() < defaultValuesList.size()) {
				cout << "The input file format for the keyword " << "*CONTROL_TERMINATION" << " is not correct!" << endl;
				exit(EXIT_FAILURE);
			}
			// Save the evaluated data to an output string vector 
			for (size_t i = 0; i < importedData.size(); i++) {
				checkedData[i] = stripString(importedData[i]);
				if (importedData[i].empty()) {
					if (i < defaultValuesList.size() && !defaultValuesList[i].empty()) {
						checkedData[i] = defaultValuesList[i];
					}
					else {
						checkedData[i] = "\"\"";
					}
				}
			}
			// Provide the output when evaluation is requested
			return make_tuple(ColumnNumber, checkedData);
		}
		else {

			ColumnNumber = 8;
			importedData = {};
			// Provide the output when evaluation is not requested
			return make_tuple(ColumnNumber, importedData);
		}
	}



	// Create a method for the keyword "airbag_simple_airbag_model"
	tuple<int, vector<string>> airbag_simple_airbag_model(const vector<string>& strVec = {}) {
		int ColumnNumber;
		vector<string> importedData;
		importedData = strVec;
		vector<string> checkedData(importedData.size());
		if (!strVec.empty()) {
			ColumnNumber = 8;

			stripString(importedData[8]);

			// Define the vector of default values with the corresponding conditions 
			if (isStringNumber(importedData[8]) && stod(importedData[8]) == 0) {
				defaultValuesList = { "none", "0", "0", "1.", "1.", "0", "0", "0", "none", \
					"none", "none", "none", "none", "none", "none", "none", "0" ,"0.", "0." , "0." , "0." ,"0." };
			}
			else {
				defaultValuesList = { "none", "0", "0", "1.", "1.", "0", "0", "0", "none", "none",\
					"none", "none", "none", "none", "none", "none", "0" };
			}

			// Get the maximum size possible 
			bigger_integer = ceil(static_cast<double>(defaultValuesList.size()) / ColumnNumber);
			max_size = bigger_integer * ColumnNumber;

			// Check for the maximum size 
			if (max_size < importedData.size()) {

				cout << "The input file format for the keyword " << "*AIRBAG_SIMPLE_AIRBAG_MODEL" << " is not correct!" << endl;
				exit(EXIT_FAILURE);
			}

			// Check for the minimum size 
			if (importedData.size() < defaultValuesList.size()) {
				cout << "The input file format for the keyword " << "*AIRBAG_SIMPLE_AIRBAG_MODEL" << " is not correct!" << endl;
				exit(EXIT_FAILURE);
			}
			// Save the evaluated data to an output string vector
			for (size_t i = 0; i < importedData.size(); i++) {
				checkedData[i] = stripString(importedData[i]);
				if (importedData[i].empty()) {
					if (i < defaultValuesList.size() && !defaultValuesList[i].empty()) {
						checkedData[i] = defaultValuesList[i];
					}
					else {
						checkedData[i] = "\"\"";
					}
				}
			}
			// Provide the output when evaluation is requested
			return make_tuple(ColumnNumber, checkedData);
		}
		else {
			ColumnNumber = 8;
			importedData = {};
			// Provide the output when evaluation is not requested
			return make_tuple(ColumnNumber, importedData);
		}
	}




	// Create a method for the keyword "node"
	// For the keyword *NODE, 7 columns are defined as default since 3 sets of 2 columns are merged into one column
	tuple<int, vector<string>> node(const vector<string>& strVec = {}) {
		int ColumnNumber;
		vector<string> importedData;
		importedData = strVec;
		vector<string> checkedData;
		if (!strVec.empty()) {
			ColumnNumber = 7;
			// A temporary string is initialized to check the data for each node 
			// The vector contains 7 elements 
			vector<string> aux_temp(7);
			aux_temp[6] = "";
			// Provide the defalut values vector 
			defaultValuesList = { "none", "0.", "0.", "0.", "0", "0" };

			for (size_t k = 0; k < importedData.size(); k += 7) {
				int tt = k;
				int t2 = k;
				// Save data for each node into the temporary vector
				for (size_t p = 0; p < aux_temp.size(); p++) {
					aux_temp[p] = stripString(importedData[tt]);
					tt = tt + 1;
				}
				// Create a boolean to check whether at least one variable is defined for a node
				// If there is no data entered for a node, it is a blank line
				bool empty_list = all_of(aux_temp.begin(), aux_temp.end(), [](const string& s) {
					return s.empty();
					});
				// If the array is empty (blank line), return an error 
				if (empty_list) {
					cout << "The input file format for the keyword " << "*NODE" << " is not correct!" << endl;
					exit(EXIT_FAILURE);
				}
				// Check the remaining nodes and evaluate the data 
				else {
					for (size_t q = 0; q < aux_temp.size(); q++) {
						if (aux_temp[q].empty()) {
							if (q < defaultValuesList.size() && !defaultValuesList[q].empty()) {
								aux_temp[q] = defaultValuesList[q];
							}
							else {
								aux_temp[q] = "\"\"";
							}
						}
					}
					// Add the "\n" sign so that the new node data is written to a new line for readability 
					aux_temp.front() = "\n" + aux_temp.front();
					checkedData.insert(checkedData.end(), aux_temp.begin(), aux_temp.end());
				}
			}
			// Provide the output when evaluation is requested
			return make_tuple(ColumnNumber, checkedData);
		}
		else {
			ColumnNumber = 7;
			importedData = {};
			// Provide the output when evaluation is not requested
			return make_tuple(ColumnNumber, importedData);
		}
	}
};


// Create a second class to map the names of the keywords to their methods in the KywordSettings class
// This is necessary since during the parsing process, a keyword is passed as a string variable 
// To return the keyword's method by a string variable mapping needs to be done 
// An object "KeywordMappingObject" from the "KeywordSettings" class is created
// a map "KeyworMapper" is cread to map the keywords to their methods 
class KeywordSettingsCaller {
private:
	KeywordSettings KeywordMappingObject;
	map<string, function<tuple<int, vector<string>>(const vector<string>&)>> KeywordMapper;


public:
	// Initialize the map that relates keywords and methods in the contructor of the class
	KeywordSettingsCaller() : KeywordMappingObject() {
		KeywordMapper["control_termination"] = [&](const vector<string>& strVec) {
			return KeywordMappingObject.control_termination(strVec); };

		KeywordMapper["airbag_simple_airbag_model"] = [&](const vector<string>& strVec) {
			return KeywordMappingObject.airbag_simple_airbag_model(strVec); };

		KeywordMapper["node"] = [&](const vector<string>& strVec) {
			return KeywordMappingObject.node(strVec); };
	}

	// Create a method to call the appropriate method for the keyword
	tuple<int, vector<string>> processKeyword(const string& currentKeyword, const vector<string>& strVec = {}) {
		if (KeywordMapper.find(currentKeyword) != KeywordMapper.end()) {
			return KeywordMapper[currentKeyword](strVec);
		}
		return make_tuple(0, vector<string>{});
	}
};



class Extract_Data {
private:
	// Initialize  variables 
	string input_File, output_File, append_overwrite;
	vector<vector<string>> Parsed_Data;
	vector<string> general_Data, default_Values, keyword, keyword_2;
	unordered_map<string, vector<string>> keywordData, EvavluatedkeywordData;
	string currentKeyword;

	// Refer to the caller of the keyword settings 
	KeywordSettingsCaller& mapper;


	// Split a line into columns based on the delimiter
	// If there is a comma present in the line, divide it based on the comma
	// Otherewise, divide the line based on the white spaces 
	vector<string> splitLine(const string& line, char delimiter) {
		vector<string> result;
		stringstream ss(line);
		string item;
		while (getline(ss, item, delimiter)) {
			if (!item.empty()) {
				result.push_back(item);
			}
		}
		return result;
	}

	// Create a function to read the data from the input file 
	// In the method, the keyword is changed to lower case for both input and output
	// This is done to prevent case sensitivity 
	void readDatafromFile() {
		ifstream inFile(input_File);
		if (!inFile) {
			cerr << "Input file cannot be opened!" << endl;
			exit(EXIT_FAILURE);
		}
		string line_aux, line_aux2;
		keyword_2 = keyword;
		// Change the keywords to lower case letters to remove case sensitivity
		for (string& word : keyword_2) {
			transform(word.begin(), word.end(), word.begin(), ::tolower);
		}

		// Change the list of the keywords to unordered_set for fast looking with no for loop 
		unordered_set<string> keywordSet(keyword_2.begin(), keyword_2.end());

		while (getline(inFile, line_aux)) {

			// Ignore the lines starting with the $ sign
			if (line_aux[0] == '$') {
				continue;
			}

			line_aux2 = line_aux;
			// Change the line to lower case letters to remove case sensitivity
			transform(line_aux2.begin(), line_aux2.end(), line_aux2.begin(), ::tolower);


			// Check if the line starts with a '*' (indicating a keyword)
			if (line_aux[0] == '*') {

				// Check if the keyword is in our set
				if (keywordSet.find(line_aux2) != keywordSet.end()) {
					currentKeyword = line_aux2;
				}
				else {
					currentKeyword.clear();
				}
			}
			else if (!currentKeyword.empty()) {
				char delimiter = (line_aux.find(',') != string::npos) ? ',' : ' ';
				// Here we assume that a line is made of 80 characters
				// In case if a keyword allows more than 80 characters, this code should be modified
				vector<string> values = splitLine(line_aux, delimiter);
				// Process the values according to the specific keyword and then save it in the general data vector 
				int MaxCharstoRead = 80;
				if (line_aux.length() > MaxCharstoRead) {
					cerr << "A line can contain a maximum of 80 characters in this code!" << endl;
					exit(EXIT_FAILURE);
				}

				// Call the method for the keyword from the keyword settings class 
				string currentKeyword_2 = currentKeyword.substr(1);
				auto result = mapper.processKeyword(currentKeyword_2);
				// Get the number of columns per line for the current keyword 
				int ColumnNumber;
				ColumnNumber = get<0>(result);
				// Enter "" value instead of columns with no value
				// This is done to complete the number of columns
				// Later this will be required to define the maximum and minimum size of the keyword data
				while (values.size() < ColumnNumber) {
					values.push_back("");
				}

				// Save the data for the keyword in an unordered map 
				keywordData[currentKeyword].insert(keywordData[currentKeyword].end(), values.begin(), values.end());
			}

		}
	}


	// Evaluate data for each keyword by calling the corresponding method 
	// In here we check for the size, default values and validity of the input 
	// This method provides the output that can be printed 
	void evaluateReadData() {
		vector<string> EvaluatedData;
		int i = 0;
		// Loop over the vector of the keywords 
		while (i < keyword.size()) {
			currentKeyword = keyword_2[i];
			vector<string> DatatoEvaluate = keywordData[currentKeyword];

			// Send the data to the keyword method for evaluation 
			string currentKeyword_3 = currentKeyword.substr(1);
			auto result_2 = mapper.processKeyword(currentKeyword_3, DatatoEvaluate);

			// Get the output 
			EvaluatedData = get<1>(result_2);

			// Save the output in an unordered map 
			EvavluatedkeywordData[currentKeyword].insert(EvavluatedkeywordData[currentKeyword].end(), \
				EvaluatedData.begin(), EvaluatedData.end());

			i = i + 1;
		}
	}


	// Create a method to write the evaluated data into the output file 
	void writeDatatoFile() {
		vector<string> CurrentData;
		ofstream outFile(output_File);
		if (!outFile) {
			cerr << "Output file cannot be opened!" << endl;
			exit(EXIT_FAILURE);
		}

		// Loop over the keyword vector 
		for (size_t i = 0; i < keyword.size(); i++) {
			currentKeyword = keyword_2[i];
			// Get data from unordered set from the previous method 
			CurrentData = EvavluatedkeywordData[currentKeyword];
			// Write the keyword to the output file 
			outFile << keyword[i] << "\n";
			// Write the data inside {} brackets 
			outFile << "{";
			for (size_t k = 0; k < CurrentData.size(); k++) {
				outFile << CurrentData[k];

				if (k != CurrentData.size() - 1) {
					outFile << ", ";
				}
			}
			outFile << "}\n";

		}

	}

public:
	// Create a constructor for the class 
	Extract_Data(const string& in, const string& out, const vector<string>& key, const string& append_overwrite0, \
		KeywordSettingsCaller& mpr)
		: input_File(in), output_File(out), keyword(key), append_overwrite(append_overwrite0), mapper(mpr) {
	}

	// Create a method to execute the operation automatically 
	void execute() {
		readDatafromFile();
		evaluateReadData();
		writeDatatoFile();
		cout << "Execution was successful. The output is written to " << output_File << endl;
	}
};



int main() {

	// Create a mapper for referncing of the keyword methods 
	KeywordSettingsCaller mapper;

	// Provide the vector of the keywords to be read 
	vector <string> keywrdlist = { "*CONTROL_TERMINATION", "*AIRBAG_SIMPLE_AIRBAG_MODEL", "*NODE" };

	// Create an object and pass the arguments 
	Extract_Data Parse_the_File_1("airbag.deploy.k", "output.txt", \
		keywrdlist, "Overwrite", mapper);
	// Execute the process 
	Parse_the_File_1.execute();

	return 0;
}

