/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   estruturas.h
 * Author: Emanuel Fragoso - a21240358@alunos.isec.pt
 *
 * Created on August 7, 2017, 11:05 AM
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#define TAM_NOME 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define fich_medicos "medicos.txt" // FICHEIRO TXT QUE CONTÉM INFO ACERCA DOS MÉDICOS
#define fich_doentes "pacientes.txt" // FICHEIRO TXT QUE CONTÉM INFO ACERCA DOS DOENTES
#define fich_consultas "consultas.bin" // FICHEIRO BINARIO COM INFO DAS CONSULTAS


typedef struct medico MED;
typedef struct doente DOE;
typedef struct data DATE;
typedef struct consulta CON, *pconsulta;
typedef struct horario HORA;

struct data {
    int dia;
    int mes;
    int ano;
};

struct horario {
        int horasEntrada;
        int minutosEntrada;
        int horasSaida;
        int minutosSaida;
    } ;

struct consulta {
    char paciente [TAM_NOME];
    char tipoConsulta[10];
    DATE data;
    char medico[TAM_NOME];
    char especialidade[TAM_NOME];
    HORA horasConsulta;
    pconsulta prox;
};

struct medico {
    char nome[TAM_NOME];
    char esp [TAM_NOME];
    HORA horario;
    HORA ultimaManha;
    HORA ultimaTarde;
    pconsulta consultaMedico;

};

struct doente {
    char nome[TAM_NOME];
    DATE nasc;
    int numConsultas;
    CON con[2];

};



// ----------------------------UTILS-------------------------------
void obtemDataSistema();
void obtemHoraSistema();
void erroFichMedicos();

// ------------------------- FICHEIROS -----------------------------

MED * leFichMedicos(int *num_med);
DOE * leFichDoentes(int *num_doe);
void gravaFichTxtDoentes(DOE *doente, int *num_doe);
void gravaFichBinConsultas(pconsulta first);
int comparaString(char a[], char b[]);
pconsulta leFichConsultas(pconsulta first, int *num_con);

//---------------------- FUNÇÕES MEMO -----------------------------

pconsulta atualizaListaConsultas(pconsulta first, pconsulta aux, MED *medico, int *num_med);
pconsulta criaConsulta(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med);
int procuraHora(pconsulta aux, MED *medico, int * num_med, int *turno, int *duracao);
HORA marcaEspecialidade(pconsulta aux, MED *medico, int *num_med, DOE *doente, int *num_doe);
HORA procuraHoraEspecialidade(pconsulta aux, MED *medico, int * num_med, int *turno, int *duracao);
HORA procuraHoraMedico(pconsulta aux, MED *medico, int * num_med, DOE * doente, int *num_doe);
HORA marcaUrgente(pconsulta aux, MED *medico, int *num_med, DOE *doente, int *num_doe);
void alteraUltimaConsulta(pconsulta aux, DOE *doente, int *i);


//------------------------ LISTAGENS ---------------------------
void listagemMedicos(MED *medico, int *num_med,pconsulta first, DOE *doente, int *num_doe);
void listaConsultasMedico(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe);
void listagemEspecialidade(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe );
void listPacientesEsp(DOE *doente, int *num_doe, pconsulta first, MED *medico, int *num_med);
void listPacientesData(DOE *doente, int *num_doe, MED *medico, int *num_med, pconsulta first);
void listagemPacientes(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe);
void listagemConsultas(pconsulta first,DOE *doente, int *num_doe, MED *medico, int *num_med);


//---------------------- MENUS -------------------------------

void menuInicial(pconsulta first, int *num_con, DOE *doente, int *num_doe, MED *medico, int *num_med);
void menuPrincipal(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med);
void menuMedicos(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med);
void menuDoentes(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med);
void menuConsultas(pconsulta first,DOE *doente, int *num_doe, MED *medico, int *num_med);
void menuGravar(pconsulta first, DOE *doente,int *num_doe, MED *medico, int *num_med);


//

#endif /* ESTRUTURAS_H */

