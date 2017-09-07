/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   menus.c
 * Author: Emanuel Fragoso - a21240358@alunos.isec.pt
 *
 * Created on August 7, 2017, 10:47 AM
 */

#include "estruturas.h"

void menuInicial(pconsulta first, int *num_con, DOE *doente, int *num_doe, MED *medico, int *num_med) {
    int opcao;
    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********    MENU INICIAL   **********\n\n");
    printf("1 - Novo dia.\n");
    printf("2 - Continuacao do dia. \n");
    printf("OPCAO: ");

    scanf("%d", &opcao);

    if (isdigit(opcao)) {
        menuInicial(first, num_con, doente, num_doe, medico, num_med);
    }

    system("cls");

    if (opcao == 1) {
        //nao lê ficheiro binario para agenda de consultas
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else if (opcao == 2) {
        first=leFichConsultas(first, num_con); //lê o ficheiro binario para a lista ligada de consultas
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuInicial(first, num_con, doente, num_doe, medico, num_med);
    }

}

void menuPrincipal(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {

    int opcao;
    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********    MENU PRINCIPAL   **********\n\n");
    printf("1 - Medicos\n");
    printf("2 - Doentes \n");
    printf("3 - Consultas \n");
    printf("4 - SAIR\n\n");
    printf("OPCAO: ");

    scanf("%d", &opcao);

    system("cls");

    if (opcao == 1) {
        menuMedicos(first, doente, num_doe, medico, num_med);
    } else if (opcao == 2) {
        menuDoentes(first, doente, num_doe, medico, num_med);
    } else if (opcao == 3) {
        menuConsultas(first, doente, num_doe, medico, num_med);
    } else if (opcao == 4) {
        menuGravar(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuPrincipal(first, doente, num_doe, medico, num_med);
    }


}

void menuMedicos(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {

    int opcao;
    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********    MENU  MEDICOS    **********\n\n");
    printf("1 - Listagem de Medicos\n");
    printf("2 - Listagem de Medicos p/ especialidade \n");
    printf("3 - Listagem de Medicos com consultas \n");
    printf("4 - VOLTAR\n\n");
    printf("OPCAO: ");

    scanf("%d", &opcao);

    system("cls");

    if (opcao == 1) {
        listagemMedicos(medico, num_med, first, doente, num_doe);
    } else if (opcao == 2) {
        listagemEspecialidade(medico, num_med, first, doente, num_doe);
    } else if (opcao == 3) {
        listaConsultasMedico(medico, num_med, first, doente, num_doe);
    } else if (opcao == 4) {
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuMedicos(first, doente, num_doe, medico, num_med);
    }


}

void menuDoentes(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {
    int opcao;

    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********     MENU DOENTES    **********\n\n");
    printf("1 - Listagem de pacientes\n");
    printf("2 - Listagem de pacientes p/ especialidade \n");
    printf("3 - Listagem de pacientes p/ data de consulta \n");
    printf("4 - VOLTAR\n\n");
    printf("OPCAO: ");

    scanf("%d", &opcao);

    system("cls");

    if (opcao == 1) {
        listagemPacientes(medico, num_med, first, doente, num_doe);
    } else if (opcao == 2) {
        listPacientesEsp(doente, num_doe, first, medico, num_med);
    } else if (opcao == 3) {
        listPacientesData(doente, num_doe, medico, num_med, first);
    } else if (opcao == 4) {
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuDoentes(first, doente, num_doe, medico, num_med);
    }


}

void menuConsultas(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {

    int opcao;
    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********    MENU CONSULTAS   **********\n\n");
    printf("1 - Criar nova consulta\n");
    printf("2 - Listagem de Consultas\n");
    printf("3 - VOLTAR\n\n");

    printf("OPCAO: ");

    scanf("%d", &opcao);

    system("cls");

    if (opcao == 1) {
        first=criaConsulta(first, doente, num_doe, medico, num_med);
        menuConsultas(first, doente, num_doe, medico, num_med);
    } else if (opcao == 2) {
        listagemConsultas(first, doente, num_doe, medico, num_med);
    } else if (opcao == 3) {
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuConsultas(first, doente, num_doe, medico, num_med);
    }


}

void menuGravar(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {

    int opcao;
    system("cls");
    printf("**********    CLINICA XPTO     **********\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("**********    MENU  GRAVAR    **********\n\n");
    printf("1 - Retomar sessão mais tarde\n");
    printf("2 - SAIR\n");
    printf("3 - Voltar para menu principal \n\n");
    printf("OPCAO: ");

    scanf("%d", &opcao);

    system("cls");

    if (opcao == 1) {
        gravaFichBinConsultas(first);
        printf("---> A guardar Backup de consultas <---\n\n");
        gravaFichTxtDoentes(doente, num_doe);
        printf("---- Programa vai terminar ----\n\n\n");
        free(doente);
        free(medico);
        free (first);
        exit(0);
    } else if (opcao == 2) {
        printf("---> Atualizando consultas de Pacientes <---\n\n");
        
        gravaFichTxtDoentes(doente, num_doe);
        printf("---- Programa vai terminar ----\n\n\n");
        free(doente);
        free(medico);
        free (first);
        exit(0);
    } else if (opcao == 3) {
        menuPrincipal(first, doente, num_doe, medico, num_med);
    } else {
        printf("*****************************************\n");
        printf("*      [ATENCAO] OPCAO NAO VALIDA       *\n");
        printf("*****************************************\n\n");
        menuGravar(first, doente, num_doe, medico, num_med);
    }


}