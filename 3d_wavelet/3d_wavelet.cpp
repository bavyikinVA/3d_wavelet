#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>



int main() 
{
    std::string input_path;
    std::cout << "Enter file path:" << std::endl;

    std::cin >> input_path;
    std::cout << std::endl;

    for (size_t i = 0; i < input_path.length(); ++i)
    {
        if (input_path[i] == '/' || input_path[i] == '\\') {
            input_path.replace(i, 1, "\\\\");
            ++i;
        }
    }

    std::ifstream fin(input_path);
    if (!fin.is_open())
    {
        std::cerr << "Error opening file: " << input_path << std::endl;
        return 1;
    }
    
    std::vector<std::vector<double>> data;
    std::string line;
    int rows = 0;
    int cols = 0;

    while (std::getline(fin, line))
    {
        std::istringstream iss(line);
        double num;
        std::vector<double> row;

        while (iss >> num) 
        {
            row.push_back(num);
        }
        cols = row.size();
        data.push_back(row);
        rows ++;
        
    }
    fin.close();

    std::cout << "select an option: 1 - list of wavelet transform scales, 2 - interval of the wavelet transform scale:" << std::endl;
    std::vector<std::vector<std::vector<double>>> result_matrix;
    int selector;
    int iter = 0;
    double time_diff = 0;
    std::vector<double> scales;
    int scales_size = 0;
    std::cin >> selector;
    if (selector == 1)
    {
        std::cout << "Enter the number of items:" << std::endl;
        std::cin >> iter;
        double num = 0;
        for (int i = 0; i < iter; i++)
        {
            std::cin >> num;
            scales.push_back(num);
        }
        scales_size = scales.size();

        double time = (double)clock() / CLOCKS_PER_SEC;
        printf("start_morlet");

        //std::vector<std::vector<std::vector<double>>> result_matrix;
        result_matrix = morlet_wavelet(data, scales, rows, cols);

        time_diff = (((double)clock()) / CLOCKS_PER_SEC) - time;
    }

    

    std::ofstream fout("C:\\Users\\bavyk\\source\\repos\\epic_parallel\\epic_parallel\\test.txt");

    // Вывод результатов
    double time2 = ((double)clock()) / CLOCKS_PER_SEC;
    for (int scale = 0; scale < scales_size; scale++)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++) 
            {
                fout << std::to_string(result_matrix[scale][row][col]) << " ";
            }
        }

        fout << std::endl;

    }
    fout.close();
    double time_diff2 = (((double)clock()) / CLOCKS_PER_SEC) - time2;
    printf("The elapsed time is %lf seconds\n", time_diff);
    printf("The elapsed time is %lf seconds\n", time_diff2);

    system("pause");
    return 0;
}