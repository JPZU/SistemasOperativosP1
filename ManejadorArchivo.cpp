
#include "ManejadorArchivo.h"

// =====================================
//  FUNCIÓN: leerArchivo()
// =====================================
// Propósito: Leer un archivo en modo binario y almacenar su contenido en un vector.
// Parámetro: `nombreArchivo` → Nombre del archivo a leer.
// Retorna: `true` si el archivo fue leído exitosamente, `false` en caso de error.
bool ManejadorArchivo::leerArchivo(const std::string& nombreArchivo) {
    // `open()` abre el archivo en modo solo lectura
    // `O_RDONLY` → Solo lectura
    int fd = open(nombreArchivo.c_str(), O_RDONLY);
    
    if (fd == -1) {  // Si `open()` falla, devuelve `-1`
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return false;
    }

    datos.clear();  // Limpiamos el vector antes de leer nuevos datos
    uint8_t buffer[1024];  // Buffer temporal de 1024 bytes
    ssize_t bytesLeidos;

    // `read(fd, buffer, sizeof(buffer))` lee el archivo en bloques de 1024 bytes
    while ((bytesLeidos = read(fd, buffer, sizeof(buffer))) > 0) {
        datos.insert(datos.end(), buffer, buffer + bytesLeidos);  // Almacena los bytes en `datos`
    }

    // `close(fd)` cierra el archivo para liberar recursos
    close(fd);
    return true;
}

// =====================================
// FUNCIÓN: convertirABits()
// =====================================
// Propósito: Convierte cada byte leído en su representación de 8 bits.
void ManejadorArchivo::convertirABits(int shift) {
    bits.clear();  // Limpiar el vector antes de convertir nuevos datos

    for (uint8_t byte : datos) {
        // Aplicar Cifrado César en ASCII (sumando el shift)
        uint8_t byteEncriptado = byte + shift;

        // Convertir el byte encriptado a binario y almacenar
        bits.push_back(std::bitset<8>(byteEncriptado).to_string());
    }
}


// =====================================
// FUNCIÓN: mostrarBits()
// =====================================
// Propósito: Muestra en pantalla los bits de cada byte leído.
void ManejadorArchivo::mostrarBits() const {
    std::cout << "Contenido en bits:\n[";

    for (const auto& bitString : bits) {
        std::cout << bitString << "]\n[";
    }
    std::cout << "]";
    std::cout << std::endl;
}

// =====================================
//  FUNCIÓN: escribirArchivo()
// =====================================
//  Propósito: Escribir los datos en un archivo de salida.
//  Parámetro: `nombreSalida` → Nombre del archivo de salida.

void ManejadorArchivo::escribirArchivo(const std::string& nombreSalida) {
    int fd = open(nombreSalida.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1) {
        std::cerr << "Error: No se pudo abrir el archivo de salida " << nombreSalida << std::endl;
        return;
    }

    // Convertir la lista de bits en caracteres ASCII encriptados
    std::vector<uint8_t> datosEncriptados;
    for (const auto& bitString : bits) {
        datosEncriptados.push_back(static_cast<uint8_t>(std::bitset<8>(bitString).to_ulong()));
    }

    // Escribir el texto encriptado en el archivo
    ssize_t bytesEscritos = write(fd, datosEncriptados.data(), datosEncriptados.size());
    
    if (bytesEscritos == -1) {
        std::cerr << "Error: No se pudo escribir en el archivo " << nombreSalida << std::endl;
    } else {
        std::cout << "Archivo encriptado guardado exitosamente: " << nombreSalida << std::endl;
    }

    close(fd);
}


// =====================================
//  FUNCIÓN: matrizBits()
// =====================================
//  Propósito: Convierte los bytes en una matriz de bits (8 bits por fila).
//  Retorna: `std::vector<std::vector<int>>`  Matriz donde cada fila representa 8 bits.
std::vector<std::vector<int>> ManejadorArchivo::matrizBits() {
    std::vector<std::vector<int>> matriz;


    // aqui se hace el algoritmo de criptografia
    for (uint8_t byte : datos) {
        std::vector<int> filaBits(8);
        for (int i = 7; i >= 0; --i) {
            filaBits[7-i] = (byte >> i) & 1; // Extrae cada bit del byte
        }
        matriz.push_back(filaBits);
    }

    return matriz;
}
