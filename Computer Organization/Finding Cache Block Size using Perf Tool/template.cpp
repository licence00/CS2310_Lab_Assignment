#include<iostream>
#include <algorithm>
#include<fstream>
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 4) {
		cout << "Usage: ./a.out block_size input_filename output_filename" << endl;
		cout << "If block_size is 0, then naive algorithm is used" << endl;
		exit(0);
	}

	int block_size = atoi(argv[1]);

	// Open the input and output files
	string infile_name(argv[2]), outfile_name(argv[3]);
	ofstream outfile;
	outfile.open(outfile_name, ios::out | ios::trunc);
	if (!outfile.is_open()) {
		cout << "Error: Cannot open file " << outfile_name << " for writing" << endl;
		exit(0);
	}
	ifstream infile;
	infile.open(infile_name, ios::in);
	if (!infile.is_open()) {
		cout << "Error: Cannot open file " << infile_name << " for reading" << endl;
		exit(0);
	}

	int n;
	infile >> n;

	int a[n][n], b[n][n], c[n][n];

	// Read the two matrices from input file
	for(int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			infile >> a[i][j];
		}
	}
	for(int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			infile >> b[i][j];
			c[i][j] = 0;
		}
	}

	// Choose the algorithm to use based on value of block size
	if (block_size == 0) {
		/* 
		 * TODO: Implement the naive algorithm for matrix multiplication here.
		 */
		for(int i=0;i<n;i++)
		{
		 for(int j=0;j<n;j++)
		 {
           for(int k=0;k<n;k++)
		   {
		    c[i][j]+=(a[i][k]*b[k][j]);
		   }
		 }
		}

	} else {
		/* 
		 * TODO: Implement the blocked algorithm for matrix multiplication here.
		 * The block_size variable holds the block size to use
		 */
		for(int p=0;p<n;p=p+block_size)
		{
        for(int l=0;l<n;l=l+block_size)
		    {
                for(int i=0;i<n;i++)
				{
                        for(int j=p;j<min(p+block_size,n);j++)
						{

                            int temp = 0;
                            for(int k=l; k<min(l+block_size,n);k++)
							{
                                temp += a[i][k]*b[k][j];
                            }
                            c[i][j] += temp;
                        }
                }
            }
       }
	}

	// Write the output matrix
	for(int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			outfile << c[i][j] << " ";
		}
		outfile << endl;
	}
}
