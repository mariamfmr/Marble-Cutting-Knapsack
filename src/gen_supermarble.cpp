/*****************************************************
 * IST - ASA 23/24 - Super Marble instance generator *
 *****************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Dimensions
int _N;
int _M;
int _P; // # pieces
int _S; // # instances

//-----------------------------------------------------------------------------

void printUsage(char *progname) {
  cerr << "Usage: " << progname << " <N> <M> <P> <S>" << endl;
  cerr << "  N: number of rows" << endl;
  cerr << "  M: number of columns" << endl;
  cerr << "  P: number of pieces (dimensions 1 to N x 1 to M)" << endl;
  cerr << "  S: number of instances to generate" << endl;
  exit(1);
}

void parseArgs(int argc, char *argv[]) {
  if (argc != 5) {
    cerr << "ERROR: Wrong number of arguments" << endl;
    printUsage(argv[0]);
  }

  sscanf(argv[1], "%d", &_N);
  if (_N < 1) {
    cerr << "ERROR: N rows must be >= 1" << endl;
    printUsage(argv[0]);
  }

  sscanf(argv[2], "%d", &_M);
  if (_M < 1) {
    cerr << "ERROR: M columns must be >= 1" << endl;
    printUsage(argv[0]);
  }

  sscanf(argv[3], "%d", &_P);
  if (_P < 1) {
    cerr << "ERROR: P pieces must be >= 1" << endl;
    printUsage(argv[0]);
  }

  sscanf(argv[4], "%d", &_S);
  if (_S < 1) {
    cerr << "ERROR: S instances must be >= 1" << endl;
    printUsage(argv[0]);
  }
}

inline int randomValue(int min, int max) {
  return rand() % (max - min + 1) + min;
}

void generateInstance(const string &filename, int numPieces) {
  // Open the file for writing
  ofstream outFile(filename);

  // Print dimensions
  outFile << _N << " " << _M << endl;
  // Print number of pieces
  outFile << numPieces << endl;

  // Print matrix
  for (int i = 0; i < numPieces; i++) {
    int x = randomValue(1, _N);
    int y = randomValue(1, _M);
    int v = randomValue(1, 2 * x * y);
    outFile << x << " " << y << " " << v << endl;
  }

  // Close the file
  outFile.close();
}

int main(int argc, char *argv[]) {
  parseArgs(argc, argv);

  // Create a folder named testsTime if it doesn't exist
  system("mkdir -p testsTime");

  // Generate input files for each instance
  for (int s = 0; s < _S; s++) {
    // Generate a unique filename based on the current time and instance index
    time_t now = time(0);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", localtime(&now));

    // Construct the filename
    string filename = "testsTime/test" + string(timestamp) + "_" + to_string(s) + ".in";

    // Generate a random number of pieces between P * 0.8 and P * 1.5
    int numPieces = _P * 0.8 + rand() % (int)(_P * 0.7);

    // Generate the instance
    generateInstance(filename, numPieces);
  }

  return 0;
}
