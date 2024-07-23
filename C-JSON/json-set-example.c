#include <stdio.h>
#include <json-c/json.h>

int main(int argc, char *argv[]){
    //Cria o objeto do paciente
    /*
    {
    }
    */
    struct json_object *patient = json_object_new_object();

    //Adiciona os dados ao paciente
    /*
        "name":"Thiago",
        "age":21,
        "condition":"Stable",
        "birthday":"27-03-2003"
    */
    json_object_object_add(patient, "name", json_object_new_string(("Thiago")));
    json_object_object_add(patient, "age", json_object_new_int(21));
    json_object_object_add(patient, "condition", json_object_new_string("Stable"));
    json_object_object_add(patient, "birthday", json_object_new_string("27-03-2003"));
    
    //Primeiro cria o objeto e seus componentes
    /*
        "medications":[
            "Dipirona",
            "Loratadina",
            "Chocolate"
        ]
    */
    struct json_object *medications = json_object_new_array();
    json_object_array_add(medications, json_object_new_string("Dipirona"));
    json_object_array_add(medications, json_object_new_string("Loratadina"));
    json_object_array_add(medications, json_object_new_string("Chocolate"));
    //Depois adiciona esse objeto como um componente do paciente
    /*
    {
        "name":"Thiago",
        "age":21,
        "condition":"Stable",
        "birthday":"27-03-2003",
        "medications":[
            "Dipirona",
            "Loratadina",
            "Chocolate"
        ]
    }
    */
    json_object_object_add(patient, "medications", medications);

    //Salva o arquivo
    FILE *fp = fopen("patient_data.json", "w");
    if(fp != NULL){
        fputs(json_object_to_json_string_ext(patient, JSON_C_TO_STRING_PRETTY), fp);
        fclose(fp);
        printf("JSON criado com sucesso.\n");
    } else {
        printf("Falha ao criar o arquivo JSON\n");
    }

    //Limpa os objetos json
    json_object_put(patient);

    return 0;
}