#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <mosquitto.h>
#include <time.h>
#include <unistd.h>

#define MQTT_HOST "localhost"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/t1"

clock_t start, end;
double pi = 3.14;


void create_json_file(const char *filename, int i) {
    struct json_object *patient = json_object_new_object();

    json_object_object_add(patient, "name", json_object_new_string("Thiago"));
    json_object_object_add(patient, "age", json_object_new_int(i));
    json_object_object_add(patient, "condition", json_object_new_string("Stable"));
    json_object_object_add(patient, "float", json_object_new_double(pi));
    json_object_object_add(patient, "birthday", json_object_new_string("27-03-2003"));

    struct json_object *medications = json_object_new_array();
    json_object_array_add(medications, json_object_new_string("Chocolate"));
    json_object_array_add(medications, json_object_new_string("Dipirona"));
    json_object_array_add(medications, json_object_new_string("Loratadina"));
    json_object_object_add(patient, "medications", medications);

    struct json_object *appointments = json_object_new_array();
    json_object_array_add(appointments, json_object_new_string("2024-07-01: General Checkup"));
    json_object_array_add(appointments, json_object_new_string("2024-07-15: Follow-up"));
    json_object_object_add(patient, "appointments", appointments);

    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        fputs(json_object_to_json_string_ext(patient, JSON_C_TO_STRING_PRETTY), fp);
        fclose(fp);
        printf("JSON file created successfully.\n");
    } else {
        printf("Failed to create JSON file.\n");
    }

    json_object_put(patient);
}

void publish_json_to_mqtt(const char *filename) {
    struct mosquitto *mosq;
    FILE *fp;
    long file_size;
    char *json_data;

    // Inicializar a biblioteca Mosquitto
    mosquitto_lib_init();

    // Criar um novo cliente Mosquitto
    mosq = mosquitto_new(NULL, true, NULL);
    if (!mosq) {
        fprintf(stderr, "Error: Unable to create mosquitto client.\n");
        return;
    }

    // Conectar ao broker MQTT
    if (mosquitto_connect(mosq, MQTT_HOST, MQTT_PORT, 60)) {
        fprintf(stderr, "Unable to connect to MQTT broker.\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    // Ler o arquivo JSON
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Failed to open JSON file.\n");
        mosquitto_destroy(mosq);
        mosquitto_lib_cleanup();
        return;
    }

    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    json_data = malloc(file_size + 1);
    fread(json_data, 1, file_size, fp);
    json_data[file_size] = '\0';
    fclose(fp);

    // Publicar o JSON no tópico MQTT
    mosquitto_publish(mosq, NULL, MQTT_TOPIC, strlen(json_data), json_data, 0, false);
    free(json_data);

    // Limpar e destruir o cliente Mosquitto
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
}

int main() {
    const char *json_filename = "patient_data.json";
    int i = 0;
    for(i = 0; i < 20; i++){
        create_json_file(json_filename, i);
        publish_json_to_mqtt(json_filename);
        sleep(5);
    }
    return 0;
}
