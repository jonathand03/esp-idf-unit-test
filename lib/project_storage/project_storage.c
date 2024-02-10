#include "project_storage.h"

storage_ret init_storage(bool verification)
{
    const char *log_path_label  = LOG_PATH_NAME;
    const char *root_path_label = ROOT_PATH_NAME;
    size_t path_size = 0, path_size_used = 0;
    esp_err_t ret;

    esp_vfs_spiffs_conf_t storage_config =
    {
        .base_path = root_path_label,
        .partition_label = root_path_label,
        .format_if_mount_failed = false,
        .max_files  = 1,
    };

    esp_vfs_spiffs_register(&storage_config);

    /* Tratamento da partição*/
    if(verification)
    {
            /*! @brief Inicializando a partição mostrando algumas informações uteis para debug */
            bool is_mounted = esp_spiffs_mounted(storage_config.partition_label);
            if(is_mounted == false) return storage_init_error;
            esp_spiffs_info(storage_config.partition_label,&path_size,&path_size_used);
            /* Verificação de anomalia de tamanho [ o tamanho total não pode ser MENOR que o tamanho usado] */
            if(path_size < path_size_used) return storage_init_error;
            printf("Sistema de arquivo inicializado com sucesso\n Total de armazenamento %d \n Total usado %d \n", path_size,path_size_used);
            ret = esp_spiffs_check(storage_config.partition_label);
            return  ret == ESP_OK ?  storage_init_sucess : storage_init_error;
    }
    return storage_init_sucess;
}

storage_ret storage_write(const void *data, const char *partition_label)
{
    FILE *file = fopen(partition_label,"w");
    if(file == NULL ) return storage_write_error;
    fprintf(file,"%s", (const char *)data);
    fclose(file);

    return storage_write_sucess;
}

storage_ret storage_read(const char *partition_label,  void *buffer, size_t read_size)
{
    FILE *file = fopen(partition_label,"r");
    if(file == NULL ) return storage_read_error;

    fgets(buffer,read_size,file);
    fclose(file);
    printf("%s \n", (const char *)buffer);

    return storage_read_sucess;
}

storage_t Storage =
{
    .init = init_storage,
    .write = storage_write,
    .read = storage_read
};