#include "LocalSearch.h"

TSol LocalSearch(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL)
{
    // we use a Random Variable Neighborhood Descent (RVND) as local search
    int k = 1;

    // predefined number of neighborhood moves
    std::vector <int> NSL;
    std::vector <int> NSLAux;
    for (int i=1; i<=1; i++)
    {
        NSL.push_back(i);
        NSLAux.push_back(i);
    }

    //printf("\nHeuristicas: ");
    while (!NSL.empty())
	{
        // current objective function
        double foCurrent = s.fo;

        // randomly choose a neighborhood
        int pos = irand(0,NSL.size()-1);
        k = NSL[pos];

        switch (k)
        {
        case 1: 
            s = LS1(s, n, m, dist, constraints_matrix, CL); 
            break;
        
        default:
            break;
        }

        // return to first neighborhood if better the current solution
        if (s.fo < foCurrent)
        {
            // refresh NSL
            NSL.clear();
            NSL = NSLAux;
        }
        // next neighborhood, otherwise
        else
        {
            // Remove N(n) from NSL
            NSL.erase(NSL.begin()+pos);
        }
	} //end while

 	return s;
}


double rand(double min, double max)
{
	return ((double)(rand()%10000)/10000.0)*(max-min)+min;
    //return uniform_real_distribution<double>(min, max)(rng);
}

int irand(int min, int max)
{
	return (int)rand(0,max-min+1.0) + min;
}



 TSol LS1(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL)
 { 
     /*
//   //Aplicar Location-allocation no centro do cluster, resolvendo o problema de atribui��o para as medianas
//     TSol solAO = s;
//     TSol solAux = solAO;

//     TSol melhorSolAux;
//     melhorSolAux.fo = 9999999999;

//     bool continua = true;
//     while (continua)
//     {
//         //trocar todas as medianas pelos pontos que estao atribuidos a ela
//         for (int i=0; i<m; i++)
//         {
//             for (int j=0; j<n; j++)
//             {
//                 solAux = solAO; //retornar para a solucao original

//                 if (solAux.pontos[j] == solAux.med[i])
//                 {
//                     //chamar o metodo para realocar os pontos
//                     solAux = Realocar3(solAux, i, j);

//                     //calcular a FO
//                     solAux = CalcularFO(solAux,3);

//                     //verificar se eh a melhor solucao encontrada ate entao...
//                     if (solAux.fo < melhorSolAux.fo)
//                         melhorSolAux = solAux;
//                 }
//             }
//         }

//         //verificar se melhorou a solucao
//         if (melhorSolAux.fo < solAO.fo)
//         {
//             solAO = melhorSolAux; //continuar a busca a partir da melhor solucao encontrada
//             continua = true;
//         }
//         else
//             continua = false;
//     }

//     //REALIZAR UM METODO DE DESCIDA CALCULANDO A MELHORA SE ALGUM PONTO FOR TROCADO DE MEDIANA
//     solAO = VND(solAO);
*/
     
     
     
     return s;//solAO;

}

// // /*****************************************************************************
// // M�todo: VND
// // Funcao: aplicar o vnd em uma solucao
// // ******************************************************************************/
// TSol VND(TSol s)
// {
//     int k = 1, 
//         r = 2;

//     double fostarVND = s.fo;

//     while (k <= r)
//     {
//         switch (k)
//         {
//             case 1:
//             {
//                 s = Shift(s);
//                 break;
//             }
//             case 2:
//             {
//                 s = Swap2(s);
//                 break;
//             }
//             case 3:
//             {
//                 s = SwapMedianas(s);
//                 break;
//             }
//         }
//         s = CalcularFO(s,3);
//         if (s.fo < fostarVND)
//         {
//             fostarVND = s.fo;
//             k = 1;
//         }
//         else
//             k += 1;
//     }

//     return s;
// }

// // /*****************************************************************************
// // Metodo: Shift
// // Funcao: retirar um ponto de uma mediana e inserir em outra
// // ******************************************************************************/
// TSol Shift(TSol s, int n, int m, std::vector < std::vector <double> > dist, std::vector <std::vector <int> > constraints_matrix, std::vector <TConstraint> CL)
// {
//     double economia = 0,
//             maiorEconomia = 0;

//     int mI = 0,
//         mJ = 0;

//     //examinar todos os pontos que nao sejam medianas e sejam atendidos por alguma mediana
//     for (int i=0; i<n; i++)
//     {
//         if (s.vec[i].sol != i)
//         {
//             //verificar a vantagem de retirar o ponto i e inserir em outra mediana j
//             for (int j=0; j<m; j++)
//             {
//                 if (s.vec[i].sol != s.med[j])
//                 {
//                     economia = dist[s.vec[i].sol][i] - dist[s.med[j]][i];

//                     //se a economia for positiva e n�o extrapolar a capacidade da mediana j
//                     if (economia > maiorEconomia) 
//                     {
//                         maiorEconomia = economia;
//                         mI = i;
//                         mJ = j;
//                     }
//                 }
//             }
//         }
//     }

//     if (maiorEconomia > 0)
//     {
//         //realizar a troca
//         s.vec[mI].sol = s.med[mJ];

//         //    double foteste = s.fo - maiorEconomia;
//     }

//     return s;
// }

// /*****************************************************************************
// M�todo: Swap2 (M�todo de Descida)
// Funcao: realizar todas as trocas poss�veis entre pontos de medianas diferentes
// ******************************************************************************/
// TSol Swap2(TSol s)
// {
//   bool melhorou = true;
//   while (melhorou)
//   {
//     melhorou = false;
//     double economia = 0,
//            maiorEconomia = 0;

//     int mI = 0,
//         mJ = 0;

//     int posMed[numPontos];
//     //construir um vetor com as posicoes das medianas que atendem os pontos
//     for (int i=0; i<pMed; i++)
//     {
//       for (int j=0; j<numPontos; j++)
//       {
//         if (s.pontos[j] == s.med[i])
//           posMed[j] = i;
//       }
//     }

//     //para cada ponto que n�o seja mediana e seja atendido por alguma mediana
//     for (int i=0; i<numPontos; i++)
//     {
//       if ((s.pontos[i] != i) && (s.pontos[i] >= 0))
//       {
//         //para cada ponto seguinte que n�o seja mediana e seja atendido por alguma, examinar a troca
//         for (int j=i+1; j<numPontos; j++)
//         {
//           if ((s.pontos[j] != j) && (s.pontos[j] >= 0))
//           {
//             //se os pontos forem atendidos por medianas diferentes
//             if (s.pontos[i] != s.pontos[j])
//             {
//               //verificar a vantagem de trocar os atendimentos dos pontos
//               economia = d[s.pontos[i]][i] - d[s.pontos[j]][i]
//                        + d[s.pontos[j]][j] - d[s.pontos[i]][j];

//               //se for a melhor troca (economia > 0) realizar a troca
//               //verificar se n�o extrapola a capacidade
//               if ((economia > maiorEconomia) &&
//                   ((s.demAtend[posMed[i]] - dados[i].dem + dados[j].dem) <= dados[0].cap) &&
//                   ((s.demAtend[posMed[j]] - dados[j].dem + dados[i].dem) <= dados[0].cap) )
//               {
//                 maiorEconomia = economia;
//                 mI = i;
//                 mJ = j;
//               }
//             }
//           }
//         }//for j
//       }
//     }//for i


//     if (maiorEconomia > 0)
//     {
// //      numSwap++;
//       melhorou = true;

//       //atualizar a demanda das medianas envolvidas na troca
//       s.demAtend[posMed[mI]] = s.demAtend[posMed[mI]] - dados[mI].dem + dados[mJ].dem;
//       s.demAtend[posMed[mJ]] = s.demAtend[posMed[mJ]] - dados[mJ].dem + dados[mI].dem;

//       //realizar a troca
//       int temp = s.pontos[mI];
//       s.pontos[mI] = s.pontos[mJ];
//       s.pontos[mJ] = temp;
//     }
//   }

//   return s;
// }

// /*****************************************************************************
// M�todo: Swap3 (M�todo de Descida - First Improment)
// Funcao: trocar dois pontos de medianas diferentes
// ******************************************************************************/
// TSol Swap3(TSol s)
// {
//   double economia = 0;

//   int posMed[numPontos];
//   //construir um vetor com as posicoes das medianas que atendem os pontos
//   for (int i=0; i<pMed; i++)
//   {
//     for (int j=0; j<numPontos; j++)
//     {
//       if (s.pontos[j] == s.med[i])
//         posMed[j] = i;
//     }
//   }

//   //para cada ponto que n�o seja mediana e seja atendido por alguma mediana
//   for (int i=0; i<numPontos; i++)
//   {
//     if ((s.pontos[i] != i) && (s.pontos[i] >= 0))
//     {
//       //para cada ponto seguinte que n�o seja mediana e seja atendido por alguma, examinar a troca
//       for (int j=i+1; j<numPontos; j++)
//       {
//         if ((s.pontos[j] != j) && (s.pontos[j] >= 0))
//         {
//           //se os pontos forem atendidos por medianas diferentes
//           if (s.pontos[i] != s.pontos[j])
//           {
//             //verificar a vantagem de trocar os atendimentos dos pontos
//             economia = d[s.pontos[i]][i] - d[s.pontos[j]][i]
//                      + d[s.pontos[j]][j] - d[s.pontos[i]][j];

//             //se for a melhor troca (economia > 0) realizar a troca
//             //verificar se n�o extrapola a capacidade
//             if ((economia > 0) &&
//                 ((s.demAtend[posMed[i]] - dados[i].dem + dados[j].dem) <= dados[0].cap) &&
//                 ((s.demAtend[posMed[j]] - dados[j].dem + dados[i].dem) <= dados[0].cap) )
//             {
//               //atualizar a demanda das medianas envolvidas na troca
//               s.demAtend[posMed[i]] = s.demAtend[posMed[i]] - dados[i].dem + dados[j].dem;
//               s.demAtend[posMed[j]] = s.demAtend[posMed[j]] - dados[j].dem + dados[i].dem;

//               //realizar a troca
//               int temp = s.pontos[i];
//               s.pontos[i] = s.pontos[j];
//               s.pontos[j] = temp;
//             }
//           }
//         }
//       }//for j
//     }
//   }//for i

//   return s;
// }

// /*****************************************************************************
// M�todo: SwapMedianas (M�todo de Descida)
// Funcao: trocar a mediana por todos os pontos atribuidos a ela
// ******************************************************************************/
// TSol SwapMedianas(TSol s)
// {
//   //Location-allocation
//   TSol solAux = s;
//   TSol melhorSolAux;
//   melhorSolAux.fo = 99999999;

//   bool continua = true;
//   while (continua)
//   {
//     //trocar todas as medianas pelos pontos que estao atribuidos a ela
//     for (int i=0; i<pMed; i++)
//     {
//       for (int j=0; j<numPontos; j++)
//       {
//         solAux = s; //retornar para a solucao original

//         //se o ponto j for atendido pela mediana i
//         if (solAux.pontos[j] == solAux.med[i])
//         {
//           //chamar o metodo para realocar os pontos
//           solAux = Realocar3(solAux, i, j);

//           solAux = CalcularFO(solAux,3);
//           //verificar se � a melhor solucao encontrada at� entao...
//           if (solAux.fo < melhorSolAux.fo)
//             melhorSolAux = solAux;
//         }
//       }
//     }

//     //verificar se melhorou a solucao
//     if (melhorSolAux.fo < s.fo)
//     {
//       s = melhorSolAux; //continuar a busca a partir da melhor solucao encontrada
//       continua = true;
//     }
//     else
//       continua = false;
//   }
//   return s;
// }

// /*****************************************************************************
// M�todo: Realocar3
// Funcao: realocar os pontos a mediana mais proxima
// ******************************************************************************/
// TSol Realocar3(TSol s, int pos, int m2)//(TSol, posicao da mediana trocada, nova mediana)
// {
//   //1* Passo - desalocar todos os pontos que est�o atribuidos a mediana[pos] da TSol
//   for (int i=0; i<numPontos; i++)
//     if (s.pontos[i] == s.med[pos])
//       s.pontos[i] = -1;

//   //trocar as medianas
//   s.med[pos] = m2;
//   s.demAtend[pos] = 0;

//   //fazer a nova mediana atender ela mesma
//   s.pontos[m2] = m2;
//   s.demAtend[pos] = dados[m2].dem;

//   for (int i=0; i<numPontos; i++)
//   {
//     //2* Passo - verificar para todos os pontos desalocados qual a mediana mais proxima
//     //           que n�o exceda a capacidade
//     if (s.pontos[i] == -1)
//     {
//       double menorDist = 9999999999;
//       int mMed = -1;
//       bool existe = false;
//       for (int j=0; j<pMed; j++)
//       {
//         if ((d[s.med[j]][i] < menorDist) &&
//             ((s.demAtend[j] + dados[i].dem) <= dados[s.med[j]].cap) )
//         {
//           mMed = j;
//           menorDist = d[s.med[j]][i];
//           existe = true;
//         }
//       }
//       if (existe)
//       {
//         s.pontos[i] = s.med[mMed];
//         s.demAtend[mMed] += dados[i].dem;
//       }
//     }

//     //3* Passo - Verificar para todos pontos j� alocados a vantagem destes
//     //           serem atribuidos a nova mediana
//     else
//     {
//       //calcular a distancia do ponto i at� a nova mediana
//       double dist = d[s.pontos[i]][i] - d[m2][i];

//       if (dist > 0)
//       {
//         //verificar a capacidade da nova mediana
//         if (s.demAtend[pos] + dados[i].dem <= dados[m2].cap)
//         {
//           //atualizar as demandas das medianas
//           s.demAtend[pos] += dados[i].dem;
//           int t=0;
//           while (s.med[t] != s.pontos[i])
//             t++;
//           s.demAtend[t] -= dados[i].dem;

//           //inserir o ponto na nova mediana
//           s.pontos[i] = m2;
//         }
//       }
//     }
//   }

//   return s;
// }