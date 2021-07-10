#include "Read.h"
using namespace std;
using std::ifstream;

void ReadData(char nameTable[], char constraints[], std::vector <std::vector <double> >& dist, std::vector <std::vector <int> >& constraints_matrix, std::vector <TConstraint>& CL, std::vector <TConstraint>& ML)
{
    char name[200] = "../InstancesTCC/";
    char nameConstraints[200] = "../InstancesTCC/";
    strcat(name, nameTable);
    strcat(nameConstraints,constraints);

    FILE *arq, *arq2;
    arq = fopen(name,"r");
    if (arq == NULL)
    {
        printf("\nERROR: File (%s) not found!\n",name);
        getchar();
        exit(1);
    }

    /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
    // => read data
    TNode nodeAux;
    vector<TNode> arr_input_data;

    // Create a text string, which is used to output the text file
    string row;
    ifstream read_file(name);
    int n_columns;
    int n_rows = 0, flag = 1;
    while (getline (read_file, row)) {
        if (flag){
            n_columns = std::count(row.begin(), row.end(), ','); // counting the number of columns of dataset that are separed by comma
            flag = 0;
        }
        if (row != ""){
            nodeAux.values.clear(); 
            //cout << row << endl;
            std::stringstream ss(row);
            for (double value; ss >> value;) {
                nodeAux.values.push_back(value); // read node's data
                if (ss.peek() == ',' || ss.peek() == ' ')
                    ss.ignore();
            }
            arr_input_data.push_back(nodeAux); // insert line by line of the dataset in arr_input_data
            n_rows++;
        }
    }
    fclose(arq);

    cout << "numero de linha do dataset: " << n_rows << endl;
    cout << "numero de colunas do dataset: " << n_columns << endl; 
    
    // calculate the euclidean distance
    dist.clear();
    dist.resize(n_rows, std::vector<double>(n_rows));
    double acum_dist;
    
     for (int i = 0; i < arr_input_data.size(); i++){
         for (int j = i; j < arr_input_data.size(); j++){
            acum_dist = 0.0;
            for (int k = 0; k < n_columns; k++){
                acum_dist += (arr_input_data[i].values[k] - arr_input_data[j].values[k]) * (arr_input_data[i].values[k] - arr_input_data[j].values[k]);
            }
            dist[i][j] = dist[j][i] = sqrt(acum_dist); 
         }
         dist[i][i] = 0.0;
     }

    /*for (int i = 0; i < n; i++){
        printf("\n");
         for (int j = 0; j < n; j++){
             printf(" %.2lf",dist[i][j]);
         }
    } */

    arq2 = fopen(nameConstraints, "r");
    if (arq2 == NULL)
    {
        printf("\nERROR: File (%s) not found!\n",nameConstraints);
        getchar();
        exit(1);
    }

    // reading the constraints of the datasets
    constraints_matrix.resize(n_rows, std::vector<int>(n_rows));
    int x, y, k;
	while (!feof(arq2))	// Enquanto não se chegar no final do arquivo /   
	{
		fscanf(arq2, "%d %d %d", &x, &y, &k);
		constraints_matrix[x][y] = constraints_matrix[y][x] = k;    

        TConstraint aux;
        aux.x = x;
        aux.y = y;
        aux.tipo = k;

        if (aux.tipo == -1)
            CL.push_back(aux); 

        if (aux.tipo == 1)
            ML.push_back(aux); 
                      
	}

    /*for (int i = 0; i < n; i++){
         for (int j = 0; j < n; j++){
             if (constraints_matrix[i][j] != 0)
                printf("\n%d %d %d",i, j, constraints_matrix[i][j]);
         }
    } 

    getchar();*/

}

void FreeMemoryProblem(std::vector <TNode> node, std::vector <std::vector <double> > dist)
{
    //specific problem
    dist.clear();
    node.clear();
}
