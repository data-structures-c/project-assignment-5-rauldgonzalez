//Project #5: 12/03/18
//Student: Raul Gonzalez ; SMC ID: 1630082

#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

//-------- Constants:

    // File name where results are stored
const char FILE_NAME[] = "AlgorithmTime.txt";

    //Minimum length needed to sort array
const int MIN_LENGTH = 2;
    //Number of algorithms tested
const int N_ALGORITHM = 4;

// Test parameters:
const int ARRAY_SIZE = 15000;
const int MAX_RAND = 1000;
const int N_SORTS = 20;



//--------- Functions -----------

//---- Class of sorting functions:
class sort_algorithm {
    public:
        void selection_sort( int[], int );
        void bubble_sort( int[], int );
        void insert_sort( int[], int );
        void merge_sort( int[], int );
    private:
        void swap_entry( int* , int* );
        void merge_array( int[], int, int[], int, int[] );
};

    // Function to swap value of two variables:
void sort_algorithm::swap_entry( int *ent_1, int *ent_2 ) {
    int placeholder = *ent_2;
    *ent_2 = *ent_1;
    *ent_1 = placeholder;
}

    // Function to sort array through selection:
void sort_algorithm::selection_sort( int array_int[], int length ) {

    if( length >= MIN_LENGTH ) {

        int max_index = 0;

        // Scanning array right to left [initial max selection]
        for( int index = (length-1) ; index >= 0 ; index -= 1 ) {

            max_index = index;

            // Scanning smaller region of input array:
            for( int index_2 = 0 ; index_2 < index ; index_2 += 1) {

                    // Storing index of largest value
                if( array_int[index_2] > array_int[max_index] ) {
                    max_index = index_2;
                }
            }
            // Swapping initial selection for new largest
            swap_entry( &array_int[index] , &array_int[max_index] );
        }
    }
}

    // Function to sort array through bubble method:
void sort_algorithm::bubble_sort( int array_int[], int length ) {

    if( length >= MIN_LENGTH ) {

        // Scanning array right to left
        for( int index = (length-1) ; index >= 0 ; index -= 1 ) {

            // Scanning smaller region of input array
            for( int index_2 = 0 ; index_2 < index ; index_2 += 1 ) {

                // If adjacent is larger, swap entries
                if( array_int[index_2+1] < array_int[index_2] ) {
                    swap_entry( &array_int[index_2] , &array_int[index_2+1] );
                }
            }
        }
    }
}

    // Function to sort array via insertion method:
void sort_algorithm::insert_sort( int array_int[], int length ) {

    if( length >= MIN_LENGTH ) {

        // Scanning array left to right:
        for( int index = 1; index < length ; index += 1 ) {

            // Initial value used for comparison
            int key = array_int[index];

            // Scanning smaller region of input array:
            for( int index_2 = (index-1) ; index_2 >= 0 ; index_2 -= 1 ) {

                // Sliding entries if values are are larger than initial
                if( array_int[index_2] > key ) {
                    array_int[index_2+1] = array_int[index_2];

                        // Place initial value at the start if the start is reached
                    if( index_2 == 0 ) {
                        array_int[index_2] = key;
                    }

                // If smaller value is found, substitute past entry, then exit
                } else {
                    array_int[index_2+1] = key;
                    break;
                }
            }
        }
    }
}

    // Function to merge two arrays:
void sort_algorithm::merge_array( int array_L[], int length_L, int array_R[], int length_R, int array_result[] ) {

    int index_L = 0;
    int index_R = 0;
    int index = 0;

    // Compare left and right arrays, then store smallest in result array
    while( (index_L < length_L) && (index_R < length_R) ) {

        if( array_L[index_L] <= array_R[index_R] ) {
            array_result[index] = array_L[index_L];
            index_L += 1;
        } else {
            array_result[index] = array_R[index_R];
            index_R += 1;
        }
        index += 1;
    }

    // Copy remaining entries of left array to result array
    while( index_L < length_L ) {
        array_result[index] = array_L[index_L];
        index_L += 1;
        index += 1;
    }
    // Copy remaining entries of right array to result array
    while( index_R < length_R ) {
        array_result[index] = array_R[index_R];
        index_R += 1;
        index += 1;
    }
}

    // Function to sort array through merging:
void sort_algorithm::merge_sort( int array_int[], int length ) {

    int mid = length/2;

    // Only divide/sort if array is not a single entry:
    if( length >= MIN_LENGTH ) {

        // Create left and right arrays:
        int array_result[length];
        int array_L[mid];
        int array_R[length - mid];

        // Store entries onto left and right arrays
        for( int index = 0 ; index < length ; index += 1 ) {
            if( index < mid ) {
                array_L[index] = array_int[index];

            } else {
                array_R[index - mid] = array_int[index];
            }
        }

        // Divide arrays into smaller sections
        merge_sort(array_L, mid);
        merge_sort(array_R, length - mid);

        // Merge smaller sections
        merge_array( array_L, mid, array_R, (length-mid), array_result );

        // Store merged result onto input array
        for( int index = 0; index < length ; index += 1 ) {
            array_int[index] = array_result[index];
        }
    }
}


//---- Miscellaneous functions:

    // Function to calculate average value of array:
float average_val( float input[], int length ) {

    float sum = 0;

    for( int index = 0 ; index < length ; index += 1 ) {
        sum += input[index];
    }
    return sum/length;
}

    //Function to calculate standard deviation of array:
float standard_deviation( float input[], int length ) {

    float average = average_val(input, length);
    float entry = 0;
    float sum = 0;

    for( int index = 0 ; index < length ; index += 1 ) {
        entry = input[index] - average;
        sum += pow( entry , 2 );
    }
    sum = sum/(length - 1);

    return sqrt(sum);
}

 // Function to copy entries of one array to another:
void copy_array( int input[], int output[], int length ) {
    if( length > 0 ) {
        for( int index = 0 ; index < length ; index += 1 ) {
            output[index] = input[index];
        }
    }
}


//--------- Main Function -----------
int main()
{
    //Classes:
    sort_algorithm func;
    clock_t time_change;

    //Arrays to random values:
    int array_rand[ARRAY_SIZE];
    int array_temp[ARRAY_SIZE];
    int length = sizeof(array_rand)/sizeof(array_rand[0]);

    float data[N_ALGORITHM][N_SORTS+1] = {0};

    // Repeating test for the same algorithm several times
    for( int rows = 0; rows < N_SORTS ; rows += 1 ) {

        // Filling array with random values
        for( int index = 0 ; index < ARRAY_SIZE ; index += 1 ) {
            array_rand[index] = rand()%(MAX_RAND + 1) + 1;
        }

        // Testing each algorithm with the same random array
        for( int column = 0; column < N_ALGORITHM ; column += 1 ) {

            copy_array( array_rand, array_temp, length );

                //Time before sorting
            time_change = clock();

                //Choosing algorithm
            if( column == 0 ) {
                func.selection_sort(array_temp, length);
            } else if ( column == 1 ) {
                func.bubble_sort(array_temp, length);
            } else if ( column == 2 ) {
                func.insert_sort(array_temp, length);
            } else if ( column == 3 ) {
                func.merge_sort(array_temp, length);
            }
                //Time after sorting
            time_change = clock() - time_change;

                //Saving execution time
            data[column][rows] = double(time_change)/CLOCKS_PER_SEC;
        }
    }

    //Saving recorded times to file:
    ofstream DataFile;
    DataFile.open( FILE_NAME );

    DataFile << "Time per algorithm: " << endl;
    DataFile << "Selection, Bubble, Insert, Merge" << endl;

    // Scanning all tests [Plus a column for averages and standard deviations]
    for( int index_1 = 0 ; index_1 < (N_SORTS+2) ; index_1 += 1 ) {

        if( index_1 == (N_SORTS) ) {
            DataFile << "Average: " << endl;
        } else if ( index_1 == (N_SORTS+1) ) {
            DataFile << "Standard deviation: " << endl;
        }

            // Scanning results per algorithm
        for( int index_2 = 0 ; index_2 < N_ALGORITHM ; index_2 += 1 ) {

            // Choosing data to save
            if( index_1 == N_SORTS ) {
                DataFile << average_val( data[index_2], N_SORTS );
            } else if ( index_1 == (N_SORTS+1) ) {
                DataFile << standard_deviation( data[index_2], N_SORTS );
            } else {
                DataFile << data[index_2][index_1];
            }

            // Adding comma to separate values
            if( index_2 != (N_ALGORITHM-1) ) {
                DataFile << " , ";
            }
        }
       DataFile << endl;
    }

    // Closing file
    DataFile.close();

    cout << "Data collected and stored - See created file" << endl;

    return 0;
}
