/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   functions.c
 * Author: Emanuel Fragoso - a21240358@alunos.isec.pt
 *
 * Created on August 7, 2017, 10:46 AM
 */
#include "estruturas.h" 

/*          LEITURAS GRAVAÇOES FICHEIROS            */
void erroFichMedicos() {
    printf("************ CLINICA  MEDICA ************\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("-----------------------------------------\n");
    printf("|    Erro ao abrir ficheiro de MEDICOS  |\n");
    printf("|         Programa vai terminar         |\n");
    printf("-----------------------------------------\n\n");
    exit(0);
}

void erroFichDoentes() {
    printf("************ CLINICA  MEDICA ************\n");
    printf("*                                       *\n");
    printf("*             EMANUEL FRAGOSO           *\n");
    printf("*               21240358                *\n");
    printf("*          PROGRAMACAO   16/17          *\n");
    printf("*                                       *\n");
    printf("*****************************************\n\n");
    printf("-----------------------------------------\n");
    printf("|    Erro ao abrir ficheiro de DOENTES  |\n");
    printf("|         Programa vai terminar         |\n");
    printf("-----------------------------------------\n\n");
    exit(0);
}

MED * leFichMedicos(int *num_med) {
    int i = 0;
    MED *medico = NULL;
    FILE *f;

    f = fopen(fich_medicos, "r");

    if (f == NULL) {
        erroFichMedicos();
        exit(0);
    }
    medico = malloc(sizeof (MED));
    while (!feof(f)) {

        fscanf(f, "%[^\n]s", medico[i].nome);
        fscanf(f, "%s %d.%d - %d.%d\n", medico[i].esp, &medico[i].horario.horasEntrada, &medico[i].horario.minutosEntrada, &medico[i].horario.horasSaida, &medico[i].horario.minutosSaida);

        if (medico[i].horario.horasEntrada >= 14) {// caso medico entre para o turno tarde
            medico[i].ultimaTarde.horasSaida = medico[i].horario.horasEntrada;
            medico[i].ultimaTarde.minutosSaida = medico[i].horario.minutosEntrada;
            medico[i].ultimaManha.horasSaida = 14;
            medico[i].ultimaManha.minutosSaida = 0;
        }

        medico[i].ultimaManha.horasSaida = medico[i].horario.horasEntrada; // turno manha
        medico[i].ultimaManha.minutosSaida = medico[i].horario.minutosEntrada;
        medico[i].ultimaTarde.horasSaida = 14; // turno tarde 
        medico[i].ultimaTarde.minutosSaida = 0;

        medico[i].consultaMedico = NULL;

        i++;
        medico = realloc(medico, sizeof (MED)*(i + 1));
    }
    medico = realloc(medico, sizeof (MED) * i);
    *num_med = i;
    fclose(f);
    return medico;
}

DOE * leFichDoentes(int *num_doe) {
    FILE *f;
    DOE *doente = NULL;
    char lixo [50];
    int i = 0, p;

    f = fopen(fich_doentes, "r");

    if (f == NULL) {
        erroFichDoentes();
        exit(0);
    }
    doente = malloc(sizeof (DOE));

    while (!feof(f)) {

        fscanf(f, " %[^\n]s", doente[i].nome);
        fscanf(f, "%d-%d-%d ", &doente[i].nasc.dia, &doente[i].nasc.mes, &doente[i].nasc.ano);
        fscanf(f, "%d%[^\n]s", &doente[i].numConsultas, lixo);
        if (doente[i].numConsultas > 0) {
            for (p = 0; p < doente[i].numConsultas; p++)
                fscanf(f, "%s - %d/%d/%d - %[^\n]s", doente[i].con[p].tipoConsulta, &doente[i].con[p].data.dia, &doente[i].con[p].data.mes, &doente[i].con[p].data.ano, doente[i].con[p].medico);
        }
        i++;
        doente = realloc(doente, sizeof (DOE)*(i + 1));
    }

    *num_doe = i;
    doente = realloc(doente, sizeof (DOE) * i);
    return doente;
}

pconsulta leFichConsultas(pconsulta first, int *num_con) {
    FILE *f;
    pconsulta aux, last = NULL;


    f = fopen(fich_consultas, "rb");
    if (f == NULL) {
        printf("Nao foram lidas consultas\n");
        exit(0);
    }

    aux = malloc(sizeof (CON));
    while (fread(aux, sizeof (CON), 1, f) == 1) {

        if (first == NULL) {
            first = aux;
            aux->prox = NULL;
        } else {

            (last)->prox = aux;
            aux->prox = NULL;
        }

        aux = malloc(sizeof (CON));
    }

    fclose(f);

    return first;

}

void gravaFichBinConsultas(pconsulta first) {
    FILE *f;
    pconsulta aux;

    f = fopen(fich_consultas, "wb");
    if (f == NULL) {
        printf("Erro no acesso de escrita ao ficheiro binario de consultas\n");
    }

    while (first != NULL) {

        fwrite(first, sizeof (CON), 1, f);
        first = first->prox;

    }

    fclose(f);

}

void gravaFichTxtDoentes(DOE *doente, int *num_doe) {
    int i, j;
    FILE *f;

    f = fopen(fich_doentes, "w");

    if (f != NULL) {
        for (i = 0; i < *num_doe; i++) {
            fprintf(f, "%s\n", doente[i].nome);
            fprintf(f, "%d-%d-%d\n", doente[i].nasc.dia, doente[i].nasc.mes, doente[i].nasc.ano);
            fprintf(f, "%d consultas\n", doente[i].numConsultas);
            for (j = 0; j < doente[i].numConsultas; j++) {
                fprintf(f, "%s - %d/%d/%d - %s\n", doente[i].con[j].tipoConsulta, doente[i].con[j].data.dia, doente[i].con[j].data.mes, doente[i].con[j].data.ano, doente[i].con[j].medico);
            }

        }
    } else {
        printf("\n\n ------- nao foi possivel abrir fich de pacientes para escrita\n\n");
    }

    fclose(f);

}

/*          LISTAGENS           */

void listagemMedicos(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe) {
    int i = 0;
    system("cls");
    for (i = 0; i < (*num_med); i++) {
        printf("%s \n %s %d.%d - %d.%d \n", medico[i].nome, medico[i].esp, medico[i].horario.horasEntrada, medico[i].horario.minutosEntrada, medico[i].horario.horasSaida, medico[i].horario.minutosSaida);
    }
    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuMedicos(first, doente, num_doe, medico, num_med);
}

void listagemEspecialidade(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe) {
    int i = 0,j = 0;
    char esp [TAM_NOME];

    system("cls");

    do {
        printf("Especialidade:\n\n");
        scanf(" %[^\n]s", esp);

        for (i = 0; i < *num_med; i++) {

            if (comparaString(esp, medico[i].esp) == 0) {
                j = 0;
                break;
            }
            j = 1;
        }
        if (j == 1)
            printf("Especialidade nao existe \n");
    } while (j == 1);

    printf(" %s \n %s %d.%d - %d.%d \n", medico[i].nome, medico[i].esp,medico[i].horario.horasEntrada, medico[i].horario.minutosEntrada,medico[i].horario.horasSaida, medico[i].horario.minutosSaida);

    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuMedicos(first, doente, num_doe, medico, num_med);
}
//   listagemHorario();

void listaConsultasMedico(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe) {
    int i;

    system("cls");

    for (i = 0; i < *num_med; i++) {
        if (medico[i].consultaMedico != NULL) {
            printf(" %s - %s \n", medico[i].nome, medico[i].esp);
            while (medico[i].consultaMedico != NULL) {
                printf(" %s - %s \n ", medico[i].consultaMedico->tipoConsulta, medico[i].consultaMedico->paciente);
                printf(" %d/%d/%d - %d:%d ate %d:%d \n\n", medico[i].consultaMedico->data.dia, medico[i].consultaMedico->data.mes, medico[i].consultaMedico->data.ano,
                        medico[i].consultaMedico->horasConsulta.horasEntrada, medico[i].consultaMedico->horasConsulta.minutosEntrada, medico[i].consultaMedico->horasConsulta.horasSaida, medico[i].consultaMedico->horasConsulta.minutosSaida);

                medico[i].consultaMedico = medico[i].consultaMedico->prox;
            }
        }

    }

    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuMedicos(first, doente, num_doe, medico, num_med);



}

void listagemPacientes(MED *medico, int *num_med, pconsulta first, DOE *doente, int *num_doe) {
    int i, p;
    system("cls");
    for (i = 0; i < *num_doe; i++) {
        printf(" %s \n %d-%d-%d \n %d consultas \n", doente[i].nome, doente[i].nasc.dia, doente[i].nasc.mes, doente[i].nasc.ano, doente[i].numConsultas);
        for (p = 0; p < doente[i].numConsultas; p++)
            printf("%s - %d/%d/%d - %s\n", doente[i].con[p].tipoConsulta, doente[i].con[p].data.dia, doente[i].con[p].data.mes, doente[i].con[p].data.ano, doente[i].con[p].medico);

    }
    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuDoentes(first, doente, num_doe, medico, num_med);

}

void listPacientesEsp(DOE *doente, int *num_doe, pconsulta first, MED *medico, int *num_med) {
    int i, j, p;
    char especialidade [15];

    printf(" Qual a Especialidade?:\n\n");
    scanf(" %[^\n]s", especialidade);


    while (first != NULL) {
        for (i = 0; i < (*num_doe); i++) {
            if (comparaString(first->especialidade, especialidade) == 0);
            if (comparaString(first->paciente, doente[i].nome) == 0) {
                printf(" %s \n %d-%d-%d \n %d consultas \n", doente[i].nome, doente[i].nasc.dia, doente[i].nasc.mes, doente[i].nasc.ano, doente[i].numConsultas);
                for (p = 0; p < doente[i].numConsultas; p++)
                    printf("%s - %d/%d/%d - %s\n", doente[i].con[p].tipoConsulta, doente[i].con[p].data.dia, doente[i].con[p].data.mes, doente[i].con[p].data.ano, doente[i].con[p].medico);
            }

        }
        first = first->prox;
    }

    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuDoentes(first, doente, num_doe, medico, num_med);



}

void listPacientesData(DOE* doente, int*num_doe, MED *medico, int *num_med, pconsulta first) {
    int i, j, dia, mes, ano;

    printf("Data: (dd/mm/aa)\n");
    scanf(" %d/%d/%d", &dia, &mes, &ano);

    for (i = 0; i < (*num_doe); i++) {

        for (j = 0; j < doente[i].numConsultas; j++) {

            if ((dia == doente[i].con[j].data.dia) && (mes == doente[i].con[j].data.mes) && (ano == doente[i].con[j].data.ano))
                printf(" %s \n %d-%d-%d \n", doente[i].nome, doente[i].nasc.dia, doente[i].nasc.mes, doente[i].nasc.ano);
        }
    }

    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuDoentes(first, doente, num_doe, medico, num_med);
}

void listagemConsultas(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {

    pconsulta aux;
    aux = first;
    if (aux == NULL)
        printf("---> Lista de consultas vazia <---\n\n");

    while (aux != NULL) {
        printf(" %s \n %s - %d/%d/%d - %s - %s\n %d.%d - %d.%d\n\n", aux->paciente, aux->tipoConsulta,
                aux->data.dia, aux->data.mes, aux->data.ano, aux->medico, aux->especialidade,
                aux->horasConsulta.horasEntrada, aux->horasConsulta.minutosEntrada, aux->horasConsulta.horasSaida, aux->horasConsulta.minutosSaida);
        aux = aux->prox;
    }
    printf("\nOK para continuar ....\n");
    fflush(stdin);
    getchar();
    menuConsultas(first, doente, num_doe, medico, num_med);

}

/*          VALIDAÇOES & COMPARAÇOES  & MEMORIA        */

pconsulta criaConsulta(pconsulta first, DOE *doente, int *num_doe, MED *medico, int *num_med) {
    char nome[TAM_NOME], medi[TAM_NOME], esp[TAM_NOME];
    int i, opcao, idade;
    pconsulta aux ;
    aux = malloc(sizeof (CON));

    //-------------NOME------------------


    do {
        printf("\nNome do paciente:\n\n");
        scanf(" %[^\n]s", nome);

        for (i = 0; i < *num_doe; i++) {

            if (comparaString(nome, doente[i].nome) == 0) {
                strcpy(aux->paciente, nome);
                break;
            }
        }
        if (comparaString(nome,aux->paciente) == 1)
            printf("O nome nao consta na lista de pacientes \n");
        
    } while (comparaString(nome,aux->paciente) == 1);

    //------------------------URGENCIA-----------------------
    printf("A consulta e urgente?:\n\n");
    printf("1 - Sim\n");
    printf("2 - Nao\n\n");
    do{
        scanf("%d", &opcao);
    }while(opcao<1 || opcao>2);

    if (opcao == 1) {
        //---------------------ESPECIALIDADE/URGENTE-----------------------

        strcpy(aux->tipoConsulta, "Urgente");
        do {
            printf("Especialidade:\n\n");
            scanf(" %[^\n]s", esp);

            for (i = 0; i < *num_med; i++) {

                if (comparaString(esp, medico[i].esp) == 0) {
                    strcpy(aux->especialidade, esp);
                    break;
                }
            }
            if (comparaString(esp, aux->especialidade) == 1)
                printf("Especialidade nao existe \n");
        } while (comparaString(esp, aux->especialidade) == 1);

        aux->horasConsulta = marcaUrgente(aux, medico, num_med, doente, num_doe);
        first = atualizaListaConsultas(first, aux, medico, num_med);
        alteraUltimaConsulta(aux, doente, num_doe);
        printf("Consulta marcada com sucesso!\n");
        fflush(stdin);
        getchar();
        return first;


    } else if (opcao == 2) { // NORMAL
        //-----------------------MEDICO------------------------
        strcpy(aux->tipoConsulta, "Normal");
        printf("MEDICO?:\n\n");
        printf("1 - Sim\n");
        printf("2 - Nao\n\n");
        scanf("%d", &opcao);


        if (opcao == 1) {
            strcpy(aux->medico, "\0");
            do {
                do {
                    printf("Medico:\n\n");
                    scanf(" %[^\n]s", medi);
                } while (medi == NULL);

                for (i = 0; i < *num_med; i++) {

                    if (comparaString(medi, medico[i].nome) == 0) {
                        strcpy(aux->medico, medi);
                        break;
                    }


                }
                if (aux->medico == '\0')
                    printf("Medico nao existe! \n");
            } while (comparaString(medi, medico[i].nome) == 1);

            aux->horasConsulta = procuraHoraMedico(aux, medico, num_med, doente, num_doe);
            first = atualizaListaConsultas(first, aux, medico, num_med);
            alteraUltimaConsulta(aux, doente, num_doe);
            printf("Consulta marcada com sucesso!\n");
            fflush(stdin);
            getchar();
            return first;


        } else if (opcao == 2);



        //---------------------ESPECIALIDADE/NORMAL/SEM MEDICO -----------------------

        do {
            printf("Especialidade:\n\n");
            scanf(" %[^\n]s", esp);

            for (i = 0; i < *num_med; i++) {

                if (comparaString(esp, medico[i].esp) == 0) {
                    strcpy(aux->especialidade, esp);
                    break;
                }
            }
            if (comparaString(esp, aux->especialidade) == 1)
                printf("Especialidade nao existe \n");
        } while (comparaString(esp, aux->especialidade) == 1);

        aux->horasConsulta = marcaEspecialidade(aux, medico, num_med, doente, num_doe);
        first = atualizaListaConsultas(first, aux, medico, num_med);
        alteraUltimaConsulta(aux, doente, num_doe);
        printf("Consulta marcada com sucesso!\n");
        fflush(stdin);
        getchar();
        return first;
    }
}

HORA marcaEspecialidade(pconsulta aux, MED *medico, int *num_med, DOE *doente, int *num_doe) {
    int i, j, numMedico, dia, mes, ano, opcao, idade, duracao, hora, min, turno;
    HORA maiscedo;
    maiscedo.horasEntrada = 0;
    maiscedo.horasSaida = 0;
    maiscedo.minutosEntrada = 0;
    maiscedo.minutosSaida = 0;


    obtemDataSistema(&dia, &mes, &ano);
    for (j = 0; j < (*num_doe); j++) {
        if (comparaString(doente[j].nome, aux->paciente) == 0) {
            idade = (ano - doente[j].nasc.ano);
            if (idade < 6 || idade > 64) {
                duracao = 2;
            } else {
                duracao = 1;
            }
        }
    }
    aux->data.dia = dia;
    aux->data.mes = mes;
    aux->data.ano = ano;

    printf("Preferencia:\n");
    printf("1- Manha\n");
    printf("2- Tarde\n\n");
    printf("3- Sem preferencia");
    scanf("%d", &opcao);


    if (opcao = 1) {
        obtemHoraSistema(&hora, &min);
        if (hora <= 13) {
            turno = 1;
        } else {
            printf("So e possivel marcar para o horario da tarde\n");
            turno = 0;
        }


    } else if (opcao == 2) {

        turno = 0;


    } else if (opcao == 3) {
        obtemHoraSistema(&hora, &min);
        if (hora <= 13) {
            turno = 1;
        } else {
            turno = 0;
        }

    }

    aux->horasConsulta = procuraHoraEspecialidade(aux, medico, num_med, &turno, &duracao);


    return aux->horasConsulta;

}

HORA marcaUrgente(pconsulta aux, MED *medico, int *num_med, DOE *doente, int *num_doe) {
    int hora, min, dia, mes, ano;
    int i, j, duracao, idade, turno;



    obtemDataSistema(&dia, &mes, &ano);
    for (j = 0; j < (*num_doe); j++) {
        if (comparaString(doente[j].nome, aux->paciente) == 0);

        idade = (ano - doente[j].nasc.ano);
        if (idade < 6 || idade > 64) {
            duracao = 2;
        } else {
            duracao = 1;
        }
        break;
    }
    aux->data.dia = dia;
    aux->data.mes = mes;
    aux->data.ano = ano;

    obtemHoraSistema(&hora, &min);
    if (hora <= 13) {
        turno = 1;
    } else {
        turno = 0;
    }

    aux->horasConsulta = procuraHoraEspecialidade(aux, medico, num_med, &turno, &duracao);


    return aux->horasConsulta;


}

HORA procuraHoraEspecialidade(pconsulta aux, MED *medico, int * num_med, int *turno, int *duracao) {
    int i, numMedico;
    HORA maiscedo;
    maiscedo.horasEntrada = 0;
    maiscedo.horasSaida = 0;
    maiscedo.minutosEntrada = 0;
    maiscedo.minutosSaida = 0;



    if ((*turno) == 1) {
        for (i = 0; i < (*num_med); i++) {

            if (comparaString(aux->especialidade, medico[i].esp) == 0) {

                if (maiscedo.horasEntrada < medico[i].ultimaManha.horasSaida) {
                    maiscedo.horasEntrada = medico[i].ultimaManha.horasSaida;
                    strcpy(aux->medico, medico[i].nome);
                } else if (maiscedo.horasEntrada = medico[i].ultimaManha.horasSaida && maiscedo.minutosEntrada > medico[i].ultimaManha.minutosSaida) {
                    maiscedo.horasEntrada = medico[i].ultimaManha.horasSaida;
                    maiscedo.minutosEntrada = medico[i].ultimaManha.minutosSaida;
                    strcpy(aux->medico, medico[i].nome);

                }
            }
        }
        maiscedo.horasSaida = maiscedo.horasEntrada + (*duracao);
        maiscedo.minutosSaida = maiscedo.minutosEntrada;
        medico[i].ultimaManha.horasSaida = maiscedo.horasSaida;
        medico[i].ultimaManha.minutosSaida = maiscedo.minutosSaida;

        return maiscedo;
    }

    if ((*turno) == 0) {
        for (i = 0; i < (*num_med); i++) {

            if (comparaString(aux->especialidade, medico[i].esp) == 0) {

                if (maiscedo.horasEntrada < medico[i].ultimaTarde.horasSaida) {
                    maiscedo.horasEntrada = medico[i].ultimaTarde.horasSaida;
                    strcpy(aux->medico, medico[i].nome);
                } else if (maiscedo.horasEntrada = medico[i].ultimaTarde.horasSaida && maiscedo.minutosEntrada > medico[i].ultimaTarde.minutosSaida) {
                    maiscedo.horasEntrada = medico[i].ultimaTarde.horasSaida;
                    maiscedo.minutosEntrada = medico[i].ultimaTarde.minutosSaida;
                    strcpy(aux->medico, medico[i].nome);

                }
            }
        }
        maiscedo.horasSaida = maiscedo.horasEntrada + (*duracao);
        maiscedo.minutosSaida = maiscedo.minutosEntrada;
        medico[i].ultimaTarde.horasSaida = maiscedo.horasSaida;
        medico[i].ultimaTarde.minutosSaida = maiscedo.minutosSaida;

        return maiscedo;
    }



}

HORA procuraHoraMedico(pconsulta aux, MED *medico, int * num_med, DOE * doente, int *num_doe) {
    int i, j, numMedico, dia, mes, ano, opcao, idade, duracao, hora, min, turno;
    HORA maiscedo;
    maiscedo.horasEntrada = 0;
    maiscedo.horasSaida = 0;
    maiscedo.minutosEntrada = 0;
    maiscedo.minutosSaida = 0;


    obtemDataSistema(&dia, &mes, &ano);
    for (j = 0; j < (*num_doe); j++) {
        if (comparaString(doente[j].nome, aux->paciente) == 0) {
            idade = (ano - doente[j].nasc.ano);
            if (idade < 6 || idade > 64) {
                duracao = 2;
            } else {
                duracao = 1;
            }
            break;
        }

    }
    aux->data.dia = dia;
    aux->data.mes = mes;
    aux->data.ano = ano;
    for (i = 0; i < (*num_med); i++) {
        if (comparaString(aux->medico, medico[i].nome) == 0)break;
    }


    printf("Preferencia:\n");
    printf("1- Manha\n");
    printf("2- Tarde\n\n");
    printf("3- Sem preferencia");
    scanf("%d", &opcao);


    if (opcao = 1) {
        obtemHoraSistema(&hora, &min);
        if (hora <= 13) {
            turno = 1;
        } else {
            printf("So e possivel marcar para o horario da tarde\n");
            turno = 0;
        }


    } else if (opcao == 2) {

        turno = 0;


    } else if (opcao == 3) {
        obtemHoraSistema(&hora, &min);
        if (hora <= 13) {
            turno = 1;
        } else {
            turno = 0;
        }

    }

    if (turno == 1) {

        maiscedo.horasEntrada = medico[i].ultimaManha.horasSaida;
        maiscedo.minutosEntrada = medico[i].ultimaManha.minutosSaida;
        maiscedo.horasSaida += duracao;
        maiscedo.minutosSaida = maiscedo.minutosEntrada;
        medico[i].ultimaManha.horasSaida = maiscedo.horasSaida;
        medico[i].ultimaManha.minutosSaida = maiscedo.minutosSaida;

    }

    if (turno == 0) {
        maiscedo.horasEntrada = medico[i].ultimaTarde.horasSaida;
        maiscedo.minutosEntrada = medico[i].ultimaTarde.minutosSaida;
        maiscedo.horasSaida = maiscedo.horasEntrada + duracao;
        maiscedo.minutosSaida = maiscedo.minutosEntrada;
        medico[i].ultimaTarde.horasSaida = maiscedo.horasSaida;
        medico[i].ultimaTarde.minutosSaida = maiscedo.minutosSaida;
    }

    return maiscedo;



}

pconsulta atualizaListaConsultas(pconsulta first, pconsulta aux, MED *medico, int *num_med) {
    int i;
    pconsulta last;
    last = first;


    if (first == NULL) {
        first = aux;
        first->prox = NULL;
    } else {
        while (last->prox != NULL) {
            last = last->prox;
        }
        last->prox = aux;
        aux->prox = NULL;

    }
    aux = first; // para procurar consultas por medico
    while (aux != NULL) {
        for (i = 0; i < (*num_med); i++) {
            if (comparaString(aux->medico, medico[i].nome) == 0);
            if (medico[i].consultaMedico == NULL) {
                medico[i].consultaMedico = aux;
                medico[i].consultaMedico->prox = NULL;
            } else {
                last = medico[i].consultaMedico;
                while (last != NULL) {
                    last = last->prox;
                }
                last->prox = aux;
                last = last->prox;
                last->prox = NULL;


            }

        }

        aux = aux->prox;
    }


    //free(last);
    return first;
}

void alteraUltimaConsulta(pconsulta aux, DOE *doente, int *num_doe) {
    int i;

    for (i = 0; i < (*num_doe); i++) {


        if (comparaString(aux->paciente, doente[i].nome) == 0)
            break;
    }


    if (doente[i].numConsultas == 0) {
        doente[i].numConsultas = 1;
        strcpy(doente[i].con[0].tipoConsulta, aux->tipoConsulta);
        doente[i].con[0].data.dia = aux->data.dia;
        doente[i].con[0].data.mes = aux->data.mes;
        doente[i].con[0].data.ano = aux->data.ano;
        strcpy(doente[i].con[0].medico, aux->medico);
    } else if (doente[i].numConsultas == 1) {
        doente[i].numConsultas = 2;
         doente[i].con[0] = doente[i].con[1];
        strcpy(doente[i].con[1].tipoConsulta, aux->tipoConsulta);
        doente[i].con[1].data.dia = aux->data.dia;
        doente[i].con[1].data.mes = aux->data.mes;
        doente[i].con[1].data.ano = aux->data.ano;
        strcpy(doente[i].con[0].medico, aux->medico);
    } else if (doente[i].numConsultas == 2) {
        doente[i].con[0] = doente[i].con[1];
        strcpy(doente[i].con[0].tipoConsulta, aux->tipoConsulta);
        doente[i].con[0].data.dia = aux->data.dia;
        doente[i].con[0].data.mes = aux->data.mes;
        doente[i].con[0].data.ano = aux->data.ano;
        strcpy(doente[i].con[0].medico, aux->medico);
    }



}


//atualizaAgendaMedico();

void obtemHoraSistema(int *hora, int *min) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);


    *hora = tm.tm_hour;
    *min = tm.tm_min;
    // printf(" hora: %d min: %d", hora, min);

}

void obtemDataSistema(int *dia, int *mes, int *ano) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);


    *dia = tm.tm_mday;
    *mes = tm.tm_mon + 1;
    *ano = tm.tm_year + 1900;
    // printf(" Data:%d/%d/%d\n", dia, mes, ano);

}
//comparaHora(); // formato :%d-%d-%d

int comparaString(char a[], char b[]) {
    char frase1[TAM_NOME], frase2[TAM_NOME];
    int i;

    for (i = 0; a[i] != '\0'; i++)
        frase1[i] = tolower(a[i]);
    frase1[i] = '\0';

    for (i = 0; b[i] != '\0'; i++)
        frase2[i] = tolower(b[i]);
    frase2[i] = '\0';

    if (strcmp(frase1, frase2) == 0) return 0;
    return 1;
}
//veIdade(); // ano atual - ano nascença
// 








