#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "zlibber.h"

using namespace std;

inline bool fileExists(const char* fileName) {
    ifstream ifile( fileName );
    if ( ifile.is_open() ) {
        ifile.close();
        return true;
    } else return false;
}

template< typename C >
inline string ToString( const C& obj ) {
	ostringstream out;
	out << obj;
	return out.str();
}

int main(int argc, char *argv[]) {
	if (argc > 2) {
		acZlibber* zlibber = new acZlibber;

		string cmd = ToString(argv[1]);
		string filename = ToString(argv[2]);

		int startTime = time( NULL );

		if (cmd == "x") {
			if (fileExists(filename.c_str())) {
				cout << "Unpacking..." << endl;

				FILE* input  = fopen(ToString(filename).c_str(), "r");
				FILE* output = fopen(ToString(filename + ".out").c_str(), "w");

				string err = zlibber->getLastError( zlibber->unpack(input, output) );
				if (!err.empty()) cout << err << endl;

				fclose(output);
				fclose(input);

				cout << "Finished in " << ( time( NULL ) - startTime ) << " seconds." << endl;
			} else cout << filename << " isn't exists." << endl;
		} else if (cmd == "a") {
			if (fileExists(filename.c_str())) {
				cout << "Packing" << filename << "..." << endl;

				FILE* input  = fopen(ToString(filename).c_str(), "r");
				FILE* output = fopen(ToString(filename + ".zlb").c_str(), "w");

				string err = zlibber->getLastError( zlibber->pack(input, output, 9) );
				if (!err.empty()) cout << err << endl;

				fclose(output);
				fclose(input);

				cout << "Finished in " << ( time( NULL ) - startTime ) << " seconds." << endl;
			} else cout << filename << " isn't exists." << endl;
		}
		delete zlibber;
	} else {
		cout << "Usage: " << argv[0] << " <command> <filename>\n" <<
				"Commands are:\n" <<
				"\tx - unpack existing zlb archive\n" <<
				"\ta - pack new zlb archive" << endl;
		return 0;
	}

	return 0;
}
