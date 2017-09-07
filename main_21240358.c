/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Emanuel Fragoso - a21240358@alunos.isec.pt
 *
 * Created on August 7, 2017, 10:46 AM
 */

#include "estruturas.h"

/*
 * 
 */
int main(int argc, char** argv) {
    //obtemHoraSistema();
    int num_med = 0, i, p, num_doe = 0, num_con = 0;


    MED *medico = NULL; //Vector dinâmico de médicos
    
    DOE *doente = NULL; //Vector dinâmico de doentes
    pconsulta first = NULL; // lista ligada de consultas
    // pconsulta last = NULL; // ultimo elemento da lista de consultas




    doente = leFichDoentes(&num_doe);
    medico = leFichMedicos(&num_med);

    menuInicial(first, &num_con, doente, &num_doe, medico, &num_med);

    //debugg leituradoentes
    /* for (i = 0; i < num_doe; i++) {
         printf(" %s \n %d-%d-%d \n %d consultas \n", doente[i].nome, doente[i].nasc.dia,doente[i].nasc.mes,doente[i].nasc.ano,doente[i].numConsultas);
         for (p = 0; p < doente[i].numConsultas; p++)
             printf("%s - %d/%d/%d - %s\n",doente[i].con[p].tipoConsulta,doente[i].con[p].data.dia,doente[i].con[p].data.mes,doente[i].con[p].data.ano,doente[i].con[p].medico);
     }*/
    //debug leituramedicos
    /* for (i = 0; i < num_med; i++) {
         printf(" %s \n %s %d.%d - %d.%d \n", medico[i].nome, medico[i].esp, medico[i].horario.horasEntrada, medico[i].horario.minutosEntrada, medico[i].horario.horasSaida, medico[i].horario.minutosSaida);
     }*/
    
    return (EXIT_SUCCESS);
}
