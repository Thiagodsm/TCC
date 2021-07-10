#include "Decoder.h"

// Sort TSol by random-keys
bool sortByRk(const TVecSol &lhs, const TVecSol &rhs) { return lhs.rk < rhs.rk; }

TSol Decoder(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL, std::vector <TConstraint> ML)
{
    // save the random-key sequence of current solution 
    TSol temp = s;

    int numDecoders = 1;

    // create a initial solution of the problem
    s.fo = 0;
    for (int j=0; j<n; j++)
    {
        s.vec[j].sol = j;
    }

    int dec = ceil(s.vec[n].rk*numDecoders);
    //printf("\n%d (%.2lf)", dec, s.vec[n].rk);

    dec = 1;
    switch (dec)
    {
        case 1: // sort decoder
            s = Dec1(s, n, m, dist, constraints_matrix, CL, ML);
            break;
        
        default:
            break;
    }

    

    // return initial random-key sequence and maintain the solution sequence
    for (int i=0; i<n; i++)
    {
        s.vec[i].rk = temp.vec[i].rk;
    }
    
    return s;
}

TSol Dec1(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL, std::vector <TConstraint> ML)
{
    // sort random-key vector 
    sort(s.vec.begin(), s.vec.end()-1, sortByRk);   

    // definir quem serao os medoids de cada cluster
    std::vector<int> medoids;
    medoids.resize(m);
    for (int j=0; j<n; j++)
    {
        if (j < m)
            medoids[j] = s.vec[j].sol;
        
        s.vec[j].sol = -1;
    }

    // alocar os medoids a eles mesmos
    for (int j=0; j<m; j++)
    {       
        s.vec[medoids[j]].sol = medoids[j];
    }

    // definir em qual cluster estara cada ponto
    for (int i=0; i<n; i++)
    {
        double menorDist = 100000000;
        int melhorMedoid = -1;

        //verificar se ha algum ponto com restricao ML ja alocado
        for (int j=0; j<n; j++)
        {
            if (constraints_matrix[i][j] == 1 && s.vec[j].sol >= 0)
            {
                melhorMedoid = s.vec[j].sol;
                break;
            }
        }

        // caso contrario, procurar o medoid mais proximo
        if (melhorMedoid == -1)
        {
            for (int j=0; j<m; j++)
            {
                if (dist[i][medoids[j]] < menorDist)
                {
                    menorDist = dist[i][medoids[j]];
                    melhorMedoid = medoids[j];
                }
            }
        }

        if (s.vec[i].sol == -1)
            s.vec[i].sol = melhorMedoid;
    }

    // tentar retirar inviabilidades CL
    for (int i=0; i<CL.size(); i++)
    {
        // verificar se x e y estao no mesmo cluster
        if (s.vec[CL[i].x].sol == s.vec[CL[i].y].sol)
        {
            int novoClusterX = -1,
                novoClusterY = -1;

            double menorDistX = 1000000,
                   menorDistY = 1000000;

            for (int j=0; j<m; j++)
            {
                // encontrar um cluster mais proximo para X
                if (medoids[j] != s.vec[CL[i].x].sol && dist[medoids[j]][CL[i].x] < menorDistX)
                {
                    menorDistX = dist[medoids[j]][CL[i].x];
                    novoClusterX = medoids[j];
                }

                // encontrar um cluster mais proximo para y
                if (medoids[j] != s.vec[CL[i].y].sol && dist[medoids[j]][CL[i].y] < menorDistY)
                {
                    menorDistY = dist[medoids[j]][CL[i].y];
                    novoClusterY = medoids[j];
                }
            }

            // trocar x ou y de cluster
            if (menorDistX < menorDistY){
                s.vec[CL[i].x].sol = novoClusterX;
            }
            else{
                s.vec[CL[i].y].sol = novoClusterY;
            }
        }
    }

    // tentar retirar inviabilidades ML
    for (int i=0; i<ML.size(); i++)
    {
        // verificar se x e y estao em clusters diferentes
        if (s.vec[ML[i].x].sol != s.vec[ML[i].y].sol)
        {
            // inserir x no mesmo cluster que y
            s.vec[ML[i].x].sol = s.vec[ML[i].y].sol;
        }
    }

    

    //calcular a funcao objetivo
    int penalidades = 0;
    double distTotal = 0.0;

    for(int i=0; i<n; i++)
    {
        // verificar se ha restricoes violadas
        for(int j=i+1; j<n; j++)
        {
            if (s.vec[i].sol == s.vec[j].sol)
            {
                //verificar se ha restricao CL entre i e j
                if (constraints_matrix[i][j] == -1)
                {
                    penalidades++;
                    s.penalidades = -1;
                }
            }
            else
            {
                //verificar se ha restricao ML entre i e j
                if (constraints_matrix[i][j] == 1)
                {
                    penalidades++;
                    s.penalidades = 1;
                }
            }
        }

        //distancia entre o ponto e medoid do seu cluster
        distTotal += dist[i][s.vec[i].sol];
    }



    // se violar, aplicar funcao para restaurar viabilidade

    s.fo = distTotal + penalidades*10000000;
    //s.penalidades = penalidades;


    return s;
}