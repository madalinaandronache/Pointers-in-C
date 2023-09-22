#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

void get_operations(void **operations);

void (*SensorFunction)(void *);

// transforma un sir de caractere intr-un text si un numar
char *transform(char *str, int *nr) {
    char s[] = " ";
    char *numar;

    // memoreaza sirul de caractere aflat pana in caracterul " "
    char *sir = strtok(str, s);

    // memoreaza sirul de caractere aflat dupa caracterul " "
    numar = strtok(NULL, s);

    if (numar != NULL) {
        // transformare in numar intreg
        *nr = atoi(numar);
    }

    return sir;
}

// citirea datelor din fisierul binar
void read(int n, sensor *v, FILE *fdata) {
    int i, j, number, integer, code;
    float fl_number;

    // citire datele pentru fiecare element de tip senzor
    for (i = 0; i < n; i++) {
        fread(&code, sizeof(int), 1, fdata);

        // verific daca elementul este de tip TIRE
        if (code == 0) {
            v[i].sensor_type = TIRE;

            v[i].sensor_data = (tire_sensor *)malloc(sizeof(tire_sensor));

            fread(&fl_number, sizeof(float), 1, fdata);
            ((tire_sensor *)v[i].sensor_data)->pressure = fl_number;

            fread(&fl_number, sizeof(float), 1, fdata);
            ((tire_sensor *)v[i].sensor_data)->temperature = fl_number;

            fread(&integer, sizeof(int), 1, fdata);
            ((tire_sensor *)v[i].sensor_data)->wear_level = integer;

            fread(&integer, sizeof(int), 1, fdata);
            ((tire_sensor *)v[i].sensor_data)->performace_score = integer;
        }

        // verific daca elementul este de tip PMU
        if (code == 1) {
            v[i].sensor_type = PMU;

            v[i].sensor_data =
                (power_management_unit *)malloc(sizeof(power_management_unit));

            fread(&fl_number, sizeof(float), 1, fdata);
            ((power_management_unit *)v[i].sensor_data)->voltage = fl_number;

            fread(&fl_number, sizeof(float), 1, fdata);
            ((power_management_unit *)v[i].sensor_data)->current = fl_number;

            fread(&fl_number, sizeof(float), 1, fdata);
            ((power_management_unit *)v[i].sensor_data)->power_consumption =
                fl_number;

            fread(&integer, sizeof(int), 1, fdata);
            ((power_management_unit *)v[i].sensor_data)->energy_regen = integer;

            fread(&integer, sizeof(int), 1, fdata);
            ((power_management_unit *)v[i].sensor_data)->energy_storage =
                integer;
        }

        fread(&integer, sizeof(int), 1, fdata);
        v[i].nr_operations = integer;
        v[i].operations_idxs = (int *)malloc(integer * sizeof(int));

        for (j = 0; j < integer; j++) {
            fread(&number, sizeof(int), 1, fdata);
            v[i].operations_idxs[j] = number;
        }
    }
}

// printarea unui element din vectorul sensor, in functie de tipul acestuia
void display(sensor *v, int index, int n) {
    if (index >= 0 && index < n) {
        if (v[index].sensor_type == TIRE) {
            printf("Tire Sensor\n");
            printf("Pressure: %.2f\n",
                   ((tire_sensor *)v[index].sensor_data)->pressure);
            printf("Temperature: %.2f\n",
                   ((tire_sensor *)v[index].sensor_data)->temperature);
            printf("Wear Level: %d%%\n",
                   ((tire_sensor *)v[index].sensor_data)->wear_level);

            if (((tire_sensor *)v[index].sensor_data)->performace_score == 0) {
                printf("Performance Score: Not Calculated\n");
            } else {
                printf("Performance Score: %d\n",
                       ((tire_sensor *)v[index].sensor_data)->performace_score);
            }
        } else {
            printf("Power Management Unit\n");
            printf("Voltage: %.2f\n",
                   ((power_management_unit *)v[index].sensor_data)->voltage);
            printf("Current: %.2f\n",
                   ((power_management_unit *)v[index].sensor_data)->current);
            printf("Power Consumption: %.2f\n",
                   ((power_management_unit *)v[index].sensor_data)
                       ->power_consumption);
            printf(
                "Energy Regen: %d%%\n",
                ((power_management_unit *)v[index].sensor_data)->energy_regen);
            printf("Energy Storage: %d%%\n",
                   ((power_management_unit *)v[index].sensor_data)
                       ->energy_storage);
        }
    } else {
        printf("Index not in range!\n");
    }
}

// eliminarea elementelor din vectorul sensor, care nu respecta conditiile
// propuse
void clear(sensor **v, int *n) {
    int i = 0, j = 0, ok;

    while (i < *n) {
        ok = 1;

        if ((*v)[i].sensor_type == PMU) {
            power_management_unit *data =
                (power_management_unit *)(*v)[i].sensor_data;
            if (data->voltage < 10 || data->voltage > 20 ||
                data->current < -100 || data->current > 100 ||
                data->power_consumption < 0 || data->power_consumption > 1000 ||
                data->energy_regen < 0 || data->energy_regen > 100 ||
                data->energy_storage < 0 || data->energy_storage > 100) {
                ok = 0;
            }
        } else if ((*v)[i].sensor_type == TIRE) {
            tire_sensor *data = (tire_sensor *)(*v)[i].sensor_data;
            if (data->pressure < 19 || data->pressure > 28 ||
                data->temperature < 0 || data->temperature > 120 ||
                data->wear_level < 0 || data->wear_level > 100) {
                ok = 0;
            }
        }
        if (ok == 0) {
            // eliberarea memoriei alocate elementului i, daca acesta nu
            // corespunde cerintei
            if ((*v)[i].sensor_data != NULL) {
                free((*v)[i].sensor_data);
            }

            free((*v)[i].operations_idxs);

            // actualizarea vectorului
            for (j = i; j < *n - 1; j++) {
                (*v)[j] = (*v)[j + 1];
            }

            // decrementarea numarului de elemente ale vectorului
            (*n)--;

            *v = (sensor *)realloc(*v, (*n) * sizeof(sensor));
        } else {
            i++;
        }
    }
}


// sortarea vectorului de tip sensor, astfel incat elementele de
// tip PMU sa fie situate in fata elementelor de tip TIRE
void sensor_sort(sensor *v, int n) {
    int i, j;

    for (i = 1; i < n; i++) {
        if (v[i].sensor_type == PMU) {
            for (j = i; j > 0; j--) {
                if(v[j - 1].sensor_type == TIRE) {
                    sensor temp = v[j];
                    v[j] = v[j - 1];
                    v[j - 1] = temp;
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    FILE *fdata;
    int n, index, j, nr, nr_operations, index_oper;
    char *s, *command;
    char text[5][10] = {"print", "analyze", "clear\n", "exit\n"};

    sensor *v;

    if (argc != 2) {
        printf("Fisierul nu a fost specificat!\n");
        return 1;
    }

    fdata = fopen(argv[1], "rb");
    if (fdata == NULL) {
        printf("Fisierul nu a putut fi deschis!\n");
        return 1;
    }

    // citirea numarului de elemente ale vectorului
    fread(&n, sizeof(int), 1, fdata);
    v = (sensor *)malloc(n * sizeof(sensor));
    read(n, v, fdata);

    sensor_sort(v, n);

    void *operations[8];
    get_operations(operations);

    s = (char *)malloc(50 * sizeof(char));
    fgets(s, 50, stdin);

    while (strcmp(s, text[3]) != 0) {
        command = transform(s, &nr);
        index = nr;
        if (strcmp(command, text[0]) == 0) {
            display(v, index, n);
        } else if (strcmp(command, text[1]) == 0) {
            nr_operations = v[index].nr_operations;

            for (j = 0; j < nr_operations; j++) {
                index_oper = v[index].operations_idxs[j];

                ((int (*)(void *))operations[index_oper])(
                    v[index].sensor_data);
            }
        } else if (strcmp(command, text[2]) == 0) {
            clear(&v, &n);
        }
        fgets(s, 50, stdin);
    }

    for (int i = 0; i < n; i++) {
        free(v[i].sensor_data);
        free(v[i].operations_idxs);
    }

    free(v);
    free(s);

    fclose(fdata);

    return 0;
}
