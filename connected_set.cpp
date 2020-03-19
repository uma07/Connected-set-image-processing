// This program takes the input an image and outputs an image with black and white color where black represents the connected set and also outputs number of these sets.



# include <iostream>
# include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int **img_matrix;


int change_val(unsigned char pixel)
{

	if(pixel >= 250 && pixel <= 255)
		return 0;

	else
		return 255;

}



void finding_connected_set(Mat in, int i, int j, int num)
{

	if(i-1 >= 0) 		//moving up from the current position
		if( (img_matrix[i-1][j] == 255) && change_val(in.at<uchar>(i-1, j)) )
		{
			img_matrix[i-1][j] = num;		//keeping the value in the matrix
			finding_connected_set(in, i-1, j, num);
		}

	if(j-1 >= 0 )		//moving left from the current position
		if( (img_matrix[i][j-1] == 255) && change_val(in.at<uchar>(i, j-1)) )
		{
			img_matrix[i][j-1] = num;
			finding_connected_set(in, i, j-1, num);
		}

	if(i+1 < in.rows)		//moving down from the current position
	{

               	cout<<"img_mat[i+1][j]: "<<i+1<<" "<<j<<" "<<img_matrix[i+1][j]<<endl;		
		if( (img_matrix[i+1][j] == 255) && change_val(in.at<uchar>(i+1, j)) )
		{
			img_matrix[i+1][j] = num;
			finding_connected_set(in, i+1, j, num);
		}
	}

	if(j+1 < in.cols)		//moving right from the current position
	{
		cout<<"img_mat[i][j+1]: "<<i<<" "<<j+1<<" "<<img_matrix[i][j+1]<<endl;
		if( (img_matrix[i][j+1] == 255) && change_val(in.at<uchar>(i, j+1)) )
		{
			img_matrix[i][j+1] = num;
			finding_connected_set(in, i, j+1, num);
		}
	}

}





int main(int argc, char *argv[])
{
 

	Mat in, out;
	int i, j, pixel, num = 0, choice, comp;

	in = imread("./lena_gray_256.tif", CV_LOAD_IMAGE_GRAYSCALE);

	if(in.empty())
	{
		cout << "SORRY !!! Image cannot be read\n";
		exit(1);
	}

	img_matrix = (int**) malloc(sizeof(int*) * in.rows);

	for(i = 0; i < in.rows; i++)
		img_matrix[i] = (int*) malloc(sizeof(int) * in.cols);
	
	for(i = 0; i < in.rows; i++)
		for(j = 0; j < in.cols; j++)
			img_matrix[i][j] = 255;

	for(i = 0; i < in.rows; i++)
		for(j = 0; j < in.cols; j++)
			if(img_matrix[i][j] == 255 && change_val(in.at<uchar>(i, j)))
			{
				img_matrix[i][j] = num;
				finding_connected_set(in, i, j, num);
				num++;
			}

	cout << "Choose from following options : \n";
	cout << "1. Total number of component sets.\n2. Show the particular component.\n3. Exiting the program\n";

	cin >> choice;

	while(1)
	{
		switch(choice)
		{
			case 1  :	cout << "Total number of component sets are : \n" << num;
					break;

			case 2  :	cout << "Please enter the component set number you want to see : ";
					cin >> comp;

					for(i = 0; i < in.rows; i++)
					{
						for(j = 0; j < out.cols; j++)
							if(img_matrix[i][j] != comp)
								out.at<uchar>(i, j) = 0; 
					}

					break;

			case 3  :	cout << "Exiting the program .....\n";
					exit(0);
					break;

			default :	cout << "Sorry !!! There are only three options\n";
					break;
		}

		cout << "Choose from following options : \n";
		cout << "1. Total number of component sets.\n2. Show the particular component.\n3. Exiting the program\n";

		cin >> choice;
	}

	namedWindow(argv[1], WINDOW_AUTOSIZE);

	if(!out.empty())
        	imshow(argv[1], out);

        waitKey(0);

        return 0;


}
